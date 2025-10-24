# models.py - 模型定义
import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision.transforms as transforms
from PIL import Image
import os
import pandas as pd
from tqdm import tqdm

class Residual(nn.Module):
    """残差块"""
    def __init__(self, input_channels, num_channels, use_1x1conv=False, strides=1):
        super().__init__()
        self.conv1 = nn.Conv2d(input_channels, num_channels,
                              kernel_size=3, padding=1, stride=strides)
        self.conv2 = nn.Conv2d(num_channels, num_channels,
                              kernel_size=3, padding=1)
        if use_1x1conv:
            self.conv3 = nn.Conv2d(input_channels, num_channels,
                                  kernel_size=1, stride=strides)
        else:
            self.conv3 = None
        self.bn1 = nn.BatchNorm2d(num_channels)
        self.bn2 = nn.BatchNorm2d(num_channels)

    def forward(self, X):
        Y = F.relu(self.bn1(self.conv1(X)))
        Y = self.bn2(self.conv2(Y))
        if self.conv3:
            X = self.conv3(X)
        Y += X
        return F.relu(Y)

class CustomResNet(nn.Module):
    """自定义ResNet模型"""
    def __init__(self, num_classes=10):
        super().__init__()
        self.l1_lambda = 1e-5  # L1正则化系数
        
        self.b1 = nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=7, stride=2, padding=3),
            nn.BatchNorm2d(64), 
            nn.ReLU(),
            nn.Dropout(0.1),
            nn.MaxPool2d(kernel_size=3, stride=2, padding=1)
        )
        
        self.b2 = self._make_layer(64, 64, 2, first_block=True)
        self.b3 = self._make_layer(64, 128, 2)
        self.b4 = self._make_layer(128, 256, 2)
        self.b5 = self._make_layer(256, 512, 2)
        
        self.avgpool = nn.AdaptiveAvgPool2d((1, 1))
        self.flatten = nn.Flatten()
        self.dropout = nn.Dropout(0.5)
        self.fc = nn.Linear(512, num_classes)
        
        # 添加预测相关的transform
        self.predict_transform = transforms.Compose([
            transforms.Resize(256),
            transforms.CenterCrop(224),
            transforms.ToTensor(),
            transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ])
    
    def _make_layer(self, input_channels, num_channels, num_residuals, first_block=False):
        layers = []
        for i in range(num_residuals):
            if i == 0 and not first_block:
                layers.append(Residual(input_channels, num_channels, use_1x1conv=True, strides=2))
            else:
                layers.append(Residual(num_channels, num_channels))
        return nn.Sequential(*layers)

    def forward(self, x):
        x = self.b1(x)
        x = self.b2(x)
        x = self.b3(x)
        x = self.b4(x)
        x = self.b5(x)
        x = self.avgpool(x)
        x = self.flatten(x)
        x = self.dropout(x)
        x = self.fc(x)
        return x 
    
    def predict_image(self, image_path, device):
        """对单张图片进行预测
        
        Args:
            image_path: 图片路径
            device: 使用的设备
        
        Returns:
            预测的类别索引
        """
        self.eval()  # 设置为评估模式
        image = Image.open(image_path).convert('RGB')
        image = self.predict_transform(image).unsqueeze(0).to(device)
        
        with torch.no_grad():
            outputs = self(image)
            probabilities = F.softmax(outputs, dim=1)
            _, predicted = torch.max(probabilities, 1)
        return predicted.item()
    
    def l1_regularization(self):
        """计算L1正则化项"""
        l1_loss = 0
        for param in self.parameters():
            l1_loss += torch.sum(torch.abs(param))
        return self.l1_lambda * l1_loss
    
class DepthwiseSeparableConv(nn.Module):
    """深度可分离卷积"""
    def __init__(self, in_channels, out_channels, stride=1):
        super().__init__()
        self.depthwise = nn.Conv2d(
            in_channels, in_channels, kernel_size=3, padding=1,
            stride=stride, groups=in_channels, bias=False
        )
        self.pointwise = nn.Conv2d(
            in_channels, out_channels, kernel_size=1,
            stride=1, bias=False
        )
        self.bn1 = nn.BatchNorm2d(in_channels)
        self.bn2 = nn.BatchNorm2d(out_channels)
    
    def forward(self, x):
        x = F.relu(self.bn1(self.depthwise(x)))
        x = F.relu(self.bn2(self.pointwise(x)))
        return x

class CustomMobileNet(nn.Module):
    """自定义MobileNet模型"""
    def __init__(self, num_classes=10):
        super().__init__()
        self.l1_lambda = 1e-5  # L1正则化系数
        
        # 第一层使用标准卷积
        self.conv1 = nn.Sequential(
            nn.Conv2d(3, 32, kernel_size=3, stride=2, padding=1, bias=False),
            nn.BatchNorm2d(32),
            nn.ReLU(),
            nn.Dropout(0.1)
        )
        
        # 深度可分离卷积层
        self.conv_dw = nn.Sequential(
            # 112x112 -> 56x56
            DepthwiseSeparableConv(32, 64, stride=1),
            DepthwiseSeparableConv(64, 128, stride=2),
            # 56x56 -> 28x28
            DepthwiseSeparableConv(128, 128, stride=1),
            DepthwiseSeparableConv(128, 256, stride=2),
            # 28x28 -> 14x14
            DepthwiseSeparableConv(256, 256, stride=1),
            DepthwiseSeparableConv(256, 512, stride=2),
            # 14x14 -> 7x7
            *[DepthwiseSeparableConv(512, 512, stride=1) for _ in range(5)],
            DepthwiseSeparableConv(512, 1024, stride=2),
            # 7x7 -> 1x1
            DepthwiseSeparableConv(1024, 1024, stride=1)
        )
        
        self.avgpool = nn.AdaptiveAvgPool2d((1, 1))
        self.flatten = nn.Flatten()
        self.dropout = nn.Dropout(0.5)
        self.fc = nn.Linear(1024, num_classes)
        
        # 添加预测相关的transform
        self.predict_transform = transforms.Compose([
            transforms.Resize(224),  # MobileNet通常使用224x224
            transforms.CenterCrop(224),
            transforms.ToTensor(),
            transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ])
    
    def forward(self, x):
        x = self.conv1(x)
        x = self.conv_dw(x)
        x = self.avgpool(x)
        x = self.flatten(x)
        x = self.dropout(x)
        x = self.fc(x)
        return x
    
    def predict_image(self, image_path, device):
        """对单张图片进行预测
        
        Args:
            image_path: 图片路径
            device: 使用的设备
        
        Returns:
            预测的类别索引
        """
        self.eval()  # 设置为评估模式
        image = Image.open(image_path).convert('RGB')
        image = self.predict_transform(image).unsqueeze(0).to(device)
        with torch.no_grad():
            outputs = self(image)
            _, predicted = torch.max(outputs, 1)
        
        return predicted.item()
    
    def l1_regularization(self):
        """计算L1正则化项"""
        l1_loss = 0
        for param in self.parameters():
            l1_loss += torch.sum(torch.abs(param))
        return self.l1_lambda * l1_loss
    