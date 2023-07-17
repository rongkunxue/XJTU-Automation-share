tic
load character3.mat;
true=0;
% for m=1:100
    num=round(rand*9);
    k=audioread(['E:\大三上\（实验）数字信号处理\第一次\语音库\6\',int2str(num),'.wav']);
    cc=Mfcc1(k);
    dist=ones(10,1)*realmax;
    update=zeros(10,1);
    for k=1:10
        for i=1:18
            j=randi(100);
            small = min(dist(k),dtw1(cc, p{k,j}));
            if small<dist(k)
                dist(k)=small;
                update(k)=update(k)+1;
            end
        end
    end
    final=1./dist.*update;
        [~,j] = max(final);
        j=j-1;
        if j==num
            true=true+1;
        end

function target = KNN(trainData, trainlabel, testData,k)
classlabel = unique(trainlabel);%得到样本标签(有哪几种标签)
c= length(classlabel); %得到标签个数(共几类标签)
n= size(trainData, 1); %得到训练样本个数
dist = zeros(n,1); %存储一个测武样本与所有训练样本的距离
for j=1:size(testData,1); %遍历则试集中的每一个样本
    cnt = zeros(c,1);%存储前k个点所在类别出现的频率(个数)
    for i=1:n %遍历训练集中的每一个点
        t=trainData{i};
        r=testData{j};
        dist(i)=DTW(t,r); %计算一个测试点与所有冰陈数据距离。
    end
    [d,index] = sort(dist); %递增排序d排序过后的值index为d中相对应值在原dist中的索引
    for i=1:k
        ind = find(classlabel == trainlabel(index(i))); %返回前k个点所在类别对应的标签返回的ind值为1
        cnt(ind) = cnt(ind)+1;%标签出现一次相对应的cnt位置加1.相当于计算前k个点所在类出现的频率
    end
end
end

%主函数获取target
% trainData= (trainData)';
% testData=(testData)';
% trainlabel=(trainlabel)';
% target = KNN(trainData, trainlabel, testData, 15):
total=sum(testlabel ==target);
totalrate = total/ length(target);
totalstrOut = ['识别率为'，num2str(totalrate*100), '%']
for i=1:10
    left=80*(i-1)+1;
    right=80*i;
    correct(i)=sum(testlabel (1,left:right)==target(1,left:right));
    rate(i) = correct(i)/ 80;
    strOut=[' 语音数字',num2str(i),'识别率为',num2str(rate(i)*100),'%']
end

% end
% result=true/100
toc