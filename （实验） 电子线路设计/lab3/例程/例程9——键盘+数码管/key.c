#include <reg51.h>
typedef unsigned char uint8;
typedef unsigned int uint16;
#define BUZZER() P3 ^= 0x01
code uint8 LED_CODE[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
void delay(uint16 x)
{
uint16 i,j;
for(i = x; i > 0; i --)
for(j = 114; j > 0; j --); 
}
uint8 Pre_KeyNO = 16,KeyNO = 16;
void Keys_Scan()
{
uint8 Tmp;
P1 = 0x0f;
delay(1);
Tmp = P1 ^ 0x0f;//高4位输出，低4位输入
switch(Tmp)
{
case 1: KeyNO = 0; break;
case 2: KeyNO = 1; break;
case 4: KeyNO = 2; break;
case 8: KeyNO = 3; break;
default: KeyNO = 16;
}
P1 = 0xf0;
delay(1);
Tmp = P1 >> 4 ^ 0x0f;//高4位输入，低4位输出
switch(Tmp)
{
case 1: KeyNO += 0; break;
case 2: KeyNO += 4; break;
case 4: KeyNO += 8; break;
case 8: KeyNO += 12;
}
}
void Beep()
{
uint8 i;
for(i=0;i<100;i++)
{
delay(1);BUZZER();
}
}
void main()
{
P0 = 0x00;
while(1)
{
P1 = 0xf0;
if(P1 != 0xf0)
Keys_Scan();
if(Pre_KeyNO != KeyNO)
{
P0 = LED_CODE[KeyNO];
Beep();
Pre_KeyNO = KeyNO;
}
delay(10);
}
}
