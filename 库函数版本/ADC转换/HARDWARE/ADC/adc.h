#ifndef __ADC_H
#define __ADC_H		
#include "sys.h"	 

void Adc_Init(void);

u16 Get_Adc_Average(u8 val,u8 times);
u16  Get_Adc(u8 val);

#endif


