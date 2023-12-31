
#include <REG52.H>    
#include <INTRINS.H>    
//本例采用89C52, 晶振为11.0592MHZ        
sbit GPIO_Beep =  P1^5 ; 
unsigned char g_beat = 0;  //节拍常数变量     
   
unsigned char code music_tab[] ={   
0x18, 0x30, 0x1C , 0x10, //格式为: 频率常数, 节拍常数, 频率常数, 节拍常数,    
0x20, 0x40, 0x1C , 0x10,   
0x18, 0x10, 0x20 , 0x10,   
0x1C, 0x10, 0x18 , 0x40,   
0x1C, 0x20, 0x20 , 0x20,   
0x1C, 0x20, 0x18 , 0x20,   
0x20, 0x80, 0xFF , 0x20,   
0x30, 0x1C, 0x10 , 0x18,   
0x20, 0x15, 0x20 , 0x1C,   
0x20, 0x20, 0x20 , 0x26,   
0x40, 0x20, 0x20 , 0x2B,   
0x20, 0x26, 0x20 , 0x20,   
0x20, 0x30, 0x80 , 0xFF,   
0x20, 0x20, 0x1C , 0x10,   
0x18, 0x10, 0x20 , 0x20,   
0x26, 0x20, 0x2B , 0x20,   
0x30, 0x20, 0x2B , 0x40,   
0x20, 0x20, 0x1C , 0x10,   
0x18, 0x10, 0x20 , 0x20,   
0x26, 0x20, 0x2B , 0x20,   
0x30, 0x20, 0x2B , 0x40,   
0x20, 0x30, 0x1C , 0x10,   
0x18, 0x20, 0x15 , 0x20,   
0x1C, 0x20, 0x20 , 0x20,   
0x26, 0x40, 0x20 , 0x20,   
0x2B, 0x20, 0x26 , 0x20,   
0x20, 0x20, 0x30 , 0x80,   
0x20, 0x30, 0x1C , 0x10,   
0x20, 0x10, 0x1C , 0x10,   
0x20, 0x20, 0x26 , 0x20,   
0x2B, 0x20, 0x30 , 0x20,   
0x2B, 0x40, 0x20 , 0x15,   
0x1F, 0x05, 0x20 , 0x10,   
0x1C, 0x10, 0x20 , 0x20,   
0x26, 0x20, 0x2B , 0x20,   
0x30, 0x20, 0x2B , 0x40,   
0x20, 0x30, 0x1C , 0x10,   
0x18, 0x20, 0x15 , 0x20,   
0x1C, 0x20, 0x20 , 0x20,   
0x26, 0x40, 0x20 , 0x20,   
0x2B, 0x20, 0x26 , 0x20,   
0x20, 0x20, 0x30 , 0x30,   
0x20, 0x30, 0x1C , 0x10,   
0x18, 0x40, 0x1C , 0x20,   
0x20, 0x20, 0x26 , 0x40,   
0x13, 0x60, 0x18 , 0x20,   
0x15, 0x40, 0x13 , 0x40,   
0x18, 0x80, 0x00   
};   
 
  
void int0()  interrupt 1   //采用中断0 控制节拍    
{
	TH0 = 0xd8;   
	TL0 = 0xef;   
	g_beat--;   
}
 
void AudioFrequencyDelay (unsigned char m)   //控制频率延时    
{   
	unsigned i=3*m;   
	while(--i);   
} 
 
void BeepTone(unsigned char tone, unsigned char beat)   
{
	g_beat = beat;
	TR0 = 1;  //开定时器1    
   	while(g_beat != 0) //等待节拍完成, 通过P1口输出音频(可多声道哦!) 
	{
		GPIO_Beep = ~GPIO_Beep;
		AudioFrequencyDelay(tone);
	}
	TR0 = 0;   //关定时器1
}
   
 
void Delay10ms(unsigned int c)   //误差 0us
{
    unsigned char a, b;
 
	//--c已经在传递过来的时候已经赋值了，所以在for语句第一句就不用赋值了--//
    for (;c>0;c--)
	{
		for (b=38;b>0;b--)
		{
			for (a=130;a>0;a--);
		}
           
	}       
}
 
 
void InitTimer0()
{
	TMOD = 0x01; //选择16位计数器
	TH0 = 0xd8;	 //(65535 - 10000) / 256
	TL0 = 0xef;  //(65535 - 10000) % 256
 
	IE=0x82;   //允许定时器T0中断和总中断
}
 
void PlaySong()
{
	unsigned char i=0;
	unsigned char tmpTone = 0;
 
	while(1)   
	{
		tmpTone = music_tab[i]; 
		if(tmpTone == 0x00)  //如果碰到结束符
		{
			return;
		}       
		else if(tmpTone == 0xff)  //若碰到休止符,延时100ms,继续取下一音符
		{ 
			++i;
			Delay10ms(10),
			TR0=0; 
			continue;
		}      
        else 
		{
			unsigned char tone, beat;
			tone = music_tab[i++];
			beat = music_tab[i++];
			BeepTone(tone, beat);	
		}
	}   
}
 
 
   
void main()   
{
	InitTimer0();
	while(1)   
	{
		PlaySong();
		Delay10ms(300);	
	}   
} 

