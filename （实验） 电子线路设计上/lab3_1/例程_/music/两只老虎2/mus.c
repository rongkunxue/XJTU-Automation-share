#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
#define HALFF  6000000  //12M晶振半频
#define MAX 65536   //16位计数器最大计数次数
sbit sound = P1^0;
uint C;
uchar STH0;
uchar STL0;
//C调音频
//#define soo 392 //低音'5'
//#define dao 523	//宏定义中音‘1’频率为523Hz
//#define re 587
//#define mi 659
//#define fa 698
//#define so 784
//#define la 880
//#define xi 987

#define soo 784 //中音'5'
#define dao 1047	//宏定义高音‘1’频率为1047Hz
#define re 1175
#define mi 1319
#define fa 1397
#define so 1568
#define la 1760
#define xi 1967

/******
 1个延时单位，1000ms
 歌曲为C调4/4拍，简谱中一个音符（最小拍）为1/4拍，现以1/4拍为1个延时单位
 关于for执行时间：
 当i定义为int(或unsign int)时，为8个时钟周期；
 当i定义为char或unsign char时，为3个时钟周期。
*/
void delay()
{
	uint i,j;
	for(i=0; i<110; i++)
		for(j=0; j<110; j++);	//1ms
}

void main()
{
	uchar i,j;
	//《两只老虎》编曲
	uint code song[] = {dao,re,mi,dao,
						dao,re,mi,dao,
						mi,fa,so,
						mi,fa,so,
						so,la,so,fa,mi,dao,
						so,la,so,fa,mi,dao,
						re,soo,dao,
						re,soo,dao,
						0xff};	//以0xff为音符结束标志
	//以下为每个音符节拍,4个延时单位为1拍
	//'4'对应4个延时单位，'2'对应2个延时单位，'1'对应1个
	uchar code JP[] = {4,4,4,4,
					   4,4,4,4,
					   4,4,8,
					   4,4,8,
					   3,1,3,1,4,4,
					   3,1,3,1,4,4,
					   4,4,8,
					   4,4,8};
	EA = 1;         //开总中断
	ET0 = 1;        //开定时器T0中断
	TMOD = 0x01;	//定时器T0用工作方式1(16位计数器)
	while(1)
	{
		i = 0;
		while(song[i] != 0xff)
		{
			C = HALFF/song[i];
			STH0 = (MAX - C) / 256; // 高8位
			STL0 = (MAX - C) % 256; // 低8位
			TR0 = 1;			   //启动定时器

			for(j=0; j<JP[i]; j++) //控制节拍
			 delay();		   //延时1个延时单位
			TR0 = 0;			   //关闭定时器
			i++;				   //播放下一个音符
		}
	}
}

/************
  定时器T0的中断服务子程序，使P1.0输出音频所要的方波
*/
/**********
  要产生音频脉冲，只要算出某一音频的周期（1/频率），
  然后将此周期除以2，即为半周期的时间。
  利用定时器计时这个半周期时间，每当计时到后就将输出脉冲的I/O反相，
  然后重复计时此半周期时间再对I/O反相，就可在I/O脚上得到此频率的脉冲
********/
void t0() interrupt 1 using 1
{
	TH0 = STH0;
	TL0 = STL0;
    sound = ~sound; 
	 
}
