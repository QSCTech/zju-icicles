
[toc]



<div style="page-break-after: always;"></div>

# 1 实验任务

本次实验选择的题目为 Proj10-02，具体实现的任务如下：

1. 设计一个全局阈值处理程序，复现课本第十章第三节中的全局阈值处理操作，将灰度图输出为一个二值图像。
2. 下载合适的图片进行实验。

# 2 算法设计

我们要设计的是自动估计阈值的算法，使用迭代以达到目的。算法如下

1. 为全局阈值T选择一个初始估计值
2. 通过下式用T分割图像，产生两组像素：G1由灰度值大于T的所有像素组成，G2由所有灰度值小于等于T的像素组成。

$$
g(x,y) = 
\begin{cases}
 1& f(x,y)\gt T\\
0& f(x,y)\leq T
\end{cases}
$$

3. 对G1和G2的像素分别计算灰度均值m1和m2
4. 计算得到一个新的阈值T
5. 迭代2-4，直到T小于ΔT。



# 3 代码实现

编程环境：Matlab

这里我设定了迭代停止条件为T<T0=0.001

**主要代码**

```matlab
I = im2double(I); 
[M,N] = size(I);
T0 = 0.001;         
T1 = (max(max(I)) +min(min(I)))/2;   
columns1 = 1;
columns2 = 1;
while 1
    for i = 1:M
        for j = 1:N
            if I(i,j)>T1
                G1(columns1) = I(i,j);  
                columns1 = columns1 + 1;
            else
                G2(columns2) = I(i,j); 
                columns2 = columns2 + 1;
            end
        end
    end
    ave1 = mean(G1);
    ave2 = mean(G2);
    T2 = (ave1 + ave2)/2;  
    if abs(T2 - T1)<T0        
        break;
    end
    T1 = T2;
    columns1 = 1;
    columns2 = 1;
end
level = T2;
end

```



# 4 实验结果

**结果分析**

选取了三组灰度图进行实验，查看效果。

第一组

![image-20220512114541907](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202205121147022.png)



第二组

![image-20220512114637108](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202205121147024.png)

第三组

![image-20220512114734702](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202205121147025.png)



对于以上三张灰度图，可见经过全局阈值处理后，图片自动化处理为了二值化黑白图像。

# 5 总结

本次实验我对灰度图像的阈值处理操作进行了实验练习，实现了对不同灰度图像的阈值自动化计算，并且输出为二值图。



# 6 附录 源代码

```matlab
% main.m
clc;clear;close all;
I =imread('dentalXray.tif');
level =global_threshold(I);           
J = im2bw(I,level);    
subplot(121)
imshow(I);
title('original image');
subplot(122)
imshow(J);
title('after global threshold');
```



```matlab
% global_threshold.m
function level =global_threshold(I)

I = im2double(I);          %对图像归一化
[M,N] = size(I);
T0 = 0.001;         
T1 = (max(max(I)) +min(min(I)))/2;   
columns1 = 1;
columns2 = 1;
while 1
    for i = 1:M
        for j = 1:N
            if I(i,j)>T1
                G1(columns1) = I(i,j);  
                columns1 = columns1 + 1;
            else
                G2(columns2) = I(i,j); 
                columns2 = columns2 + 1;
            end
        end
    end
    ave1 = mean(G1);
    ave2 = mean(G2);
    T2 = (ave1 + ave2)/2;  
    if abs(T2 - T1)<T0        
        break;
    end
    T1 = T2;
    columns1 = 1;
    columns2 = 1;
end
level = T2;
end

```

