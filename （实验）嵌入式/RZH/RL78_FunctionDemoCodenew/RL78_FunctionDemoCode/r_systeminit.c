/***********************************************************************************************************************
 * File Name    : r_systeminit.c
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
#include "r_cg_port.h"
#include "r_cg_timer.h"
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
 * Function Name: R_Systeminit
 * Description  : This function initializes every macro.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_Systeminit(void)
{
	R_CGC_Get_ResetSource();
	R_PORT_Create();
	R_CGC_Create();
	R_TAU0_Create();
	R_WDT_Create();
	CRC0CTL = 0x00U;
	IAWCTL = 0x00U;
}


/***********************************************************************************************************************
 * Function Name: hdwinit
 * Description  : This function initializes hardware setting.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void hdwinit(void)
{
	DI();
	R_Systeminit();
	EI();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
