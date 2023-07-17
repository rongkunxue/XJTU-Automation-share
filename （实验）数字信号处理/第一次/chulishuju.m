a=x9;
for j=1:100
    m=1;
    for i=1:length(a)
        if a(i,16)==j
            b(m,:)=a(i,1:15);
            m=m+1;
        end
        s(j).num9=b(1:m-1,:);
    end
end
    