#include "sys.h"	
#include "delay.h"	 
#include "led.h"

int main(void)
{
	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(108);//��ʱ��ʼ��
	LED_Init();//led��ʼ��
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





