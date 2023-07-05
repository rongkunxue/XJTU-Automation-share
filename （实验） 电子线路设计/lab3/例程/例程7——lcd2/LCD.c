#include<reg51.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
void Initiallize_LCD();
void ShowString(uchar x,uchar y,uchar *str);
extern void Write_LCD_Conmmand(uchar cmd); 
uchar num,TEMP;
bit flag=1;
uchar keynum;
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
void delay(uint x)
{
         uchar i;
      while(x--) for(i=0;i<120;i++);
}
uchar keypress()
{
 if(P3!=0XFF)    
  {
   delay(5);
   num=0;
   if(P3!=0XFF)
    {
       TEMP=P3;
       switch(TEMP)
        {
         case 0xfe:num=1;break;
         case 0xfd:num=2;break;
        }
       while(TEMP==0XFF);
      }
   return num;
  }
}
void main()
{
    uchar i;
    P0=P3=0XFF;
      IT0=1;
      EX0=1;
	  EA=1;
     Initiallize_LCD();
      ShowString(0,0,"   gaoqinag    ");
      ShowString(0,1,"201012301043      ");
      while(flag)                             
      {
       keypress();
       if(num==1)
        {
           for(i=0;i<16;i++)
            {
              Write_LCD_Conmmand(0x1c);
               ShowString(16-i,0," gaoqiang");
               ShowString(16-i,1,"201012301043");
               ShowString(16+i,0,"  gaoqinag");
               ShowString(16+i,1,"201012301043");
               ShowString(0x0f,0,"  gaoqinag");
               ShowString(0x0f,1,"201012301043");
              delay(20);
            }
            ShowString(0x0f,0,"  gaoqinag");
           ShowString(0x0f,1,"201012301043");
           delay(20);
           if(num==2)
		   {
		       Write_LCD_Conmmand(0x01);
			   break;
		   }
        }
     if(num==2)
        {
              ShowString(0,0,"gaoqinag");
             delay(100);
              ShowString(0,1,"201012301043");
             delay(100);
              ShowString(0,1,"gaoqinag");
             delay(100);
             ShowString(0,0,"201012301043");
             delay(100);
             if(num==1) {Write_LCD_Conmmand(0x01);
			 break;}
        }
      }
}
void exter0()interrupt 0
{
 flag=~flag;
}
