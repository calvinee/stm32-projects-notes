#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "beep.h"
#include "led.h"

int main(void)
{
	Stm32_Clock_Init(9);//初始化时钟端口
	delay_init(108);
	beep_Init();
	LED_Init();
	
	while(1)
	{
		LED0=0;
		beep=0;
		delay_ms(500);
		
		LED0=1;
		beep=1;
		delay_ms(500);
	
	}
	
}
