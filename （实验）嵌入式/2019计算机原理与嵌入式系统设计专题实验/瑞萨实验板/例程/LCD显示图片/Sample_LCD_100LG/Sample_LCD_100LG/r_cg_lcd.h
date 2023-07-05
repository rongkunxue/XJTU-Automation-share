/***********************************************************************************************************************
 * File Name    : r_cg_lcd.h
 * Version      : RL78/G13 V 0.01 1503 [23 Jan 2015]
 * Device(s)    : R5F100LG
 * Tool-Chain   : CA78K0R
 * Description  : This file implements main function.
 * Company Name : Getsoon Electronic Co.Ltd , Shanghai.China
 * Creation Date: 2015-1-23
 ***********************************************************************************************************************/


#ifndef R_CG_LCD_H_
#define R_CG_LCD_H_

//MACRO DEFINE----------------------------------------------

#define  OUT_HIGH     1
#define  OUT_LOW      0

void lcd_init(void);
void lcd_write(unsigned char data, unsigned char op);
void cursor_set(unsigned char pos);
void lcd_display(unsigned char pos,  void *str);
void LcdFill_Vertical();
void LcdFill_Level();
void LcdFill_REC();
void LcdClear();
#define  CLEAN_SCREEN()  lcd_write(0x01,0)
#define  CURSOR_ON()  lcd_write(0x0f,0)
#define  CURSOR_OFF()  lcd_write(0x0c,0)

void CursorSet(unsigned char pos);

#endif /* R_CG_LCD_H_ */
