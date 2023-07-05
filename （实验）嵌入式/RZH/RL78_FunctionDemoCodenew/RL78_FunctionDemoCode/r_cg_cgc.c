
/***********************************************************************************************************************
 * File Name    : r_cg_cgc.c
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
#include "r_cg_cgc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
 ***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
 * Function Name: R_CGC_Create
 * Description  : This function initializes the clock generator.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_CGC_Create(void)
{
	uint8_t           temp_stab_set;
	uint8_t           temp_stab_wait;

	/* Set fMX */
	CMC = _40_CGC_HISYS_OSC | _00_CGC_SUB_PORT | _01_CGC_SYSOSC_OVER10M | _00_CGC_SUBMODE_DEFAULT;
	OSTS = _07_CGC_OSCSTAB_SEL18;
	MSTOP = 0U;
	temp_stab_set = _FF_CGC_OSCSTAB_STA18;

	do
	{
		temp_stab_wait = OSTC;
		temp_stab_wait &= temp_stab_set;
	}
	while (temp_stab_wait != temp_stab_set);

	/* Set fMAIN */
	MCM0 = 0U;
	/* Set fSUB */
	XTSTOP = 1U;
	OSMC = _10_CGC_RTC_CLK_FIL;
	/* Set fCLK */
	CSS = 0U;
	/* Set fIH */
	HIOSTOP = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
