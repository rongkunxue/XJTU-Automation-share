tic
load character.mat;
k=audioread('E:\大三上\（实验）数字信号处理\第一次\语音库2\7\7-36.wav');
cc=Mfcc1(k);
for k=1:100
% k=56;
    ref(1).mfcc=s(k).num0;
    ref(2).mfcc=s(k).num1;
    ref(3).mfcc=s(k).num2;
    ref(4).mfcc=s(k).num3;
    ref(5).mfcc=s(k).num4;
    ref(6).mfcc=s(k).num5;
    ref(7).mfcc=s(k).num6;
    ref(8).mfcc=s(k).num7;
    ref(9).mfcc=s(k).num8;
    ref(10).mfcc=s(k).num9;
    for i=1:10
        dist(i) = dtw1(cc, ref(i).mfcc);  
    end
    [d,j] = min(dist);
%     result=j-1
    result(k)=j-1;
end
toc