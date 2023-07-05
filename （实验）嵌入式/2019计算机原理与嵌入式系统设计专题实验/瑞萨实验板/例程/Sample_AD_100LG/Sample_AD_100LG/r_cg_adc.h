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
* File Name    : r_cg_adc.h
* Version      : CodeGenerator for RL78/G13 V2.02.01.01 [30 May 2014]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for ADC module.
* Creation Date: 2015-1-21
***********************************************************************************************************************/

#ifndef ADC_H
#define ADC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Peripheral enable register 0 (PER0)
*/
/* Control of AD converter input clock (ADCEN) */
#define _00_AD_CLOCK_STOP               (0x00U) /* stop supply of input clock */
#define _20_AD_CLOCK_SUPPLY             (0x20U) /* supply input clock */

/*
    AD converter mode register 0 (ADM0)
*/
#define _00_AD_ADM0_INITIALVALUE        (0x00U)
/* AD conversion operation control (ADCS) */
#define _80_AD_CONVERSION_ENABLE        (0x80U) /* enable AD conversion operation control */
#define _00_AD_CONVERSION_DISABLE       (0x00U) /* disable AD conversion operation control */
/* Specification of AD conversion operation mode (ADMD) */
#define _00_AD_OPERMODE_SELECT          (0x00U) /* select operation mode */
#define _40_AD_OPERMODE_SCAN            (0x40U) /* scan operation mode */
/* AD conversion clock selection (FR2 - FR0) */
#define _00_AD_CONVERSION_CLOCK_64      (0x00U) /* fCLK/64 */
#define _08_AD_CONVERSION_CLOCK_32      (0x08U) /* fCLK/32 */
#define _10_AD_CONVERSION_CLOCK_16      (0x10U) /* fCLK/16 */
#define _18_AD_CONVERSION_CLOCK_8       (0x18U) /* fCLK/8 */
#define _20_AD_CONVERSION_CLOCK_6       (0x20U) /* fCLK/6 */
#define _28_AD_CONVERSION_CLOCK_5       (0x28U) /* fCLK/5 */
#define _30_AD_CONVERSION_CLOCK_4       (0x30U) /* fCLK/4 */
#define _38_AD_CONVERSION_CLOCK_2       (0x38U) /* fCLK/2 */
/* Specification AD conversion time mode (LV1, LV0) */
#define _00_AD_TIME_MODE_NORMAL_1       (0x00U) /* normal 1 mode */
#define _02_AD_TIME_MODE_NORMAL_2       (0x02U) /* normal 2 mode */
#define _04_AD_TIME_MODE_LOWVOLTAGE_1   (0x04U) /* low-voltage 1 mode */
#define _06_AD_TIME_MODE_LOWVOLTAGE_2   (0x06U) /* low-voltage 2 mode */
/* AD comparator operation control (ADCE) */
#define _01_AD_COMPARATOR_ENABLE        (0x01U) /* enable comparator operation control */
#define _00_AD_COMPARATOR_DISABLE       (0x00U) /* disable comparator operation control */

/*
    Analog input channel specification register (ADS)
*/
/* Specification of analog input channel (ADISS, ADS4 - ADS0) */
/* Select mode */
#define _00_AD_INPUT_CHANNEL_0          (0x00U) /* ANI0 */
#define _01_AD_INPUT_CHANNEL_1          (0x01U) /* ANI1 */
#define _02_AD_INPUT_CHANNEL_2          (0x02U) /* ANI2 */
#define _03_AD_INPUT_CHANNEL_3          (0x03U) /* ANI3 */
#define _04_AD_INPUT_CHANNEL_4          (0x04U) /* ANI4 */
#define _05_AD_INPUT_CHANNEL_5          (0x05U) /* ANI5 */
#define _06_AD_INPUT_CHANNEL_6          (0x06U) /* ANI6 */
#define _07_AD_INPUT_CHANNEL_7          (0x07U) /* ANI7 */
#define _10_AD_INPUT_CHANNEL_16         (0x10U) /* ANI16 */
#define _11_AD_INPUT_CHANNEL_17         (0x11U) /* ANI17 */
#define _12_AD_INPUT_CHANNEL_18         (0x12U) /* ANI18 */
#define _13_AD_INPUT_CHANNEL_19         (0x13U) /* ANI19 */
#define _80_AD_INPUT_TEMPERSENSOR_0     (0x80U) /* temperature sensor 0 output is used to be the input channel */
#define _81_AD_INPUT_INTERREFVOLT       (0x81U) /* internal reference voltage output is used to be the input channel */
/* Scan mode */
#define _00_AD_INPUT_CHANNEL_0_3        (0x00U) /* ANI0 - ANI3 */
#define _01_AD_INPUT_CHANNEL_1_4        (0x01U) /* ANI1 - ANI4 */
#define _02_AD_INPUT_CHANNEL_2_5        (0x02U) /* ANI2 - ANI5 */
#define _03_AD_INPUT_CHANNEL_3_6        (0x03U) /* ANI3 - ANI6 */
#define _04_AD_INPUT_CHANNEL_4_7        (0x04U) /* ANI4 - ANI7 */

