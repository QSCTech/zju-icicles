.PHONY: download prepare clean clean-all

# 下载数据集
download:
	@echo "正在下载数据集..."
	@kaggle competitions download -c classify-leaves
	@unzip -q classify-leaves.zip
	@rm classify-leaves.zip
	@tree
	@echo "数据集下载完成"

# 准备训练和测试数据
prepare: images/ code/organize_images.py code/count_images.py
	@echo "正在准备数据..."
	@python code/00-organize_images.py $(PWD)
	@python code/00-count_images.py $(PWD)
	@echo "数据准备完成"

# 变量定义
PYTHON := python3
TRAIN_DIR := $(PWD)/img_train
WORK_DIR := $(PWD)
GPU := 2

# 默认训练参数
EPOCHS := 25
BATCH_SIZE := 64
LR := 0.0009
N_SPLITS := 5
FOLD := 0
WEIGHT_DECAY := 5e-4

# 帮助信息
.PHONY: help
help:
	@echo "可用的命令:"
	@echo "  make download     - 下载数据集"
	@echo "  make prepare      - 准备数据集"
	@echo "  make test-gpu     - 测试GPU可用性"

	@echo "  make train        - 训练模型"
	@echo "  make predict      - 单模型预测"
	@echo "  make pe          - 集成学习预测"
	
	@echo "  make clean        - 清理训练测试目录"
	@echo "  make clean-all    - 清理所有生成的文件"


# 训练单个模型（默认第0折）
.PHONY: train
train:
	$(PYTHON) code/02-train.py \
		--train-dir $(TRAIN_DIR) \
		--work-dir $(WORK_DIR) \
		--epochs $(EPOCHS) \
		--batch-size $(BATCH_SIZE) \
		--lr $(LR) \
		--gpu $(GPU) \
		--fold 0 \
		--n-splits $(N_SPLITS) \
		--weight-decay $(WEIGHT_DECAY) \

predict: code/03-predict.py
	@echo "正在预测..."
	@python code/03-predict.py --work_dir .  --gpu_id $(GPU)
	@echo "预测完成"

# 集成学习预测
pe:
	@echo "正在使用集成学习进行预测..."
	@python code/03-ensemble_predict.py \
		--work_dir . \
		--model_csv result/model.csv \
		--gpu_id $(GPU)
	@echo "预测完成"

.PHONY: test-gpu
test-gpu:
	$(PYTHON) code/00-test_gpu.py
# 清理生成的文件
.PHONY: clean
clean:
	@echo "正在清理训练测试目录..."
	@rm -rf img_train/ img_test/
	@echo "清理完成"

# 清理所有生成的文件
clean-all: clean
	@echo "正在清理所有文件..."
	@rm -rf images/ sample_submission.csv train.csv test.csv
	@echo "清理完成"