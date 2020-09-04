#include "dac.h"
#include "sys.h"

//DAC 通道1输出初始化
void Dac1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	DAC_InitTypeDef DAC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	
	//PA4  DAC
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude= DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_1,&DAC_InitStruct);

	DAC_Cmd(DAC_Channel_1,ENABLE);
	DAC_SetChannel1Data(DAC_Align_12b_R,0x00);
	
	//DAC_GetDataOutputValue(DAC_Channel_1);
}

//设置通道1的电压值
//vol： 0~3300，代表0~3.3v
void Dac1_Set_Vol(u16 vol)
{
	float temp1 =vol;
	temp1=temp1*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp1);//12位右对齐设置DAC值


}


