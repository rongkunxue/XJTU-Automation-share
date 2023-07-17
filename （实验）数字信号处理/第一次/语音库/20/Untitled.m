% 运行平台：Windows 7 64bit，MATLAB R2014a
% 录音录2秒钟
recObj = audiorecorder(44100,16,1);
disp('Start speaking.')
recordblocking(recObj, 2);
disp('End of Recording.');
% 回放录音数据
play(recObj);
% 获取录音数据
myRecording = getaudiodata(recObj);
% 绘制录音数据波形
plot(myRecording);
%存储语音信号
filename = 'E:\wcrsb\data9.wav';
audiowrite(filename,myRecording,44100);




