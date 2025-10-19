%实验6.1
% clc;clear all;
% A=[-2 ,-3 ; 4 ,-9];
% b=[3 ; 1];
% p=[-1+2i;-1-2i];
% rankMc=rank(ctrb(A,b)) %判断是否可控
% %直接法
% x1=poly(A); %系统特征多项式系数
% x2=poly(diag(p)); %目标特征多项式系数
% T=ctrb(A,b)*[x1(2) 1 ; 1 0];
% Kc=[x2(3)-x1(3) x2(2)-x1(2)];
% K=Kc*inv(T)
%  %MATLAB函数法
% K=acker(A,b,p) 
%实验6.2
clc;clear all;
A=[1, 0 ,0 ; 0, 2, 1 ; 0 ,0 ,2];
b=[1 ; 0 ; 1];
c=[1 1 0];
d=0;
sys=ss(A,b,c,d);
p=[-3 ; -4 ; -5];
a1=A';
b1=c';
rankMo=rank(obsv(A,c)) %判断是否可观
%直接法
x1=poly(A); %系统特征多项式系数
x2=poly(diag([-3,-4,-5])); %目标特征多项式系数
T=inv([x1(3) x1(2) 1 ; x1(2) 1 0 ; 1 0 0]*obsv(A,c));%求出T逆
h=T*[x2(4)-x1(4) ; x2(3)-x1(3) ; x2(2)-x1(2)];%状态观测增益向量
A_HC=A-h*c
B_HD=b-h*d
H=h
%函数法
K=acker(a1,b1,p); %增益矩阵
est=estim(sys,K')