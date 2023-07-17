function getmfcc= MFCC3(x,fs)
 %=========================================================
 % 提取MFCC特征参数
 % 无去噪及端点检测
 % Input:音频数据x,采样率fs
 % Output：(N,M)大小的特征参数矩阵  其中N为分帧个数，M为特征维度
 % 特征参数：M=24 倒谱系数12维，一阶差分12维
 %=========================================================
tic
x = double(x);
x = x / max(abs(x));

%常数设置
FrameLen = 256;
FrameInc = 80;

amp1 = 10;
amp2 = 2;
zcr1 = 10;
zcr2 = 5;

maxsilence = 8;  % 8*10ms  = 80ms
minlen  = 15;    % 15*10ms = 150ms
status  = 0;
count   = 0;
silence = 0;


%计算过零率
tmp1  = enframe(x(1:end-1), hamming(FrameLen), FrameInc);%变汉明窗
tmp2  = enframe(x(2:end), hamming(FrameLen), FrameInc);%变汉明窗
signs = (tmp1.*tmp2)<0;
diffs = (tmp1 -tmp2)>0.02;
zcr   = sum(signs.*diffs, 2);

%计算短时能量
amp = sum(abs(enframe(filter([1 -0.9375], 1, x), hamming(FrameLen), FrameInc)), 2);%变汉明窗
%调整能量门限
amp1 = min(amp1, max(amp)/4);
amp2 = min(amp2, max(amp)/8);

%开始端点检测
x1 = 0; 
% x2 = 0;
for n=1:length(zcr)
%    goto = 0;
   switch status
   case {0,1}                   % 0 = 静音, 1 = 可能开始
      if amp(n) > amp1          % 确信进入语音段
         x1 = max(n-count-1,1);
         status  = 2;
         silence = 0;
         count   = count + 1;
      elseif amp(n) > amp2 || ... % 可能处于语音段
             zcr(n) > zcr2
         status = 1;
         count  = count + 1;
      else                       % 静音状态
         status  = 0;
         count   = 0;
      end
   case 2                       % 2 = 语音段
      if amp(n) > amp2 || ...     % 保持在语音段
         zcr(n) > zcr2
         count = count + 1;
      else                       % 语音将结束
         silence = silence+1;
         if silence < maxsilence % 静音还不够长，尚未结束
            count  = count + 1;
         elseif count < minlen   % 语音长度太短，认为是噪声
            status  = 0;
            silence = 0;
            count   = 0;
         else                    % 语音结束
            status  = 3;
         end
      end
   case 3
      break;
   end
end

count = count-silence/2;
x2 = x1 + count -1;

xx=tmp1(x1:x2,:); %截取有效段
%归一化mel滤波器组系数

bank=melbankm(24,256,fs,0,0.5,'m');%Mel滤波器的阶数为24，fft变换的长度为256，采样频率为8000Hz  

bank=full(bank);

bank=bank/max(bank(:));%[24*129]

 %设定DCT系数
 
for k=1:12

n=0:23;

dctcoef(k,:)=cos((2*n+1)*k*pi/(2*24));

end

%归一化倒谱提升窗口

w=1+6*sin(pi*[1:12]./12);

w=w/max(w);



%计算每帧的MFCC参数

for i=1:size(xx,1)

y=xx(i,:);%取一帧数据

s=y'.*hamming(256);

t=abs(fft(s));%fft快速傅立叶变换  幅度谱

t=t.^2; %能量谱

%对fft参数进行mel滤波取对数再计算倒谱
c1=dctcoef*log(bank*t(1:129));%对能量谱滤波及DCT %t(1:129)对一帧的前128个数（帧移为128）

c2=c1.*w';%归一化倒谱

%mfcc参数

m(i,:)=c2';

end

%求取一阶差分系数

dtm=zeros(size(m));

for i=3:size(m,1)-2

dtm(i,:)=-2*m(i-2,:)-m(i-1,:)+m(i+1,:)+2*m(i+2,:);

end

dtm=dtm/3;
%求取二阶差分系数

dtm2=zeros(size(dtm));

for i=3:size(dtm,1)-2

dtm2(i,:)=-2*dtm(i-2,:)-dtm(i-1,:)+dtm(i+1,:)+2*dtm(i+2,:);

end

dtm2=dtm2/3;

%合并mfcc参数和一阶差分mfcc参数

ccc=[m dtm dtm2];

%去除首尾两帧，因为这两帧的一阶差分参数为0
ccc=ccc(3:size(m,1)-2,:);

getmfcc=ccc;%返回特征值
%'MFCC特征参数提取时长'
toc

% subplot(2,1,1)
% plot(ccc(100,:));
% hold on
% plot(ccc(200,:),'r');
% plot(ccc(300,:),'g');
% plot(ccc(400,:),'y');
% plot(ccc(500,:),'b');
% xlabel('维数');
% ylabel('幅值');
% title('帧数100->500');
% subplot(2,1,2)
% plot(ccc(:,1));
% hold on
% plot(ccc(:,2),'r');
% plot(ccc(:,3),'g');
% plot(ccc(:,5),'y');
% plot(ccc(:,7),'b');
% xlabel('帧数');
% ylabel('幅值');
% title('维数1->7')

% subplot(2,1,1)
% ccc_1=ccc(:,1);
% plot(ccc_1);title('MFCC');ylabel('幅值');
% [h,w]=size(ccc);
% A=size(ccc);
% subplot(212) 
% plot([1,w],A);
% xlabel('维数');
% ylabel('幅值');
% title('维数与幅值的关系')
end