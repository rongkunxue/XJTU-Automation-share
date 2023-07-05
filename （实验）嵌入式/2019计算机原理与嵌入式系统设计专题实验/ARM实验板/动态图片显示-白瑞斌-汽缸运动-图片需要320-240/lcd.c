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
extern unsigned char gImage_pic1[];
extern unsigned char gImage_pic2[];
extern unsigned char gImage_pic3[];
extern unsigned char gImage_pic4[];
extern unsigned char gImage_pic5[];
extern unsigned char gImage_pic6[];
extern unsigned char gImage_pic7[];

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
  GLCD_bitmap (0, 0, 320, 240, gImage_pic1);

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
				 GLCD_bitmap (0, 0, 320, 240, gImage_pic1);
				 break;
		    case 1:
			     GLCD_bitmap (0, 0, 320, 240, gImage_pic2);
				 break;
			case 2:
			     GLCD_bitmap (0, 0, 320, 240, gImage_pic3);
				 break;
			case 3:
			     GLCD_bitmap (0, 0, 320, 240, gImage_pic4);
				 break;
			case 4:
			     GLCD_bitmap (0, 0, 320, 240, gImage_pic5);
				 break;
			case 5:
			     GLCD_bitmap (0, 0, 320, 240, gImage_pic6);
				 break;
			case 6:
			     GLCD_bitmap (0, 0, 320, 240, gImage_pic7);
				 break;
		}
	   if (pic++ > 12) pic = 0;
        
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
