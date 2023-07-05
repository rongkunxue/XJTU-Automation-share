#include<reg51.h>
sbit P1_0=P1^0;
void delay (unsigned char time)
{
 unsigned char j=1500;
 for (;time>0; time--)
  for(;j>0;j--);
}

void main(void)
{
     while(1)	  
	 {
	  P1_0=0;
	  delay(1000);
	  P1_0=1;
	  delay(1000);			
	  }
}	 