/*
    AD converter mode register 1 (ADM1)
*/
/* AD trigger mode selection (ADTMD1, ADTMD0) */
#define _00_AD_TRIGGER_SOFTWARE         (0x00U) /* software trigger mode */
#define _80_AD_TRIGGER_HARDWARE_NOWAIT  (0x80U) /* hardware trigger mode (no wait) */
#define _C0_AD_TRIGGER_HARDWARE_WAIT    (0xC0U) /* hardware trigger mode (wait) */
/* AD convertion mode selection (ADSCM) */
#define _00_AD_CONVMODE_CONSELECT       (0x00U) /* continuous convertion mode */
#define _20_AD_CONVMODE_ONESELECT       (0x20U) /* oneshot convertion mode */
/* Trigger signal selection (ADTRS1, ADTRS0) */
#define _00_AD_TRIGGER_INTTM01          (0x00U) /* INTTM01 */
#define _02_AD_TRIGGER_INTRTC           (0x02U) /* INTRTC */
#define _03_AD_TRIGGER_INTIT            (0x03U) /* INTIT */



/*
    AD converter mode register 2 (ADM2)
*/
/* AD VREF(+) selection (ADREFP1, ADREFP0) */
#define _00_AD_POSITIVE_VDD             (0x00U) /* use VDD as VREF(+) */
#define _40_AD_POSITIVE_AVREFP          (0x40U) /* use AVREFP as VREF(+) */
#define _80_AD_POSITIVE_INTERVOLT       (0x80U) /* use internal voltage as VREF(+) */
/* AD VREF(-) selection (ADREFM) */
#define _00_AD_NEGATIVE_VSS             (0x00U) /* use VSS as VREF(-) */
#define _20_AD_NEGATIVE_AVREFM          (0x20U) /* use AVREFM as VREF(-) */
/* AD conversion result upper/lower bound value selection (ADRCK) */
#define _00_AD_AREA_MODE_1              (0x00U) /* generates INTAD when ADLL <= ADCRH <= ADUL */
#define _08_AD_AREA_MODE_2_3            (0x08U) /* generates INTAD when ADUL < ADCRH or ADLL > ADCRH */
/* AD wakeup function selection (AWC) */
#define _00_AD_WAKEUP_OFF               (0x00U) /* stop wakeup function */
#define _04_AD_WAKEUP_ON                (0x04U) /* use wakeup function */
/* AD resolution selection (ADTYP) */
#define _00_AD_RESOLUTION_10BIT         (0x00U) /* 10 bits */
#define _01_AD_RESOLUTION_8BIT          (0x01U) /* 8 bits */

/*
    AD test function register (ADTES)
*/
/* AD test mode signal (ADTES2 - ADTES0) */
#define _00_AD_NORMAL_INPUT             (0x00U) /* normal mode */
#define _02_AD_TEST_AVREFM              (0x02U) /* use AVREFM as test signal */
#define _03_AD_TEST_AVREFP              (0x03U) /* use AVREFP as test signal */

/*
    AD port configuration register (ADPC)
*/
/* Analog input/digital input switching (ADPC3 - ADPC0) */
#define _00_AD_ADPC_8ANALOG             (0x00U) /* ANI0 - ANI7 */
#define _08_AD_ADPC_7ANALOG             (0x08U) /* ANI0 - ANI6 */
#define _07_AD_ADPC_6ANALOG             (0x07U) /* ANI0 - ANI5 */
#define _06_AD_ADPC_5ANALOG             (0x06U) /* ANI0 - ANI4 */
#define _05_AD_ADPC_4ANALOG             (0x05U) /* ANI0 - ANI3 */
#define _04_AD_ADPC_3ANALOG             (0x04U) /* ANI0 - ANI2 */
#define _03_AD_ADPC_2ANALOG             (0x03U) /* ANI0 - ANI1 */
#define _02_AD_ADPC_1ANALOG             (0x02U) /* ANI0 */
#define _01_AD_ADPC_0ANALOG             (0x01U) /* ANI0 - ANI7 (all digital) */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Upper bound (ADUL) value */
#define _FF_AD_ADUL_VALUE               (0xFFU)
/* Upper bound (ADLL) value */
#define _00_AD_ADLL_VALUE               (0x00U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    ADCHANNEL0, ADCHANNEL1, ADCHANNEL2, ADCHANNEL3, ADCHANNEL4, ADCHANNEL5, 
    ADCHANNEL6, ADCHANNEL7, ADCHANNEL16 = 16U, ADCHANNEL17, ADCHANNEL18,
    ADCHANNEL19, ADTEMPERSENSOR0 = 128U, ADINTERREFVOLT
} ad_channel_t;
typedef enum
{
    ADNORMALINPUT,
    ADAVREFM = 2U,
    ADAVREFP
} test_channel_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_ADC_Create(void);
void R_ADC_Start(void);
void R_ADC_Stop(void);
void R_ADC_Set_OperationOn(void);
void R_ADC_Set_OperationOff(void);
void R_ADC_Get_Result(uint16_t * const buffer);

void delay(unsigned char t);
void Led_display(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
