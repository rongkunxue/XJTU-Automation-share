#include "ADC.h"

unsigned int buf[2];
unsigned char ch = 0;  // 内部变量使用缩写避免与外部冲突

void Timer3_Init_ADC0(int counts) {
    Timer3_Stop;                   // 清除 TMR3CN 中断标志位 2，定时器 3 禁止（重置所有状态）
    Timer3_Reload_Init = -counts;  // 使用 TMR3RL = -counts 重载定时器 3
//    Timer3_Reload_Init = 0x0000;  // 使用 TMR3RL = -counts 重载定时器 3
    Timer3_Count_Start;            // 设置 TMR3 计满溢出，立即装载
    Disable_Timer3;                // 清除 EIE2 标志位 0，禁止定时器 3 中断
    Timer3_Start;                  // 设定 TMR3CN 中断标志位 2，定时器 3 开启
}

void ADC0_Init(void) {
    ADC0_Ctr_Set;    // ADC0 控制设置，定时器 3 溢出启动跟踪，持续三个 SAR 时钟，然后进行 AD 转换，数据右对齐
    REF_Ctr_Set;     // 关闭温度传感器, 设定芯片上的 VREF
    ADC0_Channel_1;  // ADC0 使用 AIN1 通道
    ADC0_Clk_Set;    // 设置 ADC0 SAR 转换时钟周期为 2.5MHz
    ADC0_Gain;       // ADC0 增益设置，设定 ACD0 的增益为 1
    Enable_ADC0;     // 设定 EIE2 标志位 1，允许 ADC0 转换结束产生的中断请求
}

void ADC0_Enable(unsigned char flag) {
    if (flag) {
        ADC0_Start;         // 设定 ADC0CN 允许位，ADC0 中断允许
        // Disable_Global;  // 禁止全局中断
    } else
        ADC0_Stop;          // 清除 ADC0CN 允许位，ADC0 中断禁止
}

void ADC0_ISR(void) interrupt 15 {
    ADC0_IntFlag_Clear;      // 清除 ADC0CN 转换结束中断标志位，必须使用软件清零
    buf[ch] = ADC_Value(0);  // 读 ADC0 中 AIN 通道的值
    ch++;                    // 改变通道
    if (ch == 2)
        ch = 0;
    AMX0SL = ch;             // 设置mux到下个通道
    
    timer3_value++;
}

unsigned int ADC_Value(unsigned char Flag) {
    unsigned int temp, temp0, temp1;
    if (Flag)     // ADC1
        temp0 = ADC1;
    else          // ADC0
    {
        temp0 = ADC0L;
        temp1 = ADC0H;
    }
    temp = temp1 * 256 + temp0;
    return temp;  // 取回ADC转换数据
}

unsigned int ADC_ValueReturn(unsigned char ch) {
    if (ch < 2)          // 通道范围有效
        return buf[ch];  // 取回通道对应数据
    else                      // 通道范围出错
        return 0xffff;        // 返回错误信息
}