function [y]=fir_hpf(x,Fs,As,fp,fs)
%该函数采用kaiser窗设计高通滤波器Kaiser窗是一种最优化窗，它的优化准则是:对于有限的信号能量，要求确定一个有限时宽的信号波形，它使得频宽内的能量为最大。
%也就是说，Kaiser窗的频带内能量主要集中在主瓣中，它有最好的旁瓣抑制性能。
%输入：
% x 输入信号
% Fs 采样频率
% As 阻带最小衰减
% fp通带截止频率 fs阻带截止频率（单位Hz）

%设定各种参数
b=fp-fs; 	 % 求取过渡带
M0=round((As-7.95)/(14.36*b/Fs))+2; 	% 计算窗长
M=M0+mod(M0+1,2);	% 保证窗长为奇数
wp=2*fp/Fs*pi; ws=2*fs/Fs*pi; 	
wc=(wp+ws)/2; 	% 求截止频率


%求kaiser窗的系数beta的值
if As>50
	beta=0.1102*(As-8.7);
    elseif As>=21&&As<=50
	beta=0.5842*(As-21)^0.4+0.07886*(As-21);
	else
	beta=0;
end




%设定滤波器参数
N=M-1; %设定滤波器阶数
hd=fir1(N,wc,'high',kaiser(M,beta));


%滤波
x=x-mean(x); % 消除直流分量

y=filter(hd,1,x);
