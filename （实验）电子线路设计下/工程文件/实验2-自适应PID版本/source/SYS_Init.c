#include "SYS_Init.h"

void SYSCLK_Init(void) {
    int i;          // 延时计数器
    OSCXCN = 0x67;  // 使用外部22.1184MHz晶振
    for (i = 0; i < 256; i++)
        ;           // 等待1ms
    while (!(OSCXCN & 0x80))
        ;           // 等待外部振荡器稳定
    OSCICN = 0x88;  // 切换到外部晶振
}

void PORT_Init(void) {
		P74OUT |= 0x01;
    XBR2 |= 0x40;
    P4 &= 0xfd;
    XBR1 |= 0X14;     // 设置XBR1  原来0x14
    XBR2 |= 0X44;     // 打开交叉开关和弱上拉
    P0MDOUT |= 0x03;  // 设置 P0.0 P0.1 为推挽输出
    P1MDOUT |= 0xFF;  // 设置 P1 为推挽输出
    P2MDOUT |= 0xFF;  // 设置 P2 为推挽输出
    P3MDOUT |= 0xFF;  // 设置 P3 为推挽输出

    P0 |= 0x00;
}

void SYS_Init(void) {
    Disable_Global;  // 清除 IE 标志位 7，禁止全局中断请求
    Disable_WDT;     // 关闭看门狗
    Enable_Global;   // 设定 IE 标志位 7，允许全局中断请求
    SYSCLK_Init();   // 配置系统时钟
    PORT_Init();     // 配置端口
    // REF_Ctr_Set;     // 关闭温度传感器, 设定芯片上的 VREF
}

void INT_Init(void) {
  IT1 = 0;
	//enable INT1
	EX1 = 1;
	//enable all interrupt
	EA = 1;  
	INT1_Type1;     // 设定 TCON 中断标志位 2，INT1 中断为边缘触发
  Enable_INT1;    // 设定 IE 标志位 2，允许 INT1 中断请求
}
