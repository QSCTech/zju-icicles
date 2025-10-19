import os
import shutil
from pathlib import Path

def copy_hard_samples(work_dir):
    # 定义难分类的类别
    hard_classes = {
        'aesculus_glabra',
        'aesculus_pavi',
        'ailanthus_altissima',
        'cedrus_libani',
        'larix_decidua',
        'magnolia_stellata',
        'malus_hupehensis',
        'pinus_flexilis',
        'pinus_koraiensis',
        'pinus_nigra',
        'pinus_rigida',
        'pinus_strobus',
        'pinus_virginiana',
        'prunus_sargentii',
        'prunus_subhirtella',
        'prunus_virginiana',
        'quercus_muehlenbergii'
    }
    
    # 源目录和目标目录
    src_dir = Path(work_dir) / 'img_train'
    dst_dir = Path(work_dir) / 'train_hard'
    
    # 创建目标目录
    dst_dir.mkdir(exist_ok=True)
    
    print("开始复制难分类样本...")
    for class_name in hard_classes:
        # 源类别目录
        src_class_dir = src_dir / class_name
        # 目标类别目录
        dst_class_dir = dst_dir / class_name
        
        # 如果源目录存在
        if src_class_dir.exists():
            # 创建目标类别目���
            dst_class_dir.mkdir(exist_ok=True)
            
            # 复制所有图片
            for img_file in src_class_dir.glob('*'):
                shutil.copy2(img_file, dst_class_dir)
            
            print(f"已复制 {class_name} 的样本")
    
    print("复制完成！")

if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--work_dir', type=str, default='.', help='工作目录')
    args = parser.parse_args()
    
    copy_hard_samples(args.work_dir) 