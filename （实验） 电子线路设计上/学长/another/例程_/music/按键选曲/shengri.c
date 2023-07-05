#include <reg51.h>
typedef unsigned char uint8;
typedef unsigned int uint16;

sbit K1 = P1^0;
sbit K2 = P1^1;
sbit K3 = P1^2;
sbit K4 = P1^3;
sbit BUZZER = P3^0;
code uint8 SONG_TONE1[]=
{
212,212,190,212,159,169,212,212,190,212,142,159,212,212,106,126,129,169,190,119,119,126,159,142,159,0
};
code uint8 SONG_LONG1[]=
{
9,3,12,12,12,24,9,3,12,12,12,24,9,3,12,12,12,12,12,9,3,12,12,12,24,0
};
void delay(uint16 x)
{
uint16 i,j;
for(i = x; i > 0; i --)
for(j = 114; j > 0; j --);	
}
 void PlayMusic1()
{
uint16 i =0,j,k;
while(SONG_LONG1[i]!=0||SONG_TONE1[i]!=0)
{
for(j=0;j<SONG_LONG1[i]*20;j++)
{
BUZZER = ~BUZZER;
for(k=0;k<SONG_TONE1[i]/3;k++);
}
delay(10);
i++;
}
}
void Play(uint8 t)
{
uint8 i;
for(i = 0; i < 100; i ++)
{
BUZZER = ~BUZZER;delay(t);
}
}

void main()
{
P1 = 0xFF;
while(1)
{
if(K1==0) PlayMusic1();
if(K2==0) Play(1);
if(K3==0) Play(2);
if(K4==0) Play(3);
}
}


