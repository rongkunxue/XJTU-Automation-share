function [gradX,gradY] = getgrads(X,J,Q,R,T,Y,cbar)
% input definitions
%x[i]= remaining capacity on resource i (modified by program)
%j[t]= product requested by customer t on sample path
%q[t]= quantity requested by customer t on sample path
%r[j]= revenue generated per unit sold of product j
%T = total number of customer requests
%y[i,c] = protection level for class c on resource i. We assume y[i,0]=0
%min_space[t] = minimum remaining capacity for customer t
%u[t] = quantity accepted for customer t
%gradX[i] = sample path subgradient with respect to x
%gradY[i,c] = sample path subgradient with respect to y
%cbar 保护级别个数
m=length(X);
gradX=zeros(m,1);%m未定义
gradY=zeros(m,cbar);%cbar未定义
min_space=zeros(T,1);
u=zeros(T,1);
for t=1:T
    MIN=INF;
    j=J(t);
    q=Q(t);
    n=1;%%/* compute minimum remaining capacity for j /*
    i=GetNextRes(j,n);%n未定义
    while(i~=-1)
       if(X(i)-Y(i,c(i,j)-1)<MIN)
           if(X(i)-Y(i,c(i,j)-1)>=0)
               MIN=X(i)-Y(i,c(i,j)-1);
           else
               MIN=0;
           end
       end
       n=n+1;
       i=GetNextRes(j,n);
    end
       min_space(t)=MIN;
       u(t)=min(q,MIN);
       n=1;
       i=GetNextRes(j,n);
       while(i~=-1)
           X(i)=X(i)-u(t);
           n=n+1;
           i=GetNextRes(j,n);
       end
end
for t=T:-1:1
    j=J(t);
    q=Q(t);
    MIN=min_space(t);
    SUM=0;
    n=1;
    i=GetNextRes(j,n);
    while(i~=-1)
        X(i)=X(i)+u(t);
        SUM=SUM+gradX(i);
        n=n+1;
        i=GetNextRes(j,n);
    end
    if((0<MIN)&&(MIN<=q))
        n=1;
        i=GetNextRes(j,n);
        while(i~=-1)
            if(X(i)-Y(i,c(i,j)-1)==MIN)
                gradX(i)=gradX(i)+R(j)-SUM;
                for a=1:c(i,j)-1
                    if(X(i)-Y(i,c)==MIN)
                        gradY(i,c)=gradY(i,c)-R(j)+SUM;
                    end
                end
            end
            i=GetNextRes(j,n);
        end
    end
end
end
function out=GetNextRes(j,n,max)
if(n<=max)
    out=1;
else
    out=-1;
end
end
