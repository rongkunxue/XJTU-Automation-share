#include <reg51.h>
typedef unsigned char uint8;
typedef unsigned int uint16;

sbit K1 = P1^0;
sbit BUZZER = P3^0;

code uint8 SONG_TONE[]=
{
212,212,190,212,159,169,212,212,190,212,142,159,212,212,106,126,129,169,190,119,119,126,159,142,159,0
};
code uint8 SONG_LONG[]=
{
9,3,12,12,12,24,9,3,12,12,12,24,9,3,12,12,12,12,12,9,3,12,12,12,24,0
};

void delay(uint16 x)
{
uint16 i,j;
for(i = x; i > 0; i --)
for(j = 114; j > 0; j --);	
}

void PlayMusic()
{
uint16 i =0,j,k;
while(SONG_LONG[i]!=0||SONG_TONE[i]!=0)
{
for(j=0;j<SONG_LONG[i]*20;j++)
{
BUZZER = ~BUZZER;
for(k=0;k<SONG_TONE[i]/3;k++);
}
delay(10);
i++;
}
}

void main()
{
P1 = 0xFF;
while(1)
{
if(K1==1)
{
PlayMusic();
delay(100);
}
}
}
