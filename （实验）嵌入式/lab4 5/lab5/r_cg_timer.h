/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_timer.h
* Version      : CodeGenerator for RL78/G13 V 0.01 1503 [23 Jan 2015]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 2015-1-23
***********************************************************************************************************************/

#ifndef TAU_H
#define TAU_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Peripheral Enable Register 0 (PER0)
*/
/* Control of timer array unit 0 input clock (TAU0EN) */
#define _00_TAU0_CLOCK_STOP                     (0x00U)   /* stops supply of input clock */
#define _01_TAU0_CLOCK_SUPPLY                   (0x01U)   /* supplies input clock */

/*
    Timer Clock Select Register m (TPSm)
*/
/* Operating mode and clear mode selection (PRSm03 - PRSm00) */
#define _0000_TAU_CKM0_FCLK_0                   (0x0000U) /* ckm0 - fCLK */
#define _0001_TAU_CKM0_FCLK_1                   (0x0001U) /* ckm0 - fCLK/2^1 */
#define _0002_TAU_CKM0_FCLK_2                   (0x0002U) /* ckm0 - fCLK/2^2 */
#define _0003_TAU_CKM0_FCLK_3                   (0x0003U) /* ckm0 - fCLK/2^3 */
#define _0004_TAU_CKM0_FCLK_4                   (0x0004U) /* ckm0 - fCLK/2^4 */
#define _0005_TAU_CKM0_FCLK_5                   (0x0005U) /* ckm0 - fCLK/2^5 */
#define _0006_TAU_CKM0_FCLK_6                   (0x0006U) /* ckm0 - fCLK/2^6 */
#define _0007_TAU_CKM0_FCLK_7                   (0x0007U) /* ckm0 - fCLK/2^7 */
#define _0008_TAU_CKM0_FCLK_8                   (0x0008U) /* ckm0 - fCLK/2^8 */
#define _0009_TAU_CKM0_FCLK_9                   (0x0009U) /* ckm0 - fCLK/2^9 */
#define _000A_TAU_CKM0_FCLK_10                  (0x000AU) /* ckm0 - fCLK/2^10 */
#define _000B_TAU_CKM0_FCLK_11                  (0x000BU) /* ckm0 - fCLK/2^11 */
#define _000C_TAU_CKM0_FCLK_12                  (0x000CU) /* ckm0 - fCLK/2^12 */
#define _000D_TAU_CKM0_FCLK_13                  (0x000DU) /* ckm0 - fCLK/2^13 */
#define _000E_TAU_CKM0_FCLK_14                  (0x000EU) /* ckm0 - fCLK/2^14 */
#define _000F_TAU_CKM0_FCLK_15                  (0x000FU) /* ckm0 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRSm13 - PRSm10) */
#define _0000_TAU_CKM1_FCLK_0                   (0x0000U) /* ckm1 - fCLK */
#define _0010_TAU_CKM1_FCLK_1                   (0x0010U) /* ckm1 - fCLK/2^1 */
#define _0020_TAU_CKM1_FCLK_2                   (0x0020U) /* ckm1 - fCLK/2^2 */
#define _0030_TAU_CKM1_FCLK_3                   (0x0030U) /* ckm1 - fCLK/2^3 */
#define _0040_TAU_CKM1_FCLK_4                   (0x0040U) /* ckm1 - fCLK/2^4 */
#define _0050_TAU_CKM1_FCLK_5                   (0x0050U) /* ckm1 - fCLK/2^5 */
#define _0060_TAU_CKM1_FCLK_6                   (0x0060U) /* ckm1 - fCLK/2^6 */
#define _0070_TAU_CKM1_FCLK_7                   (0x0070U) /* ckm1 - fCLK/2^7 */
#define _0080_TAU_CKM1_FCLK_8                   (0x0080U) /* ckm1 - fCLK/2^8 */
#define _0090_TAU_CKM1_FCLK_9                   (0x0090U) /* ckm1 - fCLK/2^9 */
#define _00A0_TAU_CKM1_FCLK_10                  (0x00A0U) /* ckm1 - fCLK/2^10 */
#define _00B0_TAU_CKM1_FCLK_11                  (0x00B0U) /* ckm1 - fCLK/2^11 */
#define _00C0_TAU_CKM1_FCLK_12                  (0x00C0U) /* ckm1 - fCLK/2^12 */
#define _00D0_TAU_CKM1_FCLK_13                  (0x00D0U) /* ckm1 - fCLK/2^13 */
#define _00E0_TAU_CKM1_FCLK_14                  (0x00E0U) /* ckm1 - fCLK/2^14 */
#define _00F0_TAU_CKM1_FCLK_15                  (0x00F0U) /* ckm1 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRSm21 - PRSm20) */
#define _0000_TAU_CKM2_FCLK_1                   (0x0000U) /* ckm2 - fCLK/2^1 */
#define _0100_TAU_CKM2_FCLK_2                   (0x0100U) /* ckm2 - fCLK/2^2 */
#define _0200_TAU_CKM2_FCLK_4                   (0x0200U) /* ckm2 - fCLK/2^4 */
#define _0300_TAU_CKM2_FCLK_6                   (0x0300U) /* ckm2 - fCLK/2^6 */
/* Operating mode and clear mode selection (PRSm31 - PRSm30) */
#define _0000_TAU_CKM3_FCLK_8                   (0x0000U) /* ckm2 - fCLK/2^8 */
#define _1000_TAU_CKM3_FCLK_10                  (0x1000U) /* ckm2 - fCLK/2^10 */
#define _2000_TAU_CKM3_FCLK_12                  (0x2000U) /* ckm2 - fCLK/2^12 */
#define _3000_TAU_CKM3_FCLK_14                  (0x3000U) /* ckm2 - fCLK/2^14 */

/*
    Timer Mode Register mn (TMRmn)
*/
/* Selection of macro clock (MCK) of channel n (CKSmn1 - CKSmn0) */
#define _0000_TAU_CLOCK_SELECT_CKM0             (0x0000U) /* operation clock CK0 set by PRS register */ 
#define _8000_TAU_CLOCK_SELECT_CKM1             (0x8000U) /* operation clock CK1 set by PRS register */
#define _4000_TAU_CLOCK_SELECT_CKM2             (0x4000U) /* operation clock CK2 set by PRS register */
#define _C000_TAU_CLOCK_SELECT_CKM3             (0xC000U) /* operation clock CK3 set by PRS register */
/* Selection of count clock (CCK) of channel n (CCSmn) */
#define _0000_TAU_CLOCK_MODE_CKS                (0x0000U) /* macro clock MCK specified by CKSmn bit */  
#define _1000_TAU_CLOCK_MODE_TIMN               (0x1000U) /* valid edge of input signal input from TImn pin */
/* Selection of slave/master of channel n (MASTERmn) */
#define _0000_TAU_COMBINATION_SLAVE             (0x0000U) /* operates as slave channel */
#define _0800_TAU_COMBINATION_MASTER            (0x0800U) /* operates as master channel */
/* Operation explanation of channel 1 or 3 (SPLIT) */
#define _0000_TAU_16BITS_MODE                   (0x0000U) /* operates as 16 bits timer */  
#define _0800_TAU_8BITS_MODE                    (0x0800U) /* operates as 8 bits timer */
/* Setting of start trigger or capture trigger of channel n (STSmn2 - STSmn0) */
#define _0000_TAU_TRIGGER_SOFTWARE              (0x0000U) /* only software trigger start is valid */
#define _0100_TAU_TRIGGER_TIMN_VALID            (0x0100U) /* TImn input edge is used as a start/capture trigger */
#define _0200_TAU_TRIGGER_TIMN_BOTH             (0x0200U) /* TImn input edges are used as a start/capture trigger */
#define _0400_TAU_TRIGGER_MASTER_INT            (0x0400U) /* interrupt signal of the master channel is used */
/* Selection of TImn pin input valid edge (CISmn1 - CISmn0) */
#define _0000_TAU_TIMN_EDGE_FALLING             (0x0000U) /* falling edge */
#define _0040_TAU_TIMN_EDGE_RISING              (0x0040U) /* rising edge */
#define _0080_TAU_TIMN_EDGE_BOTH_LOW            (0x0080U) /* both edges (when low-level width is measured) */
#define _00C0_TAU_TIMN_EDGE_BOTH_HIGH           (0x00C0U) /* both edges (when high-level width is measured) */
/* Operation mode of channel n (MDmn3 - MDmn0) */
#define _0000_TAU_MODE_INTERVAL_TIMER           (0x0000U) /* interval timer mode */
#define _0004_TAU_MODE_CAPTURE                  (0x0004U) /* capture mode */
#define _0006_TAU_MODE_EVENT_COUNT              (0x0006U) /* event counter mode */
#define _0008_TAU_MODE_ONE_COUNT                (0x0008U) /* one count mode */
#define _000C_TAU_MODE_HIGHLOW_MEASURE          (0x000CU) /* high-/low-level width measurement mode */
#define _0001_TAU_MODE_PWM_MASTER               (0x0001U) /* PWM Function (Master Channel) mode */
#define _0009_TAU_MODE_PWM_SLAVE                (0x0009U) /* PWM Function (Slave Channel) mode */
#define _0008_TAU_MODE_ONESHOT                  (0x0008U) /* one-shot pulse output mode */
/* Setting of starting counting and interrupt (MDmn0) */
#define _0000_TAU_START_INT_UNUSED              (0x0000U) /* interrupt is not generated when counting is started */
#define _0001_TAU_START_INT_USED                (0x0001U) /* interrupt is generated when counting is started */

