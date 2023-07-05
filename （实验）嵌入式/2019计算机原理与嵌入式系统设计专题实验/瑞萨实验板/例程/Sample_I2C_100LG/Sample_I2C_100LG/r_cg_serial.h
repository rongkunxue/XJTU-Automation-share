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
* File Name    : r_cg_serial.h
* Version      : CodeGenerator for RL78/G13 V2.02.01.01 [30 May 2014]
* Device(s)    : R5F100LG
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for Serial module.
* Creation Date: 2015-1-22
***********************************************************************************************************************/

#ifndef SERIAL_H
#define SERIAL_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Serial Clock Select Register m (SPSm)
*/
/* Operating mode and clear mode selection (PRS003 - PRS000) */
#define _0000_SAU_CK00_FCLK_0            (0x0000U)    /* ck00 - fCLK */
#define _0001_SAU_CK00_FCLK_1            (0x0001U)    /* ck00 - fCLK/2^1 */
#define _0002_SAU_CK00_FCLK_2            (0x0002U)    /* ck00 - fCLK/2^2 */
#define _0003_SAU_CK00_FCLK_3            (0x0003U)    /* ck00 - fCLK/2^3 */
#define _0004_SAU_CK00_FCLK_4            (0x0004U)    /* ck00 - fCLK/2^4 */
#define _0005_SAU_CK00_FCLK_5            (0x0005U)    /* ck00 - fCLK/2^5 */
#define _0006_SAU_CK00_FCLK_6            (0x0006U)    /* ck00 - fCLK/2^6 */
#define _0007_SAU_CK00_FCLK_7            (0x0007U)    /* ck00 - fCLK/2^7 */
#define _0008_SAU_CK00_FCLK_8            (0x0008U)    /* ck00 - fCLK/2^8 */
#define _0009_SAU_CK00_FCLK_9            (0x0009U)    /* ck00 - fCLK/2^9 */
#define _000A_SAU_CK00_FCLK_10           (0x000AU)    /* ck00 - fCLK/2^10 */
#define _000B_SAU_CK00_FCLK_11           (0x000BU)    /* ck00 - fCLK/2^11 */
#define _000C_SAU_CK00_FCLK_12           (0x000CU)    /* ck00 - fCLK/2^12 */
#define _000D_SAU_CK00_FCLK_13           (0x000DU)    /* ck00 - fCLK/2^13 */
#define _000E_SAU_CK00_FCLK_14           (0x000EU)    /* ck00 - fCLK/2^14 */
#define _000F_SAU_CK00_FCLK_15           (0x000FU)    /* ck00 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRS013 - PRS010) */
#define _0000_SAU_CK01_FCLK_0            (0x0000U)    /* ck01 - fCLK */
#define _0010_SAU_CK01_FCLK_1            (0x0010U)    /* ck01 - fCLK/2^1 */
#define _0020_SAU_CK01_FCLK_2            (0x0020U)    /* ck01 - fCLK/2^2 */
#define _0030_SAU_CK01_FCLK_3            (0x0030U)    /* ck01 - fCLK/2^3 */
#define _0040_SAU_CK01_FCLK_4            (0x0040U)    /* ck01 - fCLK/2^4 */
#define _0050_SAU_CK01_FCLK_5            (0x0050U)    /* ck01 - fCLK/2^5 */
#define _0060_SAU_CK01_FCLK_6            (0x0060U)    /* ck01 - fCLK/2^6 */
#define _0070_SAU_CK01_FCLK_7            (0x0070U)    /* ck01 - fCLK/2^7 */
#define _0080_SAU_CK01_FCLK_8            (0x0080U)    /* ck01 - fCLK/2^8 */
#define _0090_SAU_CK01_FCLK_9            (0x0090U)    /* ck01 - fCLK/2^9 */
#define _00A0_SAU_CK01_FCLK_10           (0x00A0U)    /* ck01 - fCLK/2^10 */
#define _00B0_SAU_CK01_FCLK_11           (0x00B0U)    /* ck01 - fCLK/2^11 */
#define _00C0_SAU_CK01_FCLK_12           (0x00C0U)    /* ck01 - fCLK/2^12 */
#define _00D0_SAU_CK01_FCLK_13           (0x00D0U)    /* ck01 - fCLK/2^13 */
#define _00E0_SAU_CK01_FCLK_14           (0x00E0U)    /* ck01 - fCLK/2^14 */
#define _00F0_SAU_CK01_FCLK_15           (0x00F0U)    /* ck01 - fCLK/2^15 */

