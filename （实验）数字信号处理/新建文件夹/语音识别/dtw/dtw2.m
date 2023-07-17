function dis=dtw2(x1,x2)
    A=shen(x1,x2);
    [hang,lie]=size(A);
    D0=ones(hang,lie)*realmax;
    
    D0(1,1)=A(1,1);
%     for(j=2:lie)
%         D0(1,j)=D0(1,j-1)+A(1,j);
  
    for(i=1:hang)
        for(j=1:lie)
            if((j-i)<=60)||((i-j)>=60)
                if(i==1&&j==1)
                    continue
                end
                if(i==1&&j~=1)
                    x1=realmax;
                    x2=realmax;
                    x3=D0(i,j-1);
                end
                if(i~=1)
                    x1=D0(i-1,j);
                    if(j>1)
                        x2=D0(i-1,j-1);
                        x3=D0(i,j-1);
                    else
                        x2=realmax;
                        x3=realmax;
                    end
                end
                D0(i,j)=A(i,j)+min([x1,x2,x3]);
            end
        end
    end
    dis=D0(hang,lie);
end