/*
    Timer Status Register mn (TSRmn)
*/
/* Counter overflow status of channel n (OVF) */
#define _0000_TAU_OVERFLOW_NOT_OCCURS           (0x0000U) /* overflow does not occur */
#define _0001_TAU_OVERFLOW_OCCURS               (0x0001U) /* overflow occurs */

/*
    Timer Channel Enable Status Register m (TEm)
*/
/* Indication of operation enable/stop status of channel 0 (TEm0) */
#define _0000_TAU_CH0_OPERATION_STOP            (0x0000U) /* operation is stopped */
#define _0001_TAU_CH0_OPERATION_ENABLE          (0x0001U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 1 (TEm1) */
#define _0000_TAU_CH1_OPERATION_STOP            (0x0000U) /* operation is stopped */
#define _0002_TAU_CH1_OPERATION_ENABLE          (0x0002U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 2 (TEm2) */
#define _0000_TAU_CH2_OPERATION_STOP            (0x0000U) /* operation is stopped */
#define _0004_TAU_CH2_OPERATION_ENABLE          (0x0004U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 3 (TEm3) */
#define _0000_TAU_CH3_OPERATION_STOP            (0x0000U) /* operation is stopped */
#define _0008_TAU_CH3_OPERATION_ENABLE          (0x0008U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 1 higher 8 bits (TEHm1) */
#define _0000_TAU_CH1_H8_OPERATION_STOP         (0x0000U) /* operation is stopped */
#define _0200_TAU_CH1_H8_OPERATION_ENABLE       (0x0200U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 3 higher 8 bits (TEHm3) */
#define _0000_TAU_CH3_H8_OPERATION_STOP         (0x0000U) /* operation is stopped */
#define _0800_TAU_CH3_H8_OPERATION_ENABLE       (0x0800U) /* operation is enabled */

/*
    Timer Channel Start Register m (TSm)
*/
/* Operation enable (start) trigger of channel 0 (TSm0) */
#define _0000_TAU_CH0_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0001_TAU_CH0_START_TRG_ON              (0x0001U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 1 (TSm1) */
#define _0000_TAU_CH1_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0002_TAU_CH1_START_TRG_ON              (0x0002U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 2 (TSm2) */
#define _0000_TAU_CH2_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0004_TAU_CH2_START_TRG_ON              (0x0004U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 3 (TSm3) */
#define _0000_TAU_CH3_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0008_TAU_CH3_START_TRG_ON              (0x0008U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 1 higher 8 bits (TSHm1) */
#define _0000_TAU_CH1_H8_START_TRG_OFF          (0x0000U) /* no trigger operation */
#define _0200_TAU_CH1_H8_START_TRG_ON           (0x0200U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 3 higher 8 bits (TSHm3) */
#define _0000_TAU_CH3_H8_START_TRG_OFF          (0x0000U) /* no trigger operation */
#define _0800_TAU_CH3_H8_START_TRG_ON           (0x0800U) /* operation is enabled (start trigger is generated) */

/*
    Timer Channel Stop Register m (TTm)
*/
/* Operation stop trigger of channel 0 (TTm0) */
#define _0000_TAU_CH0_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0001_TAU_CH0_STOP_TRG_ON               (0x0001U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 (TTm1) */
#define _0000_TAU_CH1_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0002_TAU_CH1_STOP_TRG_ON               (0x0002U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 2 (TTm2) */
#define _0000_TAU_CH2_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0004_TAU_CH2_STOP_TRG_ON               (0x0004U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 3 (TTm3) */
#define _0000_TAU_CH3_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0008_TAU_CH3_STOP_TRG_ON               (0x0008U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 higher 8 bits (TTHm1) */
#define _0000_TAU_CH1_H8_STOP_TRG_OFF           (0x0000U) /* no trigger operation */
#define _0200_TAU_CH1_H8_STOP_TRG_ON            (0x0200U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 3 higher 8 bits (TTHm3) */
#define _0000_TAU_CH3_H8_STOP_TRG_OFF           (0x0000U) /* no trigger operation */
#define _0800_TAU_CH3_H8_STOP_TRG_ON            (0x0800U) /* operation is stopped (stop trigger is generated) */

/*
    Timer Input Select Register m (TIS0)
*/
/* Selection of timer input used with channel 0 (TIS04) */
#define _00_TAU_CH0_INPUT_TI00                  (0x00U)   /* input signal of timer input pin (TI00) */
#define _10_TAU_CH0_INPUT_ELC                   (0x10U)   /* event input signal from ELC */
/* Selection of timer input used with channel 1 (TIS02 - TIS00) */
#define _00_TAU_CH1_INPUT_TI01                  (0x00U)   /* input signal of timer input pin (TI01) */
#define _01_TAU_CH1_INPUT_ELC                   (0x01U)   /* event input signal from ELC */
#define _02_TAU_CH1_INPUT_TI01                  (0x02U)   /* input signal of timer input pin (TI01) */
#define _03_TAU_CH1_INPUT_TI01                  (0x03U)   /* input signal of timer input pin (TI01) */
#define _04_TAU_CH1_INPUT_FIL                   (0x04U)   /* internal low speed oscillation colock (fIL) */
#define _05_TAU_CH1_INPUT_FSUB                  (0x05U)   /* sub colock (fSUB) */

/*
    Timer Output Enable Register m (TOEm)
*/
/* Timer output enable/disable of channel 0 (TOEm0) */
#define _0001_TAU_CH0_OUTPUT_ENABLE             (0x0001U) /* the TOm0 operation enabled by count operation */
#define _0000_TAU_CH0_OUTPUT_DISABLE            (0x0000U) /* the TOm0 operation stopped by count operation */
/* Timer output enable/disable of channel 1 (TOEm1) */
#define _0002_TAU_CH1_OUTPUT_ENABLE             (0x0002U) /* the TOm1 operation enabled by count operation */
#define _0000_TAU_CH1_OUTPUT_DISABLE            (0x0000U) /* the TOm1 operation stopped by count operation */
/* Timer output enable/disable of channel 2 (TOEm2) */
#define _0004_TAU_CH2_OUTPUT_ENABLE             (0x0004U) /* the TOm2 operation enabled by count operation */
#define _0000_TAU_CH2_OUTPUT_DISABLE            (0x0000U) /* the TOm2 operation stopped by count operation */
/* Timer output enable/disable of channel 3 (TOEm3) */
#define _0008_TAU_CH3_OUTPUT_ENABLE             (0x0008U) /* the TOm3 operation enabled by count operation */
#define _0000_TAU_CH3_OUTPUT_DISABLE            (0x0000U) /* the TOm3 operation stopped by count operation */

/*
    Timer Output Register m (TOm)
*/
/* Timer output of channel 0 (TOm0) */
#define _0000_TAU_CH0_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0001_TAU_CH0_OUTPUT_VALUE_1            (0x0001U) /* timer output value is "1" */
/* Timer output of channel 1 (TOm1) */
#define _0000_TAU_CH1_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0002_TAU_CH1_OUTPUT_VALUE_1            (0x0002U) /* timer output value is "1" */
/* Timer output of channel 2 (TOm2) */
#define _0000_TAU_CH2_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0004_TAU_CH2_OUTPUT_VALUE_1            (0x0004U) /* timer output value is "1" */
/* Timer output of channel 3 (TOm3) */
#define _0000_TAU_CH3_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0008_TAU_CH3_OUTPUT_VALUE_1            (0x0008U) /* timer output value is "1" */

/*
    Timer Output Level Register 0 (TOLm)
*/
/* Control of timer output level of channel 1 (TOLm1) */
#define _0000_TAU_CH1_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0002_TAU_CH1_OUTPUT_LEVEL_L            (0x0002U) /* inverted output (active-low) */
/* Control of timer output level of channel 2 (TOLm2) */
#define _0000_TAU_CH2_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0004_TAU_CH2_OUTPUT_LEVEL_L            (0x0004U) /* inverted output (active-low) */
/* Control of timer output level of channel 3 (TOLm3) */
#define _0000_TAU_CH3_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0008_TAU_CH3_OUTPUT_LEVEL_L            (0x0008U) /* inverted output (active-low) */

