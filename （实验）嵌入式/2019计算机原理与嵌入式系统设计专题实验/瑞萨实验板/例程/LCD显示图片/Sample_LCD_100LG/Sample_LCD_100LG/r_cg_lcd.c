/***********************************************************************************************************************
 * File Name    : r_cg_lcd.c
 * Version      : RL78/G13 V 0.01 1503 [23 Jan 2015]
 * Device(s)    : R5F100LG
 * Tool-Chain   : CA78K0R
 * Description  : This file implements main function.
 * Company Name : Getsoon Electronic Co.Ltd , Shanghai.China
 * Creation Date: 2015-1-23
 ***********************************************************************************************************************/

#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
#include "r_cg_lcd.h"


#define DBUS_BITS 8


#define LCD_EH()  			(P14.1 = 1)
#define LCD_EL()  			(P14.1 = 0)

#define LCD_RWH()   		(P14.7 = 1)
#define LCD_RWL()   		(P14.7 = 0)

#define LCD_RSH()   		(P14.6 = 1)
#define LCD_RSL()   		(P14.6 = 0)


#define LCD_RESTH()   		(P3.0 = 1)
#define LCD_RESTL()   		(P3.0 = 0)

#define BACKLIGHT_ON()  	(P13.0 = 1)
#define BACKLIGHT_OFF() 	(P13.0 = 0)

#if DBUS_BITS == 4
#define LCD_WDATA() 		(P2 = data)
#else
#define LCD_WDATA() 		(P2 = data)
#endif

#define GET_DB2()     		(P2.7)

#define DB2_PIN_OUT()     	(PM2 = 0x00)

#define DB2_PIN_IN()      	(PM2 = 0xff)

#define LCD_REST_OUT()      PM3&=~0x01

