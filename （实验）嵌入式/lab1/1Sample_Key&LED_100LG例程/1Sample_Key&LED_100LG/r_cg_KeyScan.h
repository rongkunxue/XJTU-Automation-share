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
* File Name    : r_cg_KeyScan.h
* Version      : RL78/G13 V2.02.01.01 [21 Jan 2015]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Company Name : Getsoon Electronic Co,Ltd. Shanghai,China
* Description  : This file implements device driver for TAU module.
* Creation Date: 2015-1-21
***********************************************************************************************************************/


#ifndef R_CG_KEYSCAN_H_
#define R_CG_KEYSCAN_H_


#define KEY_PORT    	P7
#define KEY_PORT_IN0   	P7.7
#define KEY_PORT_IN1   	P7.6
#define KEY_PORT_IN2   	P7.5
#define KEY_PORT_IN3   	P7.4

void delay(uint8_t t);
void Keyboard_scan(void);


#endif /* R_CG_KEYSCAN_H_ */
