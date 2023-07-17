path='E:\大三上\（实验）数字信号处理\第一次\语音库2\';     %语音库存储路径，根据自己的修改即可

%Character=zeros(samplenum*10,6); 
%样本参数矩阵，16列若干行，其中前15列代表mfcc特征参数，最后一列用以区分不同的语音文件：

for j=0:9
    filename=dir([path,int2str(j),'\*.wav']);
    for i=1:100
        [x,fs]=audioread([path,int2str(j),'\',filename(i).name]);
        itemchara=MFCC4(x);
        Character{j+1,i}=itemchara;
    end
end

