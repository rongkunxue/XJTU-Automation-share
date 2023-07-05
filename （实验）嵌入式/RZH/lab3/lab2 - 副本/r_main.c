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
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
unsigned int i;
extern volatile uint8_t num_keyboard;
unsigned char date[16]="_   年  月  日  ";
unsigned int x=0;
unsigned char pre=' ';
unsigned int flag=0;
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);
void display();
void getnext();
void getpre();

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
	hdwinit();
    R_MAIN_UserInit();
    lcd_init();
    num_keyboard=0;
    /* Start user code. Do not edit comment generated here */

	//lcd_init( );	
	//LcdFill_Level();



    while (1U)
    {
	//for(i = 0;i < 2000; i++)
	lcd_display(0,"    任泽华      "
			"  自动化71班    "
			"  2171411498    ");
	 lcd_display(48,date);
	 Keyboard_scan();
	 if(num_keyboard!=0)
	 display();
	 
	NOP();
	WDTE = 0xAC;
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
void display()
{
     //if(num_keyboard!=0）flag++；
     flag++;
     if(flag>25)
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
			 case(13):
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
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