/*
    Serial Mode Register mn (SMRmn)
*/
#define _0020_SAU_SMRMN_INITIALVALUE     (0x0020U)
/* Selection of macro clock (MCK) of channel n (CKSmn) */
#define _0000_SAU_CLOCK_SELECT_CK00      (0x0000U)    /* operation clock CK0 set by PRS register */ 
#define _8000_SAU_CLOCK_SELECT_CK01      (0x8000U)    /* operation clock CK1 set by PRS register */
/* Selection of transfer clock (TCLK) of channel n (CCSmn) */
#define _0000_SAU_CLOCK_MODE_CKS         (0x0000U)    /* divided operation clock MCK specified by CKSmn bit */  
#define _4000_SAU_CLOCK_MODE_TI0N        (0x4000U)    /* clock input from SCK pin (slave transfer in CSI mode) */
/* Selection of start trigger source (STSmn) */
#define _0000_SAU_TRIGGER_SOFTWARE       (0x0000U)    /* only software trigger is valid */
#define _0100_SAU_TRIGGER_RXD            (0x0100U)    /* valid edge of RXD pin */
/* Controls inversion of level of receive data of channel n in UART mode (SISmn0) */
#define _0000_SAU_EDGE_FALL              (0x0000U)    /* falling edge is detected as the start bit */
#define _0040_SAU_EDGE_RISING            (0x0040U)    /* rising edge is detected as the start bit */
/* Setting of operation mode of channel n (MDmn2, MDmn1) */
#define _0000_SAU_MODE_CSI               (0x0000U)    /* CSI mode */
#define _0002_SAU_MODE_UART              (0x0002U)    /* UART mode */
#define _0004_SAU_MODE_IIC               (0x0004U)    /* simplified IIC mode */
/* Selection of interrupt source of channel n (MDmn0) */
#define _0000_SAU_TRANSFER_END           (0x0000U)    /* transfer end interrupt */
#define _0001_SAU_BUFFER_EMPTY           (0x0001U)    /* buffer empty interrupt */

/*
    Serial Communication Operation Setting Register mn (SCRmn)
*/
/* Setting of operation mode of channel n (TXEmn, RXEmn) */
#define _0000_SAU_NOT_COMMUNICATION      (0x0000U)    /* does not start communication */
#define _4000_SAU_RECEPTION              (0x4000U)    /* reception only */
#define _8000_SAU_TRANSMISSION           (0x8000U)    /* transmission only */
#define _C000_SAU_RECEPTION_TRANSMISSION (0xC000U)    /* reception and transmission */
/* Selection of data and clock phase in CSI mode (DAPmn, CKPmn) */
#define _0000_SAU_TIMING_1               (0x0000U)    /* type 1 */
#define _1000_SAU_TIMING_2               (0x1000U)    /* type 2 */
#define _2000_SAU_TIMING_3               (0x2000U)    /* type 3 */
#define _3000_SAU_TIMING_4               (0x3000U)    /* type 4 */
/* Selection of masking of error interrupt signal (EOCmn) */
#define _0000_SAU_INTSRE_MASK            (0x0000U)    /* masks error interrupt INTSREx */
#define _0400_SAU_INTSRE_ENABLE          (0x0400U)    /* enables generation of error interrupt INTSREx */
/* Setting of parity bit in UART mode (PTCmn1 - PTCmn0) */
#define _0000_SAU_PARITY_NONE            (0x0000U)    /* none parity */
#define _0100_SAU_PARITY_ZERO            (0x0100U)    /* zero parity */
#define _0200_SAU_PARITY_EVEN            (0x0200U)    /* even parity */
#define _0300_SAU_PARITY_ODD             (0x0300U)    /* odd parity */
/* Selection of data transfer sequence in CSI and UART modes (DIRmn) */
#define _0000_SAU_MSB                    (0x0000U)    /* MSB */
#define _0080_SAU_LSB                    (0x0080U)    /* LSB */
/* Setting of stop bit in UART mode (SLCmn1, SLCmn0) */
#define _0000_SAU_STOP_NONE              (0x0000U)    /* none stop bit */
#define _0010_SAU_STOP_1                 (0x0010U)    /* 1 stop bit */
#define _0020_SAU_STOP_2                 (0x0020U)    /* 2 stop bits */
/* Setting of data length in CSI and UART modes (DLSmn2 - DLSmn0) */
#define _0005_SAU_LENGTH_9               (0x0005U)    /* 9-bit data length */
#define _0006_SAU_LENGTH_7               (0x0006U)    /* 7-bit data length */
#define _0007_SAU_LENGTH_8               (0x0007U)    /* 8-bit data length */