int XJTU_image[512] = { /* 0X00,0X01,0X40,0X00,0X40,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0XE3,0XC3,0X00,0X00,0X00,0X00,0X00,0X01,0XE1,0XC3,0X80,0X00,0X00,
0X00,0X00,0X01,0XE3,0XC7,0X80,0X00,0X00,0X00,0X00,0X70,0XFF,0XFF,0X8E,0X00,0X00,
0X00,0X00,0XFB,0XFF,0XFF,0XCF,0X00,0X00,0X00,0X00,0X7F,0XE0,0X07,0XFE,0X00,0X00,
0X00,0X00,0X3F,0X00,0X00,0XFE,0X00,0X00,0X00,0X08,0X7C,0X00,0X00,0X1E,0X10,0X00,
0X00,0X1D,0XF0,0X00,0X00,0X0F,0XB8,0X00,0X00,0X3F,0XC0,0X00,0X00,0X03,0XFC,0X00,
0X00,0X1F,0X80,0X00,0XC0,0X01,0XF8,0X00,0X00,0X0F,0X00,0X00,0XD8,0X00,0XF0,0X00,
0X01,0X1E,0X00,0X05,0XD8,0X00,0X70,0X00,0X01,0XDC,0X03,0XFD,0XDE,0X00,0X3B,0X80,
0X03,0XF8,0X02,0X00,0XDF,0X00,0X1F,0XC0,0X03,0XF8,0X01,0XFF,0XDB,0X00,0X1F,0XC0,
0X00,0XF0,0X01,0XFF,0XD9,0X80,0X0F,0X00,0X00,0XF0,0X01,0XFF,0XD9,0XC0,0X07,0X00,
0X00,0XE0,0X01,0XFF,0XD8,0XC0,0X07,0X00,0X0C,0XE0,0X00,0X00,0XD8,0X60,0X03,0X10,
0X0F,0XC0,0X01,0XFF,0XD8,0X30,0X03,0XF0,0X0F,0XC0,0X01,0XFF,0XD8,0X30,0X03,0XF0,
0X0F,0XC0,0X1F,0XFF,0XFF,0X7F,0XC1,0XF8,0X01,0X80,0X1E,0X7F,0XFF,0X7F,0X81,0X80,
0X03,0X80,0X1F,0X7F,0XFF,0X7F,0X81,0XC0,0X03,0X80,0X1D,0XFF,0XFF,0X7C,0X01,0XC0,
0X03,0X80,0X1D,0XFF,0XFF,0X70,0X01,0XC0,0X1F,0X80,0X02,0XFF,0XFF,0X00,0X01,0XF8,
0X1F,0X80,0X02,0X3F,0XFC,0X00,0X01,0XF8,0X1F,0X80,0X00,0X1F,0XF8,0X01,0X81,0XF8,
0X03,0X80,0X04,0X1F,0XF8,0X00,0X01,0XF8,0X03,0X80,0X04,0X0F,0XF8,0X00,0X01,0XC0,
0X01,0X80,0X00,0X0F,0XF8,0X00,0X01,0X80,0X1F,0XC0,0X08,0X1F,0XFC,0X00,0X01,0X80,
0X0F,0XC0,0X08,0X1F,0XFC,0X01,0X03,0XF0,0X0F,0XC0,0X10,0X3F,0XFE,0X00,0X03,0XF0,
0X0C,0XE0,0X10,0X00,0X00,0X00,0X03,0XF0,0X00,0XE0,0X10,0XFF,0XFF,0X80,0X07,0X20,
0X00,0XE0,0X20,0X00,0X00,0X00,0X07,0X00,0X00,0XF0,0X27,0XFF,0XFF,0XF0,0X0E,0X00,
0X03,0XF9,0X27,0XC8,0X88,0XF0,0X0F,0X00,0X03,0XFB,0XE7,0XEC,0X88,0XF0,0X1F,0X80,
0X01,0XDF,0XF7,0XEA,0XAA,0XF0,0X3F,0X80,0X01,0X1E,0X77,0XED,0XDD,0XF0,0X7B,0X00,
0X00,0X0F,0X10,0X00,0X00,0X00,0XF1,0X00,0X00,0X1F,0XFF,0XFF,0XFF,0XFF,0XE0,0X00,
0X00,0X3F,0XC0,0X00,0X00,0X03,0XF0,0X00,0X00,0X1F,0XF0,0X00,0X00,0X07,0XF8,0X00,
0X00,0X18,0X78,0X00,0X00,0X1F,0X70,0X00,0X00,0X00,0X7E,0X00,0X00,0X7E,0X20,0X00,
0X00,0X00,0X7F,0XE0,0X03,0XFF,0X00,0X00,0X00,0X00,0XF3,0XFF,0XFF,0XCF,0X00,0X00,
0X00,0X00,0X70,0XFF,0XFF,0X86,0X00,0X00,0X00,0X00,0X21,0XE7,0XE7,0X84,0X00,0X00,
0X00,0X00,0X01,0XE1,0XC3,0X80,0X00,0X00,0X00,0X00,0X01,0XE1,0XC3,0X80,0X00,0X00,
0X00,0X00,0X00,0X01,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};


void lcd_delay(unsigned short val)
{
	unsigned short i;
	while(val--)
		for(i = 0; i < 600; i++);
}

void shortdel(void)
{
	unsigned char i;
	for(i = 0; i < 10; i++);
}

unsigned char lcd_busy(void)             //return value ==0,is idle ,==1,is busy status
{
	unsigned char ret = 0;	
	DB2_PIN_IN();
	LCD_RSL();
	shortdel();
	LCD_RWH();
	shortdel();
	LCD_EH();
	shortdel();

	if(GET_DB2())
		ret = 1;

	LCD_EL();
	shortdel();
	DB2_PIN_OUT();
	return ret;
}

void lcd_write(unsigned char data, unsigned char op)
{
	unsigned char i;
	while(lcd_busy());   //==1,as busy
	//lcd_delay(1);
	shortdel();
	if(op == 0)
	{
		LCD_RSL();
		shortdel();
	}
	else
	{                    //if operation status is  busy,and set run status
		LCD_RSH();
		shortdel();
	}
	LCD_RWL();
	LCD_EL();
	shortdel();
#if DBUS_BITS == 4                   //if current transismission mode serial ,and ...., as parrall mode
	for(i = 0; i < 2; i++)
	{
#endif
		LCD_WDATA(data);
		shortdel();
		LCD_EH();
		shortdel();
		LCD_EL();
#if DBUS_BITS == 4
		data <<= 4;
	}
#endif
}

void WriteStr(unsigned char *s)
{ 
    while(*s>0)
   {  lcd_write(*s,1);
      s++;     
   }
}

void lcd_init(void)
{	
	//lcd_delay(100);
	
    LCD_REST_OUT();
	LCD_RESTL();
	lcd_delay(50);
	LCD_RESTH();
	lcd_delay(50);
	BACKLIGHT_ON();
	lcd_delay(5); 
#if DBUS_BITS == 4
	lcd_write(0x28,0);
	lcd_delay(5);
	LCD_EH();
	shortdel();
	LCD_EL();
	lcd_delay(5);
	lcd_write(0x28,0);
#else
	lcd_write(0x38,0);
#endif	
   lcd_write(0x0C,0);
   lcd_write(0x01,0);              // Turn on LCD and Cursor  
   lcd_write(0x02,0);              // Turn on LCD and Cursor  
   lcd_write(0x06,0);           // Entry Mode Set       
}

void CursorSet(unsigned char pos)
{
	if(pos > 63)
		return;
	pos /= 2;	
	if(pos < 8)
		lcd_write(0x80 + pos,0);
	else if(pos < 16)	
		lcd_write(0x90 + pos - 8,0);
	else if(pos < 24)	
		lcd_write(0x88 + pos - 16,0);
	else if(pos < 32)	
		lcd_write(0x98 + pos - 24,0);
}
/*
pos  16*4=64   总共可以显示64 个字符
第一行： 0~15
第二行:  16~31
第三行:  32~47
第四行:  48~63
pos  高4bit   行数
     低4bit   列数
注： 汉字占两个字符，必须是以偶数位开始，否则显示乱码
*/
void lcd_display(unsigned char pos,  void *str)
{
	unsigned char *p, *p1;
	unsigned char i,lenth;	
	if(pos > 63)
		return;
	p = p1 = (unsigned char *)str;
	lenth = 0;
	while(*p1)   
	{
		lenth++;
		p1++;
		if(lenth >= 64 - pos)
			break;
	}
	if((pos%16)!=0)		
	CursorSet(pos);
	for(i = pos; i - pos < lenth; i++)
	{
		if(i == 0)		
		   lcd_write(0x80, 0);
		else if(i == 16)		
		   lcd_write(0x90, 0);
		else if(i == 32)
		   lcd_write(0x88, 0);
		else if(i == 48) 
		   lcd_write(0x98, 0);
		lcd_write(*p++, 1);
	}
}
void LcdFill_Vertical()
{  unsigned char x,y,ii;
 #if DBUS_BITS == 4
 lcd_write(0x26,0);//扩充指令 绘图显示
 #else
 lcd_write(0x36,0);//扩充指令 绘图显示
 #endif
   for(ii=0;ii<9;ii+=8)   
     for(y=0;y<0x20;y++)     
      for(x=0;x<8;x++)
      { 		
         lcd_write(y+0x80,0);        //行地址
         lcd_write(x+0x80+ii,0);     //列地址 
         lcd_write(0xCC,1); //写数据 D15－D8 
         lcd_write(0xCC,1); //写数据 D7－D0  	
      } 
#if DBUS_BITS == 4
lcd_write(0x20,0);	
#else
lcd_write(0x30,0);
#endif	
}
void LcdFill_Level()
{  unsigned char x,y,ii;
   unsigned char k; 
	#if DBUS_BITS == 4
	lcd_write(0x26,0);//扩充指令 绘图显示
	#else
	lcd_write(0x36,0);//扩充指令 绘图显示
	#endif
   for(ii=0;ii<9;ii+=8)    
      for(y=0;y<0x20;y++)
      {     if(((y%4)==0)||((y%4)==1))
               k=0xff;
            else
               k=0;
            for(x=0;x<8;x++)
            {   
				
               lcd_write(y+0x80,0);    //行地址
               lcd_write(x+0x80+ii,0);    //列地址            
               lcd_write(k,1);
               lcd_write(k,1);
				
            }
       } 
		#if DBUS_BITS == 4
		lcd_write(0x20,0);				
		#else
		lcd_write(0x30,0);
		#endif	
} 

void LcdFill_REC()
{  
 unsigned char x,y,ii;
 int count = 0;
 #if DBUS_BITS == 4
 lcd_write(0x26,0);//扩充指令 绘图显示
 #else
 lcd_write(0x36,0);//扩充指令 绘图显示
 #endif
   for(ii=0;ii<9;ii+=8)   
     for(y=0;y<0x20;y++)     
      {
       for(x=0;x<4;x++)              // ii=0校徽上半部分，屏幕左上四分之一；ii=1，校徽下半部分，屏幕左下四分之一
        { 		
         lcd_write(y+0x80,0);        //行地址
         lcd_write(x+0x80+ii,0);     //列地址 
         lcd_write(XJTU_image[count++],1);
	 lcd_write(XJTU_image[count++],1);
        }
       for(x=4;x<8;x++)              // ii=0空白，屏幕右上四分之一；ii=1，空白，屏幕右下四分之一
        {
         lcd_write(y+0x80,0);        //行地址
         lcd_write(x+0x80+ii,0);     //列地址 
         lcd_write(0x00,1); //写数据 D15－D8 
         lcd_write(0x00,1); //写数据 D7－D0 
			 
        }
      }
#if DBUS_BITS == 4
lcd_write(0x20,0);	
#else
lcd_write(0x30,0);
#endif	
}
void LcdClear()
{  
 unsigned char x,y,ii;
 #if DBUS_BITS == 4
 lcd_write(0x26,0);//扩充指令 绘图显示
 #else
 lcd_write(0x36,0);//扩充指令 绘图显示
 #endif
   for(ii=0;ii<9;ii+=8)   
     for(y=0;y<0x20;y++)     
      {
       for(x=0;x<8;x++) 
        { 		
         lcd_write(y+0x80,0);        //行地址
         lcd_write(x+0x80+ii,0);     //列地址 
         lcd_write(0x00,1);
	 lcd_write(0x00,1);
        }
/*       for(x=4;x<8;x++)
        {
         lcd_write(y+0x80,0);        //行地址
         lcd_write(x+0x80+ii,0);     //列地址 
         lcd_write(0x00,1); //写数据 D15－D8 
         lcd_write(0x00,1); //写数据 D7－D0 
			 
        }
*/
}
#if DBUS_BITS == 4
lcd_write(0x20,0);	
#else
lcd_write(0x30,0);
#endif	
}
