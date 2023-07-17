x=audioread('E:\大三上\（实验）数字信号处理\第一次\语音库2\0\0-12.wav');
%幅度归一化到[-1,1]
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

%  MFCC特征提取
M=24;              %Mel滤波器组数
fs=8000;           %采样率8000Hz
fh=fs/2;
fl=0;              %Mel滤波器最高、最低频率
tmp=tmp1(x1:x2,:); %截取有效段
TMP=fft(tmp);      %快速傅里叶变换（可替换为自己编写的函数）
E=abs(TMP).^2;     %计算每帧数据谱线的能量
f=zeros(M+1,1);    %Mel滤波器中心频率
N=fix(x2-x1+1);         %语音段数
nmax=15;           %MFCC系数的阶数
for m=1:M+1
    f(m,1)=N/fs*Fmel_(Fmel(fl)+m*(Fmel(fh)-Fmel(fl))/(M+1));
end
S=zeros(N,M);          %Mel滤波器能量
for i=1:N              
    x=0;
    for k=1:floor(f(1))
        x=x+E(i,k)*(k-0)/(f(1)-0);
    end
    for k=floor(f(1))+1:floor(f(2))
        x=x+E(i,k)*(f(2)-k)/(f(2)-f(1));
    end
    S(i,1)=x;
    for m=2:M
        x=0;
        for k=floor(f(m-1))+1:floor(f(m))
            x=x+E(i,k)*(k-f(m-1))/(f(m)-f(m-1));
        end
        for k=floor(f(m))+1:floor(f(m+1))
            x=x+E(i,k)*(f(m+1)-k)/(f(m+1)-f(m));
        end
        S(i,m)=x;
    end
end
mfcc=zeros(N,nmax);
for i=1:N
    for n=1:nmax
        x=0;
        for m=1:M
            x=x+log(S(i,m))*cos(pi*n*(2*m-1)/(2*M));
        mfcc(i,n)=sqrt(2/M)*x;
        end
    end
end
function x=Fmel(f)
x=1125*log(1+f/700);
end
function x=Fmel_(f)
x=700*(exp(f/1125)-1);
end