/**
 * @brief 定义各种和 ADC 有关的指令与函数
 * @auther 王适未<AirWSW@outlook.com>
 * 
 * 没有了
 */

#ifndef __ADC_h
#define __ADC_h

#include "SYS_Init.h"
#include "Timer.h"
#include "c8051f020.h"
// #include <stdio.h>

// ADC0 模数转换器 0 设置 
#define ADC0_Gain          ADC0CF &= 0xf8  // ADC0 增益设置，设定 ACD0 的增益为 1
#define ADC0_Clk_Set       ADC0CF  = (SYSCLK / SAR0_CLK) << 3
                                           // 设置 ADC0 SAR 转换时钟周期
#define ADC0_Ctr_Set       ADC0CN  = 0xC4  // ADC0 控制设置，定时器 3 溢出启动跟踪，持续三个 SAR 时钟，然后进行 AD 转换，数据右对齐
#define ADC0_Start         AD0EN   = 1     // 设定 ADC0CN 允许位，ADC0 中断允许
#define ADC0_Stop          AD0EN   = 0     // 清除 ADC0CN 允许位，ADC0 中断禁止
#define ADC0_IntFlag_Clear AD0INT  = 0     // 清除 ADC0CN 转换结束中断标志位，必须使用软件清零
#define ADC0_Channel       AMX0SL          // ADC0 通道寄存器
#define ADC0_Channel_0     AMX0SL  = 0x00  // ADC0 使用 AIN0 通道
#define ADC0_Channel_1     AMX0SL  = 0x01  // ADC0 使用 AIN1 通道

void Timer3_Init_ADC0(int counts);
void ADC0_Init(void);
void ADC0_Enable(unsigned char flag);
unsigned int ADC_Value(unsigned char Flag);
unsigned int ADC_ValueReturn(unsigned char channel);

#endif