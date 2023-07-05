//矩阵键盘扫描C代码
#define u32     unsigned int 
#define REG_GPIO_CFG2  	0xFFF83020
#define REG_AIC_SCR29  	0xFFF82074
#define REG_AIC_MECR   	0xFFF82120
#define REG_KPICONF    	0xFFF88000
#define REG_KPISTATUS 		0xFFF8800C
#define EBILED_ADDRESS    	0x78000000
#define REG_EXT0CON		0xFFF01018
#define EBI_EXT0_VALUE		0xF0078003
#define WriteReg(Address,Value)  *(unsigned int volatile *)(Address) = Value
#define ReadReg(Address)        *(unsigned int volatile *)(Address)
void KPIInit(void);
int main (void){
	WriteReg(REG_EXT0CON, EBI_EXT0_VALUE);
	KPIInit();
	while(1);
	return 0;
}

void KPIInit(void){
	 WriteReg(REG_GPIO_CFG2, 0x000aaaaa);	  //将GPIO设置为KPI模式，2X8 
	 WriteReg(REG_AIC_SCR29, 0x00000045);     //将KPI 中断设置为高电平有效，优先级为5
	 WriteReg(REG_AIC_MECR,  0x20000000);
	 WriteReg(REG_KPICONF,   0x00142fff);
}

//KPI中断服务子程序
__irq void IRQ_Handler(void){
	 u32 KeyValue, temp;
	 temp = ReadReg(REG_KPISTATUS);
	 temp &= 0x0000000f;
	 if(temp > 0xB){
	 	KeyValue = temp - 0xC;
	 }
	 else if(temp < 0x4){
	 	KeyValue = temp + 0xC; 
	 }
	 else{
	 	KeyValue = temp; 
	 }
	 WriteReg(EBILED_ADDRESS, ~KeyValue);
}