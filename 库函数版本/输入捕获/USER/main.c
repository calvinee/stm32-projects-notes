#include "sys.h"
#include "key.h"
#include "timer.h"
#include "LED.h"
#include "delay.h"
#include "usart.h"


/************************************************
ʵ�飺���벶��
����TIM5��ͨ��1�����벶��ʵ�飬����PA0�ϵĸߵ�ƽ������
	��ͨ��WK_up���������룬��ͨ�����ڴ�ӡ�ߵ�ƽ����
************************************************/



extern u8 TIM5CH1_CAPTURE_STA; //���벶��״̬,�ﵽ������֮����������
extern u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ	
 int main(void)
 {		
 	u32 temp=0; 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
 
 	TIM3_PWM_Init(899,0); 		//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
 	TIM5_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� //һ��ʱ�����ھ���1us!!!
   	while(1)
	{
 		delay_ms(10);
		TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);

		if(TIM_GetCapture2(TIM3)==300)TIM_SetCompare2(TIM3,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F; //�Ƿ������
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ�� = ����ֵ+���ֵ
			printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ�� 
			TIM5CH1_CAPTURE_STA=0;//������һ�β���
		}
	}
 }
