#include "sys.h"
#include "usart.h"
#include "tpad.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
//#include ""
/************************************************
���ܣ����������������ӡȱʡֵ,
����������ʱds0�ƻ���
�����ɼ���15�ε�ʱ���DS1����
û����һ��ѭ����ds0������˸
************************************************/



 int main(void)
 {	
	 u8 t=0;
	 delay_init(); //��ʼ����ʱ����
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����жϷ���2
	 uart_init(115200);
	 LED_Init(); //��ʼ��led
	 TPAD_Init(6);//��ʼ��������������72��Ƶ�������1MHZ���ٶȼ���
  while(1)
	{
		if(TPAD_Scan(0))////mode:0,��֧����������(����һ�α����ɿ����ܰ���һ��);
		{
			LED1=!LED1;
			
		}
		t++;
		if(t==15)
		{
			t=0;
			LED0=!LED0;
		
		}
		delay_ms(10);
	}
 }
