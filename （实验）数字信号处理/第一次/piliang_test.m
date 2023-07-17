path='E:\大三上\（实验）数字信号处理\第一次\语音库\';
filename=dir([path,'1\*.wav']);
Character=zeros(10,6);
% for j=1:14
    for i=1:size(filename)
        x=audioread(['E:\大三上\（实验）数字信号处理\第一次\语音库\1\',filename(i).name]);
%         Character(end+1)=[vad(x),i];
        Character(i,:)=vad(x);
    end
% end
Character
%matlabroot,'\toolbox\voicebox;', ...