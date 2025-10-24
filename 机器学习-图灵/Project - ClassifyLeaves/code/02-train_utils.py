# train_utils.py - 训练相关的工具函数
import torch
from torch.utils.data import DataLoader
from tqdm import tqdm
import os
import matplotlib.pyplot as plt
from datetime import datetime
import torch
import torch.nn as nn
import torch.nn.functional as F
def create_dataloaders(train_dataset, val_dataset, batch_size=32, num_workers=4):
    """创建数据加载器
    
    Args:
        train_dataset: 训练数据集
        val_dataset: 验证数据集
        batch_size: 批次大小
        num_workers: 数据加载线程数
    """
    train_loader = DataLoader(
        train_dataset, 
        batch_size=batch_size, 
        shuffle=True,
        num_workers=num_workers,
        pin_memory=True
    )
    
    val_loader = DataLoader(
        val_dataset, 
        batch_size=batch_size, 
        shuffle=True,
        num_workers=num_workers,
        pin_memory=True
    )
    
    return train_loader, val_loader

def train_epoch(model, train_loader, criterion, optimizer, device):
    """训练一个epoch
    
    Returns:
        epoch_loss: 平均损失
        epoch_acc: 准确率
    """
    model.train()
    total_loss = 0
    correct = 0
    total = 0
    
    pbar = tqdm(train_loader, desc=f'训练')
    for images, labels in pbar:
        images, labels = images.to(device), labels.to(device)
        
        optimizer.zero_grad()

        outputs = model(images)
        loss = criterion(outputs, labels)
        # l1_loss = model.l1_regularization()
        # loss += l1_loss
        
        loss.backward()
        optimizer.step()
        
        total_loss += loss.item()
        _, predicted = outputs.max(1)
        total += labels.size(0)
        correct += predicted.eq(labels).sum().item()
        
        pbar.set_postfix({
            'loss': f'{total_loss/total:.4f}',
            'acc': f'{100.*correct/total:.2f}%',
        })
    
    return total_loss / len(train_loader), 100. * correct / total

def validate(model, val_loader, criterion, device):
    """验证模型
    
    Returns:
        val_loss: 平均损失
        val_acc: 准确率
    """
    model.eval()
    total_loss = 0
    correct = 0
    total = 0
    
    with torch.no_grad():
        pbar = tqdm(val_loader, desc='验证')
        for images, labels in pbar:
            images, labels = images.to(device), labels.to(device)
            outputs = model(images)
            loss = criterion(outputs, labels)
            
            total_loss += loss.item()
            _, predicted = outputs.max(1)
            total += labels.size(0)
            correct += predicted.eq(labels).sum().item()
            
            pbar.set_postfix({
                'loss': f'{total_loss/total:.4f}',
                'acc': f'{100.*correct/total:.2f}%'
            })
    
    return total_loss / len(val_loader), 100. * correct / total

def save_checkpoint(state, is_best, save_dir, filename='checkpoint.pth',fold=0):
    """保存检查点
    
    Args:
        state: 要保存的状态字典
        is_best: 是否是最佳模型
        save_dir: 保存目录
        filename: 文件名
    """
    filename = f'{fold}_checkpoint.pth'
    filepath = os.path.join(save_dir, filename)
    torch.save(state, filepath)
    if is_best:
        best_filepath = os.path.join(save_dir, f'{fold}_best_model.pth')
        torch.save(state, best_filepath)
        print(f'保存最佳模型到 {best_filepath}')

def plot_training_curves(train_losses, train_accs, val_losses, val_accs, save_dir):
    """绘制训练曲线"""
    plt.figure(figsize=(12, 5))
    
    plt.subplot(1, 2, 1)
    plt.plot(train_losses, label='Train Loss')
    plt.plot(val_losses, label='Val Loss')
    plt.title('Training and Validation Loss')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    plt.grid(True)
    
    plt.subplot(1, 2, 2)
    plt.plot(train_accs, label='Train Acc')
    plt.plot(val_accs, label='Val Acc')
    plt.title('Training and Validation Accuracy')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy (%)')
    plt.legend()
    plt.grid(True)
    
    plt.tight_layout()
    plt.savefig(os.path.join(save_dir, 'training_curves.png'))
    plt.close() 

class EarlyStopping:
    """早停机制
    
    Args:
        patience: 容忍的epoch数
        min_delta: 最小改善阈值
        mode: 'min' 用于监控损失，'max' 用于监控准确率
    """
    def __init__(self, patience=7, min_delta=0, mode='max'):
        self.patience = patience
        self.min_delta = min_delta
        self.mode = mode
        self.counter = 0
        self.best_value = None
        self.early_stop = False
        self.min_delta *= 1 if mode == 'max' else -1
    
    def __call__(self, value):
        if self.best_value is None:
            self.best_value = value
            return False
        
        if self.mode == 'max':
            delta = value - self.best_value
        else:
            delta = self.best_value - value
            
        if delta > self.min_delta:
            self.best_value = value
            self.counter = 0
        else:
            self.counter += 1
            if self.counter >= self.patience:
                self.early_stop = True
                
        return self.early_stop 

class LabelSmoothingLoss(nn.Module):
    """
    标签平滑损失函数
    
    参数:
        smoothing (float): 平滑因子,默认0.1表示使用0.1的平滑系数
    """
    def __init__(self, smoothing=0.1):
        super().__init__()
        self.confidence = 1.0 - smoothing
        self.smoothing = smoothing

    def forward(self, x: torch.Tensor, target: torch.Tensor) -> torch.Tensor:
        """
        计算平滑后的损失值
        
        参数:
            x (torch.Tensor): 模型输出的logits
            target (torch.Tensor): 目标标签
            
        返回:
            torch.Tensor: 计算得到的损失值
        """
        logprobs = F.log_softmax(x, dim=-1)
        nll_loss = -logprobs.gather(dim=-1, index=target.unsqueeze(1))
        nll_loss = nll_loss.squeeze(1)
        smooth_loss = -logprobs.mean(dim=-1)
        loss = self.confidence * nll_loss + self.smoothing * smooth_loss
        return loss.mean()

def create_criterion(name="crossentropy", smoothing=0.1):
    """
    创建损失函数
    
    参数:
        name: 损失函数名称,支持 'crossentropy' 和 'labelsmoothing'
        smoothing: 标签平滑系数,仅在使用labelsmoothing时有效
        
    返回:
        nn.Module: 损失函数
    """
    if name.lower() == "crossentropy":
        return nn.CrossEntropyLoss()
    elif name.lower() == "labelsmoothing":
        return LabelSmoothingLoss(smoothing=smoothing)
    else:
        raise NotImplementedError(f"Loss function {name} not implemented")
