#include "led.h" 
#include "delay.h" 
//#include "sys.h" 
#include "stm32f10x.h"
//ALIENTEK ս�� STM32 ������ʵ�� 1 
//�����ʵ��   
int main(void) 
 {  
  delay_init();                //��ʱ������ʼ��    
  LED_Init();               //��ʼ���� LED ���ӵ�Ӳ���ӿ� 
  while(1) 
	  {    
		
		//LED0 =0;    
		//LED1 =1; 
		//delay_ms(1000);             //��ʱ 300ms 
		//LED0 =1; 
		//LED1 =0; 
		//delay_ms(300);             //��ʱ 300ms 
		
		GPIO_SetBits(GPIOB,GPIO_Pin_5);//�øߵ�ƽ
		GPIO_SetBits(GPIOE,GPIO_Pin_5);//ͬ��
		delay_ms(3000);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);//�õ͵�ƽ
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		delay_ms(1000);
	} 
} 
