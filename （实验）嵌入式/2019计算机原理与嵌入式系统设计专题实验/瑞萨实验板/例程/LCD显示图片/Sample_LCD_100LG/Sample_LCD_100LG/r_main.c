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
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
unsigned int i;
unsigned char *string="Xi'an   JiaotongUniv.";
void lcd_displayXJTU(unsigned char pos,  void *str);

void delay(int t)
{
  int x = 0;
  int y = 0;
  for(x = 0; x < t;x++)
   for(y = 0; y < 1000;y++);
}
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */

	lcd_init( );	
	//LcdFill_Level();

    while (1U)
    {
	//for(i = 0;i < 2000; i++)
        LcdFill_REC();
	delay(1000);
	delay(1000);
	WDTE = 0xAC;
//	LcdClear();     //Clear Graph;

	lcd_displayXJTU(0,string);
	delay(1000);
	delay(1000);
	WDTE = 0xAC;
	LcdClear();     //Clear Graph;
	lcd_write(0x01,0);  
	delay(1000);
	delay(1000);
	WDTE = 0xAC;
	lcd_display(0,"     Renesas    "
			"   Electronics  "
			"    瑞萨电子    "
			"      中国       ");
	WDTE = 0xAC;
	delay(1000);
	delay(1000);		
	lcd_write(0x01,0);  // 基础指令，清除显示，地址归零
	// lcd_init( ); // 也可以清屏，没必要;
	// LcdClear();  不能清除文字
/*		lcd_display(0,"                "   // 用空字符清屏
			"                "
			"                "
			"                 ");
				WDTE = 0xAC;
*/    
	delay(1000);
	delay(1000);
	
    //	NOP();
	WDTE = 0xAC;
	
	//广 
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

/* Start user code for adding. Do not edit comment generated here */
void lcd_displayXJTU(unsigned char pos,  void *str)
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
/* End user code. Do not edit comment generated here */
