unsigned char SdInit(void);
unsigned char SdReadBlock(unsigned char *Block, unsigned long address,int len);
unsigned char SdWriteBlock(unsigned char *Block, unsigned long address,int len);
