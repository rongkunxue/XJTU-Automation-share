clear
%%%%%%%%这里给参数%%%%%%%%
t=0.02;%每一帧所对的时间20ms
Ww=t*44100;
Ww=240;%窗函数宽度882
%Nw=4999;%时窗移动数220500=441*4999.333+294
step=2*Ww/3;
step=80;%窗函数前进步数588,也就是说每一帧有294重复
%%%%%%%%%%%%%%%%%%%%%%%%%%
Tezheng1=[];%存能量
Tezheng2=[];%存过零率
zhenshu=[];
lable=zeros(1000,1);
    
    
    word=[{'zero'};{'one'};{'two'};{'three'};{'four'};{'five'};{'six'};{'seven'};{'eight'};{'nine'}];
   
for j=1:20
    for i=0:9
        [VX0,Fs]=audioread(['C:\Users\15pr\Desktop\语音识别\边策\',num2str(i),'\',word{i+1},num2str(j),'.wav']);
        VX=VX0(:,1);
        N=length(VX);%新文件的字符长度
        fps=ceil((N-160)/80);
        fps=fps-2;%可取的帧数
        zhenshu=[zhenshu,fps];
        lable((j-1)*10+i+1)=i;
    end
end
fpsmax=max(zhenshu);
fpsmin=min(zhenshu);
fpsmid=(fpsmax+fpsmin)/2;
fpsmid=ceil(fpsmid);
fpsmid=600;
for j=1:20
    for i=0:9
        [VX0,Fs]=audioread(['C:\Users\15pr\Desktop\语音识别\边策\',num2str(i),'\',word{i+1},num2str(j),'.wav']);
        VX=VX0(:,1);
        ZZZ=(j-1)*10+i+1;
        XXX=zhenshu(ZZZ);
        [E,Z,E1]=tiqu2(VX,fpsmid,XXX);
        % Z=Z/abs(max(Z));
        Tezheng1=[Tezheng1;E];
        Tezheng2=[Tezheng2;Z];
        %Tezheng1和2分别是每一个样本的特征向量为行的特征矩阵
    end
end

        







train_label=zeros(160,1);% 列向量
practise_label=zeros(40,1);

train_data0=zeros(160,fpsmid);% 矩阵，每行一个样本，每列一个特征
practise_data0=zeros(40,fpsmid);
train_data1=zeros(160,fpsmid);
practise_data1=zeros(40,fpsmid);
for i=1:1:160
    if(zhenshu(i)>=fpsmid)
        for j=1:1:fpsmid
            train_data0(i,j)=Tezheng1(i,j);
            train_data1(i,j)=Tezheng2(i,j);
        end
    else 
        for j=1:1:zhenshu(i)
            train_data0(i,j)=Tezheng1(i,j);
            train_data1(i,j)=Tezheng2(i,j);
        end
    end
    train_label(i)=lable(i);
end
for i=1:1:40
    if(zhenshu(i+160)>=fpsmid)
        for j=1:1:fpsmid
            practise_data0(i,j)=Tezheng1(i+160,j);
            practise_data1(i,j)=Tezheng2(i+160,j);
        end
    else 
        for j=1:1:zhenshu(i+160)
            practise_data0(i,j)=Tezheng1(i+160,j);
            practise_data1(i,j)=Tezheng2(i+160,j);
        end
    end
    practise_label(i)=lable(i+160);
end
%Z

train_data=[train_data1 train_data0];
practise_data=[practise_data1 practise_data0];
%{  
K近邻分类器 （KNN）
Factor = ClassificationKNN.fit(train_data, train_label, 'NumNeighbors', 10);
predict_label   =       predict(Factor, practise_data);
accuracy         =       length(find(predict_label == practise_label))/length(practise_label)*100
               
 
随机森林分类器（Random Forest）
B = TreeBagger(nTree,train_data0,train_label);
predict_label = predict(B,test_data);
 
 
朴素贝叶斯 （Na?ve Bayes）
nb = NaiveBayes.fit(train_data0, train_label);
predict_label   =       predict(nb, practise_data0);
accuracy         =       length(find(predict_label == practise_label))/length(practise_label)*100;
 
 
集成学习方法（Ensembles for Boosting, Bagging, or Random Subspace）
ens = fitensemble(train_data,train_label,'AdaBoostM1' ,100,'tree','type','classification');
predict_label   =       predict(ens, test_data);
 
 
鉴别分析分类器（discriminant analysis classifier）
obj = ClassificationDiscriminant.fit(train_data, train_label);
predict_label   =       predict(obj, practise_data);
accuracy=length(find(predict_label ==practise_label))/length(practise_label)*100;

 
 

%}  

            
    
