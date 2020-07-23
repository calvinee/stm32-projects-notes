#include "key.h"
#include "sys.h"
#include "delay.h"
#include "stm32f10x.h"

//��ʼ����������
//��ʼ��IO
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE); //����ʱ��ʹ�ܶ�
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_2|GPIO_Pin_3;			    //LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	 //����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOE, &GPIO_InitStructure);		//��ʼ��GPIOB.5
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	   //��ʼ��  WK_UP-->GPIOA.0  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	 //PA0 ���ó����룬����
	GPIO_Init(GPIOA, &GPIO_InitStructure);		//��ʼ��GPIOE.5
}
//���������� 
//���ذ���ֵ 
//mode:0,��֧��������;1,֧��������; 
//0��û���κΰ�������;1��KEY0 ����;2��KEY1 ����;3��KEY2 ����  ;4��KEY3 ����  WK_UP 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!! 

//֧�����������Ͳ���������
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1;//�ɿ���׼ ����һ��key_up
	if(mode)key_up=1;//������䣬����������
	if(key_up&(KEY0==0|KEY1==0|KEY2==0|WK_UP==1))
	{
		delay_ms(10);//����???�� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)return WKUP_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	   
	return 0;//�ް�������
}
