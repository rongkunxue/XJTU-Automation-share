
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
* File Name    : r_cg_digtalLED.c
* Version      : RL78/G13 V2.02.01.01 [21 Jan 2015]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Company Name : Getsoon Electronic Co,Ltd. Shanghai,China
* Description  : This file implements device driver for TAU module.
* Creation Date: 2015-1-21
***********************************************************************************************************************/

 
 
#include "r_cg_macrodriver.h"
#include "r_cg_digtalLED.h"

/***********************************************************************************************************************
* Function Name: Getcode
* Description  : KEY value convert DLED display coding.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

uint8_t Getcode(uint8_t  i)  /*digital_led segment table ---->"k"*/
{
	uint8_t  p;
	switch (i)
	{
	case 0:	 p=0x3f;	break;			/* 0 */
	case 1:	 p=0x06;	break;			/* 1 */
	case 2:	 p=0x5B;	break;			/* 2 */
	case 3:	 p=0x4F;	break;			/* 3 */
	case 4:	 p=0x66;	break;			/* 4 */
	case 5:	 p=0x6D;	break;			/* 5 */
	case 6:	 p=0x7D;	break;			/* 6 */
	case 7:	 p=0x07;	break;			/* 7 */
	case 8:	 p=0x7F;	break;			/* 8 */
	case 9:	 p=0x67;	break;			/* 9 */
	case 0x0a: p=0x77;  	break;		    	/* a */
	case 0x0b: p=0x7c;	break;			/* b */
	case 0x0c: p=0x39;  	break;          	/* c */
	case 0x0d: p=0x5e;	break;			/* d */
	case 0x0e: p=0x79;	break;			/* e */
	case 0x0f: p=0x71;	break;			/* f */
	case   16: p=0x80;	break;			/* . */
	case   17: p=0x73;	break;			/* p */
	case   18: p=0x3e;	break;			/* u */
	case   19: p=0x31;	break;			/* t */
	case   20: p=0x6e;	break;			/* y */
	case   21: p=0xff;	break;			/* 8.*/
	case   22: p=0x00;	break;			/*close*/
	default: 			break;
	}
	return(p);
}
