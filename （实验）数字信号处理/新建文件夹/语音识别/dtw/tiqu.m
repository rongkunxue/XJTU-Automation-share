function[E,E1,Z]=tiqu(VX,mid,fpsl)
%%%%%%%%这里给参数%%%%%%%%
t=0.02;%每一帧所对的时间20ms
Ww=t*44100;%窗函数宽度882
%Nw=4999;%时窗移动数220500=441*4999.333+294
step=2*Ww/3;%窗函数前进步数588,也就是说每一帧有294重复
%%%%%%%%%%%%%%%%%%%%%%%%%%

    data=zeros(Ww,fpsl);%每一列为一帧的数据，Ww=882,fps为最大帧数
    E=zeros(1,mid);
    E1=zeros(1,mid);
    Z=zeros(1,mid);%根据帧数建立能量和过零率数组并初始化,行向量
    for j=1:1:min(fpsl,mid) %这个循环是分帧，并对每一帧求E和Z
        for i=1:1:Ww
            %data(i,j)=VX(i+(j-1)*step)*w;
            data(i,j)=VX(i+(j-1)*step);
            E(j)=data(i,j)^2+E(j);
            E1(j)=abs(data(i,j))+E1(j);
            if(i==Ww)
                break
            end 
            Z(j)=Z(j)+abs(sign(data(i,j))-sign(data(i+1,j)))/2;
        end
        %在这里E(j) and Z(j)分别为该段语音每帧的能量和平均过零率
    end
    E1=E1/max(E1);