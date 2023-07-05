#include<reg51.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
void Initiallize_LCD();//
void ShowString(uchar x,uchar y,uchar *str);
uchar code Display[32]="0123456789abcdef 123456789abcdef";

 //字符要用双引号括起来，空格也算-一个字符，共32个字符(0~31)。

 void main()
{
 Initiallize_LCD();
 ShowString(0,0,Display); //从第一个符幵始湿示
 ShowString(0,1,Display+16);//第ニ行从第17个字符写起，0是第一个字符
 while(1);
}
 
