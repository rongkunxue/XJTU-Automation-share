#ifndef LCD_H
#define LCD_H

#include "c8051f020.h"
#include <intrins.h>
#include <stdio.h>

extern volatile int wave[128];
void Lcd_Port_Init(void);
void LcdInit(void);


void SendByte(uchar Dbyte);
uchar ReceiveByte(void);
void CheckBusy(void);

void WriteData(uchar WDLCM);
void WriteCommand (uchar Cbyte);

void LineClear(uchar l);
void LcdClear( void );

void WriteChar(uchar row,uchar col,uchar ch);
void WriteStr(uchar row,uchar col,uchar *puts);

void ImageShow(uchar *imagePtr);
void LcdShowPoint(unsigned char x);
// void dot_display(uchar x,uchar y);

#endif
