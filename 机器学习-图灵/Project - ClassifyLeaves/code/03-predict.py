import torch
import os
import argparse
from models import CustomResNet
import pandas as pd
from tqdm import tqdm
import timm
from PIL import Image
import torchvision.transforms as transforms
import torch.nn as nn
def main():
    parser = argparse.ArgumentParser(description='ResNet18预测脚本')
    parser.add_argument('--work_dir', type=str, required=True, help='工作目录路径')
    parser.add_argument('--model_path', type=str, required=True, help='模型文件路径')
    parser.add_argument('--gpu_id', type=int, default=0, help='GPU ID')
    
    args = parser.parse_args()
    
    # 设置设备
    device = f'cuda:{args.gpu_id}' if torch.cuda.is_available() else 'cpu'
    print(f'使用设备: {device}')
    
    # 获取类别信息
    train_dir = os.path.join(args.work_dir, 'img_train')
    classes = sorted(os.listdir(train_dir))
    num_classes = len(classes)
    print(f'类别数量: {num_classes}')
    


    # 创建和加载模型
    # model = timm.create_model('tf_mobilenetv3_small_minimal_100.in1k', pretrained=False)
    # model = timm.create_model('resnet18.a1_in1k', pretrained=False)
    # model = timm.create_model('inception_resnet_v2.tf_ens_adv_in1k', pretrained=False)
    model = timm.create_model('seresnext50_32x4d.racm_in1k', pretrained=False)
    model.fc = nn.Linear(model.num_features, num_classes)
    model.load_state_dict(torch.load('result/20241212_143214/0_checkpoint.pth', map_location=device)['state_dict'])
    model = model.to(device)
    model.eval()
    
    # 读取测试集CSV文件
    test_csv = os.path.join(args.work_dir, 'test.csv')
    test_df = pd.read_csv(test_csv)
    print(f'\n测试集数量: {len(test_df)} 张图片')
    
    # 开始预测
    predictions = []
    print('\n开始预测...')
    for idx, row in tqdm(test_df.iterrows(), total=len(test_df)):
        image_path = os.path.join(args.work_dir, row['image'])
        
        image = Image.open(image_path).convert('RGB')
        tr=transforms.Compose([
            transforms.Resize(224),  # MobileNet通常使用224x224
            transforms.CenterCrop(224),
            transforms.ToTensor(),
            transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ])
        image = tr(image).unsqueeze(0).to(device)
        with torch.no_grad():
            outputs = model(image)
            _, predicted = torch.max(outputs, 1)
            # print(_,predicted)
        
        
        predicted_label = classes[predicted.item()]
        predictions.append({
            'image': row['image'],
            'label': predicted_label
        })
        # print(predicted_label)
    
    # 创建并保存预测结果
    output_df = pd.DataFrame(predictions)
    output_path = os.path.join(args.work_dir, 'output_inception_resnet_v2.csv')
    output_df.to_csv(output_path, index=False)
    
    print(f'\n预测完成！结果已保存至: {output_path}')

if __name__ == '__main__':
    main()