/*
    Timer Output Mode Register m (TOMm)
*/
/* Control of timer output mode of channel 1 (TOMm1) */
#define _0000_TAU_CH1_OUTPUT_TOGGLE             (0x0000U) /* toggle operation mode */
#define _0002_TAU_CH1_OUTPUT_COMBIN             (0x0002U) /* combination operation mode */
/* Control of timer output mode of channel 2 (TOMm2) */
#define _0000_TAU_CH2_OUTPUT_TOGGLE             (0x0000U) /* toggle operation mode */
#define _0004_TAU_CH2_OUTPUT_COMBIN             (0x0004U) /* combination operation mode */
/* Control of timer output mode of channel 3 (TOMm3) */
#define _0000_TAU_CH3_OUTPUT_TOGGLE             (0x0000U) /* toggle operation mode */
#define _0008_TAU_CH3_OUTPUT_COMBIN             (0x0008U) /* combination operation mode */

/*
    Input Switch Control Register (ISC)
*/
/* Switching channel 7 input of timer array unit (ISC1) */
#define _00_TAU_CH7_NO_INPUT                    (0x00U)   /* timer input is not used */
#define _02_TAU_CH7_RXD3_INPUT                  (0x02U)   /* input signal of RxD3 pin is used as timer input */

/*
    Noise Filter Enable Register 1 (NFEN1)
*/
/* Enable/disable using noise filter of TI03 pin input signal (TNFEN03) */
#define _00_TAU_CH3_NOISE_OFF                   (0x00U)   /* noise filter OFF */
#define _08_TAU_CH3_NOISE_ON                    (0x08U)   /* noise filter ON */
/* Enable/disable using noise filter of TI02 pin input signal (TNFEN02) */
#define _00_TAU_CH2_NOISE_OFF                   (0x00U)   /* noise filter OFF */
#define _04_TAU_CH2_NOISE_ON                    (0x04U)   /* noise filter ON */
/* Enable/disable using noise filter of TI01 pin input signal (TNFEN01) */
#define _00_TAU_CH1_NOISE_OFF                   (0x00U)   /* noise filter OFF */
#define _02_TAU_CH1_NOISE_ON                    (0x02U)   /* noise filter ON */
/* Enable/disable using noise filter of TI00 pin input signal (TNFEN00) */
#define _00_TAU_CH0_NOISE_OFF                   (0x00U)   /* noise filter OFF */
#define _01_TAU_CH0_NOISE_ON                    (0x01U)   /* noise filter ON */

/*
    Format of Peripheral Enable Register 1 (PER1)
*/
/* Control of timer RJ0 input clock supply (TRJ0EN) */
#define _00_TMRJ_CLOCK_STOP                     (0x00U)    /* stops input clock supply */
#define _01_TMRJ_CLOCK_ENABLE                   (0x01U)    /* enables input clock supply */

/* 
    Timer RJ Control Register (TRJCR0)
*/
/* Timer RJ count start bit (TSTART) */
#define _00_TMRJ_COUNT_STOP                     (0x00U)    /* count stops */
#define _01_TMRJ_COUNT_START                    (0x01U)    /* count starts */
/* Timer RJ count status flag (TCSTF) */
#define _00_TMRJ_STATUS_STOP                    (0x00U)    /* count stops */
#define _02_TMRJ_STATUS_COUNT                   (0x02U)    /* during count */
/* Timer RJ count forcible stop bit (TSTOP) */
#define _00_TMRJ_FORCIBLE_STOP_DISABLE          (0x00U)    /* the count is not forcibly stopped */
#define _04_TMRJ_FORCIBLE_STOP_ENABLE           (0x04U)    /* the count is forcibly stopped */
/* Active edge judgment flag (TEDGF) */
#define _00_TMRJ_ACTIVE_EDGE_RECEIVED           (0x00U)    /* active edge not received */
#define _10_TMRJ_ACTIVE_EDGE_UNRECEIVED         (0x10U)    /* active edge received (end of measurement period) */
/* Timer RJ underflow flag (TUNDF) */
#define _00_TMRJ_UNDERFLOW_NOOCCUR              (0x00U)    /* no underflow */
#define _20_TMRJ_UNDERFLOW_OCCUR                (0x20U)    /* underflow */

/* 
    Timer RJ I/O Control Register (TRJIOC0)
*/
#define _00_TMRJ_TRJIOC_INITIAL_VALUE           (0x00U)
/* TRJIO polarity switch bit (TEDGSEL) */
#define _00_TMRJ_TRJIO_POLARITY_0               (0x00U)    /* TRJIO polarity switch bit = 0  */
#define _01_TMRJ_TRJIO_POLARITY_1               (0x01U)    /* TRJIO polarity switch bit = 1 */
/* TRJO output enable bit (TOENA) */
#define _00_TMRJ_TRJO_OUTPUT_DISABLE            (0x00U)    /* TRJO output disable */
#define _04_TMRJ_TRJO_OUTPUT_ENABLE             (0x04U)    /* TRJO output */ 
/* TRJIO input filter select bit (TIPF1, TIPF0) */
#define _00_TMRJ_TRJIO_FILTER_UNUSED            (0x00U)    /* no filter */
#define _10_TMRJ_TRJIO_FILTER_FCLK              (0x10U)    /* filter with fCLK sampling */
#define _20_TMRJ_TRJIO_FILTER_FCLK8             (0x20U)    /* filter with fCLK/8 sampling */
#define _30_TMRJ_TRJIO_FILTER_FCLK32            (0x30U)    /* filter with fCLK/32 sampling */
/* TRJIO event input control bit (TIOGT1, TIOGT0) */
#define _00_TMRJ_EVENT_ENABLE_ALWAYS            (0x00U)    /* event is counted */
#define _40_TMRJ_EVENT_ENABLE_INTP4             (0x40U)    /* event is counted during INTP4 specified period */
#define _80_TMRJ_EVENT_ENABLE_PWM               (0x80U)    /* event is counted during PWM signal period */

/* 
    Timer RJ Mode Register (TRJMR0)
*/
/* Timer RJ operating mode select bit (TMOD2 - TMOD0) */
#define _00_TMRJ_MODE_TIMER                     (0x00U)    /* timer mode */
#define _01_TMRJ_MODE_PULSE_OUTPUT              (0x01U)    /* pulse output mode */
#define _02_TMRJ_MODE_EVENT_COUNTER             (0x02U)    /* event counter mode */
#define _03_TMRJ_MODE_PULSE_WIDTH               (0x03U)    /* pulse width measurement mode */
#define _04_TMRJ_MODE_PULSE_PERIOD              (0x04U)    /* pulse period measurement mode */
/* TRJIO input polarity select bit (TEDGPL) */
#define _00_TMRJ_TRJIO_POLARITY_ONE             (0x00U)    /* one edge */
#define _08_TMRJ_TRJIO_POLARITY_BOTH            (0x08U)    /* both edges */
/* Timer RJ count source select bit (TCK2 - TCK0) */
#define _00_TMRJ_COUNT_SOURCE_FCLK              (0x00U)    /* fCLK */
#define _10_TMRJ_COUNT_SOURCE_FCLK8             (0x10U)    /* fCLK8 */
#define _30_TMRJ_COUNT_SOURCE_FCLK2             (0x30U)    /* fCLK2 */
#define _40_TMRJ_COUNT_SOURCE_FIL               (0x40U)    /* fIL */
#define _50_TMRJ_COUNT_SOURCE_FELC              (0x50U)    /* event input from event link controller (ELC) */
#define _60_TMRJ_COUNT_SOURCE_FSUB              (0x60U)    /* fSUB */

/*
    Timer RJ event pin selection register 0 (TRJISR0)
*/
/* PWM signal selection (RCCPSEL1, RCCPSEL0) */
#define _00_TMRJ_PWM_TRDIOD1                    (0x00U)    /* TRDIOD1 */
#define _01_TMRJ_PWM_TRDIOC1                    (0x01U)    /* TRDIOC1 */
#define _02_TMRJ_PWM_TO02                       (0x02U)    /* TO02 */
#define _03_TMRJ_PWM_TO03                       (0x03U)    /* TO03 */
/* PWM signal and INTP4 polarity selection (RCCPSEL2) */
#define _00_TMRJ_PWM_POLARITY_L                 (0x00U)    /* L period is counted */
#define _04_TMRJ_PWM_POLARITY_H                 (0x04U)    /* H period is counted */

/* 
     Peripheral enable register 1 (PER1)
*/
/* Control of timer RD input clock supply (TRD0EN) */
#define _00_TMRD_NOSUPPLY                       (0x00U)   /* stops input clock supply */
#define _10_TMRD_SUPPLY                         (0x10U)   /* enables input clock supply */

