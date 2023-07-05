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
* File Name    : r_cg_serial.c
* Version      : CodeGenerator for RL78/G13 V2.02.01.01 [30 May 2014]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for Serial module.
* Creation Date: 2015-1-22
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
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"


/***********************************************************************************************************************
Global variables and functions
 ***********************************************************************************************************************/
volatile uint8_t * gp_csi10_rx_address;        /* csi10 receive buffer address */
volatile uint16_t  g_csi10_rx_length;          /* csi10 receive data length */
volatile uint16_t  g_csi10_rx_count;           /* csi10 receive data count */
volatile uint8_t * gp_csi10_tx_address;        /* csi10 send buffer address */
volatile uint16_t  g_csi10_send_length;        /* csi10 send data length */
volatile uint16_t  g_csi10_tx_count;           /* csi10 send data count */

volatile uint8_t   tx_len;
volatile uint8_t   tx_count;
volatile uint8_t   return_data;
volatile uint8_t  *pTxdata;
volatile uint8_t  *pRxdata;

uint8_t  Cmd_Type;
uint8_t  Cmd_Exe_End;
uint8_t  end_txif;



/* Start user code for global. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
 * Function Name: R_SAU0_Create
 * Description  : This function initializes the SAU0 module.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_SAU0_Create(void)
{
	SAU0EN = 1U;    /* supply SAU0 clock */
	NOP();
	NOP();
	NOP();
	NOP();
	SPS0 = _0000_SAU_CK00_FCLK_0 | _0000_SAU_CK01_FCLK_0;
	R_CSI10_Create();
}

/***********************************************************************************************************************
 * Function Name: R_CSI10_Create
 * Description  : This function initializes the CSI10 module.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_CSI10_Create(void)
{
	ST0 |= _0004_SAU_CH2_STOP_TRG_ON;    /* disable CSI10 */
	CSIMK10 = 1U;    /* disable INTCSI10 interrupt */
	CSIIF10 = 0U;    /* clear INTCSI10 interrupt flag */
	/* Set INTCSI10 level2 priority */
	CSIPR110 = 1U;
	CSIPR010 = 0U;
	SIR02 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
	SMR02 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
			_0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
	SCR02 = _C000_SAU_RECEPTION_TRANSMISSION | _3000_SAU_TIMING_4 | _0000_SAU_MSB | _0007_SAU_LENGTH_8;
	SDR02 = _3200_CSI10_DIVISOR;
	SO0 &= ~_0400_SAU_CH2_CLOCK_OUTPUT_1;    /* CSI10 clock initial level */
	SO0 &= ~_0004_SAU_CH2_DATA_OUTPUT_1;    /* CSI10 SO initial level */
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable CSI10 output */
	/* Set SI10 pin */
	PMC0 &= 0xF7U;
	PM0 |= 0x08U;
	/* Set SO10 pin */
	PMC0 &= 0xFBU;
	P0 |= 0x04U;
	PM0 &= 0xFBU;
	/* Set SCK10 pin */
	P0 |= 0x10U;
	PM0 &= 0xEFU;
}

/***********************************************************************************************************************
 * Function Name: R_CSI10_Start
 * Description  : This function starts the CSI10 module operation.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_CSI10_Start(void)
{
	CSIIF10 = 0U;    /* clear INTCSI10 interrupt flag */
	CSIMK10 = 0U;    /* enable INTCSI10 */
	SO0 &= ~_0400_SAU_CH2_CLOCK_OUTPUT_1;   /* CSI10 clock initial level */
	SO0 &= ~_0004_SAU_CH2_DATA_OUTPUT_1;           /* CSI10 SO initial level */
	SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;           /* enable CSI10 output */
	SS0 |= _0004_SAU_CH2_START_TRG_ON;             /* enable CSI10 */
}

/***********************************************************************************************************************
 * Function Name: R_CSI10_Stop
 * Description  : This function stops the CSI10 module operation.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_CSI10_Stop(void)
{
	ST0 |= _0004_SAU_CH2_STOP_TRG_ON;        /* disable CSI10 */
	SOE0 &= ~_0004_SAU_CH2_OUTPUT_ENABLE;    /* disable CSI10 output */
	CSIMK10 = 1U;    /* disable INTCSI10 interrupt */
	CSIIF10 = 0U;    /* clear INTCSI10 interrupt flag */
}

uint8_t R_CSI10_CmdSend(uint8_t cmd_name,uint8_t  cmd_len)
{
	Cmd_Type = cmd_name;
	Cmd_Exe_End = 0;
	tx_len = cmd_len;
	tx_len--;
	CSIMK10 = 1U;                     /* disable INTCSI10 interrupt */
	CHIP_CS = 0;
	NOP();
	NOP();
	NOP();
	SIO10 = cmd_name;                 /* send EEPROM command */
	CSIMK10 = 0U;                     /* enable INTCSI10 interrupt */

	while((Cmd_Exe_End & 0x80) != 0x80);   //Wait a time
	return return_data;
}



void R_CSI10_DataSend(uint8_t cmd_name,uint8_t  *tempTx,uint8_t  *tempRx, uint8_t  data_len)
{
	uint8_t fs;
	Cmd_Type = cmd_name;
	Cmd_Exe_End = 0;
	tx_len = data_len;

	pTxdata = tempTx;
	pRxdata = tempRx;
	fs = *pRxdata;


	CSIMK10 = 1U;                     /* disable INTCSI10 interrupt */
	CHIP_CS = 0;
	NOP();
	NOP();
	NOP();
	SIO10 = cmd_name;                 /* send EEPROM command */
	CSIMK10 = 0U;                     /* enable INTCSI10 interrupt */

	while((Cmd_Exe_End & 0x80) != 0x80);   //Wait a time
}

/***********************************************************************************************************************
 * Function Name: R_CSI10_Send_Receive
 * Description  : This function sends and receives CSI10 data.
 * Arguments    : tx_buf -
 *                    transfer buffer pointer
 *                tx_num -
 *                    buffer size
 *                rx_buf -
 *                    receive buffer pointer
 * Return Value : status -
 *                    MD_OK or MD_ARGERROR
 ***********************************************************************************************************************/
MD_STATUS R_CSI10_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf,uint8_t cmd_name)
{
	MD_STATUS status = MD_OK;

	Cmd_Type = cmd_name;

	if (tx_num < 1U)
	{
		status = MD_ARGERROR;
	}
	else
	{
		g_csi10_tx_count = tx_num;        /* send data count */
		gp_csi10_tx_address = tx_buf;     /* send buffer pointer */
		gp_csi10_rx_address = rx_buf;     /* receive buffer pointer */
		CSIMK10 = 1U;                     /* disable INTCSI10 interrupt */
		SIO10 = *gp_csi10_tx_address;    /* started by writing data to SDR[7:0] */
		gp_csi10_tx_address++;
		g_csi10_tx_count--;
		CSIMK10 = 0U;                     /* enable INTCSI10 interrupt */
	}

	return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
