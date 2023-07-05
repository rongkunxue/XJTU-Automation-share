
/***********************************************************************************************************************
 * File Name    : r_cg_port.c
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
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
 ***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
 * Function Name: R_PORT_Create
 * Description  : This function initializes the Port I/O.
 * Arguments    : None
 * Return Value : None
 ***********************************************************************************************************************/
void R_PORT_Create(void)
{
	//LCD port define
	P2 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0 |
			_00_Pn5_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn7_OUTPUT_0;
	P13 = _00_Pn0_OUTPUT_0;
	P14 = _00_Pn1_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn7_OUTPUT_0;
	PMC14 = _00_PMCn7_DI_ON | _7F_PMC14_DEFAULT;
	ADPC = _01_ADPC_DI_ON;
	PM2 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT |
			_00_PMn4_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT;
	PM14 = _01_PMn0_NOT_USE | _00_PMn1_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT | _3C_PM14_DEFAULT;


	// AD port define
	PM1=0;
	PM5=0XC3;
	PM7=0XF0;
	PU7=0XF0;
	P7|=0x0F;

	// LED port define
	P4 = _02_Pn1_OUTPUT_1 | _04_Pn2_OUTPUT_1 | _08_Pn3_OUTPUT_1;
	POM0 = _04_POMn2_NCH_ON;
	PM4 = _01_PMn0_NOT_USE | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM4_DEFAULT;

	PCLOE0 = 0U;    /* disable PCLBUZ0 operation */
	CKS0 =0x06U;

	/* Set PCLBUZ0 pin */
	P14 &= 0xFEU;
	PM14 &= 0xFEU;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