/* 
    Timer RD ELC Register (TRDELC)
*/
/* ELC event input 0 select for timer RD input capture D0 (ELCICE0) */
#define _00_TMRD0_INPUTCAPTURE                  (0x00U)   /* input capture D0 is selected */
#define _01_TMRD0_ELC                           (0x01U)   /* the event link controller (ELC) is not selected */
/* ELC event input 0 enable for timer RD pulse output forced cutoff (ELCOBE0) */
#define _00_TMRD0_CUTOFF_DISABLED               (0x00U)   /* forced cutoff is disabled */
#define _02_TMRD0_CUTOFF_ENABLED                (0x02U)   /* forced cutoff is enabled */
/* ELC event input 1 select for timer RD input capture D1 (ELCICE1) */
#define _00_TMRD1_INPUTCAPTURE                  (0x00U)   /* input capture D1 is selected */
#define _10_TMRD1_ELC                           (0x10U)   /* event link controller (ELC) is selected */
/* ELC event input 1 enable for timer RD pulse output forced cutoff (ELCOBE1) */
#define _00_TMRD1_CUTOFF_DISABLED               (0x00U)   /* forced cutoff is disabled */
#define _20_TMRD1_CUTOFF_ENABLED                (0x20U)   /* forced cutoff is enabled */

/*
    Timer RD Start Register (TRDSTR)
*/
#define _03_TRD_COUNT_STATR_INITIAL_VALUE       (0x03U)   /* trd0/trd1 count satrts */
/* TRD0 count start flag (TSTART0) */
#define _00_TMRD_TRD0_COUNT_STOP                (0x00U)   /* trd0 count stops */
#define _01_TMRD_TRD0_COUNT_START               (0x01U)   /* trd0 count starts */
/* TRD1 count start flag (TSTART1) */
#define _00_TMRD_TRD1_COUNT_STOP                (0x00U)   /* trd1 count stops */
#define _02_TMRD_TRD1_COUNT_START               (0x02U)   /* trd1 count starts */
/* TRD0 count operation select bit (CSEL0) */
#define _00_TMRD_TRD0_COUNT_STOP_MATCH          (0x00U)   /* count stops at the compare match */
#define _04_TMRD_TRD0_COUNT_CONTINUES           (0x04U)   /* count continues after the compare match */
/* TRD1 count operation select bit (CSEL1) */
#define _00_TMRD_TRD1_COUNT_STOP_MATCH          (0x00U)   /* count stops at the compare match */
#define _08_TMRD_TRD1_COUNT_CONTINUES           (0x08U)   /* count continues after the compare match */

/* 
    Timer RD Mode Register (TRDMR)
*/
/* Timer RD synchronous bit (SYNC) */
#define _00_TMRD_INDEPENDENTLY                  (0x00U)   /* registers TRD0 and TRD1 operate independently */
#define _01_TMRD_SYNCHRONOUSLY                  (0x01U)   /* registers TRD0 and TRD1 operate synchronously */
/* TRDGRC0 register function select bit (BFC0) */
#define _00_TMRD_TRDGRC0_GENERAL                (0x00U)   /* general register */
#define _10_TMRD_TRDGRC0_BUFFER                 (0x10U)   /* buffer register of TRDGRA0 register */
/* TRDGRD0 register function select bit (BFD0) */
#define _00_TMRD_TRDGRD0_GENERAL                (0x00U)   /* general register */
#define _20_TMRD_TRDGRD0_BUFFER                 (0x20U)   /* buffer register of TRDGRB0 register */
/* TRDGRC1 register function select bit (BFC1) */
#define _00_TMRD_TRDGRC1_GENERAL                (0x00U)   /* general register */
#define _40_TMRD_TRDGRC1_BUFFER                 (0x40U)   /* buffer register of TRDGRA1 register */
/* TRDGRD1 register function select bit (BFD1) */
#define _00_TMRD_TRDGRD1_GENERAL                (0x00U)   /* general register */
#define _80_TMRD_TRDGRD1_BUFFER                 (0x80U)   /* buffer register of TRDGRB1 register */

/* 
    Timer RD PWM Mode Register (TRDPMR)
*/
/* PWM mode of TRDIOB0 select bit (PWMB0) */
#define _00_TMRD_TRDIOB0_TIMER_MODE             (0x00U)   /* TRDIOB0 used as timer mode */
#define _01_TMRD_TRDIOB0_PWM_MODE               (0x01U)   /* TRDIOB0 used as PWM mode */
/* PWM mode of TRDIOC0 select bit (PWMC0) */
#define _00_TMRD_TRDIOC0_TIMER_MODE             (0x00U)   /* TRDIOC0 used as timer mode */
#define _02_TMRD_TRDIOC0_PWM_MODE               (0x02U)   /* TRDIOC0 used as PWM mode */
/* PWM mode of TRDIOD0 select bit (PWMD0) */
#define _00_TMRD_TRDIOD0_TIMER_MODE             (0x00U)   /* TRDIOD0 used as timer mode */
#define _04_TMRD_TRDIOD0_PWM_MODE               (0x04U)   /* TRDIOD0 used as PWM mode */
/* PWM mode of TRDIOB1 select bit (PWMB1) */
#define _00_TMRD_TRDIOB1_TIMER_MODE             (0x00U)   /* TRDIOB1 used as timer mode */
#define _10_TMRD_TRDIOB1_PWM_MODE               (0x10U)   /* TRDIOB1 used as PWM mode */
/* PWM mode of TRDIOC1 select bit (PWMC1) */
#define _00_TMRD_TRDIOC1_TIMER_MODE             (0x00U)   /* TRDIOC1 used as timer mode */
#define _20_TMRD_TRDIOC1_PWM_MODE               (0x20U)   /* TRDIOC1 used as PWM mode */
/* PWM mode of TRDIOD1 select bit (PWMD1) */
#define _00_TMRD_TRDIOD1_TIMER_MODE             (0x00U)   /* TRDIOD1 used as timer mode */
#define _40_TMRD_TRDIOD1_PWM_MODE               (0x40U)   /* TRDIOD1 used as PWM mode */

/* 
    Timer RD Function Control Register (TRDFCR)
*/
/* Combination mode select bit (CMD1, CMD0) */
#define _00_TMRD_TRANSFER_DEFAULT               (0x00U)   /* in timer mode, PWM mode, or PWM3 mode */
#define _01_TMRD_TRANSFER_RESET_SYNCHRONOUS     (0x01U)   /* in reset synchronous PWM mode */
#define _02_TMRD_TRANSFER_TMRD1_UNDERFLOW       (0x02U)   /* transfer from buffer register to general register */
#define _03_TMRD_TRANSFER_TMRD0_MATCH           (0x03U)   /* transfer from buffer register to general register */
/* Normal-phase output level select bit (OLS0) */
#define _00_TMRD_NORMAL_PHASE_LEVEl_HL          (0x00U)   /* initial output "H", Active level "L" */
#define _04_TMRD_NORMAL_PHASE_LEVEl_LH          (0x04U)   /* initial output "L", Active level "H" */
/* Counter-phase output level select bit (OLS1) */
#define _00_TMRD_COUNTER_PHASE_LEVEl_HL         (0x00U)   /* initial output "H", Active level "L" */
#define _08_TMRD_COUNTER_PHASE_LEVEl_LH         (0x08U)   /* initial output "L", Active level "H" */
/* External clock input select bit (STCLK) */
#define _00_TMRD_EXTERNAL_CLOCK_DISABLE         (0x00U)   /* external clock input disabled */
#define _40_TMRD_EXTERNAL_CLOCK_ENABLE          (0x40U)   /* external clock input enabled  */
/* PWM3 mode select bit (PWM3) */   
#define _00_TMRD_PWM3_MODE                      (0x00U)   /* PWM3 mode */
#define _80_TMRD_OTHER_MODE                     (0x80U)   /* other mode */

/* 
    Timer RD Output Master Enable Register 1 (TRDOER1)
*/
#define _F0_TMRD_CHANNEL0_OUTPUT_DEFAULT        (0xF0U)
#define _0F_TMRD_CHANNEL1_OUTPUT_DEFAULT        (0x0FU)
/* TRDIOA0 output disable bit (EA0) */
#define _00_TMRD_TRDIOA0_OUTPUT_ENABLE          (0x00U)   /* enable output */
#define _01_TMRD_TRDIOA0_OUTPUT_DISABLE         (0x01U)   /* disable output */
/* TRDIOB0 output disable bit (EB0) */
#define _00_TMRD_TRDIOB0_OUTPUT_ENABLE          (0x00U)   /* enable output */
#define _02_TMRD_TRDIOB0_OUTPUT_DISABLE         (0x02U)   /* disable output */
/* TRDIOC0 output disable bit (EC0) */
#define _00_TMRD_TRDIOC0_OUTPUT_ENABLE          (0x00U)   /* enable output */
#define _04_TMRD_TRDIOC0_OUTPUT_DISABLE         (0x04U)   /* disable output */
/* TRDIOD0 output disable bit (ED0) */
#define _00_TMRD_TRDIOD0_OUTPUT_ENABLE          (0x00U)   /* enable output */
#define _08_TMRD_TRDIOD0_OUTPUT_DISABLE         (0x08U)   /* disable output */
/* TRDIOA1 output disable bit (EA1) */
#define _00_TMRD_TRDIOA1_OUTPUT_ENABLE          (0x00U)   /* enable output */
#define _10_TMRD_TRDIOA1_OUTPUT_DISABLE         (0x10U)   /* disable output */
/* TRDIOB1 output disable bit (EB1) */
#define _00_TMRD_TRDIOB1_OUTPUT_ENABLE          (0x00U)   /* enable output */
#define _20_TMRD_TRDIOB1_OUTPUT_DISABLE         (0x20U)   /* disable output */
/* TRDIOC1 output disable bit (EC1) */
#define _00_TMRD_TRDIOC1_OUTPUT_ENABLE          (0x00U)   /* enable output */
#define _40_TMRD_TRDIOC1_OUTPUT_DISABLE         (0x40U)   /* disable output */
/* TRDIOD1 output disable bit (ED1) */
#define _00_TMRD_TRDIOD1_OUTPUT_ENABLE          (0x00U)   /* enable output */
#define _80_TMRD_TRDIOD1_OUTPUT_DISABLE         (0x80U)   /* disable output */

