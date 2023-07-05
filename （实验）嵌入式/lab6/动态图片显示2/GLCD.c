/******************************************************************************/
/* GLCD.c: Functions for Graphic LCD (AUO TFT A03DL01 (960x240 pixels -       */
/*         interlaced 320x240 x 3)) driving for Winbond W90P710               */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2008 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <W90P710.H>                    /* Winbond W90P710 definitions        */
#include <W90P710_lcd.h>                /* Winbond W90P710 LCD definitions    */
#include <stdlib.h>
#include <string.h>

#ifndef _GLCD_H
#define _GLCD_H


/*********************** Hardware specific configuration **********************/

/*------------------------- Speed dependant settings -------------------------*/

/* If processor works on high frequency delay has to be increased, it can be 
   increased by factor 2^N by this constant                                   */
#define DELAY_2N    4

/*---------------------- Graphic LCD size definitions ------------------------*/

#define WIDTH       320                 /* Screen Width (in pixels)           */
#define HEIGHT      240                 /* Screen Hight (in pixels)           */
#define BPP         16                  /* Bits per pixel                     */
#define BYPP        ((BPP+7)/8)         /* Bytes per pixel                    */

#define FB_WIDTH    (3*WIDTH)                 /* Frame buffer width           */
#define FB_HEIGHT   240                       /* Frame buffer height          */
#define FB_SIZE     (FB_WIDTH*FB_HEIGHT*BYPP) /* Frame buffer size (in bytes) */

/*--------------- Graphic LCD interface hardware definitions -----------------*/


/*---------------------------- Global variables ------------------------------*/

unsigned char *fb_start;                /* Start address of frame buffer      */

/******************************************************************************/


/************************ Local auxiliary functions ***************************/

/*******************************************************************************
* Delay in while loop cycles                                                   *
*   Parameter:    cnt:    number of while cycles to delay                      *
*   Return:                                                                    *
*******************************************************************************/

static void delay (int cnt) {

  cnt <<= DELAY_2N;
  while (cnt--);
}


/*******************************************************************************
* Wait while control of display is busy                                        *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

static void wait_while_busy (void) {

  Reg32(REG_USI_CNTRL) |= 0x01;
	while(Reg32(REG_USI_CNTRL) & 0x01);
}


/************************ Exported functions **********************************/

