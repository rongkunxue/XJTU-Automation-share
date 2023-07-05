#include <reg51.h>    //包含头文件
sbit KEY1=P1^0;     //用位定义指令分别定义4个按键所对应的引脚
sbit KEY2=P1^1;
sbit KEY3=P1^2;
sbit KEY4=P1^3;
unsigned char keyval;  // 全局变量定义，定义键值变量
//LED流水灯延时函数
void led_delay(void)
{
  unsigned char i,j;
 for(i = 0;i < 251;i++)
 {
   for(j = 0;j < 251;j++);
 }
}
//按键消抖延时函数
void delay20ms(void)
{
  unsigned char i,j;
 for(i = 0;i < 100;i++)
 {
   for(j = 0;j < 60;j++);
 }
}
//正向流水灯
void forward(void)
{
 P3 = 0xfe;     //点亮P3.0引脚的LED灯
 led_delay();
 P3 = 0xfd;
 led_delay();
 P3 = 0xfb;
 led_delay();
 P3 = 0xf7;
 led_delay();
 P3 = 0xef;
 led_delay();
 P3 = 0xdf;
 led_delay();
 P3 = 0xbf;
 led_delay();
 P3 = 0x7f;
 led_delay();
 P3 = 0xfe;
 led_delay();
}
//反向流水灯
void backward(void)
{
 P3 = 0x7f;    //点亮P3.7引脚的LED灯
 led_delay();
 P3 = 0xbf;
 led_delay();
 P3 = 0xdf;
 led_delay();
 P3 = 0xef;
 led_delay();
 P3 = 0xf7;
 led_delay();
 P3 = 0xfb;
 led_delay();
 P3 = 0xfd;
 led_delay();
 P3 = 0xfe;
 led_delay();
 P3 = 0x7f;
 led_delay();
}
//关闭所有LED灯
void stop(void)
{
  P3 = 0xff; 
}
//所有LED闪烁
void flash(void)
{
  P3 = 0xff;
 led_delay();
 P3 = 0x00;
 led_delay(); 
}
//键盘扫描函数
void key_scan(void)
{
  if((P1 & 0x0f)!=0x0f)    //检测是否有按键被按下
 {
   delay20ms();
  if((P1 & 0x0f)!=0x0f)    //延时后再次检测是否有按键被按下
  {
   if(KEY1 == 0)    //判断是那个按键被按下
   {
     keyval = 1;
   }
   if(KEY2 == 0)
   {
     keyval = 2;
   }
   if(KEY3 == 0)
   {
     keyval = 3;
   }
   if(KEY4 == 0)
   {
     keyval = 4;
   }
  }
 }
}
//主函数
void main(void)
{
 keyval = 0;      //
 while(1)
 {
   key_scan();    //调用键值检测函数
  switch(keyval)     //根据键值实现相应功能
  {
   case 1:forward();
          break;
   case 2:backward();
          break;
   case 3:stop();
          break;
   case 4:flash();
          break;
  }
 }
} 