/* 
    Timer RD Output Master Enable Register 2 (TRDOER2)
*/
/* INT0 of pulse output forced cutoff signal input enabled bit (PTO) */
#define _00_TMRD_ALL_OUTPUT_DISABLE             (0x00U)   /* pulse output forced cutoff input disabled */
#define _80_TMRD_ALL_OUTPUT_ENABLE              (0x80U)   /* pulse output forced cutoff input enabled */
/* Forced cutoff flag (SHUTS) */
#define _00_TMRD_INTERCEPTION_STOP              (0x00U)   /* not forcibly cut off */
#define _01_TMRD_INTERCEPTION                   (0x01U)   /* forcibly cut off */

/* 
    Timer RD Output Control Register (TRDOCR)
*/
/* TRDIOA0 output level select bit (TOA0) */
#define _00_TMRD_TRDIOA0_INITIAL_OUTPUT_L       (0x00U)   /* initial output "L" or inactive level */
#define _01_TMRD_TRDIOA0_INITIAL_OUTPUT_H       (0x01U)   /* initial output "H" or active level */
/* TRDIOB0 output level select bit (TOB0) */
#define _00_TMRD_TRDIOB0_INITIAL_OUTPUT_L       (0x00U)   /* initial output "L" or inactive level */
#define _02_TMRD_TRDIOB0_INITIAL_OUTPUT_H       (0x02U)   /* initial output "H" or active level */
/* TRDIOC0 output level select bit (TOC0) */
#define _00_TMRD_TRDIOC0_INITIAL_OUTPUT_L       (0x00U)   /* initial output "L" or inactive level */
#define _04_TMRD_TRDIOC0_INITIAL_OUTPUT_H       (0x04U)   /* initial output "H" or active level */
/* TRDIOD0 output level select bit (TOD0) */
#define _00_TMRD_TRDIOD0_INITIAL_OUTPUT_L       (0x00U)   /* initial output "L" or inactive level */
#define _08_TMRD_TRDIOD0_INITIAL_OUTPUT_H       (0x08U)   /* initial output "H" or active level */
/* TRDIOA1 output level select bit (TOA1) */
#define _00_TMRD_TRDIOA1_INITIAL_OUTPUT_L       (0x00U)   /* initial output "L" or inactive level */
#define _10_TMRD_TRDIOA1_INITIAL_OUTPUT_H       (0x10U)   /* initial output "H" or active level */
/* TRDIOB1 output level select bit (TOB1) */
#define _00_TMRD_TRDIOB1_INITIAL_OUTPUT_L       (0x00U)   /* initial output "L" or inactive level */
#define _20_TMRD_TRDIOB1_INITIAL_OUTPUT_H       (0x20U) /* initial output "H" or active level */
/* TRDIOC1 output level select bit (TOC1) */
#define _00_TMRD_TRDIOC1_INITIAL_OUTPUT_L       (0x00U)   /* initial output "L" or inactive level */
#define _40_TMRD_TRDIOC1_INITIAL_OUTPUT_H       (0x40U)   /* initial output "H" or active level */
/* TRDIOD1 output level select bit (TOD1) */
#define _00_TMRD_TRDIOD1_INITIAL_OUTPUT_L       (0x00U)   /* initial output "L" or inactive level */
#define _80_TMRD_TRDIOD1_INITIAL_OUTPUT_H       (0x80U)   /* initial output "H" or active level */

/* 
    Timer RD Digital Filter Function Select Register i (TRDDFi)
*/
/* TRDIOA pin digital filter function select bit (DFA) */
#define _00_TMRD_TRDIOA_DIGITAL_FILTER_DISABLE  (0x00U)   /* TRDIOA pin digital filter function is not used */
#define _01_TMRD_TRDIOA_DIGITAL_FILTER_ENABLE   (0x01U)   /* TRDIOA pin digital filter function is used */
/* TRDIOB pin digital filter function select bit (DFB) */
#define _00_TMRD_TRDIOB_DIGITAL_FILTER_DISABLE  (0x00U)   /* TRDIOB pin digital filter function is not used */
#define _02_TMRD_TRDIOB_DIGITAL_FILTER_ENABLE   (0x02U)   /* TRDIOB pin digital filter function is used */
/* TRDIOD pin pulse forced cutoff control (DFB, DFA) */
#define _00_TMRD_TRDIOD_FORCEDCUTOFF_DISABLE    (0x00U)   /* forced cutoff disabled */
#define _01_TMRD_TRDIOD_HIGHIMPEDANCE_OUTPUT    (0x01U)   /* high-impedance output */
#define _02_TMRD_TRDIOD_LOW_OUTPUT              (0x02U)   /* low output */
#define _03_TMRD_TRDIOD_HIGH_OUTPUT             (0x03U)   /* high output */
/* TRDIOC pin digital filter function select bit (DFC) */
#define _00_TMRD_TRDIOC_DIGITAL_FILTER_DISABLE  (0x00U)   /* TRDIOC pin digital filter function is not used */
#define _04_TMRD_TRDIOC_DIGITAL_FILTER_ENABLE   (0x04U)   /* TRDIOC pin digital filter function is used */
/* TRDIOD pin digital filter function select bit (DFD) */
#define _00_TMRD_TRDIOD_DIGITAL_FILTER_DISABLE  (0x00U)   /* TRDIOD pin digital filter function is not used */
#define _08_TMRD_TRDIOD_DIGITAL_FILTER_ENABLE   (0x08U)   /* TRDIOD pin digital filter function is used */
/* TRDIOC pin pulse forced cutoff control (DFD, DFC) */
#define _00_TMRD_TRDIOC_FORCEDCUTOFF_DISABLE    (0x00U)   /* forced cutoff disabled */
#define _04_TMRD_TRDIOC_HIGHIMPEDANCE_OUTPUT    (0x04U)   /* high-impedance output */
#define _08_TMRD_TRDIOC_LOW_OUTPUT              (0x08U)   /* low output */
#define _0C_TMRD_TRDIOC_HIGH_OUTPUT             (0x0CU)   /* high output */
/* TRDIOB pin pulse forced cutoff control (PENB1, PENB0) */
#define _00_TMRD_TRDIOB_FORCEDCUTOFF_DISABLE    (0x00U)   /* forced cutoff disabled */
#define _10_TMRD_TRDIOB_HIGHIMPEDANCE_OUTPUT    (0x10U)   /* high-impedance output */
#define _20_TMRD_TRDIOB_LOW_OUTPUT              (0x20U)   /* low output */
#define _30_TMRD_TRDIOB_HIGH_OUTPUT             (0x30U)   /* high output */
/* Clock select bits for digital filter function (DFCK1, DFCK0) */
#define _00_TMRD_DIGITAL_FILTER_CLOCK_F32       (0x00U)   /* fCLK/2^5 */
#define _40_TMRD_DIGITAL_FILTER_CLOCK_F8        (0x40U)   /* fCLK/2^3 */
#define _80_TMRD_DIGITAL_FILTER_CLOCK_F1        (0x80U)   /* fCLK */
#define _C0_TMRD_DIGITAL_FILTER_CLOCK_SOURCE    (0xC0U)   /* count source */
/* TRDIOA pin pulse forced cutoff control (DFCK1, DFCK0) */
#define _00_TMRD_TRDIOA_FORCEDCUTOFF_DISABLE    (0x00U)   /* forced cutoff disabled */
#define _40_TMRD_TRDIOA_HIGHIMPEDANCE_OUTPUT    (0x40U)   /* high-impedance output */
#define _80_TMRD_TRDIOA_LOW_OUTPUT              (0x80U)   /* low output */
#define _C0_TMRD_TRDIOA_HIGH_OUTPUT             (0xC0U)   /* high output */

