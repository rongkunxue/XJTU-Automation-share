function num=findmaxnum(place,train_lable)
b = 0:9;
a = train_lable(place);
c = histc(a,b)
[max_num, max_index] = max(c)
num = b(max_index);
end
