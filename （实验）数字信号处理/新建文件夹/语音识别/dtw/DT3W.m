function [d,Testout]=DTW(A,x,y,Testin)
    if (Testin(x,y)~=0)
        d=Testin(x,y);
        Testout=Testin;
    end
    if (x==1&&y==1)
        d=A(x,y);
        Testout(x,y)=d;
    end
    if(x==1||y==1)
        if(x==1)
            [d0,~]=DTW(A,x,y-1,Testin);
            d=A(x,y)+d0;
            Testout(x,y)=d;
        end
        if(y==1)
            [d0,~]=DTW(A,x-1,y,Testin);
            d=A(x,y)+d0;                                        
            Testout(x,y)=d;
        end
    end
    if(x>1&&y>1)
        [d1,~]=DTW(A,x-1,y,Testin);
        [d2,~]=DTW(A,x-1,y,Testin);
        [d3,~]=DTW(A,x-1,y,Testin);
        d0=min(d1,d2,d3);
        d=A(x,y)+d0;
        Testout(x,y)=d;
    end
end

    
    