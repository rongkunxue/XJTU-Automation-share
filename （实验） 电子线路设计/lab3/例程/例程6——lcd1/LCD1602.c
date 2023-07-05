#include<reg51.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;
void DelayMS(uint ms)//延时
{
 uchar i;
 while(ms--)
 {
  for(i=0;i<120;i++); 
  }
}
 uchar Busy_Check()   //忙检查，控制器每次进行读写操作之前，都必须进行读写检测，
                      //确保STA7为0
{
  uchar	LCD_Status;//根据芯片操作时序，读操作时RS=0，RW=1，EN高脉冲（150ns）
  RS=0;	 //RS=0 选择命令，RS=1选择数据
  RW=1;	 // RW=1选择读， RW=0选择写
  EN=1;	 //开始读
  DelayMS(1);
  LCD_Status=P0; //读出STA7的状态，也就是P0的最高位
  EN=0;
  return LCD_Status;//退回状态值
}
void Write_LCD_Conmmand(uchar cmd)   //写LCD命令，RS=0，RW=0，EN高脉冲
{
 while((Busy_Check()&0x80)==0x80);//忙等待，最高位为0时，LCD空闲，继续
  RS=0;	 //命令
  RW=0;	 //写
  EN=0;
  DelayMS(1);
  P0=cmd;
  EN=1;
  //DelayMS(1);
  EN=0;
}
void Write_LCD_Data(uchar dat)//发送数据
{
 while((Busy_Check()&0x80)==0x80);//忙等待
  RS=1;	 //数据
  RW=0;	 //写
  EN=0;
   DelayMS(1);
  P0=dat;
  EN=1;
  //DelayMS(1);
  EN=0;
}
void Initiallize_LCD() //LCD初始化
{
  Write_LCD_Conmmand(0x38);  //指令0x38代表设置16*2液晶显示，5*7点阵，8位
  DelayMS(1);
  Write_LCD_Conmmand(0x01);  //清屏
  DelayMS(1);
  Write_LCD_Conmmand(0x06);
  DelayMS(1);
  Write_LCD_Conmmand(0x0C);
  DelayMS(1);
}
void ShowString(uchar x,uchar y,uchar *str) //显示字符串，x取值0~15，y取值0~1（1602液晶每行显示16个字符，共两行）
{
  uchar i=0;  //设置显示起始位置
  if(y==0) //第一行
  {
   Write_LCD_Conmmand(0x80|x);// 0x80第一行的数据指针指令码
   }
   if(y==1) //第二行
   {
    Write_LCD_Conmmand(0xC0|x);
	}
   for(i=0;i<16;i++)  //每行16个字符
   {
	 Write_LCD_Data(str[i]);
	}
}