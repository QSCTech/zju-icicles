import pandas as pd

# 读取数据
train_df = pd.read_csv("train.csv")

# 基本信息统计
print("数据集基本信息:")
print(f"总样本数: {len(train_df)}")
print(f"总类别数: {len(train_df['label'].unique())}")

# 统计每个类别的样本数量
class_counts = train_df['label'].value_counts()

print("\n样本数最多的前10个类别:")
for class_name, count in class_counts.head(10).items():
    print(f"{class_name}: {count}个样本")

print("\n样本数最少的前10个类别:")
for class_name, count in class_counts.tail(10).items():
    print(f"{class_name}: {count}个样本")

# 计算类别分布的一些统计指标
print("\n类别分布统计:")
print(f"平均每类样本数: {class_counts.mean():.2f}")
print(f"最大样本数: {class_counts.max()}")
print(f"最小样本数: {class_counts.min()}")
print(f"样本数标准差: {class_counts.std():.2f}")

print(train_df.describe()   )