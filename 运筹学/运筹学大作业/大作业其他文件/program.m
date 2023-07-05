% N 迭代次数
% gradY[i,c]对y的偏导
cbar = 2;
X = 300;
need_temp=xlsread("needs3.xlsx");
Q = need_temp(:, 2);
J = need_temp(:, 3);
R = [1900 1000 300];
[T,~] = size(need_temp);
%y = zeros(1,cbar); %initial solution
y=[1,2];
k = 0;
N = 1000;
step = 0;
grand_space=[];
for k = 1 : N
    step = 1*1/k;
   % gradY = zeros(1,cbar);
    gradY = getgrads(X,J,Q,R,T,y,cbar,1);
    grand_space=[grand_space gradY'];
    temp = y +  step * gradY;
    H = [2 0; 0 2];
    f = [0 0];
    A = [1 -1];
    b=temp(1,2)-temp(1,1);
    lb = - temp';
    ub = [170 170]'+lb;
    temp_noninteger = quadprog(H, f, A, b, [], [], lb, ub)';
    temp_noninteger=temp_noninteger+temp;
    y = ceil(temp_noninteger);
end
%getRevemnue(X,J,Q,R,T,y,cbar)
function gradY = getgrads(X,J,Q,R,T,Y,cbar,max)
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
    MIN=inf;
    j=J(t);
    q=Q(t);
    n=1;%%/* compute minimum remaining capacity for j /*
    i=GetNextRes(j,n,max);%n未定义
    while(i~=-1)
        if j>1
            tmp=X(i)- Y(i,j-1);
        else
            tmp=X(i);
        end
        if(tmp<MIN)
           if(tmp>=0)
               MIN=tmp;
           else
               MIN=0;
           end
       end
       n=n+1;
       i=GetNextRes(j,n,max);
    end
       min_space(t)=MIN;
       u(t)=min(q,MIN);
       n=1;
       i=GetNextRes(j,n,max);
       while(i~=-1)
           X(i)=X(i)-u(t);
           n=n+1;
           i=GetNextRes(j,n,max);
       end
end
for t=T:-1:1
    j=J(t);
    q=Q(t);
    if t>1
        MIN=min_space(t-1)-min_space(t);
    else
        MIN=min_space(t);
    end
    MIN2=min_space(t);
    SUM=0;
    n=1;
    i=GetNextRes(j,n,max);
    while(i~=-1)
        X(i)=X(i)+u(t);
        SUM=SUM+gradX(i);
        n=n+1;
        i=GetNextRes(j,n,max);
    end
    if((0<MIN2)&&(MIN2<=q))
        n=1;
        i=GetNextRes(j,n,max);
        while(i~=-1)
            if j>1
                tmp=X(i)- Y(i,j-1);
            else
                tmp=X(i);
            end
            if(tmp==MIN2)
                c=J(n);
                gradX(i)=gradX(i)+R(j)-SUM;
                for c=1:j-1
                    if(X(i)-Y(i,c)==MIN2)
                        gradY(i,c)=gradY(i,c)-R(j)+SUM;
                    end
                end
            end
            n=n+1;
            i=GetNextRes(j,n,max);
        end
    end
end
end
function out=GetNextRes(j,n,max)%%简单写法
if(n<=max)
    out=1;
else
    out=-1;
end
end