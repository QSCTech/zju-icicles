[toc]



<div style="page-break-after: always;"></div>

# 1 实验任务

本次实验选择的题目为 Proj03-03，要求编程实现图像的空间域滤波器。取定空间蒙版大小为 3*3，实现了自定义系数的空间滤波。





# 2 算法设计

原理：对于图像中的任意一点$(x, y)$，滤波器的响应$g(x,y)$是滤波器系数与该滤波器包围的图像像素的乘积之和。
$$
g(x,y)=\sum^1_{i=-1}\sum^1_{j=-1}w(i,j)f(x+i,y+j)
$$
空间滤波器效果的差别在于构造的$w$不同。这里我选择了以下两种 $w$，分别用于图像增强和图像平滑处理，实现了这两种图像滤波。

![image-20220319112254193](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202203191446319.png)



1. 扩展原图形的边界像素，便于边界像素进行滤波处理。
2. 通过对目标位置像素的邻域进行计算，得到每一个目标位置像素的RGB值。
2. 遍历所有像素，得到的结果就是目标图像





# 3 代码实现

编程环境：Matlab

**主要代码和注释**

```matlab
% 获取图像大小
[rows, cols, k] = size(image);

% 创建矩阵，用于存储结果
dst_enhancement = zeros(rows, cols, k, 'uint8');
dst_average = zeros(rows, cols, k, 'uint8');

% 对边界像素进行扩展，这里采用的是复制扩展
extension_image = zeros(rows+2, cols+2, k, 'uint8');
for i = 1:k
    extension_image(:,:,i) = padarray(image(:,:,i), [1, 1], 'replicate');    
end

% 定义蒙版矩阵
M_enhance = [0, -1, 0; ...
             -1, 5, -1; ...
             0, -1, 0];
M_average = [1, 1, 1; ...
             1, 1, 1; ...
             1, 1, 1];
         
for i = 1:rows
    for j = 1:cols
        for idx = 1:k
           % 取蒙版矩阵
            Rect = double(extension_image(i:i+2, j:j+2, idx));
            % 增强处理
            dst_enhancement(i, j, idx) = uint8(sum(M_enhance.*Rect, 'all'));
            % 均值滤波
            dst_average(i, j, idx) = uint8(average(M_average.*Rect)); 
        end
    end
end
```



# 4 实验结果



三张图依次为：

1. 原图像
2. 均值滤波图像
3. 增强图像

一共进行了 4 组实验，每一组中，第一列是原数据，后面两列均为比较（结果）数据

<div style="page-break-after: always;"></div>

* **第一组**

![image-20220319112025732](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202205102039835.png)

- **第二组**

![image-20220319112351970](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202205102039169.png)

- **第三组**

![image-20220319112518833](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202205102039172.png)

- **第四组**

![image-20220319112745170](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202205102039662.png)

<div style="page-break-after: always;"></div>

**结果分析**

定义的滤波器矩阵如上所述。四组图像都进行了平滑、增强处理。



# 5 总结

整个过程是循序渐进的，我从直接调用matlab自带的图像滤波查看滤波效果，到自己实现灰度图滤波，再到实现RGB位图的滤波，每次都多使用一些技术，多学习一点知识。最后用自己写的滤波器对一些喜欢的图片进行了处理，体验很好😆



# 6 附录 源代码

```matlab
clear; clc; close all

image= imread('./.jpg');

% 原图像
subplot(1, 3, 1)
imshow(image)
title('original image')

% -----     下面手动进行空域滤波     -----

% 获取图像大小
[rows, cols, k] = size(image);

% 创建矩阵，用于存储结果
dst_enhancement = zeros(rows, cols, k, 'uint8');
dst_average = zeros(rows, cols, k, 'uint8');

% 对边界像素进行扩展，这里采用的是复制扩展
extension_image = zeros(rows+2, cols+2, k, 'uint8');
for i = 1:k
    extension_image(:,:,i) = padarray(image(:,:,i), [1, 1], 'replicate');    
end

% 定义蒙版矩阵
M_enhance = [0, -1, 0; ...
             -1, 5, -1; ...
             0, -1, 0];
M_average = [1, 1, 1; ...
             1, 1, 1; ...
             1, 1, 1];
         
for i = 1:rows
    for j = 1:cols
        for idx = 1:k
           % 取蒙版矩阵
            Rect = double(extension_image(i:i+2, j:j+2, idx));
            % 增强处理
            dst_enhancement(i, j, idx) = uint8(sum(M_enhance.*Rect, 'all'));
            % 均值滤波
            dst_average(i, j, idx) = uint8(average(M_average.*Rect)); 
        end
    end
end

% 打印图像，进行对比。
subplot(1, 3, 2)
imshow(dst_average)
title('hands on average filter')
subplot(1, 3, 3)
imshow(dst_enhancement)
title('hands on enhancement filter')
```

