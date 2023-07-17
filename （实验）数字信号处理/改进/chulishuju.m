a=xlsread('E:\大三上\（实验）数字信号处理\改进\Character_MFCC9.xls');
for j=1:100
    m=1;
    for i=1:length(a)
        if a(i,46)==j
            b(m,:)=a(i,1:45);
            m=m+1;
        end
        s(j).num9=b(1:m-1,:);
    end
end
    