#ifndef __TIMER_H
#define __TIMER_H

#include "c8051f020.h"

// TMR0/1 定时器 0/1 设置
#define Timer0_Set_Method1 TMOD &= 0xF0; TMOD |= 0x01 // 设置定时器 0 为方式 1 定时器功能
#define Timer0_Stop        TR0   = 0                  // 清除 TCON 中断标志位 4，定时器 0 禁止
#define Timer0_Start       TR0   = 1                  // 设定 TCON 中断标志位 4，定时器 0 开启
#define Timer1_Set_Method1 TMOD &= 0x0F; TMOD |= 0x10 // 设置定时器 1 为方式 1 定时器功能
#define Timer1_Stop        TR1   = 0                  // 清除 TCON 中断标志位 6，定时器 1 禁止
#define Timer1_Start       TR1   = 1                  // 设定 TCON 中断标志位 6，定时器 1 开启

// T2 定时器 2 设置
#define Timer2_Set_Method1 T2CON  = 0x00  // 设置定时器 2 为方式 1 定时器功能
#define Timer2_Stop        T2CON &= 0xFB  // 清除 T2CON 中断标志位 2，定时器 2 禁止
#define Timer2_Start       T2CON |= 0x04  // 设定 T2CON 中断标志位 2，定时器 2 开启
#define Timer2_Clear_Flag  T2CON &= 0x7F  // 清除 T2CON 中断标志位 7，对定时器 2 溢出位软件清 0

// TMR3 定时器 3 设置
sfr16 TMR3RL = 0x92;  // 定义 TMR3RL 的 sfr16 地址
sfr16 TMR3   = 0x94;  // 定义 TMR3 的 sfr16 地址

#define Timer3_Reload_Init TMR3RL            // 使用 TMR3RL 重载定时器 3
#define Timer3_Count_Start TMR3    = 0xffff  // 设置 TMR3 计满溢出，立即装载
#define Timer3_Stop        TMR3CN  = 0x02    // 清除 TMR3CN 中断标志位 2，定时器 3 禁止（重置所有状态）
#define Timer3_Start       TMR3CN |= 0x04    // 设定 TMR3CN 中断标志位 2，定时器 3 开启

// T4 定时器 4 设置
#define Timer4_Set_Method1 T4CON  = 0x00  // 设置定时器 4 为方式 1 定时器功能
#define Timer4_Stop        T4CON &= 0xFB  // 清除 T4CON 中断标志位 2，定时器 4 禁止
#define Timer4_Start       T4CON |= 0x04  // 设定 T4CON 中断标志位 2，定时器 4 开启
#define Timer4_Clear_Flag  T4CON &= 0x7F  // 清除 T4CON 中断标志位 7，对定时器 4 溢出位软件清 0

extern unsigned int timer0_value;
extern unsigned int timer1_value;
extern unsigned int timer2_value;
extern unsigned int timer3_value;
extern unsigned int timer4_value;

#endif