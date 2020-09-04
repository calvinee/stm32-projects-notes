#include "lsens.h"
#include "delay.h"
#include "adc.h"
//#include "sys.h"

//初始化光敏传感器
void Lsens_Init(void)  //初始化光敏传感器
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOF,&GPIO_InitStruct);//初始化PF8

	Adc3_Init();//初始化ADC3
}

//读取光敏传感器的值
//0~100为返回值，0对应最暗的环境，100最亮的环境
u8 Lsens_Get_Val(void)//读取光敏传感器的值
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<LSENS_READ_TIMES;t++)
	{
		temp_val+=Get_Adc3(LSENS_ADC_CHX);//读取ADC的值的总和
		delay_ms(5);
	}
	temp_val/=LSENS_READ_TIMES;//取ADC平均值
	if(temp_val>4000)
		temp_val=4000;
	return (u8)(100-(temp_val/40));
}


