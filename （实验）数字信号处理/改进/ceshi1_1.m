tic
load character100_24.mat;
true=0;
sample=20;
formnum=100;
for m=1:100
    num=round(rand*9);
    [k,fs]=audioread(['D:\大三上\（实验）数字信号处理\改进\test\',int2str(num),'.wav']);
    cc=MFCC2(k,fs);
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
%     for i=1:10
%         average(i,1)=mean(dist(i,:));
%     end
%     for i=1:10
%         variance(i,1)=var(dist(i,:));
%         cut=0;
%         for j=1:sample
%             if abs(dist(i,j)-average(i,1))>variance(i,1)
%                 dist(i,j)=0;
%                 cut=cut+1;
%             end
%         end
%         average(i,1)=sum(dist(i,:))/(sample-cut);
%         for j=1:sample
%             equal(j)=~isequal(dist(i,j),0);
%         end
%         variance(i,1)=sum((average(i,:)-dist(1,:)).^2.*equal)/(sample-cut);
%     end
    for i=1:10
        minum(i,1)=min(dist(i,:));
    end
%     final=0.2*average+0.9*minum+0.1*variance;
%     [~,j]=min(final);
    [~,j]=min(minum);
    j=j-1;
    if j==num
        true=true+1;
    end
    fprintf('真实值为%d，识别为%d\n',num,j);
end

result=true/100
toc