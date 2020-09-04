#include "lsens.h"
#include "delay.h"
#include "adc.h"
//#include "sys.h"

//��ʼ������������
void Lsens_Init(void)  //��ʼ������������
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStruct);//��ʼ��PF8

	Adc3_Init();//��ʼ��ADC3
}

//��ȡ������������ֵ
//0~100Ϊ����ֵ��0��Ӧ��Ļ�����100�����Ļ���
u8 Lsens_Get_Val(void)//��ȡ������������ֵ
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<LSENS_READ_TIMES;t++)
	{
		temp_val+=Get_Adc3(LSENS_ADC_CHX);//��ȡADC��ֵ���ܺ�
		delay_ms(5);
	}
	temp_val/=LSENS_READ_TIMES;//ȡADCƽ��ֵ
	if(temp_val>4000)
		temp_val=4000;
	return (u8)(100-(temp_val/40));
}


