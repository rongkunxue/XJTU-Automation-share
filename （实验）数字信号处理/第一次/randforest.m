train_data = xlsread('Character.xls','sheet1','A1:E200') ;
train_label = xlsread('Character.xls','sheet1','F1:F200') ;
test_data = xlsread('Character.xls','sheet1','A201:E210') ;
test_label = xlsread('Character.xls','sheet1','F201:F210') ;

% 随机森林分类器（Random Forest）

nTree = 5
result=zeros(100,1);
for j=1:100
    B = TreeBagger(nTree,train_data,train_label);
    predict_label = predict(B,test_data);
    for i=1:10
        if ischar(predict_label{i,1})
                predict_label{i,1}=str2num(predict_label{i,1});
        end
    end
    m=0;
    for i=1:10
        if predict_label{i,1}==test_label(i,1)
            m=m+1;
        end
    end
    result(j)=m/10;
end
results=mean(result)
 