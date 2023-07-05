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


#define LED_NUM     8                   /* Number of user LEDs                */
#define LED8        (1 << 0)            /* LED8                               */
#define LED9        (1 << 1)            /* LED9                               */
#define LED10       (1 << 2)            /* LED8                               */
#define LED11       (1 << 3)            /* LED8                               */
#define LED12       (1 << 4)            /* LED8                               */
#define LED13       (1 << 5)            /* LED8                               */
#define LED14       (1 << 6)            /* LED8                               */
#define LED15       (1 << 7)            /* LED8                               */
#define LED_ALL     (LED8  |LED9  |     /* Mask of all LEDs                  */\
                     LED10 |LED11 |\
                     LED12 |LED13 |\
                     LED14 |LED15 )


const int led_mask[] = {LED8,  LED9,    /* All LEDs Mask                      */
                        LED10, LED11, 
                        LED12, LED13, 
                        LED14, LED15 };

extern unsigned char Clock100ms;
extern unsigned char Clock1s;
extern unsigned char Background[];
extern unsigned char ARM_Animation[];
extern unsigned char gImage_bz001[];
extern unsigned char gImage_bz002[];
extern unsigned char gImage_bz003[];
extern unsigned char gImage_bz004[];
extern unsigned char gImage_bz005[];
extern unsigned char gImage_bz006[];
extern unsigned char gImage_bz007[];
extern unsigned char gImage_bz008[];
extern unsigned char gImage_bz009[];
extern unsigned char gImage_bz010[];
extern unsigned char gImage_bz011[];
extern unsigned char gImage_bz012[];
extern unsigned char gImage_bz013[];
extern unsigned char gImage_bz014[];
extern unsigned char gImage_bz015[];
extern unsigned char gImage_bz016[];
extern unsigned char gImage_bz017[];
extern unsigned char gImage_bz018[];
extern unsigned char gImage_bz019[];

int main (void) {                       /* Main Function                      */

  int num     = -1; 
  int dir     =  1;
  int off     =  0; 
  int pic     =  0;
  int clk_ani =  0;

  Reg8(0x78000000) = LED_ALL;           /* Turn off all LEDs                  */

  /* Setup Timer1 to generate interrupt every 10 ms                           */
  REG_TCR1  = 0xAC000000 + (15-1);      /* Dbg, IE, period mode, rst, prsc=80 */
  REG_TCR1  = 0xA8000000 + (15-1);      /* Dbg, IE, period mode,      prsc=80 */
  REG_TICR1 = (15000000 / (15 * 100));  /* Reload value=15MHz/(prescaler*100) */
  REG_TCR1 |= (1 << 30);                /* Start Timer 1                      */

  /* Setup AIC for Timer1 interrupt                                           */
  REG_AIC_SCR14 = (1 << 6) | 1;         /* Int trig on high level, priority 1 */
  REG_AIC_TEST  =  1;                   /* Enable Debugging of AIC            */
  REG_AIC_MECR  = (1 << IRQ_TIMER1);    /* Enable Timer 1 interrupt           */

  GLCD_init();
  GLCD_bitmap (0, 0, 320, 240, gImage_bz001);

  for (;;) 
  {                            /* Loop forever                       */

    if (Clock100ms) 
	{
      Clock100ms = 0;

      if (clk_ani++ == 1) 
	  {             /* Draw animation picture every 200 ms*/
        clk_ani = 0;
        
		switch(pic)		//通过画图工具-图像-属性将293*220的图片补齐到320*240再转码，即可正常显示，否则一片花。
		{
			case 0:
				 GLCD_bitmap (0, 0, 320, 240, gImage_bz001);
				 break;
		    case 1:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz002);
				 break;
			case 2:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz003);
				 break;
			case 3:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz004);
				 break;
			case 4:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz005);
				 break;
			case 5:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz006);
				 break;
			case 6:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz007);
				 break;
			case 7:
				 GLCD_bitmap (0, 0, 320, 240, gImage_bz008);
				 break;
		    case 8:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz009);
				 break;
			case 9:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz010);
				 break;
			case 10:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz011);
				 break;
			case 11:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz012);
				 break;
			case 12:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz013);
				 break;
			case 13:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz014);
				 break;
			case 14:
				 GLCD_bitmap (0, 0, 320, 240, gImage_bz015);
				 break;
		    case 15:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz016);
				 break;
			case 16:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz017);
				 break;
			case 17:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz018);
				 break;
			case 18:
			     GLCD_bitmap (0, 0, 320, 240, gImage_bz019);
				 break;
		}
	   if (pic++ > 18) pic = 0;
        
      }
    }
	 
    if (Clock1s) 
	{                      /* Blink LED every 1 second           */
      Clock1s = 0;
	  
      if (!off) 
	  {
        /* Calculate 'num': 0, 1, ... , LED_NUM-1, LED_NUM-1, ... , 1, 0, 0, .*/
        num += dir;
        if (num == LED_NUM) { dir = -1; num =  LED_NUM-1; } 
        else if   (num < 0) { dir =  1; num =  0;         }

        Reg8(0x78000000) = ~led_mask[num];  /* Turn  on LED with index 'num'  */
      } else 
	  {
       Reg8(0x78000000) = LED_ALL;         /* Turn off all LEDs              */
      }

      off = !off;
    } 	
  }
}
