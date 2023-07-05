/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V2.03.01.03 [30 Jan 2015]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 2017/5/26
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_lcd.h"
#include "r_cg_KeyScan.h"
#include "r_cg_digtalLED.h"
#include "r_cg_timer.h"
#include "r_cg_pclbuz.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
unsigned int i;
extern volatile uint8_t num_keyboard;
extern volatile uint8_t num;
uint8_t num_10;
uint8_t  count=0;
bit bit_control;
uint8_t array_key[2];
uint8_t buzflag=0;
unsigned char date[16]="_   年  月  日  ";
unsigned int x=0;
unsigned char pre=' ';
unsigned int flag=0;
int bflag=0;
int sflag=0;
int change=0;
int mydisplay=0;
unsigned char *string="谢  谢  （^__^）~~~~~~~~";
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);
void display();
void getnext();
void getpre();
void delaya(void);
void leddispaly(void);
void lcd_displayth(unsigned char pos,  void *str);
void setdate();
void Loop_display();
void delayb(int t)
{
  int x = 0;
  int y = 0;
  for(x = 0; x < t;x++)
   for(y = 0; y < 1000;y++);
}
/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    hdwinit();
    	R_PCLBUZ0_Create();
	R_TAU0_Create();
	R_TAU0_Channel0_Start();
    R_MAIN_UserInit();
    lcd_init();
    num_keyboard=0;
    /* Start user code. Do not edit comment generated here */
    while (1U)
    {
	    lcd_display(0,"    菜    单    "
			"1.键盘输入  定时"
			"2.循环显示图片  "
			"3.按16退出  ");
			//"");
	    Keyboard_scan();
	    switch(num_keyboard)
		 {
			 case(1):mydisplay=0;setdate();break;
			 case(2):Loop_display();break;
		 }

    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}
void setdate()
{
	while (mydisplay==0)
        {
	 num_keyboard=0;
	lcd_display(0,"    任泽华      "
			"  自动化71班    "
			"  2171411498    ");
	 lcd_display(48,date);
	 Keyboard_scan();
	 if(num_keyboard==14){sflag=1;}
	 if(sflag==1)num_10 = num/10;
	 else {num=0;num_10=0;}
	 if(bflag==0 && num_10==10){ R_PCLBUZ0_Start();  bflag=1; delaya();R_PCLBUZ0_Stop();}
		
	 if(num_keyboard==13){bflag=0; num=0;num_keyboard=0;sflag=0;}

	 if(num_keyboard!=0)
	 display();
	 if(num_keyboard==13){bflag=0; num=0;num_keyboard=0;sflag=0;}
	 leddispaly();
	//delayb(1000);
	//delayb(1000);
	NOP();
	WDTE = 0xAC;
	if(num_keyboard==16) {num_keyboard=0; mydisplay=1;lcd_write(0x01,0);break;}
        }
}
void Loop_display()
{
	while(1)
	{
	Keyboard_scan();if(num_keyboard==16){num_keyboard=0; LcdClear();break;}
	lcd_write(0x01,0);
        LcdFill_REC();
	delayb(1000);
	delayb(1000);
	WDTE = 0xAC;
	Keyboard_scan();if(num_keyboard==16){num_keyboard=0;LcdClear(); break;}
	lcd_displayth(0,string);
	delayb(1000);
	delayb(1000);
	WDTE = 0xAC;
	Keyboard_scan();if(num_keyboard==16){num_keyboard=0;LcdClear(); break;}
	LcdClear();     //Clear Graph;
	lcd_write(0x01,0); 
	delayb(1000);
	delayb(1000);
	WDTE = 0xAC;
	Keyboard_scan();if(num_keyboard==16){num_keyboard=0;LcdClear(); break;}
	LcdFill_REC2();
	delayb(1000);
	delayb(1000);
	WDTE = 0xAC;
	Keyboard_scan();if(num_keyboard==16){num_keyboard=0; LcdClear();break;}
	LcdClear();     //Clear Graph;
	lcd_write(0x01,0); 
	delayb(1000);
	delayb(1000);
	LcdFill_REC3();
	delayb(1000);
	delayb(1000);
	WDTE = 0xAC;
	Keyboard_scan();if(num_keyboard==16){num_keyboard=0;LcdClear(); break;}
	LcdClear();     //Clear Graph;
	lcd_write(0x01,0); 
	delayb(1000);
	delayb(1000);
	lcd_display(0,"    任泽华      "
			"  自动化71班    "
			"  2171411498    ");
	lcd_display(48,date);
	delayb(1000);
	delayb(1000);
	lcd_write(0x01,0);
	delayb(1000);
	delayb(1000);
	Keyboard_scan();if(num_keyboard==16){num_keyboard=0;LcdClear();  break;}
	}
}
void display()
{
     //if(num_keyboard!=0）flag++；
     flag++;
     if(flag>35)
     {
	  if(num_keyboard>10)
	  {
		 
		 switch(num_keyboard)
		 {
			 case(11):
			 {
				 getpre();
				 date[x]=' ';
				 break;
			 }
			 case(12):
			 {
				 date[x]=pre;
				 getpre();
				 pre=date[x];
				 date[x]=95;
				 break;
			 }
		 }
	  }
	  else
	  {
		date[x]=num_keyboard+47;
		x++;
		
		getnext();

		if(x!=0) date[x]=95;//显示_指示下一位输入位置
	  }
          flag=0;
          num_keyboard=0;
     }
}
void getnext()
{
	switch(x)
	{
	     case(4):x=x+2;break;
	     case(8):x=x+2;break;
	     case(12):x=0;break;
	     default:break;
	}
}
void getpre()
{
	switch(x)
		 {
		         case(6):x=x-3;break;
		         case(10):x=x-3;break;
			 case(0):x=11;break;
	                 default:x--;
		 }
}
void leddispaly(void)
{
	array_key[0]=num_10%10;    //the second char
	array_key[1]=num_10/10;    //the front char
	if(count<2)
	{
		if(count==0)bit_control=1;    //from bit4 to bit1
		if(count==1)bit_control=0;
		//testvalue1 = Getcode(array_key[count]);
		//DIGTAL_PORT = testvalue1;
		DIGTAL_LED_D4 = ~bit_control;
		DIGTAL_LED_D3 = ~bit_control;


		DIGTAL_PORT = Getcode(array_key[count]);

		DIGTAL_LED_D4 = bit_control;
		DIGTAL_LED_D3 = ~bit_control;
		count++;
	}
	else
	{
		count=0;

	}
}
void delaya(void)
{
	int i,j;
	for(i=0;i<800;i++)
	   for(j=0;j<800;j++);
}
void lcd_displayth(unsigned char pos,  void *str)
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
		   lcd_write(0x80+4, 0);
		else if(i == 8)		
		   lcd_write(0x90+4, 0);
		else if(i == 16)
		   lcd_write(0x88+4, 0);
		else if(i == 24) 
		   lcd_write(0x98+4, 0);
		lcd_write(*p++, 1);
		delay(200);
	}
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
