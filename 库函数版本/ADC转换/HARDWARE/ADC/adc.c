#include "adc.h"
#include "stm32f10x.h"
#include "delay.h"
//#include "sys.h"
//初始化 ADC
//常规通道
//默认开启通道0`3
void Adc_Init(void)
{
	
	//宣告结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	//使能外设管脚
	//开ADC1和PA1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC最大采样频率14MHZ，否则不准
	//设置PA1
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//复位ADC
	//将外设ADC1的全部寄存器设置为缺省值
	ADC_DeInit(ADC1);
	
	//初始化ADC
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//单次转换模式
	ADC_InitStruct.ADC_DataAlign =ADC_DataAlign_Right;//ADC数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//转换由软件而不是外部触发启动
	ADC_InitStruct.ADC_Mode =  ADC_Mode_Independent; //设置为独立模式
	ADC_InitStruct.ADC_NbrOfChannel =1; // 顺序进行规则转换的ADC通道的数量
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;//单通道模式
	ADC_Init(ADC1,&ADC_InitStruct);
    //使能ADC
	ADC_Cmd(ADC1,ENABLE);
	////设置通道参数
	ADC_ResetCalibration(ADC1);//开启复位校准
	while(ADC_GetResetCalibrationStatus(ADC1));//等待复位校准结束
	ADC_StartCalibration(ADC1);//开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));//等待校准结束
}
//获得ADC值
//ch ：通道值0`3
u16  Get_Adc(u8 val)
{
	//设置指定ADC的规则组通道，一个序列，采样时间周期
	ADC_RegularChannelConfig(ADC1,val,1,ADC_SampleTime_239Cycles5);//ADC1,ADC通道,采样时间为239.5周期
//	ADC 的转换时间可以由以下公式计算：
//Tcovn=采样时间+12.5 个周期
//上一个函数定义	ADC时钟频率为12MHZ
//其中：Tcovn 为总转换时间，采样时间是根据每个通道的 SMP 位的设置来决定的。
//              sampletime        采样周期     采样时间US
//              1.5               14           7/6
//              7.5               20           5/3
//              13.5              26           13/6
//	            28..5             41           41/12
//              41.5              54           9/2=4.5
//              71.5              84           7
//              239.5	          252          21
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果

}
//获得ADC采样值的品均值
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
