#include "led.h"

/*select以及display函数，其中第一个是选择数码管，从上到下从左到右1-12，第二个是显示数字*/

void display(int a)  // 显示数字
{
	switch(a)
	{
		case 0:P7=0xC0;break;
		case 1:P7=0xF9;break;
		case 2:P7=0xA4;break;
		case 3:P7=0xB0;break;
		case 4:P7=0x99;break;
		case 5:P7=0x92;break;
		case 6:P7=0x82;break;
		case 7:P7=0xF8;break;
		case 8:P7=0x80;break;
		case 9:P7=0x90;break;
		case 10:P7=0x88;break;//A
		case 11:P7=0x83;break;
		case 12:P7=0xC6;break;
		case 13:P7=0xA1;break;
		case 14:P7=0x86;break;
		case 15:P7=0x8e;break;
		default:P7=0xc0;break;
	}
}

void select(int b)  // 选择数码管
{
	switch(b)
	{			
		case 1: P5 = 0XFE;P6 = 0XFF;break;
		case 2: P5 = 0XFD;P6 = 0XFF;break;
		case 3: P5 = 0XFB;P6 = 0XFF;break;
		case 4: P5 = 0XF7;P6 = 0XFF;break;
		case 5: P5 = 0XEF;P6 = 0XFF;break;
		case 6: P5 = 0XDF;P6 = 0XFF;break;
		case 7: P5 = 0XBF;P6 = 0XFF;break;
		case 8: P5 = 0X7F;P6 = 0XFF;break;
		
		case 9: P6 = 0XFE;P5 = 0XFF;break;
		case 10:P6 = 0XFD;P5 = 0XFF;break;
		case 11:P6 = 0XFB;P5 = 0XFF;break;
		case 12:P6 = 0XF7;P5 = 0XFF;break;
	}
}

void Led_Port_Init()
{
    //set to push_pull model
    P74OUT &= 0xff;

    //enable crossbar
    XBR2 |= 0x40;
}

void LedInit()
{
	Led_Port_Init();
	P5 |= 0xff;
	P6 |= 0x0f;
	P7 = 0xff;
}

void LedDispNum()  //数码管显示数字
{
		uchar temp1[4];
		uchar temp2[4];
		uchar temp3[4];
	
		temp1[0] = Time_num%10;
		temp1[1] = Time_num%100/10;
		temp1[2] = Time_num%1000/100;  
		temp1[3] = Time_num/1000;
	
		temp2[0] = score%10;
		temp2[1] = score%100/10;
		temp2[2] = score%1000/100;  
		temp2[3] = score/1000;
	
		temp3[0] = time%10;
		temp3[1] = time%100/10;
		temp3[2] = time%1000/100;  
		temp3[3] = time/1000;
	
//	temp[0] = Time_num%10;
//	temp[1] = Time_num%100/10;
//	temp[2] = Time_num%1000/100;  // 秒的个位
//	temp[3] = Time_num/1000;

	// 最上边一行显示
	select(4);display(temp1[0]); Delay(500); P7 = 0xff;
	select(3);display(temp1[1]); Delay(500); P7 = 0xff;
	select(2);display(temp1[2]); P7 = P7 & ~0x80; Delay(500); P7 = 0xff;            
	select(1);display(temp1[3]); Delay(500); P7 = 0xff; 

	// 中间一行
	select(8);display(temp2[0]); Delay(500); P7 = 0xff;
	select(7);display(temp2[1]); Delay(500); P7 = 0xff;
	select(6);display(temp2[2]); Delay(500); P7 = 0xff;
	select(5);display(temp2[3]); Delay(500); P7 = 0xff; // Delay(500);

	// 下边一行
	select(12);display(temp3[0]); Delay(500); P7 = 0xff;
	select(11);display(temp3[1]); //P7 = P7 & ~0x80; 
	Delay(500); P7 = 0xff;
	select(10);display(temp3[2]); P7 = P7 & ~0x80; Delay(500); P7 = 0xff;
	select(9) ;display(temp3[3]); Delay(500); P7 = 0xff; // Delay(500);
	
}
void ResDispNum()  //数码管显示数字
{
		uchar temp2[4];
		uchar temp3[4];
	
		temp2[0] = score%10;
		temp2[1] = score%100/10;
		temp2[2] = score%1000/100;  
		temp2[3] = score/1000;
	
		temp3[0] = time%10;
		temp3[1] = time%100/10;
		temp3[2] = time%1000/100;  
		temp3[3] = time/1000;

	// 最上边一行显示
	select(4);display(0); Delay(500); P7 = 0xff;
	select(3);display(0); Delay(500); P7 = 0xff;
	select(2);display(0); Delay(500); P7 = 0xff;            
	select(1);display(0); Delay(500); P7 = 0xff; 

	// 中间一行
	select(8);display(temp2[0]); Delay(500); P7 = 0xff;
	select(7);display(temp2[1]); Delay(500); P7 = 0xff;
	select(6);display(temp2[2]); Delay(500); P7 = 0xff;
	select(5);display(temp2[3]); Delay(500); P7 = 0xff; 

	// 下边一行
	select(12);display(temp3[0]); Delay(500); P7 = 0xff;
	select(11);display(temp3[1]); Delay(500); P7 = 0xff;
	select(10);display(temp3[2]); P7 = P7 & ~0x80; Delay(500); P7 = 0xff;
	select(9) ;display(temp3[3]); Delay(500); P7 = 0xff; 
	
}