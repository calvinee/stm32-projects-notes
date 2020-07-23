#include "sys.h"	
#include "delay.h"	 
#include "led.h"

int main(void)
{
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(108);//延时初始化
	LED_Init();//led初始化
	while(1)
	{
		LED0=0;
		LED1=0;
		delay_ms(500);
		
		LED0=1;
		LED1=1;
		delay_ms(500);
	}
	
}





