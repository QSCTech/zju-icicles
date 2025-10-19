# Classify Leaves Project 
## Description


The task is predicting categories of leaf images. This dataset contains 176 categories, 18353 training images, 8800 test images. Each category has at least 50 images for training. The test set is split evenly into the public and private leaderboard.

The evaluation metric for this competition is Classification Accuracy.


## File descriptions:

- train.csv - the training set
- test.csv - the test set
- sample\_submission.csv - a sample submission file in the correct format (the labels are randomly generated so the initial accuracy is roughly 1/176)
- images/ - the folder contains all images

## Data fields

- image - the image path, such as images/0.jpg
- label - the category name



## Files

```
.
├── code
│   ├── 00-copy_hard_samples.py
│   ├── 00-count_images.py
│   ├── 00-info.py
│   ├── 00-organize_images.py
│   ├── 00-test_gpu.py
│   ├── 01-dataset.py
│   ├── 01-models.py
│   ├── 01-Resnet50.py
│   ├── 02-train2.py
│   ├── 02-train.py
│   ├── 02-train_utils.py
│   ├── 03-ensemble_predict.py
│   └── 03-predict.py
├── final_model
│   ├── inception_resnet_v2.tf_ens_adv_in1k.pth
│   ├── mixnet_xl.pth
│   ├── mobilenetv2_100.ra_in1k.pth
│   ├── resnet101.a1h_in1k.pth
│   ├── resnet50d.pth
│   ├── resnext50_32x4d.fb_swsl_ig1b_ft_in1k_2.pth
│   ├── resnext50_32x4d.fb_swsl_ig1b_ft_in1k.pth
│   └── seresnext50_32x4d.racm_in1k.pth
├── model    # 预训练模型
│   ├── convnext_tiny.in12k_ft_in1k.bin
│   ├── convnextv2_large.fcmae_ft_in22k_in1k.bin
│   ├── eva02_large_patch14_448.mim_m38m_ft_in22k_in1k.bin
│   ├── inception_resnet_v2.tf_ens_adv_in1k.bin
│   ├── mixnet_xl.bin
│   ├── mobilenetv2_100.ra_in1k.bin
│   ├── mobilenetv3_small_minimal_100.in1k.bin
│   ├── resnet101.a1h_in1k.bin
│   ├── resnet18.a1_in1k.bin
│   ├── resnet50d_ra2-464e36ba.pth
│   ├── resnext50_32x4d.fb_swsl_ig1b_ft_in1k.bin
│   ├── seresnext50_32x4d.racm_in1k.bin
│   └── vit_base_patch16_224.augreg2_in21k_ft_in1k.bin
├── README.md
├── requirements.txt
├── Makefile
├── result
│   ├── 20241209_152338
│   │   ├── best_model_acc_94.93.pth
│   │   ├── exp.log
│   │   ├── final_model.pth
│   │   └── training_curves.png
│   ├── 20241209_163042
│   │   ├── best_model.pth
│   │   ├── checkpoint.pth
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241209_172359
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241211_153734
│   │   ├── best_model.pth
│   │   ├── checkpoint.pth
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241211_164351
│   │   ├── best_model.pth
│   │   ├── checkpoint.pth
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241211_235611
│   │   ├── best_model.pth
│   │   ├── checkpoint.pth
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_001640
│   │   ├── best_model.pth
│   │   ├── checkpoint.pth
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_013554
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_020242
│   │   ├── 0_best_model.pth
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_021324
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_110329
│   │   ├── 0_best_model.pth
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_111033
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_142840
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_143214
│   │   ├── 0_best_model.pth
│   │   ├── 0_checkpoint.pth
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── 20241212_143856
│   │   ├── exp.log
│   │   └── training_curves.png
│   ├── model.csv
│   ├── resnet101.a1h_in1k
│   │   ├── exp.log
│   │   └── training_curves.png
│   └── resnet18.a1_in1k
│       ├── exp.log
│       └── training_curves.png
├── test.csv
└── train.csv
```
