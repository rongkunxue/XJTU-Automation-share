#include <REGX52.H>
#include "SD.h"
#include <intrins.h> 
//数码管段码端口
#define PP  P3
//共阳极数码管段码
unsigned char code SEG7[]={/*0,1,2,3,4,5,6,7,8,9,*/
0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,};
//数码管显示缓冲
unsigned char num[]={1,2};
//数码管位码端口
sbit      q1=P2^6;
sbit      q2=P2^7;
//复位开始停止加1减1按键
sbit      k1=P2^5;
sbit      k2=P1^4;
sbit      k3=P1^5;
sbit      k4=P1^6;
sbit      k5=P1^7;
//----------------------------------------------------
unsigned long  SD_ADDR=0;
unsigned int count;
unsigned char xdata DATA[512];
sbit E = P2^0;
sbit RW = P2^1;
sbit RS = P2^2;
sbit CS2 = P2^3;
sbit CS1 = P2^4;	//端口定义
#define DataPort P0
 /*12864判忙 */
bit Chek_Busy(void)
{
    DataPort = 0xff;
    RW = 1;
    RS = 0;
    E = 1;
    E = 0;
    return (bit)(DataPort & 0x80);
}
/*------------------------------------------------
            选屏
i:0是左屏,1是右屏,2全屏
------------------------------------------------*/
void Choose_12864(unsigned char i)
{						 
   switch (i)			 
   {
       case 0: CS1 = 0;CS2 = 1;break;   
       case 1: CS1 = 1;CS2 = 0;break;
       case 2: CS1 = 0;CS2 = 0;break;
	   default: break;
   }
}
/*------------------------------------------------
        写命令
------------------------------------------------*/
void LCD_Cmd(unsigned char cmd)
{
    while(Chek_Busy());
    RW = 0;	         
    RS = 0;
    DataPort = cmd;
    E = 1;
    E = 0;          
}
/*------------------------------------------------
        读LCD
------------------------------------------------*/
unsigned char LCD_Read()
{
    unsigned char read_data;
    while(Chek_Busy());
    RW = 1;//需进行一次空读
    RS = 1;
    E = 1;
    E = 0;

    RW = 1;
    RS = 1;
    E = 1;
    read_data = DataPort;
    E = 0;        
    return (read_data);    
}
/*------------------------------------------------
        写数据
------------------------------------------------*/
void  LCD_Data(unsigned char dat)
{
    while(Chek_Busy());
    RW = 0;	         
    RS = 1;
    DataPort = dat;
    E = 1;
    E = 0; 
}
/*------------------------------------------------
             设置地址
PAGE:0-7;
Y_Address:0-63
------------------------------------------------*/
void Set_PageY(unsigned char PAGE,unsigned char Y_Address)
{
    LCD_Cmd(0xB8 + PAGE);
    LCD_Cmd(0x40 + Y_Address);
}
/*------------------------------------------------
                清屏
------------------------------------------------*/
void LCD_Clear(void)
{
    unsigned char page,row;
    Choose_12864(2);
    for (page = 0xb8; page < 0xc0; page ++)
    {
        LCD_Cmd(page);
    	LCD_Cmd(0x40);
    	for (row = 0; row < 64; row ++)
    	{
    	    LCD_Data(0x00);//对12864所有地址全部写零
    	}
    }
}
/*------------------------------------------------
               初始化
------------------------------------------------*/
void LCD_Init(void)
{
    CS2 = 0;
    CS1 = 0;
    LCD_Cmd(0x3F);//开显示
}
/*-------------------------------------------------
    显示一幅12864图片
-------------------------------------------------*/
void Dis_Picture(unsigned char *picture)
{
    unsigned char ii,kk;
    for (kk = 0; kk < 4; kk ++)//LCD共分7=8页
    {
        Choose_12864(2);
        Set_PageY(kk,0);
        Choose_12864(0);        
        for (ii = 0; ii < 128; ii ++)
        {
            LCD_Data(*picture);
            picture ++;
            if (ii == 63)
            {
                Choose_12864(1);
            }
        }
    }
}
void Dis_Pictureb(unsigned char *picture)
{
    unsigned char ii,kk;
    for (kk = 4; kk < 8; kk ++)//LCD共分7=8页
    {
        Choose_12864(2);
        Set_PageY(kk,0);
        Choose_12864(0);        
        for (ii = 0; ii < 128; ii ++)
        {
            LCD_Data(*picture);
            picture ++;
            if (ii == 63)
            {
                Choose_12864(1);
            }
        }
    }
}
void delayus(unsigned char t)
{
    while(--t);
}
void delayms(unsigned char t)
{
    while(t--)
    {
        delayus(245);
        delayus(245);
    }
}

