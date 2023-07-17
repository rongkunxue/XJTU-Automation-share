function lable=BNN(struct,practise,train_lable)
d=zeros(700,1);
place=zeros(10,1);
for i=1:700
    d(i)=dtw2(struct(i).juzhen,practise);
end
for j=1:10
[~,where]=min(d);
place(j)=where;
d(where)=realmax;
end
lable=findmaxnum(place,train_lable);
end