/* 
    Timer RD Control Register i (TRDCRi)
*/
/* Count source select bit (TCK2 - TCK0) */
#define _00_TMRD_INETNAL_CLOCK_F1_FIH           (0x00U)   /* fCLK, fIH */
#define _01_TMRD_INETNAL_CLOCK_F2               (0x01U)   /* fCLK/2 */
#define _02_TMRD_INETNAL_CLOCK_F4               (0x02U)   /* fCLK/2^2 */
#define _03_TMRD_INETNAL_CLOCK_F8               (0x03U)   /* fCLK/2^3 */
#define _04_TMRD_INETNAL_CLOCK_F32              (0x04U)   /* fCLK/2^5 */
#define _05_TMRD_INETNAL_CLOCK_TRDCLK           (0x05U)   /* TRDCLK input */
/* External clock edge select bit (CKEG1, CKEG0) */
#define _00_TMRD_EXTERNAL_CLOCK_EDGE_RISING     (0x00U)   /* count at the rising edge */
#define _08_TMRD_EXTERNAL_CLOCK_EDGE_FALLING    (0x08U)   /* count at the falling edge */
#define _10_TMRD_EXTERNAL_CLOCK_EDGE_BOTH       (0x10U)   /* count at both edges */
/* TRDi counter clear select bit (CCLR2 - CCLR0) */
#define _00_TMRD_COUNTER_CLEAR_DISABLE          (0x00U)   /* disable clear (free-running operation) */
#define _20_TMRD_COUNTER_CLEAR_TRDGRA           (0x20U)   /* clear with the TRDGRAi register */
#define _40_TMRD_COUNTER_CLEAR_TRDGRB           (0x40U)   /* clear with the TRDGRBi register */
#define _60_TMRD_COUNTER_CLEAR_SYNCHRONOUS      (0x60U)   /* synchronous clear */
#define _A0_TMRD_COUNTER_CLEAR_TRDGRC           (0xA0U)   /* clear by input capture with TRDGRCi register */
#define _C0_TMRD_COUNTER_CLEAR_TRDGRD           (0xC0U)   /* clear by input capture with TRDGRDi register */

/* 
    Timer RD I/O Control Register Ai (TRDIORAi)
*/
/* TRDGRA control bit (IOA1, IOA0) */
#define _00_TMRD_TRDGRA_CAPTURE_RISING          (0x00U)   /* input capture to the TRDGRAi register at the rising edge */
#define _01_TMRD_TRDGRA_CAPTURE_FALLING         (0x01U)   /* input capture to TRDGRAi register at falling edge */
#define _02_TMRD_TRDGRA_CAPTURE_BOTH            (0x02U)   /* input capture to the TRDGRAi register at the both edges */
#define _00_TMRD_TRDGRA_COMPARE_OUTPUT_DISABLE  (0x00U)   /* pin output by compare match is disabled */
#define _01_TMRD_TRDGRA_COMPARE_OUTPUT_LOW      (0x01U)   /* "L" output by compare match with the TRDGRAi register */
#define _02_TMRD_TRDGRA_COMPARE_OUTPUT_HIGH     (0x02U)   /* "H" output by compare match with the TRDGRAi register */
#define _03_TMRD_TRDGRA_COMPARE_OUTPUT_TOGGLE   (0x03U)   /* toggle output by compare match with the TRDGRAi register */
/* TRDGRA mode select bit (IOA2) */
#define _00_TMRD_TRDGRA_COMPARE                 (0x00U)   /* output compare */
#define _04_TMRD_TRDGRA_CAPTURE                 (0x04U)   /* input capture */
/* TRDGRB control bit (IOB1, IOB0) */
#define _00_TMRD_TRDGRB_CAPTURE_RISING          (0x00U)   /* input capture to the TRDGRBi register at the rising edge */
#define _10_TMRD_TRDGRB_CAPTURE_FALLING         (0x10U)   /* input capture to TRDGRBi register at falling edge */
#define _20_TMRD_TRDGRB_CAPTURE_BOTH            (0x20U)   /* input capture to the TRDGRBi register at the both edges */
#define _00_TMRD_TRDGRB_COMPARE_OUTPUT_DISABLE  (0x00U)   /* disable output prohibition by compare agreement */
#define _10_TMRD_TRDGRB_COMPARE_OUTPUT_LOW      (0x10U)   /* "L" output by compare match with the TRDGRBi register */
#define _20_TMRD_TRDGRB_COMPARE_OUTPUT_HIGH     (0x20U)   /* "H" output by compare match with the TRDGRBi register */
#define _30_TMRD_TRDGRB_COMPARE_OUTPUT_TOGGLE   (0x30U)   /* toggle output by compare match with the TRDGRBi register */
/* TRDGRB mode select bit (IOB2) */
#define _00_TMRD_TRDGRB_COMPARE                 (0x00U)   /* output compare */
#define _40_TMRD_TRDGRB_CAPTURE                 (0x40U)   /* input capture */

/* 
    Timer RD I/O Control Register Ci (TRDIORCi)
*/
/* TRDGRC control bit (IOC1, IOC0) */
#define _00_TMRD_TRDGRC_CAPTURE_RISING          (0x00U)   /* input capture to the TRDGRCi register at rising edge */
#define _01_TMRD_TRDGRC_CAPTURE_FALLING         (0x01U)   /* input capture to TRDGRCi register at falling edge */
#define _02_TMRD_TRDGRC_CAPTURE_BOTH            (0x02U)   /* input capture to the TRDGRCi register at the both edges */
#define _00_TMRD_TRDGRC_COMPARE_OUTPUT_DISABLE  (0x00U)   /* disable pin output by the compare match */
#define _01_TMRD_TRDGRC_COMPARE_OUTPUT_LOW      (0x01U)   /* "L" output by compare match with the TRDGRCi register */
#define _02_TMRD_TRDGRC_COMPARE_OUTPUT_HIGH     (0x02U)   /* "H" output by compare match with the TRDGRCi register */
#define _03_TMRD_TRDGRC_COMPARE_OUTPUT_TOGGLE   (0x03U)   /* toggle output by compare match with the TRDGRCi register */
/* TRDGRC mode select bit (IOC2) */
#define _00_TMRD_TRDGRC_COMPARE                 (0x00U)   /* output compare */
#define _04_TMRD_TRDGRC_CAPTURE                 (0x04U)   /* input capture */
/* TRDGRC register function select bit (IOC3) */
#define _00_TMRD_TRDGRC_OUTPUT_REGISTER         (0x00U)   /* output register */
#define _08_TMRD_TRDGRC_GENERAL_BUFFER_REGISTER (0x08U)   /* general register or buffer register */
/* TRDGRD control bit (IOD1, IOD0) */
#define _00_TMRD_TRDGRD_CAPTURE_RISING          (0x00U)   /* input capture to TRDGRDi register at rising edge */
#define _10_TMRD_TRDGRD_CAPTURE_FALLING         (0x10U)   /* input capture to TRDGRDi register at falling edge */
#define _20_TMRD_TRDGRD_CAPTURE_BOTH            (0x20U)   /* input capture to TRDGRDi register at both edges */
#define _00_TMRD_TRDGRD_COMPARE_OUTPUT_DISABLE  (0x00U)   /* disable pin output by the compare match */
#define _10_TMRD_TRDGRD_COMPARE_OUTPUT_LOW      (0x10U)   /* "L" output by compare match with the TRDGRDi register */
#define _20_TMRD_TRDGRD_COMPARE_OUTPUT_HIGH     (0x20U)   /* "H" output by compare match with the TRDGRDi register */
#define _30_TMRD_TRDGRD_COMPARE_OUTPUT_TOGGLE   (0x30U)   /* toggle output by compare match with the TRDGRDi register */
/* TRDGRD mode select bit (IOD2) */
#define _00_TMRD_TRDGRD_COMPARE                 (0x00U)   /* output compare */
#define _40_TMRD_TRDGRD_CAPTURE                 (0x40U)   /* input capture */
/* TRDGRD register function select bit (IOD3) */
#define _00_TMRD_TRDGRD_OUTPUT_REGISTER         (0x00U)   /* output register */
#define _80_TMRD_TRDGRD_GENERAL_BUFFER_REGISTER (0x80U)   /* general register or buffer register */

