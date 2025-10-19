%实验4.1
% clc;clear all;
% s=tf('s');
% H=50/(s+1)/(s+5)/(s-2);
% figure(1);
% nyquist(H)
% G=feedback(H,1,-1)
% if(isstable(G))%判断稳定性
%     disp("传递函数稳定")
% else
%     disp("传递函数不稳定")
% end
% t=[0:0.1:10];
% figure(2);
% impulse(G,t)
%实验4.2
clc,clear
s=tf('s');
Px=50;%设定一个上界裕度
for K=40:0.01:50%根据幅频特性确定K的大致范围
    Gs=K*(s+1)/(s+2)/(s^2+4*s+5);
    [Gm,Pm,Wcg,Wcp] = margin(Gs);
    if (abs(Pm-45)<abs(Px-45))&&(Pm>45)%差分代替导数
        Kx=K;
        Px=Pm;
    end
end

