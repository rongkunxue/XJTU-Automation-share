clear;
train_lable=zeros(700,1); 
practise_lable=zeros(300,1); 
predict_lable=zeros(300,1);
word=[{'zero'};{'one'};{'two'};{'three'};{'four'};{'five'};{'six'};{'seven'};{'eight'};{'nine'}];

% for j=1:70
%     for i=0:9
%         train_lable(10*(j-1)+i+1)=i;
%     end
% end
for j=1:70
    for i=0:9
        [VX0,Fs]=audioread(['C:\Users\Administrator\Desktop\”Ô“Ù2\±ﬂ≤ﬂ\',num2str(i),'\',word{i+1},num2str(j),'.wav']);
        VX=VX0(:,1);
        MC(10*(j-1)+i+1).juzhen=mfccshen(VX);
        train_lable(10*(j-1)+i+1)=i;
    end
end
for j=71:100
    for i=0:9
        [VX0,Fs]=audioread(['C:\Users\Administrator\Desktop\”Ô“Ù2\±ﬂ≤ﬂ\',num2str(i),'\',word{i+1},num2str(j),'.wav']);
        VX=VX0(:,1);
        practise=mfccshen(VX);
        place=BNN(MC,practise);
        practise_lable(10*(j-71)+i+1)=i;
        predict_lable(10*(j-71)+i+1)=train_lable(place);
    end
end
        
        
        