/*
    Serial Output Level Register m (SOLm)
*/
/* Selects inversion of the level of the transmit data of channel n in UART mode */
#define _0000_SAU_CHANNEL0_NORMAL        (0x0000U)    /* normal bit level */
#define _0001_SAU_CHANNEL0_INVERTED      (0x0001U)    /* inverted bit level */
#define _0000_SAU_CHANNEL1_NORMAL        (0x0000U)    /* normal bit level */
#define _0002_SAU_CHANNEL1_INVERTED      (0x0002U)    /* inverted bit level */
#define _0000_SAU_CHANNEL2_NORMAL        (0x0000U)    /* normal bit level */
#define _0004_SAU_CHANNEL2_INVERTED      (0x0004U)    /* inverted bit level */
#define _0000_SAU_CHANNEL3_NORMAL        (0x0000U)    /* normal bit level */
#define _0008_SAU_CHANNEL3_INVERTED      (0x0008U)    /* inverted bit level */

/*
    Noise Filter Enable Register 0 (NFEN0)
*/
/* Use of noise filter */
#define _00_SAU_RXD3_FILTER_OFF          (0x00U)      /* noise filter off */
#define _40_SAU_RXD3_FILTER_ON           (0x40U)      /* noise filter on */
#define _00_SAU_RXD2_FILTER_OFF          (0x00U)      /* noise filter off */
#define _10_SAU_RXD2_FILTER_ON           (0x10U)      /* noise filter on */
#define _00_SAU_RXD1_FILTER_OFF          (0x00U)      /* noise filter off */
#define _04_SAU_RXD1_FILTER_ON           (0x04U)      /* noise filter on */
#define _00_SAU_RXD0_FILTER_OFF          (0x00U)      /* noise filter off */
#define _01_SAU_RXD0_FILTER_ON           (0x01U)      /* noise filter on */

/*
    Format of Serial Status Register mn (SSRmn)
*/
/* Communication status indication flag of channel n (TSFmn) */
#define _0040_SAU_UNDER_EXECUTE          (0x0040U)    /* communication is under execution */
/* Buffer register status indication flag of channel n (BFFmn) */
#define _0020_SAU_VALID_STORED           (0x0020U)    /* valid data is stored in the SDRmn register */
/* Framing error detection flag of channel n (FEFmn) */
#define _0004_SAU_FRAM_ERROR             (0x0004U)    /* a framing error occurs during UART reception */
/* Parity error detection flag of channel n (PEFmn) */
#define _0002_SAU_PARITY_ERROR           (0x0002U)    /* a parity error occurs or ACK is not detected */
/* Overrun error detection flag of channel n (OVFmn) */
#define _0001_SAU_OVERRUN_ERROR          (0x0001U)    /* an overrun error occurs */

/*
    Serial Channel Start Register m (SSm)
*/
/* Operation start trigger of channel 0 (SSm0) */
#define _0000_SAU_CH0_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0001_SAU_CH0_START_TRG_ON       (0x0001U)    /* sets SEm0 to 1 and enters the communication wait status */
/* Operation start trigger of channel 1 (SSm1) */
#define _0000_SAU_CH1_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0002_SAU_CH1_START_TRG_ON       (0x0002U)    /* sets SEm1 to 1 and enters the communication wait status */
/* Operation start trigger of channel 2 (SSm2) */
#define _0000_SAU_CH2_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0004_SAU_CH2_START_TRG_ON       (0x0004U)    /* sets SEm2 to 1 and enters the communication wait status */
/* Operation start trigger of channel 3 (SSm3) */
#define _0000_SAU_CH3_START_TRG_OFF      (0x0000U)    /* no trigger operation */
#define _0008_SAU_CH3_START_TRG_ON       (0x0008U)    /* sets SEm3 to 1 and enters the communication wait status */

