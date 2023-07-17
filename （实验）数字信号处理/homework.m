n=zeros(1,1024);
x=linspace(0,1,512);
% for i=1:54
%     n(i)=-sin(0.6*pi*(i-27))/(pi*(i-27))*(0.42-0.5*cos(i*pi/27)+0.08*cos(2*i*pi/27));
% end
% n(27)=0.4;
for i=1:32
    n(i)=sin(0.3*pi*(i-16))/(pi*(i-16))*(0.54-0.46*cos(i*pi/16));
end
n(16)=0.3;
N=fft(n);
A=abs(N);
fai=angle(N);
A=20*log(A);
subplot(2,1,1);
plot(x,A(1:512));
title('∑˘∆µœÏ”¶');
subplot(2,1,2);
plot(x,fai(1:512));
title('œ‡∆µœÏ”¶');
