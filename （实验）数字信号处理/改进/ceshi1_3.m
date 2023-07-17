tic
load character100_24.mat;
true=0;
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
%     dist2=dist(:);
%     medianm=median(dist2);
average=mean(mean(dist));
    number=zeros(10,1);
    for i=1:10
        for j=1:20
            if dist(i,j)<average
                number(i)=number(i)+1;
            end
        end
    end
    [~,j]=max(number);
    j=j-1;
    if j==num
        true=true+1;
    end
%     fprintf('真实值为%d，识别为%d\n',num,j);
end

result=true/100
toc