/*
    Serial Channel Stop Register m (STm)
*/
/* Operation stop trigger of channel 0 (STm0) */
#define _0000_SAU_CH0_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0001_SAU_CH0_STOP_TRG_ON        (0x0001U)    /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 (STm1) */
#define _0000_SAU_CH1_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0002_SAU_CH1_STOP_TRG_ON        (0x0002U)    /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 2 (STm2) */
#define _0000_SAU_CH2_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0004_SAU_CH2_STOP_TRG_ON        (0x0004U)    /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 3 (STm3) */
#define _0000_SAU_CH3_STOP_TRG_OFF       (0x0000U)    /* no trigger operation */
#define _0008_SAU_CH3_STOP_TRG_ON        (0x0008U)    /* operation is stopped (stop trigger is generated) */

/*
    Format of Serial Flag Clear Trigger Register mn (SIRmn)
*/
/* Clear trigger of overrun error flag of channel n (OVCTmn) */
#define _0001_SAU_SIRMN_OVCTMN           (0x0001U)
/* Clear trigger of parity error flag of channel n (PECTmn) */
#define _0002_SAU_SIRMN_PECTMN           (0x0002U)
/* Clear trigger of framing error of channel n (FECTMN) */
#define _0004_SAU_SIRMN_FECTMN           (0x0004U)

/*
    Serial Output Enable Register m (SOEm)
*/
/* Serial output enable/disable of channel 0 (SOEm0) */
#define _0001_SAU_CH0_OUTPUT_ENABLE      (0x0001U)    /* stops output by serial communication operation */
#define _0000_SAU_CH0_OUTPUT_DISABLE     (0x0000U)    /* enables output by serial communication operation */
/* Serial output enable/disable of channel 1 (SOEm1) */
#define _0002_SAU_CH1_OUTPUT_ENABLE      (0x0002U)    /* stops output by serial communication operation */
#define _0000_SAU_CH1_OUTPUT_DISABLE     (0x0000U)    /* enables output by serial communication operation */
/* Serial output enable/disable of channel 2 (SOEm2) */
#define _0004_SAU_CH2_OUTPUT_ENABLE      (0x0004U)    /* stops output by serial communication operation */
#define _0000_SAU_CH2_OUTPUT_DISABLE     (0x0000U)    /* enables output by serial communication operation */
/* Serial output enable/disable of channel 3 (SOEm3) */
#define _0008_SAU_CH3_OUTPUT_ENABLE      (0x0008U)    /* stops output by serial communication operation */
#define _0000_SAU_CH3_OUTPUT_DISABLE     (0x0000U)    /* enables output by serial communication operation */

/*
    Serial Output Register m (SOm)
*/
/* Serial data output of channel 0 (SOm0) */
#define _0000_SAU_CH0_DATA_OUTPUT_0      (0x0000U)    /* Serial data output value is "0" */
#define _0001_SAU_CH0_DATA_OUTPUT_1      (0x0001U)    /* Serial data output value is "1" */
/* Serial data output of channel 1 (SOm1) */
#define _0000_SAU_CH1_DATA_OUTPUT_0      (0x0000U)    /* Serial data output value is "0" */
#define _0002_SAU_CH1_DATA_OUTPUT_1      (0x0002U)    /* Serial data output value is "1" */
/* Serial data output of channel 2 (SOm2) */
#define _0000_SAU_CH2_DATA_OUTPUT_0      (0x0000U)    /* Serial data output value is "0" */
#define _0004_SAU_CH2_DATA_OUTPUT_1      (0x0004U)    /* Serial data output value is "1" */
/* Serial data output of channel 3 (SOm3) */
#define _0000_SAU_CH3_DATA_OUTPUT_0      (0x0000U)    /* Serial data output value is "0" */
#define _0008_SAU_CH3_DATA_OUTPUT_1      (0x0008U)    /* Serial data output value is "1" */
/* Serial clock output of channel 0 (CKOm0) */
#define _0000_SAU_CH0_CLOCK_OUTPUT_0     (0x0000U)    /* Serial clock output value is "0" */
#define _0100_SAU_CH0_CLOCK_OUTPUT_1     (0x0100U)    /* Serial clock output value is "1" */
/* Serial clock output of channel 1 (CKOm1) */
#define _0000_SAU_CH1_CLOCK_OUTPUT_0     (0x0000U)    /* Serial clock output value is "0" */
#define _0200_SAU_CH1_CLOCK_OUTPUT_1     (0x0200U)    /* Serial clock output value is "1" */
/* Serial clock output of channel 2 (CKOm2) */
#define _0000_SAU_CH2_CLOCK_OUTPUT_0     (0x0000U)    /* Serial clock output value is "0" */
#define _0400_SAU_CH2_CLOCK_OUTPUT_1     (0x0400U)    /* Serial clock output value is "1" */
/* Serial clock output of channel 3 (CKOm3) */
#define _0000_SAU_CH3_CLOCK_OUTPUT_0     (0x0000U)    /* Serial clock output value is "0" */
#define _0800_SAU_CH3_CLOCK_OUTPUT_1     (0x0800U)    /* Serial clock output value is "1" */

