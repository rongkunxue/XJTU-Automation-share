function [E,Z,N]=tiqu1(x,framelenth,frameinc)
tmp1 = enframe(x(1:end-1),hamming(framelenth,'periodic'),frameinc);
tmp2 = enframe(x(2:end),hamming(framelenth,'periodic'),frameinc);
%tmp1 = enframe(x(1:end-1),600,200);
%tmp2 = enframe(x(2:end),600,200);
signs = (tmp1.*tmp2)<0;
diffs = (tmp1 - tmp2)>1e-6;
Z = sum(signs.*diffs,2);
% filter([1 -0.9375],1,x)
E = sum(abs(enframe(x,hamming(framelenth,'periodic'),frameinc)),2);
X=enframe(x,hamming(framelenth,'periodic'),frameinc);
%E = sum(abs(enframe(x,600,200)),2);
%X=enframe(x,600,200);
X=X.*X;
N=sum(X,2);
end