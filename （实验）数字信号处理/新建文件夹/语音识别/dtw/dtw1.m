function [dis,D]=dtw1(A)
    [hang,lie]=size(A);
    Test=zeros(hang,lie);
    D=zeros(hang,lie);
    D(1,1)=A(1,1);
    Test(1,1)=2;
    while (D(hang,lie)==0)
        Test=avail(Test,hang,lie);
        [r,c]=find(Test==1);
        for(i=1:length(r))
            if(r(i)==1)
                D(r(i),c(i))=D(r(i),c(i)-1)+A(r(i),c(i));
                Test(r(i),c(i))=2;
            end
            if(c(i)==1)
                D(r(i),c(i))=D(r(i)-1,c(i))+A(r(i),c(i));
                Test(r(i),c(i))=2;
            end
            if(r(i)>1&&c(i)>1)
                %d=min(D(r(i)-1,c(i)),D(r(i),c(i)-1),D(r(i)-1,c(i)-1));
                x0=D(r(i)-1,c(i));
                x1=D(r(i),c(i)-1);
                x2=D(r(i)-1,c(i)-1);
                d=min([x0,x1,x2]);
                D(r(i),c(i))=d+A(r(i),c(i));
                Test(r(i),c(i))=2;
            end
        end
    end
    dis=D(hang,lie);
end
    
        
    