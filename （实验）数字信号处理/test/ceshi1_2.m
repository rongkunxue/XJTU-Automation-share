tic
load character24_plus.mat;
true=0;
sample=20;
for m=1:100
    num=round(rand*9);
    [k,fs]=audioread(['D:\大三上\（实验）数字信号处理\改进\test\',int2str(num),'.wav']);
    cc=MFCC2(k,fs);
    dist=ones(10,sample)*realmax;
    for k=1:10
        for i=1:sample
            j=randi(20);
            dist(k,i)=dtw1(cc, Character{k,j});
            while isnan(dist(k,i))
                j=randi(20);
                dist(k,i)=dtw1(cc, Character{k,j});
            end
        end
    end
number=zeros(10,1);
for i=1:10
    for j=1:20
        if dist(i,j)<2e+05
            number(i)=number(i)+1;
        end
    end
end
%     for i=1:10
%         minum(i,1)=1/min(dist(i,:));
%     end
%     minum=(minum-min(minum))/(max(minum)-min(minum));
%     number=(number-min(number))/(max(number)-min(number));
%     final=0.5*minum+0.5*number;
    [~,j]=max(number);
    j=j-1;
    if j==num
        true=true+1;
    end
    fprintf('真实值为%d，识别为%d\n',num,j);
end

result=true/100
toc