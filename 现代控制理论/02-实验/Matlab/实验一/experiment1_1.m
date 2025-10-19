clc;clear;
%实验1.1
% A=[-2.8,-1.4,0,0;1.4,0,0,0;-1.8,-0.3,-1.4,-0.6;0,0,0.6,0];
% B=[1,0,1,0]';
% C=[0,0,0,1];
% D=0;
% [b,a]=ss2tf(A,B,C,D);%状态空间模型转化为传递函数，得到分子分母系数
% G=tf(b,a)            %进而表示出传递函数
% [z,p,k]=zpkdata(G);  %求出零极点
% G1=zpk(z,p,k)        %绘制零极点模型
% if(isstable(G1))
%     disp('该系统稳定');
% else
%     disp('该系统不稳定');
% end
%实验1.2
s=tf('s');
G1=1/(s+1);
G2=1/(s+2);
G3=1/(s+3);
G4=1/(s+4);
G5=1/(s+5);
G24=feedback(G2,series(G3,G4),-1);%G3后的引出点左移
G1245=feedback(series(G1,G24),G5,1);
G=feedback(series(G1245,G3),1,-1)

