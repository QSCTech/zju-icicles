
[toc]



<div style="page-break-after: always;"></div>

# 1 实验任务

本次实验选择的题目为 Proj09-01，具体实现的任务如下：

1. 设计一个能够对图像进行形态学处理（腐蚀、膨胀）的程序

2. 设计程序进行集合的交、并、补基本操作

   



# 2 算法设计

算法原理如下

**腐蚀**
$$
A \oplus B=\{z|(\hat B)_z \cap A \neq\emptyset \}
$$
**膨胀**
$$
A \ominus B=\{ z|(B)_z \subseteq A\}
$$

1. 在A对应的图像中取B原点，找到其符合SE的像素
2. 遍历所有A的像素，输出结果

**集合运算**

使用矩阵的按位逻辑运算实现



# 3 代码实现

编程环境：Matlab

**主要代码**

**腐蚀**

```matlab
function im_N=ImageErode(im,B)
    [m,n]=size(im);
    zero_ac=zeros(m,1);
    zero_ar=zeros(1,n+2);
    im1=[zero_ar;[zero_ac,im,zero_ac];zero_ar];
    im_N=zeros(m,n);
    for i=2:m+1
        for j=2:n+1
            N_zero=find([im1(i-1,j-1) im1(i-1,j) im1(i-1,j+1) im1(i,j-1) im1(i,j) im1(i,j+1) im1(i+1,j-1) im1(i+1,j) im1(i+1,j+1)]);
            if size(N_zero,2)==9
                im_N(i-1,j-1)=1;
        end
    end
end
```

**膨胀**

```matlab
function im_N=ImageDilation(im,B)
    [m,n]=size(im);
    zero_ac=zeros(m,1);
    zero_ar=zeros(1,n+2);
    im1=[zero_ar;[zero_ac,im,zero_ac];zero_ar];
    im_N=zeros(m,n);
    for i=2:m+1
        for j=2:n+1
            N_zero=find([im1(i-1,j-1) im1(i-1,j) im1(i-1,j+1) im1(i,j-1) im1(i,j) im1(i,j+1) im1(i+1,j-1) im1(i+1,j) im1(i+1,j+1)]);
            if size(N_zero,2)>0
                im_N(i-1,j-1)=1;
        end
    end
end
```

**位运算**

```matlab
im_inter = im_1 & im_2;

im_differ = im_1 & ~im_2;

im_complete = ~im_1;
```



# 4 实验结果

原始数据

分别选取以下两张图片为A，B进行实验，然后交换得到B，A进行实验。

![image-20220422205526692](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202204222056654.png)![image-20220422205543832](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202204222056656.png)

**形态学操作**

第一组

![image-20220422205247002](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202204222056657.png)

第二组

![image-20220422205327678](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202204222056658.png)

**位运算**

第一组

![image-20220422205357767](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202204222056659.png)

第二组

![image-20220422205431963](https://raw.githubusercontent.com/Jack-Chan-2001/clouding/main/image/202204222056660.png)

<div style="page-break-after: always;"></div>

**结果分析**

每种操作均进行了两组实验，符合图像形态学操作和图像集合操作。



# 5 总结

本次实验对形态学基本操作（腐蚀、膨胀）进行了实现，也对二值图像的集合运算进行了实现。不过选取的图像数据比较大，导致形态学操作不是很明显，但是放大观察还是可以看出腐蚀和膨胀操作的。集合运算的效果则比较明显。



# 6 附录 源代码

main.m

```matlab
clear;close all;clc;

B=ones(3,3);

im_1=imread('1.tif');
im_2=imread('2.tif');

figure()
subplot(131);
imshow(im_1);
title('original')

im_N1=ImageDilation(im_1,B);
subplot(132);
imshow(im_N1);
title('dilate')

im_N2=ImageErosion(im_1,B);
subplot(133);
imshow(im_N2);
title('erode')

figure()
im_inter = im_1 & im_2;
subplot(131);
imshow(im_inter);
title('inter')

im_differ = im_1 & ~im_2;
subplot(132);
imshow(im_differ);
title('differencing')

im_complete = ~im_1;
subplot(133);
imshow(im_complete);
title('completment')
```

ImageDilation.m

```matlab
function im_N=ImageDilation(im,B)
    [m,n]=size(im);
    zero_ac=zeros(m,1);
    zero_ar=zeros(1,n+2);
    im1=[zero_ar;[zero_ac,im,zero_ac];zero_ar];
    im_N=zeros(m,n);
    for i=2:m+1
        for j=2:n+1
            N_zero=find([im1(i-1,j-1) im1(i-1,j) im1(i-1,j+1) im1(i,j-1) im1(i,j) im1(i,j+1) im1(i+1,j-1) im1(i+1,j) im1(i+1,j+1)]);
            if size(N_zero,2)>0
                im_N(i-1,j-1)=1;
        end
    end
end
```

ImageErosion.m

```
function im_N=ImageErode(im,B)
    [m,n]=size(im);
    zero_ac=zeros(m,1);
    zero_ar=zeros(1,n+2);
    im1=[zero_ar;[zero_ac,im,zero_ac];zero_ar];
    im_N=zeros(m,n);
    for i=2:m+1
        for j=2:n+1
            N_zero=find([im1(i-1,j-1) im1(i-1,j) im1(i-1,j+1) im1(i,j-1) im1(i,j) im1(i,j+1) im1(i+1,j-1) im1(i+1,j) im1(i+1,j+1)]);
            if size(N_zero,2)==9
                im_N(i-1,j-1)=1;
        end
    end
end
```

