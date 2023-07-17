tic
load character1024.mat;
true=0;
% true2=0;
sample=20;
formnum=100;
for m=1:100
    num=round(rand*9);
    [k,fs]=audioread(['E:\大三上\（实验）数字信号处理\改进\test\',int2str(num),'.wav']);
    cc=MFCC4(k);
    dist=ones(10,sample)*realmax;
    for k=1:10
        for i=1:sample
            j=randi(formnum);
            dist(k,i)=dtw1(cc, Character{k,j});
            while isnan(dist(k,i))
                j=randi(formnum);
                dist(k,i)=dtw1(cc, Character{k,j});
            end
        end
    end
 
for i=1:10
number(i)=min(dist(i,:));
end
    [~,j]=min(number);
    j=j-1;
    if j==num
        true=true+1;
    end
    fprintf('真实值为%d，最小值法识别为%d\n',num,j);
%     average=mean(dist,2);
%     [~,i]=min(average);
%     i=i-1;
%     if i==num
%         true2=true2+1;
%     end
%     fprintf('真实值为%d，平均值法识别为%d\n',num,j);
end

result=true/100
% result2=true2/100
toc