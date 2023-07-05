/**
 * @brief 定义各种和 DAC 有关的指令与函数
 * @auther 王适未<AirWSW@outlook.com>
 * 
 * 没有了
 */

#ifndef __DAC_H
#define __DAC_H

#include "SYS_Init.h"
#include "c8051f020.h"

// DAC0 数模转换器 0 设置 
#define DAC0_Ctr_Set DAC0CN = 0x80  // 打开 DAC0，右对齐模式，输出更新发生在写 DAC0H 时

// DAC1 数模转换器 1 设置 
#define DAC1_Ctr_Set DAC1CN = 0x80  // 打开 DAC1，右对齐模式，输出更新发生在写 DAC1H 时

void DAC0_Init(void);
// void DAC1_Init(void);
void DAC0_Output(unsigned int val);
// void DAC1_Output(unsigned int val);

#endif