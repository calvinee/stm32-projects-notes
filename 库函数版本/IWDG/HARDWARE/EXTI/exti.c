#include "exti.h"
#include "BEEP.h"
#include "key.h"
#include "LED.h"
#include "delay.h"
#include "usart.h"

void EXTIX_Init(void)
{
	//定义宣告结构体
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	//初始化key
	KEY_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	
	EXTI_InitStruct.EXTI_Mode =EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Line = EXTI_Line2;
	EXTI_InitStruct.EXTI_LineCmd =ENABLE;
	EXTI_InitStruct.EXTI_Trigger =EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI2_IRQHandler(void)
{
	delay_ms(10);//防抖动
	if(KEY2==0)
	{
	LED0=!LED0;
	delay_ms(300);
	LED1=!LED1;	
	}
	
	EXTI_ClearITPendingBit(EXTI_Line2);
}
