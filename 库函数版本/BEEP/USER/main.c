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
		
		LED0 = 0;//Ϩ��LED
		BEEP = 1;//�رշ�����
		delay_ms(500);
		
		LED0 = 1;//����LED
		BEEP = 0;//����������
		delay_ms(500);
		

	}
}
