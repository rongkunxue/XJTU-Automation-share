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
* File Name    : r_cg_adc.c
* Version      : CodeGenerator for RL78/G13 V2.02.01.01 [30 May 2014]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for ADC module.
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
#include "r_cg_adc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

int mun[10]={0x3f,0x06,0x5B,0x4F,0x66,0x6d,0x7D,0x07,0x7F,0x6F};

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_ADC_Create
* Description  : This function initializes the AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADC_Create(void)
{    
	ADCEN = 1U;  /* supply AD clock */
	ADM0 = 0;  /* disable AD conversion and clear ADM0 register */
	ADMK = 1U;  /* disable INTAD interrupt */
	ADIF = 0U;  /* clear INTAD interrupt flag */
	/* Set INTAD low priority */
	ADPR1 = 1U;
	ADPR0 = 1U;
	/* Set ANI0 - ANI7 pin as analog input */
	PM2 |= 0xFFU;
	/* Set ANI19 pin */
	PMC12 |= 0x01U;
	PM12 |= 0x01U;
	ADM0 = 7;
	ADM1 = 0x20;
	ADM2 = 0;
	ADUL = 255;
	ADLL = 0;
	ADS = 0x13;
}

/***********************************************************************************************************************
* Function Name: R_ADC_Start
* Description  : This function starts the AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADC_Start(void)
{   
	ADCE = 1U;
	ADIF = 0U;  /* clear INTAD interrupt flag */
	ADMK = 0U;  /* enable INTAD interrupt */
	ADCS = 1U;  /* enable AD conversion */
	while(ADCS);
}

/***********************************************************************************************************************
* Function Name: R_ADC_Stop
* Description  : This function stops the AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADC_Stop(void)
{
	ADCS = 0U;  /* disable AD conversion */
	ADMK = 1U;  /* disable INTAD interrupt */
	ADIF = 0U;  /* clear INTAD interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_ADC_Set_OperationOn
* Description  : This function enables comparator operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADC_Set_OperationOn(void)
{
    ADCE = 1U;  /* enable AD comparator */
}

/***********************************************************************************************************************
* Function Name: R_ADC_Set_OperationOff
* Description  : This function stops comparator operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ADC_Set_OperationOff(void)
{
    ADCE = 0U;  /* disable AD comparator */
}

/***********************************************************************************************************************
* Function Name: R_ADC_Get_Result
* Description  : This function returns the conversion result in the buffer.
* Arguments    : buffer -
*                    the address where to write the conversion result
* Return Value : None
***********************************************************************************************************************/
void R_ADC_Get_Result(uint16_t * const buffer)
{
	*buffer = (uint16_t)(ADCR >> 6U);
}


/***********************************************************************************************************************
* Function Name: delay
* Description  : nop instruction wait.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void delay(unsigned char t)
{
	for(;t>0;t--);
	for(;t>0;t--);  /*delay some time,not sure*/
}

/***********************************************************************************************************************
* Function Name: Led_display
* Description  : DLED¡¡display function
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void Led_display(void)
{
	long s,i;
	s=(long)(ADCR>>6)*5000/1024;
	for(i=0;i<3000;i++)
	{
		P5&=~(0xf<<2);
		P1=(mun[s/1000]|(1<<7));
		P5.2=1;
		delay(2000);
		P5.2=0;
		delay(10);
		P1=mun[s%1000/100];
		P5.3=1;
		delay(2000);
		P5.3=0;
		delay(10);
		P1=mun[s%100/10];
		P5.4=1;
		delay(2000);
		P5.4=0;
		delay(10);
		P1=mun[s%10];
		P5.5=1;
		delay(2000);
		P5.5=0;
		delay(10);
	}

}


/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
