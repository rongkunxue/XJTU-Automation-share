		#include<reg52.h>
typedef unsigned char u8;
typedef unsigned int u16;
u8 which,buff[6];
u8 s_1,s_2,s_3,s_4,s_5,s_6;
sbit DI=P3^6;
sbit LED=P3^7;
u8 code right[]={1,2,3,4,5,6};
u8 code distab[]={
0xc0,0xF9,0xA4,0xB0,0x99,				 
0x92,0x82,0xF8,0x80,0x90,			
0x88,0x83,0xC6,0xA1,0x86,			
0x8E,0xFF,0x0C,0x89,0x7F,0xBF};
void delayms(u8 xms)
{
	u16 i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}
void di()
{
	DI=0;
	delayms(500);
	DI=1;
	delayms(500);
}

u8 conn()
{
	if((buff[0]==right[0])&&(buff[1]==right[1])&&(buff[2]==right[2])&&
		(buff[3]==right[3])&&(buff[4]==right[4])&&(buff[5]==right[5]))
	return 1;
	else return 0;
} 
void display(u8 num)
{
	if(which>0)
	switch(which)
		{
			case 1:if(num==21)which=0;s_1=num;if(num==20)which=0;buff[0]=s_1;	 break;
			case 2:if(num==21)which=1;s_2=num;if(num==20)which=1;buff[1]=s_2;	 break;
			case 3:if(num==21)which=2;s_3=num;if(num==20)which=2;buff[2]=s_3;	 break;
			case 4:if(num==21)which=3;s_4=num;if(num==20)which=3;buff[3]=s_4;    break;
			case 5:if(num==21)which=4;s_5=num;if(num==20)which=4;buff[4]=s_5;    break;
			case 6:if(num==21)which=5;s_6=num;if(num==20)which=5;buff[5]=s_6;	 break;
			case 7:		which=6;
						if(num==21)
						{
							if(conn()==0)
							{
								di();di();di();
								LED=1;
							}
							else 
							{
								LED=0;delayms(500);delayms(500);LED=1;
							}
							which=0;
						}
						break;
			default:	which=6;					         break;
		}
		else di();
} 
void dis()
{
	switch(which)
	{
	 case 1:P0=distab[s_1];	P2=0x80;delayms(5);	P0=0xff;  P2=0x00;	 break;
	 case 2:P0=distab[s_1];	P2=0x40;delayms(5);	P0=0xff;
	 		P0=distab[s_2];	P2=0x80;delayms(5);	P0=0xff;  P2=0x00;	 break;
	 case 3:P0=distab[s_1];	P2=0x20;delayms(5);	P0=0xff;
	 		P0=distab[s_2];	P2=0x40;delayms(5);	P0=0xff;  
			P0=distab[s_3];	P2=0x80;delayms(5);	P0=0xff;  P2=0x00;	 break;
	 case 4:P0=distab[s_1];	P2=0x10;delayms(5);	P0=0xff;
	 		P0=distab[s_2];	P2=0x20;delayms(5);	P0=0xff;  
			P0=distab[s_3];	P2=0x40;delayms(5);	P0=0xff;  
	 		P0=distab[s_4];	P2=0x80;delayms(5);	P0=0xff;  P2=0x00;	 break;
	 case 5:P0=distab[s_1];	P2=0x08;delayms(5);	P0=0xff;
	 		P0=distab[s_2];	P2=0x10;delayms(5);	P0=0xff;  
			P0=distab[s_3];	P2=0x20;delayms(5);	P0=0xff;  
	 		P0=distab[s_4];	P2=0x40;delayms(5);	P0=0xff;  
			P0=distab[s_5];	P2=0x80;delayms(5);	P0=0xff;  P2=0x00;	 break;
	 case 6:P0=distab[s_1];	P2=0x04;delayms(5);	P0=0xff;
	 		P0=distab[s_2];	P2=0x08;delayms(5);	P0=0xff;  
			P0=distab[s_3];	P2=0x10;delayms(5);	P0=0xff;  
	 		P0=distab[s_4];	P2=0x20;delayms(5);	P0=0xff;  
			P0=distab[s_5];	P2=0x40;delayms(5);	P0=0xff;  
			P0=distab[s_6];	P2=0x80;delayms(5);	P0=0xff;  P2=0x00;	 break;
	}
}
void matrixkeyscan()					   //matrix矩阵
{
	u8 temp,key;						   //temp临时变量
	P1=0xfe;							   //将第一行电平置低，其余行全为高
	temp=P1;							   //读取P3口当前状态的置赋予临时变量temp，用于后面计算
	temp=temp&0xf0;						   //判断temp的高四位是否有0，如果temp的高四位有0，那么与运算后
										    //结果必然不等于0xf0;temp的高四位实际上是矩阵键盘的4个列线
										    //从而通过temp与0xf0"&"运算后的结果是否为0xf0来判断第一行是否
										    //有按键按下
	if(temp!=0xf0)						//“temp&0xf0”的结果，如果temp不等于0xf0，说明有键被按下
	{
		delayms(10);					
		temp=P1;					   //重新读一次P3口数据
		temp=temp&0xf0;				   //重新进行一次与运算
		if(temp!=0xf0)
		{
			temp=P1;
			switch(temp)
			{
				case 0xee:	key=0;	which+=1;	break;
				case 0xde:	key=1;	which+=1;	break;
				case 0xbe:	key=2;	which+=1;	break;
				case 0x7e:	key=3;	which+=1;	break;
			}
			while(temp!=0xf0)			   //等待按键释放
			{
				temp=P1;
				temp=temp&0xf0;
			}
			display(key);
		}
	}
	P1=0xfd;
	temp=P1;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delayms(10);
		temp=P1;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=P1;
			switch(temp)
			{
				case 0xed:	key=4;	which+=1;break;
				case 0xdd:	key=5;	which+=1;break;
				case 0xbd:	key=6;	which+=1;break;
				case 0x7d:	key=7;	which+=1;break;
			}
			while(temp!=0xf0)
			{
				temp=P1;
				temp=temp&0xf0;
			}
			display(key);
		}
	}
	P1=0xfb;
	temp=P1;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delayms(10);
		temp=P1;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=P1;
			switch(temp)
			{
				case 0xeb:	key=8;	which+=1;break;
				case 0xdb:	key=9;	which+=1;break;
//				case 0xbb:	key=10;	which+=1;break;
//				case 0x7b:	key=11;	which+=1;break;
			}
			while(temp!=0xf0)
			{
				temp=P1;
				temp=temp&0xf0;
			}
			display(key);
		}
	}
	P1=0xf7;
	temp=P1;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delayms(10);
		temp=P1;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=P1;
			switch(temp)
			{
				case 0xe7:	key=20;	break;
				case 0xd7:	key=21; which+=1;	break;
//				case 0xb7:	key=14;	which+=1;break;
//				case 0x77:	key=15;	which+=1;break;
			}
			while(temp!=0xf0)
			{
				temp=P1;
				temp=temp&0xf0;
			}
			display(key);
		}
	}
}
void main() 
{ 
	while(1) 
	{ 
		if(which==0)
		{
		   	 P0=0X8C;P2=0x01;delayms(5);P0=0xff;
			 P0=0X86;P2=0x02;delayms(5);P0=0xff;
			 P0=distab[20];P2=0xfc;delayms(5);P0=0xff;
		}
		if(which>=1)dis();
		matrixkeyscan();	
	} 
} 
