clc;clear;
% 实验3.1
% s=tf('s');
% G=10*(s^2+8*s+20)/(s*(s+4));
% H=0.2/(s+2);
% rlocus(G*H);
% sgrid();
% sgrid(0.565,5);
% [A]=rlocfind(G*H)
% Gs=feedback(G*A,H,-1);
% [z,p,k]=tf2zp(Gs.num{1,1},Gs.den{1,1});%求零极点
% Gs=zpk(z,p,k)%零极点模型
%实验3.2
s=tf('s');
G=(s^2+6*s+13)/s/(s+3);
H=1/(s+1);
rlocus(G*H);
Mp=1.0948;
z=-log(Mp-1)/sqrt(pi*pi+(log(Mp-1))^2)
%根据二阶系统Mp公式反解出ζ，且ζ为正值
sgrid(z,5);%画出ζ线
[K1]=rlocfind(G*H)%第一个交点增益
Gs1=feedback(G*K1,H,-1);
[z,p,k]=tf2zp(Gs1.num{1,1},Gs1.den{1,1});%求零极点
Gs1=zpk(z,p,k)%零极点模型
[K2]=rlocfind(G*H)%第二个交点增益
Gs2=feedback(G*K2,H,-1);
[z,p,k]=tf2zp(Gs2.num{1,1},Gs2.den{1,1});%求零极点
Gs2=zpk(z,p,k)%零极点模型