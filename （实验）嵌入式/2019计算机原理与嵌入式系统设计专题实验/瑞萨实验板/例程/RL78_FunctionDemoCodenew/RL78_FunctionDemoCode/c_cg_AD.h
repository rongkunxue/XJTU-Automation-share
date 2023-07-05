 /***********************************************************************************************************************
 * File Name    : c_cg_AD.h
 * Version      : RL78/G13 V 0.01 1503 [23 Jan 2015]
 * Device(s)    : R5F100LG
 * Tool-Chain   : CA78K0R
 * Description  : This file implements main function.
 * Company Name : Getsoon Electronic Co.Ltd , Shanghai.China
 * Creation Date: 2015-1-23
 ***********************************************************************************************************************/

#ifndef GETSOON_AD_H_
#define GETSOON_AD_H_

void AD_delay(unsigned char t);
void ADC_init(void);
void ADC_Start(void);
void ADC_Stop(void);
void Led_display(void);

#endif /* GETSOON_AD_H_ */
