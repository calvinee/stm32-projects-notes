#include "adc.h"
#include "stm32f10x.h"
#include "delay.h"
//#include "sys.h"
//��ʼ�� ADC
//����ͨ��
//Ĭ�Ͽ���ͨ��0`3
void Adc_Init(void)
{
	
	//����ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	//ʹ������ܽ�
	//��ADC1��PA1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC������Ƶ��14MHZ������׼
	//����PA1
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//��λADC
	//������ADC1��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_DeInit(ADC1);
	
	//��ʼ��ADC
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//����ת��ģʽ
	ADC_InitStruct.ADC_DataAlign =ADC_DataAlign_Right;//ADC�����Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ת��������������ⲿ��������
	ADC_InitStruct.ADC_Mode =  ADC_Mode_Independent; //����Ϊ����ģʽ
	ADC_InitStruct.ADC_NbrOfChannel =1; // ˳����й���ת����ADCͨ��������
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;//��ͨ��ģʽ
	ADC_Init(ADC1,&ADC_InitStruct);
    //ʹ��ADC
	ADC_Cmd(ADC1,ENABLE);
	////����ͨ������
	ADC_ResetCalibration(ADC1);//������λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);//����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�У׼����
}
//���ADCֵ
//ch ��ͨ��ֵ0`3
u16  Get_Adc(u8 val)
{
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ������
	ADC_RegularChannelConfig(ADC1,val,1,ADC_SampleTime_239Cycles5);//ADC1,ADCͨ��,����ʱ��Ϊ239.5����
//	ADC ��ת��ʱ����������¹�ʽ���㣺
//Tcovn=����ʱ��+12.5 ������
//��һ����������	ADCʱ��Ƶ��Ϊ12MHZ
//���У�Tcovn Ϊ��ת��ʱ�䣬����ʱ���Ǹ���ÿ��ͨ���� SMP λ�������������ġ�
//              sampletime        ��������     ����ʱ��US
//              1.5               14           7/6
//              7.5               20           5/3
//              13.5              26           13/6
//	            28..5             41           41/12
//              41.5              54           9/2=4.5
//              71.5              84           7
//              239.5	          252          21
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����

}
//���ADC����ֵ��Ʒ��ֵ
u16 Get_Adc_Average(u8 val,u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(val);
		delay_ms(5);
	}
	return temp_val/times;

}
