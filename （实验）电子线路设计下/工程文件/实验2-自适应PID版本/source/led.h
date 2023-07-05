#ifndef LED_H
#define LED_H

#include "c8051f020.h"
#include "lcd.h"

extern unsigned int Time_num;
extern void display(int a);
extern void select(int b);
extern void Led_Port_Init();
extern void LedInit();
extern void LedDispNum();
void my_LedDispNum(unsigned int num1,unsigned int num2,unsigned int num3);

#endif
