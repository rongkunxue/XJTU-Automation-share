path='E:\大三上\（实验）数字信号处理\第一次\语音库2\';     %语音库存储路径，根据自己的修改即可
samplenum=100;     %实验样本数（每个样本包括0~9 10个录音）

%Character=zeros(samplenum*10,6); 
%样本参数矩阵，16列若干行，其中前15列代表mfcc特征参数，最后一列用以区分不同的语音文件：

for j=0:9
    filename=dir([path,int2str(j),'\*.wav']);
    s=0; %计行数变量
    for i=1:samplenum
        x=audioread([path,int2str(j),'\',filename(i).name]);
        itemchara=Mfcc(x);
        for k=1:size(itemchara,1)
            Character(s+k,:)=[itemchara(k,:),i];
        end
        s=s+size(itemchara,1);
    end
    fname=['MFCC',num2str(j), '.xls'];
    xlswrite(fname,Character);
    clear Character
end

