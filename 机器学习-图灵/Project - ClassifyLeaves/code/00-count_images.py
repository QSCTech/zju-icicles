import os
import argparse
from pathlib import Path

def parse_args():
    parser = argparse.ArgumentParser(description='统计图片数量')
    parser.add_argument('root_dir', type=str, help='项目根目录的路径')
    return parser.parse_args()

def count_images(root_dir):
    # 统计测试集图片数量
    test_dir = Path(root_dir) / 'img_test'
    test_count = len(list(test_dir.glob('*')))
    print(f"测试集图片共有: {test_count}\n")
    
    # 统计训练集文件夹数量
    train_dir = Path(root_dir) / 'img_train'
    train_folders = list(train_dir.glob('*'))
    print(f"训练集图片共有文件夹: {len(train_folders)}")
    
    # 统计训练集各类别图片数量
    print("\n训练集各类别图片数量:")
    for folder in sorted(train_folders):
        if folder.is_dir():
            images_count = len(list(folder.glob('*')))
            print(f"{folder.name}: {images_count}")

if __name__ == '__main__':
    args = parse_args()
    count_images(args.root_dir)