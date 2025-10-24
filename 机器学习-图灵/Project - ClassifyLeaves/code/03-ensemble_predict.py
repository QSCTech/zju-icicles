import torch
import os
import argparse
import pandas as pd
from tqdm import tqdm
import timm
import torch.nn as nn
from PIL import Image
import torchvision.transforms as transforms
import torch.nn.functional as F
from collections import Counter
class EnsemblePredictor:
    def __init__(self, model_csv, device, num_classes,args):
        """初始化集成预测器
        
        Args:
            model_csv: 模型配置CSV文件路径
            device: 使用的设备
            num_classes: 类别数量
        """
        self.device = device
        self.models = []
        self.num_classes = num_classes
        
        # 读取模型配置
        model_df = pd.read_csv(model_csv)
        print(f"\n读取模型配置文件: {model_csv}")
        print(f"模型数量: {len(model_df)}")
        print("\n模型配置:")
        print(model_df)
        print("\n加载模型中...")
        for _, row in model_df.iterrows():
            if row['label'] == 0:
                continue
            model_name = row['model']
            label = row['label']
            print(f"加载模型: {model_name}")
            
            # 创建模型
            model = timm.create_model(model_name, pretrained=False)
            if hasattr(model, 'fc'):
                model.fc = nn.Linear(model.num_features, num_classes)
            elif model_name=='mixnet_xl' or model_name=='mobilenetv2_100.ra_in1k':
                model.fc = nn.Linear(model.classifier.in_features, num_classes)
            elif model_name=='inception_resnet_v2.tf_ens_adv_in1k':
                model.fc = nn.Linear(model.classif.in_features, num_classes)
               
            
            # 加载权重
            model.load_state_dict(torch.load(f'{args.work_dir}/final_model/{model_name}.pth', map_location=device)['state_dict'])
            model = model.to(device)
            model.eval()
            
            self.models.append(model)
        
        print(f"成功加载 {len(self.models)} 个模型")
    
    def predict_image(self, image_path):
        """对单张图片进行集成预测
        
        Args:
            image_path: 图片路径
            
        Returns:
            predicted_class: 预测的类别
            probabilities: 各类别的概率
        """
        
        
        
        # 收集所有模型的预测结果
        vote = []
        for enum,model in enumerate(self.models):
            # print(f"第{enum}个模型")
            tr=transforms.Compose([
                transforms.Resize(224),  # MobileNet通常使用224x224
                transforms.CenterCrop(224),
                transforms.ToTensor(),
                transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
            ])
            image = Image.open(image_path).convert('RGB')
            image = tr(image).unsqueeze(0).to(self.device)
            with torch.no_grad():
                outputs = model(image)
                _, predicted = torch.max(outputs, 1)
                # 获取每个类别的概率分布
                probabilities = F.softmax(outputs, dim=1).squeeze()
                vote.append(probabilities)
                      
        weights = [0.5,0.5,0.971,0.5,0.78]
        
        # 加权平均所有模型的预测概率
        weighted_probs = torch.zeros(176).to(self.device)
        for i, probs in enumerate(vote):
            weighted_probs += weights[i] * probs
            
        final_prediction = torch.argmax(weighted_probs).item()
        return final_prediction

def main():
    parser = argparse.ArgumentParser(description='集成学习预测脚本')
    parser.add_argument('--work_dir', type=str, required=True, help='工作目录路径')
    parser.add_argument('--model_csv', type=str, required=True, help='模型配置CSV文件路径')
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
    
    # 创建集成预测器
    predictor = EnsemblePredictor(args.model_csv, device, num_classes,args)
    
    # 读取测试集CSV文件
    test_csv = os.path.join(args.work_dir, 'test.csv')
    test_df = pd.read_csv(test_csv)
    print(f'\n测试集数量: {len(test_df)} 张图片')

    # 开始预测
    predictions = []
    print('\n开始预测...')

    for idx, row in tqdm(test_df.iterrows(), total=len(test_df)):
        image_path = os.path.join(args.work_dir, row['image'])
        predicted_class = predictor.predict_image(image_path)
        predicted_label = classes[predicted_class]
        # if predicted_label not in hard_classes:
        predictions.append({
            'image': row['image'],
            'label': predicted_label
        })
    
    # 创建并保存预测结果
    output_df = pd.DataFrame(predictions)
    output_path = os.path.join(args.work_dir, 'ensemble_predictions.csv')
    output_df.to_csv(output_path, index=False)
    
    print(f'\n预测完成！结果已保存至: {output_path}')

if __name__ == '__main__':
    main() 