#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "BEEP.h"
#include "led.h"

int main(void)
{
	
	delay_init();
	BEEP_Init();
	LED_Init();
	while(1)
	{
		
		LED0 = 0;//Ï¨ÃğLED
		BEEP = 1;//¹Ø±Õ·äÃùÆ÷
		delay_ms(500);
		
		LED0 = 1;//µãÁÁLED
		BEEP = 0;//Æô¶¯·äÃùÆ÷
		delay_ms(500);
		

	}
}
