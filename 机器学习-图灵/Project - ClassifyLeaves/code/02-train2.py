# train.py - 主训练脚本
import torch
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
from sklearn.model_selection import KFold
import os
import argparse
from datetime import datetime
import timm
from models import CustomResNet, CustomMobileNet
from Resnet50 import ResNet50D
from train_utils import (
    create_dataloaders, train_epoch, validate,
    save_checkpoint, plot_training_curves,
    EarlyStopping
)
from dataset import create_train_val_datasets
import albumentations


def learner(args,device):
    # 创建模型
    num_classes = len(torchvision.datasets.ImageFolder(args.train_dir).classes)
    model = timm.create_model('eva02_large_patch14_448.mim_m38m_ft_in22k_in1k', pretrained=False)
    model.load_state_dict(torch.load('model/eva02_large_patch14_448.mim_m38m_ft_in22k_in1k.bin', map_location=device))
    model.fc = nn.Linear(model.head.in_features, num_classes)
    nn.init.xavier_uniform_(model.fc.weight)
    model.cuda()
 
    # if args.model_path != '':
    #     model.load_state_dict(torch.load(args.model_path, map_location=device)['model_state_dict'])
    #     print(f"加载预训练模型: {args.model_path}")
        # # 冻结除最后两层外的所有层
        # for name, param in model.named_parameters():
        #     if not any(layer in name for layer in ['dropout', 'fc']):
        #         param.requires_grad = False
                
        # print("\n冻结模型参数情况:")
        # for name, param in model.named_parameters():
        #     print(f"{name}: {'需要梯度' if param.requires_grad else '已冻结'}")
    # 定义损失函数和优化器
    criterion = nn.CrossEntropyLoss()
    # optimizer = torch.optim.Adam(model.parameters(), lr=args.lr)
    # optimizer = torch.optim.SGD(
    #     model.parameters(),
    #     lr=args.lr,
    #     momentum=args.momentum,
    #     weight_decay=args.weight_decay
    # )

    # 使用d2l中讲过的一个方法，finetune的backbone和fc使用不同的学习率
    params = [param for name, param in model.named_parameters()
             if name not in ["fc.weight", "fc.bias"]]

    optimizer = torch.optim.AdamW([{'params': params},
                                    {'params': model.fc.parameters(),
                                        'lr': args.lr * 10}],
                                    lr=args.lr, weight_decay=2e-4)



    scheduler = torch.optim.lr_scheduler.CosineAnnealingLR(
        optimizer, T_max=args.epochs, eta_min=args.lr/20
    )
    
    # 添加早停机制
    # early_stopping = EarlyStopping(
    #     patience=args.patience,
    #     min_delta=args.min_delta,
    #     mode='max'
    # )
    return model,criterion,optimizer,scheduler
    
    


def train(args):
    # 设置设备
    device = f'cuda:{args.gpu}' if torch.cuda.is_available() else 'cpu'
    torch.cuda.set_device(args.gpu)
    
    # 创建保存目录
    timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
    save_dir = os.path.join(args.work_dir, 'result', timestamp)
    os.makedirs(save_dir, exist_ok=True)
    
    # 数据预处理
    transform_train = transforms.Compose([
        transforms.RandomResizedCrop(448),
        transforms.RandomVerticalFlip(p=0.5),
        transforms.RandomRotation(30,expand=False, center=None),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
    ])
    
    transform_val = transforms.Compose([
        transforms.Resize(512),
        transforms.CenterCrop(448),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
    ])
    
    
    
    for fold in range(1):
        # 创建数据集和加载器
        train_dataset, val_dataset = create_train_val_datasets(
            args.train_dir, 
            transform_train, 
            transform_val,
            fold, args.n_splits
        )
        
        train_loader, val_loader = create_dataloaders(
            train_dataset, val_dataset,
            args.batch_size, args.workers
        )
        # 训练循环
        best_acc = 0
        train_losses, train_accs = [], []
        val_losses, val_accs = [], []
        print(f'Start Fold{fold}...')
        model,criterion,optimizer,scheduler = learner(args,device)
        for epoch in range(args.epochs):
            # 训练一个epoch
            train_loss, train_acc = train_epoch(
                model, train_loader, criterion, optimizer, device
            )
            
            # 验证
            val_loss, val_acc = validate(model, val_loader, criterion, device)
            
            # 更新学习率
            scheduler.step()
            
            # 记录指标
            train_losses.append(train_loss)
            train_accs.append(train_acc)
            val_losses.append(val_loss)
            val_accs.append(val_acc)
            
            # 保存检查点
            is_best = val_acc > best_acc
            best_acc = max(val_acc, best_acc)
            
            save_checkpoint({
                'epoch': epoch + 1,
                'state_dict': model.state_dict(),
                'best_acc': best_acc,
                'optimizer': optimizer.state_dict(),
            }, is_best, save_dir,fold)
            
            # 绘制训练曲线
            plot_training_curves(
                train_losses, train_accs,
                val_losses, val_accs,
                save_dir
            )
            
            # 检查是否需要早停
            # if early_stopping(val_acc):
            #     print(f"\n触发早停！在epoch {epoch+1}")
            #     print(f"最佳验证准确率: {best_acc:.2f}%")
            #     break
            
            print(f'Epoch [{epoch+1}/{args.epochs}]')
            print(f'Train Loss: {train_loss:.4f}, Train Acc: {train_acc:.2f}%')
            print(f'Val Loss: {val_loss:.4f}, Val Acc: {val_acc:.2f}%')
            # print(f'Learning Rate: {scheduler.get_last_lr()[0]:.6f}')
            print('--------------------')

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--train-dir', required=True, help='训练数据目录')
    parser.add_argument('--work-dir', required=True, help='工作目录')
    parser.add_argument('--epochs', type=int, default=100)
    parser.add_argument('--batch-size', type=int, default=128)
    parser.add_argument('--lr', type=float, default=0.1)
    parser.add_argument('--momentum', type=float, default=0.9)
    parser.add_argument('--weight-decay', type=float, default=5e-4)
    parser.add_argument('--gpu', type=int, default=0)
    parser.add_argument('--workers', type=int, default=4)
    parser.add_argument('--fold', type=int, default=0, help='使用第几折作为验证集')
    parser.add_argument('--n-splits', type=int, default=5, help='总折数')
    parser.add_argument('--model-path', type=str, default='', help='预训练模型路径')
    parser.add_argument('--patience', type=int, default=7, help='早停耐心值')
    parser.add_argument('--min-delta', type=float, default=0.1, help='早停最小改善阈值')
    parser.add_argument('--model', type=str, default='resnet', choices=['resnet', 'mobilenet'],
                        help='选择模型类型')
    
    args = parser.parse_args()
    print(args.model_path,'!!!!!!!!!!!')
    train(args) 