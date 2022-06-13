
[toc]



<div style="page-break-after: always;"></div>

# 1 实验任务

本次实验选择的题目为 Proj06-04，自己从网上下载了图片，实现图像的Color Segment Region。



# 2 算法设计

1. 图片输入
2. 选取目标颜色
3. 遍历图像的像素，计算每个像素目标颜色在阈值范围内的点，选取满足阈值的点并输出图像。



# 3 代码实现

编程环境：Matlab

**主要代码**

```matlab
R1 = R;
R1_ave = mean(mean(R1(:)));
[M, N] = size(R1);
sd = 0.0;
for i = 1:M
    for j = 1:N
        sd = sd + (R1(i, j) - R1_ave) * (R1(i, j) - R1_ave);
    end
end
R1_d = sqrt(sd/(M*N));

R2 = ones(size(img, 1), size(img, 2));
index = find((R > R1_ave - 1.25*R1_d) & (R < R1_ave + 1.25*R1_d));
R2(index) = 0;
```



# 4 实验结果

选取红色作为目标颜色，处理以下两张图像，分别对比了原图像、RGB单维度图像，颜色提取图像。

**第一组**

原图像

![image-20220419113936525](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121926763.png)

单维度图像

![image-20220419114012553](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121926765.png)

颜色分割图像

![image-20220419114038698](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121926766.png)



**第二组**

原图像

![image-20220419114140296](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121926767.png)



单维度图像

![image-20220419114203284](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121926769.png)



颜色提取图像

![image-20220419114222886](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121926770.png)

<div style="page-break-after: always;"></div>

**结果分析**

对两张图片的红色像素进行了提取，可以看到在颜色提取示意图中大体上仅有红色被显示。



# 5 总结

本次实验处理的是彩色图像，和灰度图比起来更加符合实际生活，实验与生活联系得更加紧密。



# 6 附录 源代码

```matlab
close all;clc;clear all;

img = imread('2.jpg');
figure;
imshow(img);
title('original image');

img1 = im2double(img);
R = img1(:, :, 1);
G = img1(:, :, 2);
B = img1(:, :, 3);

figure;
subplot(1, 3, 1);
imshow(R);
title('Red');
subplot(1, 3, 2);
imshow(G);
title('Green');
subplot(1, 3, 3);
imshow(B);
title('Blue');

R1 = R;
R1_ave = mean(mean(R1(:)));
[M, N] = size(R1);
sd = 0.0;
for i = 1:M
    for j = 1:N
        sd = sd + (R1(i, j) - R1_ave) * (R1(i, j) - R1_ave);
    end
end
R1_d = sqrt(sd/(M*N));

R2 = ones(size(img, 1), size(img, 2));
index = find((R > R1_ave - 1.25*R1_d) & (R < R1_ave + 1.25*R1_d));
R2(index) = 0;

figure;
imshow(R2);
title('segment');

```

