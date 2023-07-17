function j=shibie(cc)
% load character1.mat;
% dist=zeros(10,1);
% for k=1:10
%     for i=1:18
%         j=randi(100);
%         dist(k) = dist(k)+dtw1(cc, p{k,j});
%     end
% end
% [~,j] = min(dist);
% j=j-1;
% end
load character24_plus.mat;
true=0;
sample=20;
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
    [~,j]=max(number);
    j=j-1;
end