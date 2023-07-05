
/***********************************************************************************************************************
 * File Name    : r_cg_timer.c
 * Version      : RL78/G13 V 0.01 1503 [23 Jan 2015]
 * Device(s)    : R5F100LG
 * Tool-Chain   : CA78K0R
 * Description  : This file implements main function.
 * Company Name : Getsoon Electronic Co.Ltd , Shanghai.China
 * Creation Date: 2015-1-23
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
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
 ***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
 * Function Name: R_TAU0_Create
 * Description  : This function initializes the TAU0 module.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_TAU0_Create(void)
{
	TAU0EN = 1U;    /* supplies input clock */
	TPS0 = _0002_TAU_CKM0_FCLK_2 | _0000_TAU_CKM1_FCLK_0 | _0000_TAU_CKM2_FCLK_1 | _0000_TAU_CKM3_FCLK_8;
	/* Stop all channels */
	TT0 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON |
			_0008_TAU_CH3_STOP_TRG_ON | _0200_TAU_CH1_H8_STOP_TRG_ON | _0800_TAU_CH3_H8_STOP_TRG_ON;
	/* Mask channel 0 interrupt */
	TMMK00 = 1U;    /* disable INTTM00 interrupt */
	TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
	/* Mask channel 1 interrupt */
	TMMK01 = 1U;    /* disable INTTM01 interrupt */
	TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
	/* Mask channel 1 higher 8 bits interrupt */
	TMMK01H = 1U;    /* disable INTTM01H interrupt */
	TMIF01H = 0U;    /* clear INTTM01H interrupt flag */
	/* Mask channel 2 interrupt */
	TMMK02 = 1U;    /* disable INTTM02 interrupt */
	TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
	/* Mask channel 3 interrupt */
	TMMK03 = 1U;    /* disable INTTM03 interrupt */
	TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
	/* Mask channel 3 higher 8 bits interrupt */
	TMMK03H = 1U;    /* disable INTTM03H interrupt */
	TMIF03H = 0U;    /* clear INTTM03H interrupt flag */
	/* Set INTTM00 low priority */
	TMPR100 = 1U;
	TMPR000 = 1U;
	/* Channel 0 used as interval timer */
	TMR00 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE |
			_0000_TAU_TRIGGER_SOFTWARE | _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
	TDR00 = _9C3F_TAU_TDR00_VALUE;
	TO0 &= ~_0001_TAU_CH0_OUTPUT_VALUE_1;
	TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
}

/***********************************************************************************************************************
 * Function Name: R_TAU0_Channel0_Start
 * Description  : This function starts TAU0 channel 0 counter.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_TAU0_Channel0_Start(void)
{
	TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
	TMMK00 = 0U;    /* enable INTTM00 interrupt */
	TS0 |= _0001_TAU_CH0_START_TRG_ON;
}

/***********************************************************************************************************************
 * Function Name: R_TAU0_Channel0_Stop
 * Description  : This function stops TAU0 channel 0 counter.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_TAU0_Channel0_Stop(void)
{
	TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
	/* Mask channel 0 interrupt */
	TMMK00 = 1U;    /* disable INTTM00 interrupt */
	TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
