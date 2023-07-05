/******************************************************************************/
/* BLINKY.C: LED Flasher                                                      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2008 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include <W90P710.H>                    /* Winbond W90P710 definitions        */
#include "GLCD.h"

#define LED_ALL     0xff

extern unsigned char Background0[];
extern unsigned char Background1[];
extern unsigned char Background2[];
extern unsigned char Background3[];	 
extern unsigned char Background4[];
extern unsigned char Background5[];

#define u32     unsigned int 
#define REG_GPIO_CFG2  	0xFFF83020
#define REG_AIC_SCR29  	0xFFF82074
#define REG_AIC_MECR   	0xFFF82120
#define REG_KPICONF    	0xFFF88000
#define REG_KPISTATUS 		0xFFF8800C
#define EBILED_ADDRESS    	0x78000000
#define REG_EXT0CON		0xFFF01018
#define EBI_EXT0_VALUE		0xF0078003
#define WriteReg(Address,Value)  *(unsigned int volatile *)(Address) = Value
#define ReadReg(Address)        *(unsigned int volatile *)(Address)
int keynum=-1;
void KPIInit(void);
int main (void){
    //extern int keynum;
    //keynum=0;
	WriteReg(REG_EXT0CON, EBI_EXT0_VALUE);
	KPIInit();
	while(1);
	return 0;
}

void KPIInit(void){
	 WriteReg(REG_GPIO_CFG2, 0x000aaaaa);	  //将GPIO设置为KPI模式，2X8 
	 WriteReg(REG_AIC_SCR29, 0x00000045);     //将KPI 中断设置为高电平有效，优先级为5
	 WriteReg(REG_AIC_MECR,  0x20000000);
	 WriteReg(REG_KPICONF,   0x00142fff);
}

//KPI中断服务子程序
__irq void IRQ_Handler(void){
	 //extern int keynum;
	 //int keynum=0;
	 u32 KeyValue, temp;
	 temp = ReadReg(REG_KPISTATUS);
	 temp &= 0x0000000f;
	 if(temp > 0xB){
	 	KeyValue = temp - 0xC;
	 }
	 else if(temp < 0x4){
	 	KeyValue = temp + 0xC; 
	 }
	 else{
	 	KeyValue = temp; 
	 }
	if(KeyValue==0)   keynum++;
	 switch (keynum)
	 {
	    case 0:
		{
		       Reg8(0x78000000) = LED_ALL;           /* Turn off all LEDs                  */
               GLCD_bitmap (0, 0, 320, 240, Background0);
               GLCD_init();
			   break;
		}
	    case 1:
		{
		       Reg8(0x78000000) = LED_ALL;           /* Turn off all LEDs                  */
               GLCD_bitmap (0, 0, 320, 240, Background1);
               GLCD_init();
			   break;
		}
		 case 2:
		{
		       Reg8(0x78000000) = LED_ALL;           /* Turn off all LEDs                  */
               GLCD_bitmap (0, 0, 320, 240, Background2);
               GLCD_init();
			   break;
		}
		 case 3:
		{
		       Reg8(0x78000000) = LED_ALL;           /* Turn off all LEDs                  */
               GLCD_bitmap (0, 0, 320, 240, Background3);
               GLCD_init();
			   break;
		}
		 case 4:
		{
		       Reg8(0x78000000) = LED_ALL;           /* Turn off all LEDs                  */
               GLCD_bitmap (0, 0, 320, 240, Background4);
               GLCD_init();
			   break;
		}
	     case 5:
		{
		       Reg8(0x78000000) = LED_ALL;           /* Turn off all LEDs                  */
               GLCD_bitmap (0, 0, 320, 240, Background5);
               GLCD_init();
			   break;
		}
	 }
	 if(keynum==6)   keynum=-1;
}