/*
    SAU Standby Control Register m (SSCm)
*/
/* SAU Standby Wakeup Control Bit (SWC) */
#define _0000_SAU_CH0_SNOOZE_OFF         (0x0000U)    /* disable start function from STOP state of chip */
#define _0001_SAU_CH0_SNOOZE_ON          (0x0001U)    /* enable start function from STOP state of chip */

/* SAU used flag */
#define _00_SAU_IIC_MASTER_FLAG_CLEAR    (0x00U)
#define _01_SAU_IIC_SEND_FLAG            (0x01U)
#define _02_SAU_IIC_RECEIVE_FLAG         (0x02U)
#define _04_SAU_IIC_SENDED_ADDRESS_FLAG  (0x04U)

/*
    Input switch control register (ISC)
*/
/* Channel 0 SSI00 input setting in CSI communication and slave mode (SSIE00) */
#define _00_SAU_SSI00_UNUSED             (0x00U)      /* disables SSI00 pin input */
#define _80_SAU_SSI00_USED               (0x80U)      /* enables SSI00 pin input */

/*
    IICA Control Register (IICCTLn0)
*/
/* IIC operation enable (IICEn) */
#define _00_IICA_OPERATION_DISABLE       (0x00U)    /* stop operation */
#define _80_IICA_OPERATION_ENABLE        (0x80U)    /* enable operation */
/* Exit from communications (LRELn) */
#define _00_IICA_COMMUNICATION_NORMAL    (0x00U)    /* normal operation */
#define _40_IICA_COMMUNICATION_EXIT      (0x40U)    /* exit from current communication */
/* Wait cancellation (WRELn) */
#define _00_IICA_WAIT_NOTCANCEL          (0x00U)    /* do not cancel wait */
#define _20_IICA_WAIT_CANCEL             (0x20U)    /* cancel wait */
/* Generation of interrupt when stop condition (SPIEn) */
#define _00_IICA_STOPINT_DISABLE         (0x00U)    /* disable */
#define _10_IICA_STOPINT_ENABLE          (0x10U)    /* enable */
/* Wait and interrupt generation (WTIMn) */
#define _00_IICA_WAITINT_CLK8FALLING     (0x00U)    /* generated at the eighth clock's falling edge */
#define _08_IICA_WAITINT_CLK9FALLING     (0x08U)    /* generated at the ninth clock's falling edge */
/* Acknowledgement control (ACKEn) */
#define _00_IICA_ACK_DISABLE             (0x00U)    /* disable acknowledgement */
#define _04_IICA_ACK_ENABLE              (0x04U)    /* enable acknowledgement */
/* Start condition trigger (STTn) */
#define _00_IICA_START_NOTGENERATE       (0x00U)    /* do not generate start condition */
#define _02_IICA_START_GENERATE          (0x02U)    /* generate start condition */
/* Stop condition trigger (SPTn) */
#define _00_IICA_STOP_NOTGENERATE        (0x00U)    /* do not generate stop condition */
#define _01_IICA_STOP_GENERATE           (0x01U)    /* generate stop condition */

