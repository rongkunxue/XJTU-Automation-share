//LED灯闪烁程序C代码
#define WriteReg(Address,Value)  *(unsigned int volatile *)(Address) = Value
#define U32       unsigned int
#define REG_EXT0CON	      0xFFF01018 
#define EBILED_ADDRESS       0x78000000 
//子函数声明 
void EBILedSet(U32 Value); 
void Delay(U32 t); 
//主函数 
int main(void) 
{ 
     U32 i;
     WriteReg(REG_EXT0CON, 0xF0078003); 
     while(1) 
     { 
         for(i = 0 ;i < 8; i++) 
         { 
              EBILedSet(0x1<<i); 
              Delay(1000000); 
         } 
     } 
     return 0; 
} 
//延时 
void Delay(U32 t) 
{ 
     do 
     { 
         t--; 
     }while(t); 
} 
//控制LED 灯的亮灭 
void EBILedSet(U32 Value) 
{ 
	WriteReg(EBILED_ADDRESS, ~Value); 
}