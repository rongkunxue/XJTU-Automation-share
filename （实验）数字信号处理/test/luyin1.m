function [k,fs] = luyin1()
% 录音录2秒钟
recObj = audiorecorder(44100, 16 ,1);
disp('Start speaking.')
recordblocking(recObj, 2);
disp('End of Recording.');
myRecording = getaudiodata(recObj);
%存储语音信号
filename = 'D:\大三上\（实验）数字信号处理\test\test.wav'; 
audiowrite(filename,myRecording,44100);
[k,fs]=audioread(filename);
end