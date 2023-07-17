function [E,Z,N]=tiqu2(VX,mid,fpsl,framelenth,frameinc)
%VX=VX/max(VX);
VX= mapminmax(VX, -1, 1);
[E0,Z0,N0]=tiqu1(VX,framelenth,frameinc);
E=zeros(1,mid);
Z=zeros(1,mid);
N=zeros(1,mid);
if fpsl>=mid
    E(1:mid)=E0(1:mid);
    Z(1:mid)=Z0(1:mid);
    N(1:mid)=N0(1:mid);
else
    E(1:fpsl)=E0(1:fpsl);
    Z(1:fpsl)=Z0(1:fpsl);
    N(1:fpsl)=N0(1:fpsl);
end
E = mapminmax(E, 0, 1);
Z= mapminmax(Z, 0, 1);
 N= mapminmax(N, 0, 1);
end