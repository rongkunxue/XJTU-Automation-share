function dist = dtw1(t, r)
n = size(t,1);
m = size(r,1);
% Ö¡Æ¥Åä¾àÀë¾ØÕó
d = zeros(n,m);
for i = 1:n
    for j = 1:m
        d(i,j) = sum((t(i,:)-r(j,:)).^2);
    end
end
% ÀÛ»ı¾àÀë¾ØÕó
D = ones(n,m) *realmax;
for i=1:n
    for j=1:m
        if i==1&&j==1
            D(i,j)=d(1,1);
            D1=0;
            D2=0;
            D3=0;
        end
        if i==1&&j>1
            D1=D(i,j-1);
            D2=realmax;
            D3=realmax;
        end
        if j==1&&i>1
            D1=D(i-1,j);
            D2=realmax;
            D3=realmax;
        end
        if i>1&&j>1
            D1=D(i-1,j);
            D2=D(i,j-1);
            D3=D(i-1,j-1);
        end
        D(i,j)=d(i,j)+min([D1,D2,D3]);
    end
end
dist = D(n,m);
end