#include <REGX52.H>
#include "SD.h"
sbit ACC0=ACC^0;
sbit ACC1=ACC^1;
sbit ACC2=ACC^2;
sbit ACC3=ACC^3;
sbit ACC4=ACC^4;
sbit ACC5=ACC^5;
sbit ACC6=ACC^6;
sbit ACC7=ACC^7;
//定义SD卡需要的4根信号线
sbit SD_CLK = P1^0;
sbit SD_DI  = P1^2;
sbit SD_DO  = P1^1;
sbit SD_CS  = P1^3;
//写一字节到SD卡,模拟SPI总线方式
void SdWrite(unsigned char DATA)
{
    ACC=DATA;
    SD_CLK=0;
    SD_DI=ACC7;
    SD_CLK=1;

    SD_CLK=0;
    SD_DI=ACC6;
    SD_CLK=1;

    SD_CLK=0;
    SD_DI=ACC5;
    SD_CLK=1;

    SD_CLK=0;
    SD_DI=ACC4;
    SD_CLK=1;

    SD_CLK=0;
    SD_DI=ACC3;
    SD_CLK=1;

    SD_CLK=0;
    SD_DI=ACC2;
    SD_CLK=1;

    SD_CLK=0;
    SD_DI=ACC1;
    SD_CLK=1;

    SD_CLK=0;
    SD_DI=ACC0;
    SD_CLK=1;
    SD_DI=1;//在空闲状态下DI需为高电平 
}
//从SD卡读一字节,模拟SPI总线方式
unsigned char SdRead()
{
    SD_CLK=0;
    SD_CLK=1;
    ACC7=SD_DO;

    SD_CLK=0;
    SD_CLK=1;
    ACC6=SD_DO;

    SD_CLK=0;
    SD_CLK=1;
    ACC5=SD_DO;

    SD_CLK=0;
    SD_CLK=1;
    ACC4=SD_DO;

    SD_CLK=0;
    SD_CLK=1;
    ACC3=SD_DO;

    SD_CLK=0;
    SD_CLK=1;
    ACC2=SD_DO;

    SD_CLK=0;
    SD_CLK=1;
    ACC1=SD_DO;

    SD_CLK=0;
    SD_CLK=1;
    ACC0=SD_DO;
    return ACC;
}
//检测SD卡的响应
unsigned char SdResponse()
{
    unsigned char i=0,response;
    
    while(i<=8)
    {
        response = SdRead();
        if(response==0x00)
        break;
        if(response==0x01)
        break;
        i++;
    }
    return response;
} 
//发命令到SD卡
void SdCommand(unsigned char command, unsigned long argument, unsigned char CRC)
{

    SdWrite(command|0x40);
    SdWrite(((unsigned char *)&argument)[0]);
    SdWrite(((unsigned char *)&argument)[1]);
    SdWrite(((unsigned char *)&argument)[2]);
    SdWrite(((unsigned char *)&argument)[3]);
    SdWrite(CRC);
}
//初始化SD卡
unsigned char SdInit(void)
{
    int delay=0, trials=0;
    unsigned char i;
    unsigned char response=0x01;
    
    SD_CS=1;
    for(i=0;i<=9;i++)
    SdWrite(0xff);
    SD_CS=0;
    
    //Send Command 0 to put MMC in SPI mode
    SdCommand(0x00,0,0x95);
    
    
    response=SdResponse();
    
    if(response!=0x01)
    {
        return 0;
    } 

    while(response==0x01)
    {
        SD_CS=1;
        SdWrite(0xff);
        SD_CS=0;
        SdCommand(0x01,0x00ffc000,0xff);
        response=SdResponse();
    } 

    SD_CS=1;
    SdWrite(0xff);
    return 1; 
}
//往SD卡指定地址写数据,一次最多512字节
unsigned char SdWriteBlock(unsigned char *Block, unsigned long address,int len)
{
    unsigned int count;
    unsigned char dataResp;
    //Block size is 512 bytes exactly
    //First Lower SS
    
    SD_CS=0;
    //Then send write command
    SdCommand(0x18,address,0xff);
    
    if(SdResponse()==00)
    {
        SdWrite(0xff);
        SdWrite(0xff);
        SdWrite(0xff);
        //command was a success - now send data
        //start with DATA TOKEN = 0xFE
        SdWrite(0xfe);
        //now send data
        for(count=0;count<len;count++) SdWrite(*Block++);
        
        for(;count<512;count++) SdWrite(0);
        //data block sent - now send checksum
        SdWrite(0xff); //两字节CRC校验, 为0XFFFF 表示不考虑CRC
        SdWrite(0xff);
        //Now read in the DATA RESPONSE token
        dataResp=SdRead();
        //Following the DATA RESPONSE token
        //are a number of BUSY bytes
        //a zero byte indicates the MMC is busy
        
        while(SdRead()==0);
        
        dataResp=dataResp&0x0f; //mask the high byte of the DATA RESPONSE token
        SD_CS=1;
        SdWrite(0xff);
        if(dataResp==0x0b)
        {
            return 0;
        }
        if(dataResp==0x05)
           return 1;
        return 0;
    }
    return 0;
}

//从SD卡指定地址读取数据,一次最多512字节
unsigned char SdReadBlock(unsigned char *Block, unsigned long address,int len)
{
    unsigned int count;
    //Block size is 512 bytes exactly
    //First Lower SS
    
    
    SD_CS=0;
    //Then send write command
    SdCommand(0x11,address,0xff);

    if(SdResponse()==00)
    {
        //command was a success - now send data
        //start with DATA TOKEN = 0xFE
        while(SdRead()!=0xfe);
        
        for(count=0;count<len;count++) *Block++=SdRead(); 
        
        for(;count<512;count++) SdRead();
        
        //data block sent - now send checksum
        SdRead();
        SdRead();
        //Now read in the DATA RESPONSE token
        SD_CS=1;
        SdRead();
        return 1;
    }
    return 0;
}