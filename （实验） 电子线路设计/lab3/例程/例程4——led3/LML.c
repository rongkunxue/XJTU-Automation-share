#include<reg51.h>
#define uchar unsigned char
void delay()
{
uchar a,b;
for(a=500;a;a--)
{
for(b=500;b;b--);
}
}
void main()
{
uchar tmp=1;
while(1)
{
P0=(~tmp);
delay();
tmp<<=1;
if(tmp==0)//移到最高位要重新置1
{
tmp=1;
}
}
}
