
/***********************************************************************************************************************
 * File Name    : r_main.c
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
#include "c_cg_AD.h"
#include "r_cg_lcd.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"


/***********************************************************************************************************************
Global variables and functions
 ***********************************************************************************************************************/


/* Start user code for global. Do not edit comment generated here */
#define  Clear_WDT()  WDTE = 0xAC

uint8_t  Lcd_Flashlight;

uint16_t  time_lenth = 0;
uint16_t  buzzle_time = 0;
uint16_t  buzzle_cycle = 0;
uint16_t  buzzle_flash = 0;


int i,j;

void R_PCLBUZ0_Start(void)
{
	PCLOE0 = 1U;    /* enable PCLBUZ0 operation */
}

void R_PCLBUZ0_Stop(void)
{
	PCLOE0 = 0U;    /* disable PCLBUZ0 operation */
}
void BUZZLE_Delay(void)
{
	for(buzzle_time = 0; buzzle_time <50000; buzzle_time++)
		for(buzzle_cycle = 0; buzzle_cycle <10; buzzle_cycle++);
}
void R_BUZZLE_Run(void)
{
	for(buzzle_flash = 0; buzzle_flash < 4; buzzle_flash++)
	{
		R_PCLBUZ0_Start();
		BUZZLE_Delay();
		R_PCLBUZ0_Stop();
		BUZZLE_Delay();
	}
}
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
 * Function Name: main
 * Version      : RL78/G14 Demo Board V1.02.1317
 * Device(s)    : R5F104LE
 * Tool-Chain   : CA78K0R
 * Description  : AD Sample process
 * Author       : R.B.Xie
 * Company Name : Getsoon Electronic Co.Ltd,Shanghai,China
 * Creation Date: 2013-4-3
 ***********************************************************************************************************************/
void main(void)
{
	/* Start user code. Do not edit comment generated here */
	Lcd_Flashlight = 0;
	EI();
	R_TAU0_Channel0_Start();
	ADC_init();
	lcd_init( );	
	lcd_display(0,"     Renesas    "
			"   Electronics  "
			"    瑞萨电子    "
			"      中国       ");

	R_BUZZLE_Run();
	while (1U)
	{
		ADC_Start();
		ADC_Stop();
		Clear_WDT();

		time_lenth++;

		if(time_lenth == 3)
		{	
		    lcd_write(0x01,0); 		
			switch(Lcd_Flashlight)
			{
			case 0: lcd_display(0,"RL78/G13  Family"
					"MCU Demo Board  "
					"RL78/G13  系列  "
					"MCU Demo  板   ");
			Lcd_Flashlight++;
			break;
			case 1: lcd_display(0,"     Getsoon    "
					"   Electronics  "	
			        "    格州电子    "
					"  股份有限公司  ");
			Lcd_Flashlight++;
			break;
			case 2: lcd_display(0,"瑞萨杯2017全国大学生电子设计竞赛  "
									"  激情创造    "
									"    精彩无限    ");			
			Lcd_Flashlight++;
			break;
			case 3:
				LcdFill_REC();
				Lcd_Flashlight=0;
			break;
#if 0
			case 4:			 
            LcdFill_Vertical();
			Lcd_Flashlight++;
			break;
			
			case 5:				 
			LcdFill_Level();
			Lcd_Flashlight=0;
			break;
#endif			
			default: Lcd_Flashlight = 0;
            break;
			}
			time_lenth = 0;
		}

	}
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