/*******************************************************************************
* Initialize the Graphic LCD controller                                        *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_init (void) { 

  Reg32(REG_GPIO_CFG6)     = 0x00555555;/* Configure LCD GPIO (GPIO 30-41)    */
                           	
	/* Configure LCD controller control register                                */
  Reg32(REG_LCD_LCDCON)   |= LCD_LCDCON_LCDTFT                     |
                             LCD_LCDCON_LCDBUS_24                  |
                             LCD_LCDCON_CASIOSHOWTYPE_R1G1B1R2G2B2 |
                             LCD_LCDCON_LCDTFTTYPE                 |
                             LCD_LCDCON_RGBSEQ_RBG                 |
                             LCD_LCDCON_BPP_16;



  fb_start = malloc(FB_SIZE);           /* Initialize Frame Buffer            */
  memset(fb_start, 0xFF, FB_SIZE);      /* Clear Frame Buffer                 */

  delay(200);
  
  /* Configure dummy display color pattern register                           */
  Reg32(REG_LCD_DDISPCP)   = 0;
    
  /* Configure valid display window starting coordinate                       */
  Reg32(REG_LCD_DISPWINS)  = 0;

  /* Configure valid display window ending coordinate                         */
  Reg32(REG_LCD_DISPWINE)  = (FB_HEIGHT << 16) | FB_WIDTH;

  /* Configure LCD timing generation                                          */
  Reg32(REG_LCD_LCDTCON1)  = 0x0003B166;
  Reg32(REG_LCD_LCDTCON2)  = 0x03BF00F1;
  Reg32(REG_LCD_LCDTCON3)  = 0x00105401;
  Reg32(REG_LCD_LCDTCON4)  = 0x00020101;
  Reg32(REG_LCD_LCDTCON5)  = 0x0000000E;
		
  /* Configure LCD FIFO1 transfer parameters                                  */
  Reg32(REG_LCD_FIFO1PRM)  = LCD_FIFO1PRM_F1BURSTY_16DATABURST | 
                             LCD_FIFO1PRM_F1TRANSZ_4BYTE;
	
  /* FIFO1 transfer data count register                                       */
  Reg32(REG_LCD_F1DREQCNT) = ((FB_WIDTH << 16) >> 1) | FB_HEIGHT;
   
  /* FIFO 1 real column count register */
  Reg32(REG_LCD_FIFO1RELACOLCNT) = FB_WIDTH >> 1;

  /* FIFO 1 start address register                                            */
  Reg32(REG_LCD_F1SADDR)   = (unsigned long) fb_start;

	/* Configure LCD FIFOs controller register and tigger the engine            */
  Reg32(REG_LCD_FIFOCON)   = LCD_FIFOCON_FIFOEN_FIFO1;
   
  /* LCD Controller Enable                                                    */
  Reg32(REG_LCD_LCDCON)   |= LCD_LCDCON_LCDCEN;
                       
  /* Enable USI pins for communication with display                           */
  Reg32(REG_GPIO_CFG5)    &= 0xFFF00FFF;
  Reg32(REG_GPIO_CFG5)    |= 0x000AA000;

  /* Setup communication parameters                                           */	
  Reg32(REG_USI_DIVIDER)   = 0x27;      /* SCLK = PCLK / 80 = 1 MHz           */
  Reg32(REG_USI_SSR)       = 0;         /* CS active low                      */
  Reg32(REG_USI_CNTRL)     = 0x84;      /* 16 bits; Tx fall, Rx rise edge     */

  Reg32(REG_USI_SSR)      |= 0x01;      /* Activate CS0                       */
  Reg32(REG_USI_Tx0)       = 0x0596;    /* Set register R5                    */
  wait_while_busy();
  Reg32(REG_USI_SSR)      &= 0xFE;      /* Deactivate CS0                     */

  delay (1);
  Reg32(REG_USI_SSR)      |= 0x01;      /* Activate CS0                       */
  Reg32(REG_USI_Tx0)       = 0x0408;    /* Set register R4                    */
  wait_while_busy();
  Reg32(REG_USI_SSR)      &= 0xFE;      /* Deactivate CS0                     */

  delay (1);
  Reg32(REG_USI_SSR)      |= 0x01;      /* Activate CS0                       */
  Reg32(REG_USI_Tx0)       = 0x07F1;    /* Set register R7                    */
  wait_while_busy();
  Reg32(REG_USI_SSR)      &= 0xFE;      /* Deactivate CS0                     */

  delay (1);
  Reg32(REG_USI_SSR)      |= 0x01;      /* Activate CS0                       */
  Reg32(REG_USI_Tx0)       = 0x08C0;    /* Set register R8                    */
  wait_while_busy();
  Reg32(REG_USI_SSR)      &= 0xFE;      /* Deactivate CS0                     */

  delay (1);
  Reg32(REG_USI_SSR)      |= 0x01;      /* Activate CS0                       */
  Reg32(REG_USI_Tx0)       = 0x0616;    /* Set register R6                    */
  wait_while_busy();
  Reg32(REG_USI_SSR)      &= 0xFE;      /* Deactivate CS0                     */

  delay (1);
  Reg32(REG_USI_SSR)      |= 0x01;      /* Activate CS0                       */
  Reg32(REG_USI_Tx0)       = 0x05D7;    /* Set register R5                    */
  wait_while_busy();
  Reg32(REG_USI_SSR)      &= 0xFE;      /* Deactivate CS0                     */
}

/*******************************************************************************
* Display graphical bitmap image at position x horizontally and y vertically   *
* (This function is optimized for 16 bits per pixel format, it has to be       *
*  adapted for any other bits per pixel format)                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        width of bitmap                                  *
*                   h:        height of bitmap                                 *
*                   bitmap:   address at which the bitmap data resides         *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_bitmap (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap) {

  unsigned int  i, j;
  unsigned char *disp_start;
  unsigned char *disp_ptr0;
  unsigned char *disp_ptr1;
  unsigned char *disp_ptr2;
  unsigned char *bitmap_ptr;
  unsigned char pixel;
  unsigned int  row_add;

  disp_start = fb_start + (x + y * WIDTH) * BYPP;

  disp_ptr0  = disp_start;
  disp_ptr1  = disp_start +     WIDTH * HEIGHT * BYPP;
  disp_ptr2  = disp_start + 2 * WIDTH * HEIGHT * BYPP;
  bitmap_ptr = bitmap;

  row_add    = (WIDTH - w) * BYPP;

  for (j = 0; j < h; j++) {
    for (i = 0; i < w*BYPP; i++) {
      pixel = *bitmap_ptr++;
      *disp_ptr0++ = pixel;
      *disp_ptr1++ = pixel;
      *disp_ptr2++ = pixel;
    }
    disp_ptr0 += row_add;
    disp_ptr1 += row_add;
    disp_ptr2 += row_add;
  }
}


#endif /* _GLCD_H */

/******************************************************************************/
