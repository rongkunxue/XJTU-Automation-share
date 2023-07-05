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
* File Name    : r_cg_serial_user.c
* Version      : CodeGenerator for RL78/G13 V2.02.01.01 [30 May 2014]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for Serial module.
* Creation Date: 2015-1-22
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTIIC10 r_iic10_interrupt
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
extern volatile uint8_t   g_iic10_master_status_flag;  /* iic10 start flag for send address check by master mode */
extern volatile uint8_t * gp_iic10_tx_address;         /* iic10 send data pointer by master mode */
extern volatile uint16_t  g_iic10_tx_count;            /* iic10 send data size by master mode */
extern volatile uint8_t * gp_iic10_rx_address;         /* iic10 receive data pointer by master mode */
extern volatile uint16_t  g_iic10_rx_count;            /* iic10 receive data size by master mode */
extern volatile uint16_t  g_iic10_rx_length;           /* iic10 receive data length by master mode */

uint8_t  end_if;
uint8_t  end_rxif;
uint16_t  teststatic = 0;

/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_iic10_interrupt
* Description  : This function is INTIIC10 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_iic10_interrupt(void)
{
	WDTE = 0xAC;
	teststatic = SSR02;
    if ((teststatic & _0002_SAU_PARITY_ERROR) == 0U)
    {
        /* Control for master send */
        if ((g_iic10_master_status_flag & _01_SAU_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic10_tx_count > 0U)
            {
                SIO10 = *gp_iic10_tx_address;
                //SIO10 = 0x55;
                gp_iic10_tx_address++;
                g_iic10_tx_count--;
            }
            else
            {
                R_IIC10_StopCondition();
                r_iic10_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else
        {
            if ((g_iic10_master_status_flag & _04_SAU_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                ST0 |= _0004_SAU_CH2_STOP_TRG_ON;
                SCR02 &= ~_C000_SAU_RECEPTION_TRANSMISSION;
                SCR02 |= _4000_SAU_RECEPTION;
                SS0 |= _0004_SAU_CH2_START_TRG_ON;
                g_iic10_master_status_flag |= _04_SAU_IIC_SENDED_ADDRESS_FLAG;
                SIO10 = 0xFFU;
            }
            else
            {
                if (g_iic10_rx_count < g_iic10_rx_length)
                {
                    *gp_iic10_rx_address = SIO10;
                    gp_iic10_rx_address++;
                    g_iic10_rx_count++;

//                    if (g_iic10_rx_count == (g_iic10_rx_length - 1U))
//                    {
//                        SOE0 &= ~_0004_SAU_CH2_OUTPUT_ENABLE;    /* disable IIC10 out */
//                        SIO10 = 0xFFU;
//                    }
//                    else if (g_iic10_rx_count == g_iic10_rx_length)
//                    {
//                        R_IIC10_StopCondition();
//                        r_iic10_callback_master_receiveend();
//                    }
                    if (g_iic10_rx_count == g_iic10_rx_length-1)
                    {
                    	R_IIC10_StopCondition();
                    	r_iic10_callback_master_receiveend();
                    }
                    else                    {
                        SIO10 = 0xFFU;
                    }


                }

            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_iic10_callback_master_receiveend
* Description  : This function is a callback function when IIC10 finishes master reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iic10_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
	end_rxif = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_iic10_callback_master_sendend
* Description  : This function is a callback function when IIC10 finishes master transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iic10_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
	end_if = 1;

    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
