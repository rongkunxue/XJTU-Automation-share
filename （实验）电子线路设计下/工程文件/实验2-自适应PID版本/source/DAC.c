#include "DAC.h"

void DAC0_Init(void) {
    // REF0CN = 0x03;  // 使用内部VREF发生器
    DAC0_Ctr_Set;  // 打开 DAC0，右对齐模式，输出更新发生在写 DAC0H 时
}

// void DAC1_Init(void) {
//     // REF0CN = 0x03;  // 使用内部VREF发生器
//     DAC1_Ctr_Set;  // 打开 DAC1，右对齐模式，输出更新发生在写 DAC1H 时
// }

void DAC0_Output(unsigned int val) {
    DAC0L = (unsigned char)val;         //送DA值低2位
    DAC0H = (unsigned char)(val >> 8);  //送DA值高8位
}

// void DAC1_Output(unsigned int val) {
//     DAC1L = (unsigned char)val;         //送DA值低2位
//     DAC1H = (unsigned char)(val >> 8);  //送DA值高8位
// }