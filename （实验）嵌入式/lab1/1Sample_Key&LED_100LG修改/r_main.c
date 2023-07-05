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
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V2.02.01.01 [30 May 2014]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 2015-1-21
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
#include "r_cg_timer.h"
#include "r_cg_KeyScan.h"
#include "r_cg_digtalLED.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

extern volatile uint8_t flag_digital_led;
extern volatile uint8_t num_keyboard;
uint8_t array_key[2];
uint8_t  n_count = 0;

extern uint8_t  testvalue;
uint8_t  testvalue1;
uint8_t  a;
uint8_t  i;
uint8_t array_key[2];
uint8_t  count=0;
uint32_t  counter=0;
uint8_t  ii;
uint8_t  ccount=0;
uint8_t num[3]={0,0,0};

bit bit_control;


/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);
void dispaly(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
	hdwinit();
	R_TAU0_Create();
	R_MAIN_UserInit();
	R_TAU0_Channel0_Start();
	
	while(1U)
	{
	   R_WDT_Restart();	
	    Keyboard_scan();
		/*scan which button pressed*/
		if(flag_digital_led==1)
		{
			dispaly();        				/*digital_led display button number*/
			flag_digital_led = 0;
		};
	}
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

/***********************************************************************************************************************
* Function Name: dispaly
* Description  : KEY operation and  DLED display function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void dispaly(void)
{

	
	
	counter++;
	if(counter>300)
	{
		if (num_keyboard!=0)
		{
			num[n_count]=num_keyboard%10;
			
			n_count++;
			if(n_count>=3)
			{
				n_count=0;
			}
			counter=0;
			
			for(ii=0;ii<200;ii++)
			{
				;
			}
			
		}
	}
	num_keyboard=0;
	if(count<3)
	{
		if(count==0)
		{
			DIGTAL_LED_D4 = 1;
			DIGTAL_LED_D3 = 0;
			DIGTAL_LED_D2 = 0;
		}
		else if(count==1)
		{
			DIGTAL_LED_D4 = 0;
			DIGTAL_LED_D3 = 1;
			DIGTAL_LED_D2 = 0;

		}
		else if(count==2)
		{
			DIGTAL_LED_D4 = 0;
			DIGTAL_LED_D3 = 0;
			DIGTAL_LED_D2 = 1;

		}
		DIGTAL_PORT = Getcode(num[count]);
		
		count++;
	}
	else
	{
		count=0;

	}
    
    
}


/* End user code. Do not edit comment generated here */
