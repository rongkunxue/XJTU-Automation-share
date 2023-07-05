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
* Copyright (C) 2011, 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_KeyScan.c
* Version      : RL78/G13 V2.02.01.01 [21 Jan 2015]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Company Name : Getsoon Electronic Co,Ltd. Shanghai,China
* Description  : This file implements device driver for TAU module.
* Creation Date: 2015-1-21
***********************************************************************************************************************/

#include "r_cg_macrodriver.h"
#include "r_cg_KeyScan.h"

volatile uint8_t num_keyboard;
//uint8_t array_key[2];
uint8_t temp = 0;

uint8_t  testvalue;

/***********************************************************************************************************************
* Function Name: delay
* Description  : nop instruction wait.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void delay(uint8_t t)
{
   for(;t>0;t--);
   for(;t>0;t--);
}

/***********************************************************************************************************************
* Function Name: Keyboard_scan
* Description  : check key state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/


void Keyboard_scan(void)
{

	KEY_PORT = 0xff;
	P7.3=0;
	temp = KEY_PORT;
	temp=temp&0xf0;   							/*check  four  lower  bits*/
	if(temp!=0xf0)    							/*first check*/
	{
		delay(100);								/*delay some time*/
		temp = KEY_PORT;
		temp=temp&0xf0;							/*check  four  lower  bits*/
		if(temp!=0xf0)							/*second check*/
		{
			temp=KEY_PORT;
			temp=temp&0xf0;
			switch(temp)
			{
			case 0xe0:  num_keyboard=1; break;
			case 0xd0:  num_keyboard=5; break;
			case 0xb0:  num_keyboard=9; break;
			case 0x70:  num_keyboard=13; break;
			}
		}
		testvalue=num_keyboard;
	}

	KEY_PORT = 0xff;        					/*as above*/
	P7.2=0;
	temp=KEY_PORT;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delay(100);
		temp=KEY_PORT;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{  temp=KEY_PORT;
		temp=temp&0xf0;
		switch(temp)
		{
		case 0xe0:  num_keyboard=2; break;
		case 0xd0:  num_keyboard=6; break;
		case 0xb0:  num_keyboard=10; break;
		case 0x70:  num_keyboard=14; break;
		}
		}
	}

	KEY_PORT = 0xff;        					/*as above*/
	P7.1=0;
	temp=KEY_PORT;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delay(100);
		temp=KEY_PORT;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{  temp=KEY_PORT;
		temp=temp&0xf0;
		switch(temp)
		{
		case 0xe0:  num_keyboard=3; break;
		case 0xd0:  num_keyboard=7; break;
		case 0xb0:  num_keyboard=11; break;
		case 0x70:  num_keyboard=15; break;
		}
		}
	}

	KEY_PORT = 0xff;        					/*as above*/
	P7.0=0;
	temp=KEY_PORT;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delay(100);
		temp=KEY_PORT;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{  temp=KEY_PORT;
		temp=temp&0xf0;
		switch(temp)
		{
		case 0xe0:  num_keyboard=4; break;
		case 0xd0:  num_keyboard=8; break;
		case 0xb0:  num_keyboard=12; break;
		case 0x70:  num_keyboard=16; break;
		}
		}
	}

}
/*this function is used to define digital_led segment table*/
