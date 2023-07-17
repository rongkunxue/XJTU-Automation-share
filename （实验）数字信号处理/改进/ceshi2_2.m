tic
load character100_24.mat;
true=0;
sample=20;
formnum=100;
mistake=zeros(10);
for m=1:20
    for n=0:9
        [k,fs]=audioread(['D:\大三上\（实验）数字信号处理\第一次\语音库\',int2str(m),'\',int2str(n),'.wav']);
        cc=MFCC2(k,fs);
        for o=1:5
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
%         number=mean(dist,2);
            for i=1:10
            number(i)=min(dist(i,:));
            end
            [~,j]=min(number);
            j=j-1;
            if j==n
                true=true+1;
            else
                mistake(n+1,j+1)=mistake(n+1,j+1)+1;
            end
            fprintf('真实值为%d，识别为%d\n',n,j);
        end
    end
end

result=true/1000
toc