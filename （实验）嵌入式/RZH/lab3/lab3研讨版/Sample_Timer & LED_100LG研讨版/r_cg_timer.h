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
* File Name    : r_cg_timer.h
* Version      : CodeGenerator for RL78/G13 V2.02.01.01 [30 May 2014]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for TAU module.
* Creation Date: 2015-1-21
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
#define _0000_TAU_COMBINATION_MASTER            (0x0000U) /* channel0 operates as master channel */
#define _0800_TAU_COMBINATION_MASTER            (0x0800U) /* channel2, 4, 6 operates as master channel */
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
/* Indication of operation enable/stop status of channel 4 (TEm4) */
#define _0000_TAU_CH4_OPERATION_STOP            (0x0000U) /* operation is stopped */
#define _0010_TAU_CH4_OPERATION_ENABLE          (0x0010U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 5 (TEm5) */
#define _0000_TAU_CH5_OPERATION_STOP            (0x0000U) /* operation is stopped */
#define _0020_TAU_CH5_OPERATION_ENABLE          (0x0020U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 6 (TEm6) */
#define _0000_TAU_CH6_OPERATION_STOP            (0x0000U) /* operation is stopped */
#define _0040_TAU_CH6_OPERATION_ENABLE          (0x0040U) /* operation is enabled */
/* Indication of operation enable/stop status of channel 7 (TEm7) */
#define _0000_TAU_CH7_OPERATION_STOP            (0x0000U) /* operation is stopped */
#define _0080_TAU_CH7_OPERATION_ENABLE          (0x0080U) /* operation is enabled */
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
/* Operation enable (start) trigger of channel 4 (TSm4) */
#define _0000_TAU_CH4_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0010_TAU_CH4_START_TRG_ON              (0x0010U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 5 (TSm5) */
#define _0000_TAU_CH5_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0020_TAU_CH5_START_TRG_ON              (0x0020U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 6 (TSm6) */
#define _0000_TAU_CH6_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0040_TAU_CH6_START_TRG_ON              (0x0040U) /* operation is enabled (start trigger is generated) */
/* Operation enable (start) trigger of channel 7 (TSm7) */
#define _0000_TAU_CH7_START_TRG_OFF             (0x0000U) /* no trigger operation */
#define _0080_TAU_CH7_START_TRG_ON              (0x0080U) /* operation is enabled (start trigger is generated) */
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
/* Operation stop trigger of channel 4 (TTm4) */
#define _0000_TAU_CH4_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0010_TAU_CH4_STOP_TRG_ON               (0x0010U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 5 (TTm5) */
#define _0000_TAU_CH5_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0020_TAU_CH5_STOP_TRG_ON               (0x0020U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 6 (TTm6) */
#define _0000_TAU_CH6_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0040_TAU_CH6_STOP_TRG_ON               (0x0040U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 7 (TTm7) */
#define _0000_TAU_CH7_STOP_TRG_OFF              (0x0000U) /* no trigger operation */
#define _0080_TAU_CH7_STOP_TRG_ON               (0x0080U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 higher 8 bits (TTHm1) */
#define _0000_TAU_CH1_H8_STOP_TRG_OFF           (0x0000U) /* no trigger operation */
#define _0200_TAU_CH1_H8_STOP_TRG_ON            (0x0200U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 3 higher 8 bits (TTHm3) */
#define _0000_TAU_CH3_H8_STOP_TRG_OFF           (0x0000U) /* no trigger operation */
#define _0800_TAU_CH3_H8_STOP_TRG_ON            (0x0800U) /* operation is stopped (stop trigger is generated) */

