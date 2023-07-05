function f=conjugate_grad_2d(x0,t)
%用共轭梯度法求已知函数f(x1,x2)=x1^2+2*x2^2-4*x1-2*x1*x2的极值点?
%已知初始点坐标：x0?
%已知收敛精度：t?
%求得已知函数的极值：f?
x=x0;
syms xi yi a; %定义自变量，步长为符号变量?
f=xi^2+2*yi^2-4*xi-2*xi*yi; %创建符号表达式f?
fx=diff(f,xi); %求表达式f对xi的一阶求导
fy=diff(f,yi); %求表达式f对yi的一阶求导?
fx=subs(fx,{xi,yi},x0); %代入初始点坐标计算对xi的一阶求导实值
fy=subs(fy,{xi,yi},x0); %代入初始点坐标计算对yi的一阶求导实值?
fi=[fx,fy]; %初始点梯度向量
count=0; %搜索次数初始为0?
while double(sqrt(fx^2+fy^2))>t %搜索精度不满足已知条件
    s=-fi; %第一次搜索的方向为负梯度方向?????
    if count<=0
        s=-fi;
    else
        s=s1;
    end
    x=x+a*s; %进行一次搜索后的点坐标?
    f=subs(f,{xi,yi},x); %构造一元搜索的一元函数φ(a)?????
    f1=diff(f); %对函数φ(a)进行求导
    f1=solve(f1); %得到最佳步长a?????
    if f1~=0 
        ai=double(f1); %强制转换数据类型为双精度数值?????
    else
        break %若a=0，则直接跳出循环，此点即为极值点?????
    end
    x=subs(x,a,ai);%得到一次搜索后的坐标值
    f=xi^2+2*yi^2-4*xi-2*xi*yi;
    fxi=diff(f,xi);
    fyi=diff(f,yi);
    fxi=subs(fxi,{xi,yi},x);
    fyi=subs(fyi,{xi,yi},x);
    fii=[fxi,fyi];%下一点梯度向量
    d=(fxi^2+fyi^2)/(fx^2+fy^2);
    s1=-fii+d*s;%下一点搜索的方向向量
    count=count+1;%搜索次数加一
    fx=fxi;
    fy=fyi;%搜索后终点坐标变为下一次搜索的始点坐标
end
x,f=subs(f,{xi,yi},x),count %输出极值点，极小值及搜索次数
    