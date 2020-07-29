//#include "sys.h"
#include "LED.h"
#include "exti.h"
#include "BEEP.h"
#include "key.h"
#include "usart.h"
#include "delay.h"

 int main(void)
{	
	 //��ʼ������
	 LED_Init(); //LED��ʼ��
	 EXTIX_Init();//�жϳ�ʼ��
	 uart_init(115200); //���ڳ�ʼ��
	 delay_init();
	 KEY_Init();
	 BEEP_Init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//����LEDΪ�͵�ƽ������
	 LED0=1;
	 LED1=0;
	 
	 while(1)
	{
		printf("���\r\n");
		delay_ms(1000);
	}
	
}
