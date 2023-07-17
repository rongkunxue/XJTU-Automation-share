path='E:\大三上\（实验）数字信号处理\第一次\语音库\';     %语音库存储路径，根据自己的修改即可
samplenum=14;     %实验样本数（每个样本包括0~9 10个录音）

Character=zeros(samplenum*10,7); 
%样本参数矩阵，7列若干行，其中每列代表的参数为：
%[
%短时能量最大值，短时能量最小值，短时能量平均值，
%短时过零点数最大值，短时过零点数最小值，短时过零点数平均值，样本标签（0~9）
%]

for j=1:samplenum
    filename=dir([path,int2str(j),'\*.wav']);
    for i=1:size(filename)
        x=audioread([path,int2str(j),'\',filename(i).name]);
        Character((j-1)*10+i,:)=[vad(x),i-1];
    end
end
Character
%PS：我发现短时过零点数最小值都是0，就是说语音段里面总有一帧没有过零点，分类时可以删去降维？
% for j=0:9
%     filename=dir([path,int2str(j),'\*.wav']);
%     s=0; %计行数变量
%     for i=1:size(filename)
%         x=audioread([path,int2str(j),'\',filename(i).name]);
%         for j=1:size(itemchara,1)
%             Character(j*samplenum+i,:)=[vad(x),i];
%     end
%     fname=['Character2.xls'];
%     xlswrite(fname,Character);
% end