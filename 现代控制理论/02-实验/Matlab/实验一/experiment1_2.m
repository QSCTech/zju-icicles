%实验2.1.1
%clc,clear
% s=tf('s');
% wn=6;
% H=@(zeta) wn^2/(s^2+2*zeta*wn*s+wn^2);
% figure(1);
% hold on;
% for i=0.1:0.1:2
%     step(H(i))
% end
% hold off;
%实验2.1.2
% clc;clear;
% s=tf('s');
% zeta=0.7;
% H=@(wn)wn^2/(s^2+2*zeta*wn*s+wn^2);
% figure(2);
% hold on;
% for i=2:2:12
%     step(H(i));
% end
% hold off;
%实验2.2
clc;clear;
s=tf('s');
G=1/(s^2+s+1);
wn=1;
zeta=1/(2*wn);%计算zetaζ
step(G)%画出阶跃响应图像
%上升时间
fai=atan(sqrt(1-zeta^2)/zeta);
Tr=(pi-fai)/wn/sqrt(1-zeta^2);
%超调量
oi=exp(-zeta*pi/sqrt(1-zeta^2));
%峰值时间
wd=wn*sqrt(1-zeta^2);
Tp=pi/wd;
%稳态时间(5%误差)
Ts=-log(0.05*sqrt(1-zeta^2))/wn/zeta;
fprintf("上升时间：%fs\n",Tr);
fprintf("超调量：%f%%\n",oi*100);
fprintf("峰值时间：%fs\n",Tp);
fprintf("稳态时间：%fs\n",Ts);