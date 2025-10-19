import os
import shutil
import pandas as pd
import argparse

# 添加命令行参数解析
def parse_args():
    parser = argparse.ArgumentParser(description='整理图片到训练和测试目录')
    parser.add_argument('root_dir', type=str, help='项目根目录的路径')
    return parser.parse_args()

# 全局变量现在需要通过函数来设置
def get_output_dirs(root_dir):
    return {
        'train': os.path.join(root_dir, 'img_train'),
        'test': os.path.join(root_dir, 'img_test')
    }

def setup_directories(dirs):
    """创建必要的输出目录"""
    for directory in dirs.values():
        if not os.path.exists(directory):
            os.makedirs(directory)

def process_train_images(dirs, train_csv_path='train.csv'):
    """处理训练集图片"""
    print("开始处理训练集图片...")
    
    df_train = pd.read_csv(train_csv_path)
    
    labels = df_train['label'].unique()
    for label in labels:
        label_dir = os.path.join(dirs['train'], label)
        if not os.path.exists(label_dir):
            os.makedirs(label_dir)
    
    for index, row in df_train.iterrows():
        src = row['image']
        dst = os.path.join(dirs['train'], row['label'], os.path.basename(src))
        
        try:
            shutil.copy2(src, dst)
            print(f"复制 {src} 到 {dst}")
        except FileNotFoundError:
            print(f"警告: 找不到文件 {src}")
        except Exception as e:
            print(f"复制 {src} 时发生错误: {str(e)}")
    
    print("训练集图片整理完成!")

def process_test_images(dirs, test_csv_path='test.csv'):
    """处理测试集图片"""
    print("\n开始处理测试集图片...")
    
    df_test = pd.read_csv(test_csv_path)
    test_images = df_test['image'].tolist()
    
    for img_path in test_images:
        try:
            src = img_path
            dst = os.path.join(dirs['test'], os.path.basename(img_path))
            
            shutil.copy2(src, dst)
            print(f"复制 {src} 到 {dst}")
        except FileNotFoundError:
            print(f"警告: 找不到文件 {src}")
        except Exception as e:
            print(f"复制 {src} 时发生错误: {str(e)}")
    
    print("测试集图片整理完成!")

def main():
    """主函数"""
    args = parse_args()
    output_dirs = get_output_dirs(args.root_dir)
    
    setup_directories(output_dirs)
    process_train_images(output_dirs)
    process_test_images(output_dirs)

if __name__ == "__main__":
    main() 