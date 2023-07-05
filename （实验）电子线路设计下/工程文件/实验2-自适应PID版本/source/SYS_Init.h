#ifndef __SYS_INIT_H
#define __SYS_INIT_H

#include "c8051f020.h"

sbit INT1 = P0 ^ 3;
#define INT1_Start INT1 = 1  // 设定 P0 ^ 2 为 1，INT1 中断开启
#define INT1_Stop  INT1 = 0  // 设定 P0 ^ 2 为 0，INT1 中断关闭

// CLK 时钟参数设置 11059200
#define SYSCLK     11059200  // SYSCLK frequency in Hz
#define SAMPLERATE 25000     // ADC0 采样率 Hz
#define SAR0_CLK   2500000   // ADC0 SAR 转换时钟数值为 2.5MHz

#define TIMER_PRESCALER 12    // Based on Timer CKCON settings

#define LED_TOGGLE_RATE 100  // LED toggle rate in milliseconds 1ms

// There are SYSCLK/TIMER_PRESCALER timer ticks per second, so
// SYSCLK/TIMER_PRESCALER/1000 timer ticks per millisecond.
#define TIMER_TICKS_PER_MS SYSCLK / TIMER_PRESCALER / 1000

// Note: LED_TOGGLE_RATE*TIMER_TICKS_PER_MS should not exceed 65535 (0xFFFF)
// for the 16-bit timer

#define AUX1 TIMER_TICKS_PER_MS * LED_TOGGLE_RATE
#define AUX2 -AUX1
#define AUX3 AUX2 & 0x00FF
#define AUX4 ((AUX2 & 0xFF00) >> 8)

#define TIMER0_RELOAD_HIGH AUX4  // Reload value for Timer0 high byte
#define TIMER0_RELOAD_LOW  AUX3  // Reload value for Timer0 low byte

// REF0CN
#define REF_Ctr_Set REF0CN = 0x03  // 关闭温度传感器, 设定芯片上的 VREF

// IE 中断允许寄存器
#define Enable_INT0    EX0 = 1  // 设定 IE 标志位 0，允许 INT0 中断请求
#define Enable_Timer0  ET0 = 1  // 设定 IE 标志位 1，允许 Timer0 溢出中断请求
#define Enable_INT1    EX1 = 1  // 设定 IE 标志位 2，允许 INT1 中断请求
#define Enable_Timer1  ET1 = 1  // 设定 IE 标志位 3，允许 Timer1 溢出中断请求
#define Enable_Timer2  ET2 = 1  // 设定 IE 标志位 5，允许 Timer2 溢出中断请求
#define Enable_Global  EA  = 1  // 设定 IE 标志位 7，允许全局中断请求
#define Disable_Global EA  = 0  // 清除 IE 标志位 7，禁止全局中断请求

// WDT 看门狗定时器
#define Disable_WDT WDTCN = 0xDE;WDTCN = 0xAD  // 禁止看门狗计时器

// TCON 定时器控制寄存器
#define INT0_Type0 IT0 = 0  // 清除 TCON 中断标志位 0，INT0 中断为电平触发
#define INT0_Type1 IT0 = 1  // 设定 TCON 中断标志位 0，INT0 中断为边缘触发
#define INT1_Type0 IT1 = 0  // 清除 TCON 中断标志位 2，INT1 中断为电平触发
#define INT1_Type1 IT1 = 1  // 设定 TCON 中断标志位 2，INT1 中断为边缘触发

// EIE2 扩展中断允许 2 设置
#define Enable_Timer3  EIE2 |= 0x01  // 设定 EIE2 标志位 0，允许 Timer3 溢出中断请求
#define Enable_ADC0    EIE2 |= 0x02  // 设定 EIE2 标志位 1，允许 ADC0 转换结束产生的中断请求
#define Enable_Timer4  EIE2 |= 0x04  // 设定 EIE2 标志位 2，允许 Timer4 溢出中断请求
#define Enable_ADC1    EIE2 |= 0x08  // 设定 EIE2 标志位 3，允许 ADC1 转换结束产生的中断请求
#define Disable_Timer3 EIE2 &= 0xFE  // 清除 EIE2 标志位 0，禁止定时器 3 中断
#define Disable_ADC0   EIE2 &= 0xFD  // 清除 EIE2 标志位 1，禁止 ADC0 转换结束产生的中断请求
#define Disable_Timer4 EIE2 &= 0xFB  // 清除 EIE2 标志位 2，禁止定时器 4 中断
#define Disable_ADC1   EIE2 &= 0xF7  // 清除 EIE2 标志位 3，禁止 ADC1 转换结束产生的中断请求

void SYSCLK_Init (void);
void PORT_Init (void);
void SYS_Init(void);
void INT_Init(void);

#endif