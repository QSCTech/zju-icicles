[toc]



<div style="page-break-after: always;"></div>

# 1 实验任务

本次实验选择的题目为 Proj05-02，具体要求如下：

- 将前置实验 `Proj 03-03` 中的滤波器修改为 `3 X 3` 的中值滤波器
- 选取图片，进行加噪，增加特定的椒盐噪声
- 对加噪后的图片进行中值滤波处理，进行图像恢复，解释结果。





# 2 算法设计

椒盐噪声的生成直接使用 matlab 内置的 API  `imnoise(I, 'salt & papper') `来实现，设置其噪声密度为0.2.

中值滤波器的设计公式如下
$$
\hat{f}(x,y)=median_{(s,t)\in S_{xy}}\{g(s,t)\}
$$
选取一个 `3 X 3` 的蒙版矩阵作为邻域后，选取其中的中值作为目标图像的像素结果。同时因为我选取的图片是彩色的，R，G，B三个色道都需要作这样的处理。



# 3 代码实现

编程环境：Matlab

**主要代码和注释**

- median_filter.m

```matlab
function dst_median = median_filter(image) % 彩色图像中值滤波器

% 获取图像大小
[rows, cols, k] = size(image);

% 创建矩阵，用于存储结果
dst_median = zeros(rows, cols, k, 'uint8');

% 对边界像素进行扩展
extension_image = zeros(rows+2, cols+2, k, 'uint8');
for i = 1:k
    extension_image(:,:,i) = padarray(image(:,:,i), [1, 1]);    
end

for i = 1:rows
    for j = 1:cols
        for idx = 1:k
            % 取蒙版矩阵
            Rect = double(extension_image(i:i+2, j:j+2, idx));
            % 中值滤波
            dst_median(i, j, idx) = uint8(median(Rect, 'all')); 
        end
    end
end

end
```



# 4 实验结果



三张图依次为：

1. 原图像
2. 加噪后图像（椒盐噪声）
3. 恢复后图像

一共进行了 4 组实验，每一组中，第一列是原数据，第二列是加噪数据，第三列是恢复数据。

<div style="page-break-after: always;"></div>

* **第一组**

![](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121930521.png)

- **第二组**

![](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202204071109342.png)

- **第三组**

![](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121930522.png)

- **第四组**

![](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202206121930523.png)

<div style="page-break-after: always;"></div>

**结果分析**

可以看到的是，总体上中值滤波器对椒盐噪声的滤除效果是非常好的，基本上能够恢复地很不错，不过有时还留下了少量噪点



# 5 总结

本次实验我对一些喜欢的图片进行了加噪处理和中值滤波恢复，通过实验验证了中值滤波器对于椒盐噪声的比较不错的恢复效果。

同时也是对我上一次实验的一个延申，因为其中的子函数模块是改自第一次实验的空域滤波器的。这种基于原来实验进行其他实验工作的感觉也很棒。



# 6 附录 源代码

- 主函数

```matlab
clear; clc; close all

image= imread('./1.jpg');

% 原图像
subplot(1, 3, 1)
imshow(image)
title('original image')

% 加噪图像
image_noise = imnoise(image, 'salt & pepper', 0.2);
subplot(1, 3, 2)
imshow(image_noise)
title('image with salt & papper noise')

% 恢复图像
image_filtered = median_filter(image_noise);
subplot(1, 3, 3)
imshow(image_filtered)
title('image after median filter')
```

- 子函数

```matlab
function dst_median = median_filter(image) % 彩色图中值滤波器

% 获取图像大小
[rows, cols, k] = size(image);

% 创建矩阵，用于存储结果
dst_median = zeros(rows, cols, k, 'uint8');

% 对边界像素进行扩展
extension_image = zeros(rows+2, cols+2, k, 'uint8');
for i = 1:k
    extension_image(:,:,i) = padarray(image(:,:,i), [1, 1]);    
end

for i = 1:rows
    for j = 1:cols
        for idx = 1:k
            % 取蒙版矩阵
            Rect = double(extension_image(i:i+2, j:j+2, idx));
            % 中值滤波
            dst_median(i, j, idx) = uint8(median(Rect, 'all')); 
        end
    end
end

end
```

