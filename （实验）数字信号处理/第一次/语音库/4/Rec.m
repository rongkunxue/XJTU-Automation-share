clc;
clear;
rec0 = audiorecorder(44100,16,1);
disp('Start speaking.')
recordblocking(rec0,4);
disp('End of Recording.')
play(rec0);
myRecording = getaudiodata(rec0);
plot(myRecording);
filename = 'C:\Users\iair\Desktop\”Ô“Ùø‚\sound0_wu.wav';
audiowrite(filename,myRecording,44100)