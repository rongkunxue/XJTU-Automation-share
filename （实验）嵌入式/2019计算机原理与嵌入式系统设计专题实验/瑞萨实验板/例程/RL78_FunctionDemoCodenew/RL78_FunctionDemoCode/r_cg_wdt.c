
/***********************************************************************************************************************
 * File Name    : r_cg_wdt.c
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
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
 ***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
 * Function Name: R_WDT_Create
 * Description  : This function initializes the watchdogtimer.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_WDT_Create(void)
{
	WDTIMK = 1U;    /* disable INTWDTI interrupt */
	WDTIIF = 0U;    /* clear INTWDTI interrupt flag */
	/* Set INTWDTI low priority */
	WDTIPR1 = 1U;
	WDTIPR0 = 1U;
	WDTIMK = 0U;    /* enable INTWDTI interrupt */
}

/***********************************************************************************************************************
 * Function Name: R_WDT_Restart
 * Description  : This function restarts the watchdog timer.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_WDT_Restart(void)
{
	WDTE = 0xACU;     /* restart watchdog timer */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
