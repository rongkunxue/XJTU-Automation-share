function D=shen(x1,x2)
% x1=rand(400,16);
% x2=rand(300,16);
[r1,c1]=size(x1);
[r2,c2]=size(x2);

x1s=sum(x1.^2,2);
x1s=repmat(x1s,1,r2);
x2s=sum(x2.^2,2);
x2s=repmat(x2s',r1,1);
xc=x1*x2';

D=x1s+x2s-2*xc;
D=sqrt(D);
end
% D0=zeros(r1,r2);
% for(i=1:r1)
%     for(j=1:r2)
%         D0(i,j)=sum((x1(i,:)-x2(j,:)).^2);
%     end
% end
% D0=sqrt(D0);