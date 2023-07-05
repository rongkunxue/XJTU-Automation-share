/**
 * @brief 定义延时相关函数
 * @auther 王适未<AirWSW@outlook.com>
 *
 * 没有了
 */

#ifndef __DELAY_H
#define __DELAY_H

#include "c8051F020.h"
#include <intrins.h>

void Delay_us(unsigned int val);
void Delay_ms(unsigned int val);
void Delay1(uint k);
// void Delay_s(unsigned int val);

#endif