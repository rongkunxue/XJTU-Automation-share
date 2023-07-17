function Test=avail(Test,hang,lie)
    for(i=1:hang)
        for(j=1:lie)
            
            if(Test(i,lie)==2)
                break;
            end
            if(Test(i,j)==0)
                if(i==1&&Test(i,j-1)==2)
                    Test(i,j)=1;
                    break;
                end
            
                if(j==1&&Test(i-1,j)==2)
                    Test(i,j)=1;
                    break;
                end
            
                if(Test(i-1,j)==2&&Test(i,j-1)==2&&Test(i-1,j-1)==2)
                    Test(i,j)=1;
                    break;
                end
            end
        end
    end
end

                    
                