//--------------------------------------------------------------------
//倒计时模块
//延时函数ms
void _delay_ms(unsigned int t)
{
   unsigned int i,j;
   for(i=0;i<t;i++)
     for(j=0;j<120;j++);
}
//数码管显示
void dis()
{ 
 //------------------  
 //显示第1位
  PP=num[0];
  q1=1;
  _delay_ms(2);
  q1=0;
 //显示第2位
  PP=num[1];
  q2=1;
  _delay_ms(2);
  q2=0;
 
}
//计时变量
unsigned int jishu1s=10;
unsigned int jishu1=10;
unsigned int jishu2;
//开始停止变量
unsigned int  bz;
//显示控制
void dispaly()
{ 
   num[0]=SEG7[jishu1%100/10];	//显示个位
   num[1]=SEG7[jishu1%10]; //显示小数位
}
//按键处理
void key()
{
  if(k1==0){jishu1=jishu1s;while(k1==0);}//复位
  if(k2==0){bz=1;while(k2==0);}//开始
  if(k3==0){bz=0;while(k3==0);}//停止
  if(bz==0)
  {
    if(k4==0){if(jishu1s<99)jishu1s=jishu1s+1;jishu1=jishu1s;while(k4==0);} //+1
    if(k5==0){if(jishu1s>0 )jishu1s=jishu1s-1;jishu1=jishu1s;while(k5==0);} //-1
  }
} 

//----------------------------
void main(void)
{
_delay_ms(10);  
   //定时器0配置方式1 16
  TMOD=0x01;	
  //使能定时器0 
  ET0=1;
  //定时器的初值
  TH0=(65536-50000)/256; 
  TL0=(65536-50000)%256;
  //停止开启定时器0
  TR0=1;
  EA=1;	  
	LCD_Init();
	LCD_Clear();
	SdInit();
	DATA[0]=255;;
	DATA[1]=1;
	DATA[2]=2;
	DATA[3]=3;
	DATA[511]=0xf0;
	while(1)
  {
   dispaly();//显示控制 
   dis(); //显示
   key();//按键
	 if(jishu1==0)
	 {
		 while(1)
		{
				while(!SdReadBlock(DATA,SD_ADDR,512));
				SD_ADDR+=512;
				Dis_Picture(DATA);
				while(!SdReadBlock(DATA,SD_ADDR,512));
				Dis_Pictureb(DATA);
				SD_ADDR+=512;
				delayms(100);
			  key();//按键
			  if(jishu1!=0) break;
			  if(bz==1) SD_ADDR=0;
	  }
   }
  }
	  
}
 //----T0 计数		 
void  Time0() interrupt 1
{
  //重装初值50ms;
  TH0=(65536-50000)/256;  
  TL0=(65536-50000)%256;
  //开始
  if(bz==1)
  {
   jishu2=jishu2+1;
   //到达1s
   if(jishu2==20)
   { 
     jishu2=0;
     if(jishu1>0)jishu1=jishu1-1;//减1s
     if(jishu1==0)bz=0;//结束
   }
  }
  
}