/* 
    Timer RD Status Register 0 (TRDSR0)
*/
#define _E0_TMRD_TRDSR0_DEFAULT_VALUR           (0xE0U)   /* TRDSR0 register default value */
/* Input capture/compare match flag A (IMFA) */
#define _00_TMRD0_INTA_FLAG_CLEAR               (0x00U)   /* interrupt A not generate */
#define _01_TMRD0_INTA_GENERATE_FLAG            (0x01U)   /* interrupt A generate */
/* Input capture/compare match flag B (IMFB) */
#define _00_TMRD0_INTB_FLAG_CLEAR               (0x00U)   /* interrupt B not generate */
#define _02_TMRD0_INTB_GENERATE_FLAG            (0x02U)   /* interrupt B generate */
/* Input capture/compare match flag C (IMFC) */
#define _00_TMRD0_INTC_FLAG_CLEAR               (0x00U)   /* interrupt C not generate */
#define _04_TMRD0_INTC_GENERATE_FLAG            (0x04U)   /* interrupt C generate */
/* Input capture/compare match flag D (IMFD) */
#define _00_TMRD0_INTD_FLAG_CLEAR               (0x00U)   /* interrupt D not generate */
#define _08_TMRD0_INTD_GENERATE_FLAG            (0x08U)   /* interrupt D generate */
/* Overflow flag (OVF) */
#define _00_TMRD0_INTOV_FLAG_CLEAR              (0x00U)   /* interrupt overflow not generate */
#define _10_TMRD0_INTOV_GENERATE_FLAG           (0x10U)   /* interrupt overflow generate */

/* 
    Timer RD Status Register 1 (TRDSR1)
*/
#define _C0_TMRD_TRDSR1_DEFAULT_VALUR           (0xC0U)   /* TRDSR1 register default value */
/* Input capture/compare match flag A (IMFA) */
#define _00_TMRD1_INTA_FLAG_CLEAR               (0x00U)   /* interrupt A not generate */
#define _01_TMRD1_INTA_GENERATE_FLAG            (0x01U)   /* interrupt A generate */
/* Input capture/compare match flag B (IMFB) */
#define _00_TMRD1_INTB_FLAG_CLEAR               (0x00U)   /* interrupt B not generate */
#define _02_TMRD1_INTB_GENERATE_FLAG            (0x02U)   /* interrupt B generate */
/* Input capture/compare match flag C (IMFC) */
#define _00_TMRD1_INTC_FLAG_CLEAR               (0x00U)   /* interrupt C not generate */
#define _04_TMRD1_INTC_GENERATE_FLAG            (0x04U)   /* interrupt C generate */
/* Input capture/compare match flag D (IMFD) */
#define _00_TMRD1_INTD_FLAG_CLEAR               (0x00U)   /* interrupt D not generate */
#define _08_TMRD1_INTD_GENERATE_FLAG            (0x08U)   /* interrupt D generate */
/* Overflow flag (OVF) */
#define _00_TMRD1_INTOV_FLAG_CLEAR              (0x00U)   /* interrupt overflow not generate */
#define _10_TMRD1_INTOV_GENERATE_FLAG           (0x10U)   /* interrupt overflow generate */

/* 
    Timer RD Interrupt Enable Register i (TRDIERi)
*/
/* Input capture/compare match interrupt enable bit A (IMIEA) */
#define _00_TMRD_IMIA_DISABLE                   (0x00U)   /* disable interrupt (IMIA) by the IMFA bit */
#define _01_TMRD_IMIA_ENABLE                    (0x01U)   /* enable interrupt (IMIA) by the IMFA bit */
/* Input capture/compare match interrupt enable bit B (IMIEB) */
#define _00_TMRD_IMIB_DISABLE                   (0x00U)   /* disable interrupt (IMIB) by the IMFB bit */
#define _02_TMRD_IMIB_ENABLE                    (0x02U)   /* enable interrupt (IMIB) by the IMFB bit */
/* Input capture/compare match interrupt enable bit C (IMIEC) */
#define _00_TMRD_IMIC_DISABLE                   (0x00U)   /* disable interrupt (IMIC) by the IMFC bit */
#define _04_TMRD_IMIC_ENABLE                    (0x04U)   /* enable interrupt (IMIC) by the IMFC bit */
/* Input capture/compare match interrupt enable bit D (IMIED) */
#define _00_TMRD_IMID_DISABLE                   (0x00U)   /* disable interrupt (IMID) by the IMFD bit */
#define _08_TMRD_IMID_ENABLE                    (0x08U)   /* enable interrupt (IMId) by the IMFD bit */
/* Overflow/underflow interrupt enable bit (OVIE) */
#define _00_TMRD_OVIE_DISABLE                   (0x00U)   /* disable interrupt (OVI) by the OVF or UDF bit */
#define _10_TMRD_OVIE_ENABLE                    (0x10U)   /* enable interrupt (OVI) by the OVF or UDF bit */

/* 
    Timer RD PWM Mode Output Level Control Register i (TRDPOCRi)
*/
/* PWM mode output level control bit B (POLB) */
#define _00_TMRD_TRDIOB_OUTPUT_ACTIVE_L         (0x00U)   /* "L" active TRDIOBi output level is selected */
#define _01_TMRD_TRDIOB_OUTPUT_ACTIVE_H         (0x01U)   /* "H" active TRDIOBi output level is selected */
/* PWM mode output level control bit C (POLC) */
#define _00_TMRD_TRDIOC_OUTPUT_ACTIVE_L         (0x00U)   /* "L" active TRDIOCi output level is selected */
#define _02_TMRD_TRDIOC_OUTPUT_ACTIVE_H         (0x02U)   /* "H" active TRDIOCi output level is selected */
/* PWM mode output level control bit D (POLD) */
#define _00_TMRD_TRDIOD_OUTPUT_ACTIVE_L         (0x00U)   /* "L" active TRDIODi output level is selected */
#define _04_TMRD_TRDIOD_OUTPUT_ACTIVE_H         (0x04U)   /* "H" active TRDIODi output level is selected */

/* 
    Timer RG Mode Register (TRGMR)
*/
/* PWM mode select bit (PWM) */
#define _00_TMRG_MODE_TIMER                     (0x00U)   /* timer Mode */
#define _01_TMRG_MODE_PWM                       (0x01U)   /* PWM mode */
/* Phase counting mode select bit (MDF) */
#define _00_TMRG_COUNT_MODE_INCREMENT           (0x00U)   /* increment */
#define _02_TMRG_COUNT_MODE_PHASE               (0x02U)   /* phase counting mode */
/* Digital filer function select bit for TRGIOA pin (DFA) */
#define _00_TMRG_TRGIOA_FILTER_UNUSED           (0x00U)   /* digital filter function not used */
#define _04_TMRG_TRGIOA_FILTER_USED             (0x04U)   /* digital filter function used */
/* Digital filer function select bit for TRGIOB pin (DFB) */
#define _00_TMRG_TRGIOB_FILTER_UNUSED           (0x00U)   /* digital filter function not used */
#define _08_TMRG_TRGIOB_FILTER_USED             (0x08U)   /* digital filter function used */
/* Digital filter function clock select bit (DFCK1 - DFCK0) */
#define _00_TMRG_FILTER_CLOCK_FCLK32            (0x00U)   /* fCLK/2^5 */
#define _10_TMRG_FILTER_CLOCK_FCLK8             (0x10U)   /* fCLK/2^3 */
#define _20_TMRG_FILTER_CLOCK_FCLK              (0x20U)   /* fCLK */
#define _30_TMRG_FILTER_CLOCK_SOURCE            (0x30U)   /* clock selected by bits TCK0 to TCK2 in TRGCR register */
/* ELC input capture request select bit (ELCICE) */
#define _00_TMRG_ELC_UNUSE                      (0x00U)   /* external output signal B is selected */
#define _40_TMRG_ELC_USE                        (0x40U)   /* event input (input capture) from ELC is selected */
/* Timer RG count start bit (TSTART) */
#define _00_TMRG_COUNT_STOP                     (0x00U)   /* count stops */
#define _80_TMRG_COUNT_START                    (0x80U)   /* count starts */

/* 
    Timer RG Count Control Register (TRGCNTC)
*/
/* Counter enable bit 0 (CNTEN0) */
#define _00_TMRG_COUNTER_BIT0_DISABLE           (0x00U)   /* disabled counter 0 */
#define _01_TMRG_COUNTER_BIT0_ENABLE            (0x01U)   /* decrement (TRGCLKA is high and rising edge of TRGCLKB) */
/* Counter enable bit 1 (CNTEN1) */
#define _00_TMRG_COUNTER_BIT1_DISABLE           (0x00U)   /* disabled counter 1 */
#define _02_TMRG_COUNTER_BIT1_ENABLE            (0x02U)   /* decrement (TRGCLKB is low and rising edge of TRGCLKA) */
/* Counter enable bit 2 (CNTEN2) */
#define _00_TMRG_COUNTER_BIT2_DISABLE           (0x00U)   /* disabled counter 2 */
#define _04_TMRG_COUNTER_BIT2_ENABLE            (0x04U)   /* decrement (TRGCLKA is low and falling edge of TRGCLKB) */
/* Counter enable bit 3 (CNTEN3) */
#define _00_TMRG_COUNTER_BIT3_DISABLE           (0x00U)   /* disabled counter 3 */
#define _08_TMRG_COUNTER_BIT3_ENABLE            (0x08U)   /* decrement (TRGCLKB is high and falling edge of TRGCLKA) */
/* Counter enable bit 4 (CNTEN4) */
#define _00_TMRG_COUNTER_BIT4_DISABLE           (0x00U)   /* disabled counter 4 */
#define _10_TMRG_COUNTER_BIT4_ENABLE            (0x10U)   /* increment (TRGCLKB is low and falling edge of TRGCLKA) */
/* Counter enable bit 5 (CNTEN5) */
#define _00_TMRG_COUNTER_BIT5_DISABLE           (0x00U)   /* disabled counter 5 */
#define _20_TMRG_COUNTER_BIT5_ENABLE            (0x20U)   /* increment (TRGCLKA is high and falling edge of TRGCLKB) */
/* Counter enable bit 6 (CNTEN6) */
#define _00_TMRG_COUNTER_BIT6_DISABLE           (0x00U)   /* disabled counter 6 */
#define _40_TMRG_COUNTER_BIT6_ENABLE            (0x40U)   /* increment (TRGCLKB is high and rising edge of TRGCLKA) */
/* Counter enable bit 7 (CNTEN7) */
#define _00_TMRG_COUNTER_BIT7_DISABLE           (0x00U)   /* disabled counter 7 */
#define _80_TMRG_COUNTER_BIT7_ENABLE            (0x80U)   /* increment (TRGCLKA is low and rising edge of TRGCLKB) */

