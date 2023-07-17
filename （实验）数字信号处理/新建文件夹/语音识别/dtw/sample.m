clear
[VX,Fs]=audioread('1.wav');
% audiowrite(filename,y,Fs);
%%这里我的wav因为是手机上录的是双声道有两行后面有一个分行的命令这里你们改一下
t=1/Fs;%采样时间

%%%%%%%%这里给参数%%%%%%%%
Ww=1200;%窗函数宽度
Nw=4000;%时窗移动数
step=900;%窗函数前进步数
%%%%%%%%%%%%%%%%%%%%%%%%%%

T=(Nw-1)*step+Ww;%总取样点数
w=ones(Ww,1);%窗函数

VX=[VX;zeros(Nw-step,2)];
VX1=VX(:,1);
VX2=VX(:,2);
XF1=zeros(size(VX1));
XF2=zeros(size(VX1));
if T>=length(VX1)
    VX1=[VX1;zeros(T-length(VX1),1)];
else
    VX1=VX1(1:T);
end
X1=zeros(Ww,Nw);
for i=1:Nw
    X1(:,i)=VX1((i-1)*step+1:(i-1)*step+Ww);
end

%%%%%%X1为结果 一列是一帧%%%%%%

