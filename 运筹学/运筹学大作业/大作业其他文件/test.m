oursolution=getRevemnue(X,J,Q,R,T,y,cbar)
revemnue=[];
for i=1:X
    for j=i:X
        y=[i,j];
        a=getRevemnue(X,J,Q,R,T,y,cbar);
        revemnue=[revemnue,a];
    end
end
best=max(revemnue)
function revenue = getRevemnue(X,J,Q,R,T,Y,cbar)
    revenue = 0.0;
    m=length(X);
    gradX=zeros(m,1);%m未定义
    gradY=zeros(m,cbar);%cbar未定义
    min_space=zeros(T,1);
    u=zeros(T,1);
    for t=1:T
        MIN=inf;
        j=J(t);
        q=Q(t);
        i = 1;
        if j>1
            tmp=X(i)- Y(i,j-1);
        else
            tmp=X(i);
        end
        if( tmp<MIN)
            if(tmp>=0)
                MIN=tmp;
            else
                MIN=0;
            end
            min_space(t)=MIN;
            u(t)=min(q,MIN);
            X(i)=X(i)-u(t);
        end
    end
    
    for t = 1 : T
       j = J(t);
        revenue = revenue + u(t) * R(j) ;
    end
end