/* 
    Timer RG Control Register (TRGCR)
*/
/* Count source select bit (TCK2 - TCK0) */
#define _00_TMRG_COUNT_SOURCE_FCLK              (0x00U)   /* fCLK */
#define _01_TMRG_COUNT_SOURCE_FCLK2             (0x01U)   /* fCLK/2 */
#define _02_TMRG_COUNT_SOURCE_FCLK4             (0x02U)   /* fCLK/2^2 */
#define _03_TMRG_COUNT_SOURCE_FCLK8             (0x03U)   /* fCLK/2^3 */
#define _04_TMRG_COUNT_SOURCE_FCLK32            (0x04U)   /* fCLK/2^5 */
#define _05_TMRG_COUNT_SOURCE_TRGCLKA           (0x05U)   /* TRGCLKA input */
#define _07_TMRG_COUNT_SOURCE_TRGCLKB           (0x07U)   /* TRGCLKB input */
/* External clock active edge select bit (CKEG1 - CKEG0) */
#define _00_TMRG_ACTIVE_EDGE_RISING             (0x00U)   /* count at the rising edge */
#define _08_TMRG_ACTIVE_EDGE_FALLING            (0x08U)   /* count at the falling edge */
#define _10_TMRG_ACTIVE_EDGE_BOTH               (0x10U)   /* count at both the rising/falling edges */
/* Timer RG register clear source select bit (CCLR1 - CCLR0) */
#define _00_TMRG_CLEAR_SOURCE_DISABLE           (0x00U)   /* clear disabled */
#define _20_TMRG_CLEAR_SOURCE_TRGGRA            (0x20U)   /* cleared by TRGGRA register */
#define _40_TMRG_CLEAR_SOURCE_TRGGRB            (0x40U)   /* cleared by TRGGRB register */

/* 
    Timer RG Interrupt Enable Register (TRGIER)
*/
/* Input-capture/compare-match interrupt enable bit A (IMIEA) */
#define _00_TMRG_INTERRUPT_CAPCOMA_DISABLE      (0x00U)   /* interrupt by IMIEA bit disabled */
#define _01_TMRG_INTERRUPT_CAPCOMA_ENABLE       (0x01U)   /* interrupt by IMIEA bit enabled */
/* Input-capture/compare-match interrupt enable bit B (IMIEB) */
#define _00_TMRG_INTERRUPT_CAPCOMB_DISABLE      (0x00U)   /* interrupt by IMIEB bit disabled */
#define _02_TMRG_INTERRUPT_CAPCOMB_ENABLE       (0x02U)   /* interrupt by IMIEB bit enabled */
/* Underflow interrupt enable bit (UDIE) */
#define _00_TMRG_INTERRUPT_UNDERFLOW_DISABLE    (0x00U)   /* interrupt by UDF bit disabled */
#define _04_TMRG_INTERRUPT_UNDERFLOW_ENABLE     (0x04U)   /* interrupt by UDF bit enabled */
/* Overflow interrupt enable bit (OVIE) */
#define _00_TMRG_INTERRUPT_OVERFLOW_DISABLE     (0x00U)   /* interrupt by OVF bit disabled */
#define _08_TMRG_INTERRUPT_OVERFLOW_ENABLE      (0x08U)   /* interrupt by OVF bit enabled */

/* 
    Timer RG Status Register (TRGSR)
*/
/* Input-capture/compare-match flag A (IMFA) */
#define _00_TMRG_INTA_FLAG_CLEAR                (0x00U)   /* interrupt A not generate */
#define _01_TMRG_INTA_GENERATE_FLAG             (0x01U)   /* interrupt A generate */
/* Input-capture/compare-match flag B (IMFB) */
#define _00_TMRG_INTB_FLAG_CLEAR                (0x00U)   /* interrupt B not generate */
#define _02_TMRG_INTB_GENERATE_FLAG             (0x02U)   /* interrupt B generate */
/* Underflow flag bit (UDF) */
#define _00_TMRG_INTUD_FLAG_CLEAR               (0x00U)   /* interrupt underflow not generate */
#define _04_TMRG_INTUD_GENERATE_FLAG            (0x04U)   /* interrupt underflow generate */
/* Overflow flag bit (OVF) */
#define _00_TMRG_INTOV_FLAG_CLEAR               (0x00U)   /* interrupt overflow not generate */
#define _08_TMRG_INTOV_GENERATE_FLAG            (0x08U)   /* interrupt overflow generate */
/* Count direction flag (DIRF) */
#define _00_TMRG_DIRECTION_FLAG_CLEAR           (0x00U)   /* TRG register is decremented */
#define _10_TMRG_DIRECTION_GENERATE_FLAG        (0x10U)   /* TRG register is incremented */

/* 
    Timer RG I/O Control Register (TRGIOR)
*/
/* TRGGRA control bit (IOA1 - IOA0) */
#define _00_TMRG_TRGGRA_CAPRISING_CMPDISABLE    (0x00U)   /* capture at the rising edge, pin output is disabled */
#define _01_TMRG_TRGGRA_CAPFALLING_CMPLOW       (0x01U)   /* capture at the falling edge, low-level output at compare */
#define _02_TMRG_TRGGRA_CAPBOTH_CMPHIGH         (0x02U)   /* capture at both edges, high-level output at compare */
#define _03_TMRG_TRGGRA_COMPARE_TOGGLE          (0x03U)   /* toggle output at compare match with TRGGRA */
/* TRGGRA mode select bit (IOA2) */
#define _00_TMRG_TRGGRA_MODE_COMPARE            (0x00U)   /* output compare function */
#define _04_TMRG_TRGGRA_MODE_CAPTURE            (0x04U)   /* input capture function */
/* TRGGRC register function select bit (BUFA) */
#define _00_TMRG_TRGGRA_BUFFER_UNUSED           (0x00U)   /* not used as the buffer register of the TRGGRA register */
#define _08_TMRG_TRGGRA_BUFFER_USED             (0x08U)   /* used as the buffer register of the TRGGRA register */
/* TRGGRB control bit (IOB1 - IOB0) */
#define _00_TMRG_TRGGRB_CAPRISING_CMPDISABLE    (0x00U)   /* capture at the rising edge, pin output is disabled */
#define _10_TMRG_TRGGRB_CAPFALLING_CMPLOW       (0x10U)   /* capture at the falling edge, low-level output at compare */
#define _20_TMRG_TRGGRB_CAPBOTH_CMPHIGH         (0x20U)   /* capture at both edges, high-level output at compare */
#define _30_TMRG_TRGGRB_COMPARE_TOGGLE          (0x30U)   /* toggle output at compare match with TRGGRB */
/* TRGGRB mode select bit (IOB2) */
#define _00_TMRG_TRGGRB_MODE_COMPARE            (0x00U)   /* output compare function */
#define _40_TMRG_TRGGRB_MODE_CAPTURE            (0x40U)   /* input capture function */
/* TRGGRD register function select bit (BUFB) */
#define _00_TMRG_TRGGRB_BUFFER_UNUSED           (0x00U)   /* not used as the buffer register of the TRGGRB register */
#define _80_TMRG_TRGGRB_BUFFER_USED             (0x80U)   /* used as the buffer register of the TRGGRB register */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* 16-bit timer data register 00 (TDR00) */
#define _9C3F_TAU_TDR00_VALUE                   (0x9C3FU)
/* Clock divisor for TAU0 channel 0 */
#define _0004_TAU0_CHANNEL0_DIVISOR             (0x0004U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    TMCHANNELA,
    TMCHANNELB,
    TMCHANNELC,
    TMCHANNELD,
    TMCHANNELELC
} timer_channel_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_TAU0_Create(void);
void R_TAU0_Channel0_Start(void);
void R_TAU0_Channel0_Stop(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
