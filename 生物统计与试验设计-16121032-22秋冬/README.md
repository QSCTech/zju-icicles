## 关于本课程

本课程是农学院2022-2023学年秋冬学期生物统计与试验设计课程，课程号16121032，教师是卢运海和徐海明，课程较难，这里整理了我之前的手写笔记，仅供参考。

历年卷也在98发布了，点击[此处](https://www.cc98.org/topic/5505331/1)前往。

## 各章节要点梳理

### 第1章

#### chapter1.1

chapter1主要还是打基础为主，就是概统相关知识，掌握群体、样本、均值、方差、协方差、常见分布（特别是正态）、中心极限定理等即可。
考试不会直接考，但是要理解概念。

#### chapter1.2科学试验和误差控制

感觉每次考试都会考到，无论是出现在一整个大题（比如第一题基本概念），还是出现在各大题的前一两小题或者最后一两小题
考前一定要把英文内容阅读一遍并且在旁边备注，考试期间没时间看的
* 试验设计的基本思路和步骤（这次就考到了
* 数量性状和质量性状（为后面打基础）
* 试验误差的来源
* 试验误差的分类
* 控制试验误差的三种方法
* 田间试验特点、误差来源、控制误差方法、改进方法
* 常规试验设计方法（对比、间比）
* 随机试验设计（完全随机、随机区组、Latin Square等，为后面打基础）

### 第2章

#### chapter2.1_note_Fundamental of Mathematical Statistics1

课件写得十分详细，卢老师也讲得十分详细，主要还是打基础，超级基础的概统
考试直接考的也不多，关注基本概念、方差的计算、自由度、正态分布、抽样分布，特别是正态分布和抽样分布
（文件过大，我就删了一些讲得太基础的part，留了一些有笔记的）

#### chapter2.2_note_Fundamental of Mathematical Statistics2

我感觉是chapter2中最重要的一个section，特别多检测方法和基本概念在这里提到了，并且考试极可能会出题（这次就出了）

* H0和HA、小样本和大样本(n>30)、正态分布u测验和t分布t检验、一尾两尾测验、接受区否定区
* 假设检验的两种错误、统计功效（考了）
* 成组数据平均数比较（sigma都已知、小样本sigma未知、sigma未知且不等）
* 成对数据比较（以及与成组数据的区别）
* 单样本概率与理论值比较
* 两个样本频率比较
* 参数区间估计（置信限，这次考了）与假设检验
* ANOVA基本原理（打基础）、组间组内变异、自由度平方和分解
* F分布和F test检验变异（这次考了）

#### chapter2.3_note_Fundamental of Mathematical Statistics3

这个section也很重要，主要包括卡方测验、一个样本与总体方差比较、3个以上方差的同质性检验、适合度测验；
还有历年曾经考过的独立性测验（2x2独立性测验，2xC独立性测验等）；
参数估计方法（重点关注最小二乘法和最大似然法）

### 第3章

#### chapter3.1_note_Matrix Theory

超级基础的线代内容，关注矩阵的转置、rank、trace等基本概念
还有广义逆、射影矩阵、随机矩阵、quadratic form（为后面打基础）

#### chapter3.2_note_Principles of Simple Regression Analysis

非常重要的回归分析以及方差原理的基础部分，重点是理解**各个parameter的概念和计算方法**
是每次几乎必考的chapter4的基础
* regression model的表达式正确写法，参数、自变量、随机变量区分
* Y的期望方差，b0和b1的分布及估计
* 经过原点或不经过原点的**SCP/SSx/SSTO/SSR/SSE/R方/Radj方/rho/MSE**计算方法（考了）
* **F-test检验模型线性、t-test检验各个参数以及区间估计**（考了）
* Jackknife resampling方法要留个印象（MLM中会用到）

### 第4章

#### chapter4_note_Methods of Multi-variable Regression Analysis

考试热点、重难点，应该每次都有一个大题=。=
并且是后面各种模型分析思路的基础（包括MLM）

* 多元线性回归模型表达、**矩阵表达**、参数自变量随机变量、Y分布（这次考了）
* 平方和分解，不用多说了，**SSTO/SSR/SSE/MSR/MSE/E(MS)**（这次考了）
* **方差分析表**，自由度、F-test检验全模型线性度（这次考了）
* R方、Radj方计算方法及实际意义
* bi的显著性检验，广义线性检验，K、b、m矩阵形式（这次考了）
* 各参数的区间估计（这次考了）
* **过原点模型的区别之处**（注意自由度以及SS是否使用均值校正了）（这次考了）
* **SSR的分组分解**，F-test检验参数，部分决定系数（这次考了）
* 三种筛选自变量的方法

### 第5章

#### chapter5_note_other multiple regression and non-linear regression

是简单线性回归的延伸，同时也为之后的析因设计等打下基础，因为交互效应就需要多项式回归模型分析
考试直接出题应该不多，主要掌握**dummy variable**的概念（为啥要用dummy variable，作用是啥，调整截距/斜率的用法），分段回归模型、非线性回归模型（与内蕴线性回归模型相区分；使用SAS的NLIN模块）

### 第6章

#### chapter6_note_The analysis of variance and randomized block design

我感觉chapter6/7/8/9需要综合起来理解，考试也是必考的
* 平衡数据和非平衡数据区别、**Type I SS以及Type III SS**区别及联系
* **Fixed Model和Random Model的区别**，特别是方差分析表上EMS的差异以及检验参数时的H0/HA
* 多重比较**alpha_pc和alpha_ew**值之间的关系以及实际意义
* 多重比较的方法**LSD、Tukey**等，以及如何分析grouping的结果
* **完全随机区组设计**思路、优缺点，模型、方差分析表
* **Latin Squares Design**的思路，有replication和没有的区别，模型表达、方差分析

关键是理解到位，考试不会考到一模一样的实验例子，但是有些会长得很像，因此把握思路更重要

### 第7&8&9章

考试必考点，与chapter6重复的点就不再强调了
* 突出互作效应，互作效应加入后SS、EMS怎么求，互作效应是否显著怎么下推断
* 将某个效应正交分解成线性、二次性、三次性等关系，如何设置dummy variable
* 何时使用nested design、引入协变量
* 在Fixed/Random/Mixed model条件下，各种SSA、SSB、SSAB怎么计算，各种EMS怎么计算，特别是F-test的时候的分母以及自由度

### 第10章

考试必考一题，通常最后一题（我感觉
* MLM的通式，特别是各个**效应向量以及系数矩阵**
* 常用的**随机效应分布假设**，模型中需要分析的参数
* **估计随机效应分量的方法**（Henderson III method、ML method、REML method、MINQUE），掌握表达式以及假设
* Henderson III method的优缺点，ML与REML的区别，**REML与MINQUE的区别**
* 随机效应值的预测方法及公式，**BLUP**/LUP/AUP
* 估计固定效应的公式：BLUE，包括**GLS和OLS**
* 检验方差显著性方法：渐进多元正态分布、Jackknife resampling


