# dataset.py - 数据集处理相关函数
import torchvision
from torch.utils.data import Subset
from sklearn.model_selection import StratifiedKFold
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd


def create_train_val_datasets(train_dir, transform_train, transform_val, fold_idx=0, n_splits=5):
    """创建训练集和验证集，使用分层K折交叉验证
    
    Args:
        train_dir: 训练数据目录
        transform_train: 训练集数据增强
        transform_val: 验证集数据增强
        fold_idx: 使用第几折作为验证集
        n_splits: 总折数
    
    Returns:
        train_dataset: 训练数据集
        val_dataset: 验证数据集
    """
    # 加载完整数据集
    dataset = torchvision.datasets.ImageFolder(train_dir)
    
    # 获取所有标签
    labels = np.array([label for _, label in dataset.samples])
    
    # 创建分层K折交叉验证对象
    skf = StratifiedKFold(n_splits=n_splits, shuffle=True, random_state=42)
    
    # 获取当前折的索引
    splits = list(skf.split(np.zeros(len(labels)), labels))
    train_indices, val_indices = splits[fold_idx]
    
    # 创建训练集和验证集，应用不同的transform
    train_dataset = torchvision.datasets.ImageFolder(
        train_dir,
        transform=transform_train
    )
    val_dataset = torchvision.datasets.ImageFolder(
        train_dir,
        transform=transform_val
    )
    
    # 使用索引子集
    train_dataset = Subset(train_dataset, train_indices)
    val_dataset = Subset(val_dataset, val_indices)
    
    # 计算每个类别在训练集和验证集中的样本数
    train_labels = labels[train_indices]
    val_labels = labels[val_indices]
    unique_labels = np.unique(labels)
    
    
    
    # 打印基本信息
    print(f"\n数据集信息:")
    print(f"类别数量: {len(dataset.classes)}")
    # print(f"类别映射: {dataset.class_to_idx}")
    print(f"训练集样本数: {len(train_dataset)}")
    print(f"验证集样本数: {len(val_dataset)}")
    
    # # 准备绘图数据
    # plot_data = []
    # for label in sorted(unique_labels)[:10]:
    #     train_count = np.sum(train_labels == label)
    #     val_count = np.sum(val_labels == label)
    #     class_name = dataset.classes[label]
    #     plot_data.extend([
    #         {'类别': class_name, '数据集': '训练集', '样本数': train_count},
    #         {'类别': class_name, '数据集': '验证集', '样本数': val_count}
    #     ])
    
    # df = pd.DataFrame(plot_data)
    
    # # 创建柱状图
    # plt.figure(figsize=(15, 6))
    # sns.barplot(data=df, x='类别', y='样本数', hue='数据集')
    # plt.xticks(rotation=45, ha='right')
    # plt.title('各类别样本分布')
    # plt.tight_layout()
    # plt.savefig('class_distribution.png')
    # plt.close()
    
    return train_dataset, val_dataset 