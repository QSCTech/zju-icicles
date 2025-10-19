%实验5
clc;clear all;
N=100;
b=0.632;
a=[1 -1.368 0.568];
t=0:0.1:6;%持续时间6s，采样周期0.1s
x=square(pi*t);%生成方波
y=dlsim(b,a,x);%离散系统响应
stem(t,x,'red')
hold on;
stem(t,y,'blue')