/*
    IICA Status Register (IICSn)
*/
/* Master device status (MSTSn) */
#define _00_IICA_STATUS_NOTMASTER        (0x00U)    /* slave device status or communication standby status */
#define _80_IICA_STATUS_MASTER           (0x80U)    /* master device communication status */
/* Detection of arbitration loss (ALDn) */
#define _00_IICA_ARBITRATION_NO          (0x00U)    /* arbitration win or no arbitration */
#define _40_IICA_ARBITRATION_LOSS        (0x40U)    /* arbitration loss */
/* Detection of extension code reception (EXCn) */
#define _00_IICA_EXTCODE_NOT             (0x00U)    /* extension code not received */
#define _20_IICA_EXTCODE_RECEIVED        (0x20U)    /* extension code received */
/* Detection of matching addresses (COIn) */
#define _00_IICA_ADDRESS_NOTMATCH        (0x00U)    /* addresses do not match */
#define _10_IICA_ADDRESS_MATCH           (0x10U)    /* addresses match */
/* Detection of transmit/receive status (TRCn) */
#define _00_IICA_STATUS_RECEIVE          (0x00U)    /* receive status */ 
#define _08_IICA_STATUS_TRANSMIT         (0x08U)    /* transmit status */
/* Detection of acknowledge signal (ACKDn) */
#define _00_IICA_ACK_NOTDETECTED         (0x00U)    /* ACK signal was not detected */
#define _04_IICA_ACK_DETECTED            (0x04U)    /* ACK signal was detected */
/* Detection of start condition (STDn) */
#define _00_IICA_START_NOTDETECTED       (0x00U)    /* start condition not detected */
#define _02_IICA_START_DETECTED          (0x02U)    /* start condition detected */
/* Detection of stop condition (SPDn) */
#define _00_IICA_STOP_NOTDETECTED        (0x00U)    /* stop condition not detected */
#define _01_IICA_STOP_DETECTED           (0x01U)    /* stop condition detected */

/*
    IICA Flag Register (IICFn)
*/
/* STT clear flag (STCFn) */
#define _00_IICA_STARTFLAG_GENERATE      (0x00U)    /* generate start condition */
#define _80_IICA_STARTFLAG_UNSUCCESSFUL  (0x80U)    /* start condition generation unsuccessful */
/* IIC bus status flag (IICBSYn) */
#define _00_IICA_BUS_RELEASE             (0x00U)    /* bus release status */
#define _40_IICA_BUS_COMMUNICATION       (0x40U)    /* bus communication status */
/* Initial start enable trigger (STCENn) */
#define _00_IICA_START_WITHSTOP          (0x00U)    /* generate start condition upon detecting a stop condition */
#define _02_IICA_START_WITHOUTSTOP       (0x02U)    /* generate start condition without detection of a stop condition */
/* Communication reservation function disable bit (IICRSVn) */
#define _00_IICA_RESERVATION_ENABLE      (0x00U)    /* enable communication reservation */
#define _01_IICA_RESERVATION_DISABLE     (0x01U)    /* disable communication reservation */

/*
    IICA Control Register 1 (IICCTLn1)
*/
/* Control of address match wakeup (WUPn) */
#define _00_IICA_WAKEUP_STOP             (0x00U)    /* stop address match wakeup function in STOP mode */
#define _80_IICA_WAKEUP_ENABLE           (0x80U)    /* enable address match wakeup function in STOP mode */
/* Detection of SCL0 pin level (CLDn) */
#define _00_IICA_SCL_LOW                 (0x00U)    /* detect clock line at low level */
#define _20_IICA_SCL_HIGH                (0x20U)    /* detect clock line at high level */
/* Detection of SDA0 pin level (DADn) */
#define _00_IICA_SDA_LOW                 (0x00U)    /* detect data line at low level */
#define _10_IICA_SDA_HIGH                (0x10U)    /* detect data line at high level */
/* Operation mode switching (SMCn) */
#define _00_IICA_MODE_STANDARD           (0x00U)    /* operates in standard mode */
#define _08_IICA_MODE_HIGHSPEED          (0x08U)    /* operates in high-speed mode */
/* Digital filter operation control (DFCn) */
#define _00_IICA_FILTER_OFF              (0x00U)    /* digital filter off */ 
#define _04_IICA_FILTER_ON               (0x04U)    /* digital filter on */
/* Operation of clock dividing frequency permission (PRSn) */
#define _00_IICA_fCLK                    (0x00U)    /* clock of dividing frequency operation (fCLK) */ 
#define _01_IICA_fCLK_HALF               (0x01U)    /* 2 clock of dividing frequency operation (fCLK/2) */
/* IICA used flag */
#define _80_IICA_ADDRESS_COMPLETE        (0x80U)
#define _00_IICA_MASTER_FLAG_CLEAR       (0x00U)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _9E00_IIC10_DIVISOR              (0x9E00U)
#define IIC10_WAITTIME                   (160U) /* change the waiting time according to the system */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_SAU0_Create(void);
void R_IIC10_Create(void);
void R_IIC10_Master_Send(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);
void R_IIC10_Master_Receive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num);
void R_IIC10_Stop(void);
void R_IIC10_StartCondition(void);
void R_IIC10_StopCondition(void);
static void r_iic10_callback_master_receiveend(void);
static void r_iic10_callback_master_sendend(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
