
/***********************************************************************************************************************
 * File Name    : r_cg_timer_user.c
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
#pragma interrupt INTTM00 r_tau0_channel0_interrupt
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
 ***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#define  Clear_WDT()  WDTE = 0xAC
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
 ***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
 * Function Name: r_tau0_channel0_interrupt
 * Description  : This function is INTTM00 interrupt service routine.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
__interrupt static void r_tau0_channel0_interrupt(void)
{
	/* Start user code. Do not edit comment generated here */
	P4.2 = !P4.2;
	Clear_WDT();

	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
