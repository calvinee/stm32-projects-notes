#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define LED0 PBout(5)  //gpiob.5
#define LED1 PEout(5) //gpioe.5

void LED_Init(void); //LED ≥ı ºªØ
#endif
