#include "timer.h"
#include "LED.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 

//V1.1 20120904
//1,����TIM3_PWM_Init������
//2,����LED0_PWM_VAL�궨�壬����TIM3_CH2����									  
//////////////////////////////////////////////////////////////////////////////////  
   	  
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	//����ṹ������
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//����1����ʱ��ʹ��-TIM
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	//����ʱ����arr��psc��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_Trigger,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		LED1=!LED1;
		}
}




//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	

}


//TIM_ICInitTypeDef 	TIM5_ICInitStruct;

void TIM5_Cap_Init(u16 arr,u16 psc)
{
	TIM_ICInitTypeDef 	TIM5_ICInitStruct;
	GPIO_InitTypeDef	 GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef	 TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef 	NVIC_InitStruct;
	// ע������һ��Ҫ���ں���ͷ��λ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; //PA0 ���� 
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//GPIO��ʼ��
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // TDTS = Tck_tim
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period = arr;//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;////Ԥ��Ƶ��
	//TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);//��ʱ����ʼ��
	
	TIM5_ICInitStruct.TIM_Channel = TIM_Channel_1; //ѡ������� IC1 ӳ�䵽 TI1 ��
	TIM5_ICInitStruct.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM5_ICInitStruct.TIM_ICPolarity =TIM_ICPolarity_Rising;//�����ز���
	TIM5_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//���������Ƶ,����Ƶ
	TIM5_ICInitStruct.TIM_ICSelection =TIM_ICSelection_DirectTI;//ӳ�䵽 TI1 ��
	TIM_ICInit(TIM5,&TIM5_ICInitStruct);//����Ƚϳ�ʼ��
	
	NVIC_InitStruct.NVIC_IRQChannel	 =TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStruct);//�жϳ�ʼ��
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//TIM�ĸ����ж�����
	TIM_Cmd(TIM5,ENABLE);//ʹ�ܶ�ʱ��
	


}

u8 TIM5CH1_CAPTURE_STA = 0 ;//���벶��ߵ�ƽʱ���������ʼ��
u16 TIM5CH1_CAPTURE_VAL ;//���벶��ֵ
//TIM5���жϷ�����
void TIM5_IRQHandler(void)
{
	
	if((TIM5CH1_CAPTURE_STA&0X80)==0)  //δ�ɹ�����
	{
		if(TIM_GetITStatus(TIM5,TIM_IT_Update!=RESET))	//δ�ɹ�����
		{
			if(TIM5CH1_CAPTURE_STA&0X40) //�ɹ�����ߵ�ƽ
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F) //�ߵ�ƽ̫��
				{
					TIM5CH1_CAPTURE_STA|= 0X80; //��ǳɹ�����
					TIM5CH1_CAPTURE_VAL = 0XFFFF;
					
				}
				else TIM5CH1_CAPTURE_STA++;
				
			}
		}
		if(TIM_GetITStatus(TIM5,TIM_IT_CC1)!=RESET) //����ͨ��1���������¼�
		{
			if (TIM5CH1_CAPTURE_STA&0x40)//����һ���½���
			{
				TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�����һ��������
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);//��ʱ���Ƚ����ȼ�����Ϊ�����ز���
			}
			else //��û�п�ʼ��һ�β������ǵ�һ�β��������� 
			{
				TIM5CH1_CAPTURE_STA=0; //���
				TIM5CH1_CAPTURE_VAL=0;//���
				TIM_SetCounter(TIM5,0); 
				TIM5CH1_CAPTURE_STA|=0X40; //��ǲ�����������,Ҳ�������ʱһ��ʱ��ʱ��*64��ʱ��
				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}
	
	TIM_ClearITPendingBit(TIM5,TIM_IT_CC1|TIM_IT_Update);//����жϱ�־λ

}


