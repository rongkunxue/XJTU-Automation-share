/************************************************************************************************************************
 * File Name    : c_cg_AD.c
 * Version      : RL78/G13 V 0.01 1503 [23 Jan 2015]
 * Device(s)    : R5F100LG
 * Tool-Chain   : CA78K0R
 * Description  : This file implements main function.
 * Company Name : Getsoon Electronic Co.Ltd , Shanghai.China
 * Creation Date: 2015-1-23
 ***********************************************************************************************************************/


#pragma sfr
#pragma DI
#pragma EI
#pragma interrupt INTAD r_adc_interrupt     

int mun[10]={0x3f,0x06,0x5B,0x4F,0x66,0x6d,0x7D,0x07,0x7F,0x6F};

void ADC_init(void)
{
	ADCEN = 1U;  /* supply AD clock */
	ADM0 = 0;  /* disable AD conversion and clear ADM0 register */
	ADMK = 1U;  /* disable INTAD interrupt */
	ADIF = 0U;  /* clear INTAD interrupt flag */
	/* Set INTAD low priority */
	ADPR1 = 1U;
	ADPR0 = 1U;
	/* Set ANI0 - ANI7 pin as analog input */
	PM2 |= 0xFFU;
	/* Set ANI19 pin */
	PMC12 |= 0x01U;
	PM12 |= 0x01U;
	ADM0 = 7;
	ADM1 = 0x20;
	ADM2 = 0;
	ADUL = 255;
	ADLL = 0;
	ADS = 0x13;
}
void AD_delay(unsigned char t)
{
	for(;t>0;t--);
	for(;t>0;t--);  /*delay some time,not sure*/
}
void ADC_Start(void)
{
	ADCE = 1U;
	ADIF = 0U;  /* clear INTAD interrupt flag */
	ADMK = 0U;  /* enable INTAD interrupt */
	ADCS = 1U;  /* enable AD conversion */
	while(ADCS);
	
	// delay(1000);
}
void Led_display(void)
{
	int s,i;
	s=(long)(ADCR>>6)*5000/1024;
	for(i=0;i<3000;i++)
	{
		P5&=~(0xf<<2);
		P1=(mun[s/1000]|(1<<7));
		P5.2=1;
		AD_delay(1000);
		P5.2=0;
		AD_delay(10);
		P1=mun[s%1000/100];
		P5.3=1;
		AD_delay(1000);
		P5.3=0;
		AD_delay(10);
		P1=mun[s%100/10];
		P5.4=1;
		AD_delay(1000);
		P5.4=0;
		AD_delay(10);
		P1=mun[s%10];
		P5.5=1;
		AD_delay(1000);
		P5.5=0;
		AD_delay(10);
	}

}
void ADC_Stop(void)
{
	ADCS = 0U;  /* disable AD conversion */
	ADMK = 1U;  /* disable INTAD interrupt */
	ADIF = 0U;  /* clear INTAD interrupt flag */
}

__interrupt static void r_adc_interrupt(void)
{
	/* Start user code. Do not edit comment generated here */
	WDTE = 0xAC;
	Led_display();
	
	/* End user code. Do not edit comment generated here */
}



