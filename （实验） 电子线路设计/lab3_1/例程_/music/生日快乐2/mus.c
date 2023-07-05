#include<reg52.h>
#define   uint   unsigned int
#define   uchar  unsigned char
sbit      speaker=P1^0; //学校给的学习板次了点，用两个I/O口控制蜂鸣器。不过大多数的学习板是一个I/O口控制。
//sbit      speaker1=P1^1; //如果你的板是一个I/O控制的，这行可以删掉。
uint k,i;
unsigned char timer0h,timer0l,time;
        //生日歌
code unsigned char sszymmh[]={
         5,1,1, 5,1,1, 6,1,2, 5,1,2, 1,2,2, 7,1,4,
         5,1,1, 5,1,1, 6,1,2, 5,1,2, 2,2,2, 1,2,4,
         5,1,1, 5,1,1, 5,2,2, 3,2,2, 1,2,2, 7,1,2, 6,1,2,
         4,2,1, 4,2,1, 3,2,2, 1,2,2, 2,2,2, 1,2,4};
       // 音阶频率表 高八位
code unsigned char FREQH[]={
        0xF2,0xF3,0xF5,0xF5,0xF6,0xF7,0xF8,
        0xF9,0xF9,0xFA,0xFA,0xFB,0xFB,0xFC,0xFC, //1,2,3,4,5,6,7,8,i
        0xFC,0xFD,0xFD,0xFD,0xFD,0xFE,
        0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,
                            } ;// 音阶频率表 低八位
code unsigned char FREQL[]={
      0x42,0xC1,0x17,0xB6,0xD0,0xD1,0xB6,
      0x21,0xE1,0x8C,0xD8,0x68,0xE9,0x5B,0x8F, //1,2,3,4,5,6,7,8,i
      0xEE,0x44, 0x6B,0xB4,0xF4,0x2D,
      0x47,0x77,0xA2,0xB6,0xDA,0xFA,0x16,
                            };
void delay(unsigned char t)
   {
   unsigned char t1;
   unsigned long t2;
   for(t1=0;t1<t;t1++)
   {
    for(t2=0;t2<8000;t2++)
       {
        ;
        }
   }
   TR0=0;
 }
void t0int() interrupt 1
{
 TR0=0;
 speaker=!speaker;
 TH0=timer0h;
 TL0=timer0l;
 TR0=1;
 }
void song()
{
 TH0=timer0h;
 TL0=timer0l;
 TR0=1;
 delay(time);                      
 }
 void main(void)
 {
speaker=0; //一个I/O控制的话这行也要删掉
 //unsigned int k,i;
 TMOD=1; //置CT0定时工作方式1
 EA=1;
 ET0=1;//IE=0x82 //CPU开中断,CT0开中断
 while(1)
    {
       i=0; 
       while(i<75)
    {         //音乐数组长度 ，唱完从头再来       
       k=sszymmh[i]+7*sszymmh[i+1]-1;
       timer0h=FREQH[k];
       timer0l=FREQL[k];
       time=sszymmh[i+2];
       i=i+3;
       song();
        }
    }
  }