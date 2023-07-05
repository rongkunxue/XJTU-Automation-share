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


extern unsigned char Background1[];



int main (void) {                       /* Main Function                      */
  Reg8(0x78000000) = LED_ALL;           /* Turn off all LEDs                  */
  GLCD_bitmap (0, 0, 320, 240, Background1);
  GLCD_init();
 }