/*
    Timer Input Select Register m (TIS0)
*/
/* Selection of timer input used with channel 5 (TIS02 - TIS00) */
#define _00_TAU_CH5_INPUT_TI05                  (0x00U)   /* input signal of timer input pin (TI05) */
#define _01_TAU_CH5_INPUT_TI05                  (0x01U)   /* input signal of timer input pin (TI05) */
#define _02_TAU_CH5_INPUT_TI05                  (0x02U)   /* input signal of timer input pin (TI05) */
#define _03_TAU_CH5_INPUT_TI05                  (0x03U)   /* input signal of timer input pin (TI05) */
#define _04_TAU_CH5_INPUT_FIL                   (0x04U)   /* internal low speed oscillation colock (fIL) */
#define _05_TAU_CH5_INPUT_FSUB                  (0x05U)   /* sub colock (fSUB) */

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
/* Timer output enable/disable of channel 4 (TOEm4) */
#define _0010_TAU_CH4_OUTPUT_ENABLE             (0x0010U) /* the TOm4 operation enabled by count operation */
#define _0000_TAU_CH4_OUTPUT_DISABLE            (0x0000U) /* the TOm4 operation stopped by count operation */
/* Timer output enable/disable of channel 5 (TOEm5) */
#define _0020_TAU_CH5_OUTPUT_ENABLE             (0x0020U) /* the TOm5 operation enabled by count operation */
#define _0000_TAU_CH5_OUTPUT_DISABLE            (0x0000U) /* the TOm5 operation stopped by count operation */
/* Timer output enable/disable of channel 6 (TOEm6) */
#define _0040_TAU_CH6_OUTPUT_ENABLE             (0x0040U) /* the TOm6 operation enabled by count operation */
#define _0000_TAU_CH6_OUTPUT_DISABLE            (0x0000U) /* the TOm6 operation stopped by count operation */
/* Timer output enable/disable of channel 7 (TOEm7) */
#define _0080_TAU_CH7_OUTPUT_ENABLE             (0x0080U) /* the TOm7 operation enabled by count operation */
#define _0000_TAU_CH7_OUTPUT_DISABLE            (0x0000U) /* the TOm7 operation stopped by count operation */

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
/* Timer output of channel 4 (TOm4) */
#define _0000_TAU_CH4_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0010_TAU_CH4_OUTPUT_VALUE_1            (0x0010U) /* timer output value is "1" */
/* Timer output of channel 5 (TOm5) */
#define _0000_TAU_CH5_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0020_TAU_CH5_OUTPUT_VALUE_1            (0x0020U) /* timer output value is "1" */
/* Timer output of channel 6 (TOm6) */
#define _0000_TAU_CH6_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0040_TAU_CH6_OUTPUT_VALUE_1            (0x0040U) /* timer output value is "1" */
/* Timer output of channel 7 (TOm7) */
#define _0000_TAU_CH7_OUTPUT_VALUE_0            (0x0000U) /* timer output value is "0" */
#define _0080_TAU_CH7_OUTPUT_VALUE_1            (0x0080U) /* timer output value is "1" */

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
/* Control of timer output level of channel 4 (TOLm4) */
#define _0000_TAU_CH4_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0010_TAU_CH4_OUTPUT_LEVEL_L            (0x0010U) /* inverted output (active-low) */
/* Control of timer output level of channel 5 (TOLm5) */
#define _0000_TAU_CH5_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0020_TAU_CH5_OUTPUT_LEVEL_L            (0x0020U) /* inverted output (active-low) */
/* Control of timer output level of channel 6 (TOLm6) */
#define _0000_TAU_CH6_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0040_TAU_CH6_OUTPUT_LEVEL_L            (0x0040U) /* inverted output (active-low) */
/* Control of timer output level of channel 7 (TOLm7) */
#define _0000_TAU_CH7_OUTPUT_LEVEL_H            (0x0000U) /* positive logic output (active-high) */
#define _0080_TAU_CH7_OUTPUT_LEVEL_L            (0x0080U) /* inverted output (active-low) */

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
/* Control of timer output mode of channel 4 (TOMm4) */
#define _0000_TAU_CH4_OUTPUT_TOGGLE             (0x0000U) /* toggle operation mode */
#define _0010_TAU_CH4_OUTPUT_COMBIN             (0x0010U) /* combination operation mode */
/* Control of timer output mode of channel 5 (TOMm5) */
#define _0000_TAU_CH5_OUTPUT_TOGGLE             (0x0000U) /* toggle operation mode */
#define _0020_TAU_CH5_OUTPUT_COMBIN             (0x0020U) /* combination operation mode */
/* Control of timer output mode of channel 6 (TOMm6) */
#define _0000_TAU_CH6_OUTPUT_TOGGLE             (0x0000U) /* toggle operation mode */
#define _0040_TAU_CH6_OUTPUT_COMBIN             (0x0040U) /* combination operation mode */
/* Control of timer output mode of channel 7 (TOMm7) */
#define _0000_TAU_CH7_OUTPUT_TOGGLE             (0x0000U) /* toggle operation mode */
#define _0080_TAU_CH7_OUTPUT_COMBIN             (0x0080U) /* combination operation mode */

/*
    Input Switch Control Register (ISC)
*/
/* Switching channel 7 input of timer array unit (ISC1) */
#define _00_TAU_CH7_NO_INPUT                    (0x00U)   /* timer input is not used */
#define _02_TAU_CH7_RXD3_INPUT                  (0x02U)   /* input signal of RxD3 pin is used as timer input */

/*
    Noise Filter Enable Register 1 (NFEN1)
*/
/* Enable/disable using noise filter of TI07 pin input signal (TNFEN07) */
#define _00_TAU_CH7_NOISE_OFF                   (0x00U)   /* noise filter OFF */
#define _80_TAU_CH7_NOISE_ON                    (0x80U)   /* noise filter ON */
/* Enable/disable using noise filter of TI06 pin input signal (TNFEN06) */
#define _00_TAU_CH6_NOISE_OFF                   (0x00U)   /* noise filter OFF */
#define _40_TAU_CH6_NOISE_ON                    (0x40U)   /* noise filter ON */
/* Enable/disable using noise filter of TI05 pin input signal (TNFEN05) */
#define _00_TAU_CH5_NOISE_OFF                   (0x00U)   /* noise filter OFF */
#define _20_TAU_CH5_NOISE_ON                    (0x20U)   /* noise filter ON */
/* Enable/disable using noise filter of TI04 pin input signal (TNFEN04) */
#define _00_TAU_CH4_NOISE_OFF                   (0x00U)   /* noise filter OFF */
#define _10_TAU_CH4_NOISE_ON                    (0x10U)   /* noise filter ON */
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


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* 16-bit timer data register 00 (TDR00) */
#define _C34F_TAU_TDR00_VALUE                   (0xC34FU)
/* Clock divisor for TAU0 channel 0 */
#define _0020_TAU0_CHANNEL0_DIVISOR             (0x0020U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_TAU0_Create(void);
void R_TAU0_Channel0_Start(void);
void R_TAU0_Channel0_Stop(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
