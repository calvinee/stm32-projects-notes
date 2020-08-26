#include "stm32f10x.h"
#include "LED.h"
#include "timer.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

/************************************************
ʵ������led0����72M/900=8
************************************************/


 int main(void)
 {	
  u16 led0pwm=0; //����led0�ĳ�ʼ��״̬Ϊ0   
  //u32 bound1=115200;
  u8 dir =1; //
	 delay_init(); ////��ʼ����ʱ��
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж����ȼ�2
	 uart_init(115200); // ���ô���Ƶ��
	 
	 LED_Init();//��ʼ��led
	 TIM3_PWM_Init(899,0); //��ʼ����ʱ��TIM3-pwm���ã�����PWM��Ƶ�ʣ��Ҽ�������÷�ΧΪ100<=f<=72	M (HZ)
  while(1)
	{
		delay_ms(10);  //ÿ��ѭ����ʱ10ms����������ʱ�������Ϊ20ms��������������
		if (dir)led0pwm++;  
		else led0pwm--;
		if(led0pwm>300)
			dir=0;
		if(led0pwm==0)dir=1;
		TIM_SetCompare2(TIM3,led0pwm); //�޸� TIM3_CCR2 ������ռ�ձ�
	}
 }
