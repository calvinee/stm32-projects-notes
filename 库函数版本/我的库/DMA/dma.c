#include "dma.h"
#include "sys.h"

DMA_InitTypeDef DMA_InitStructure;
u16 DMA1_MEM_LEN;//保存DMA 每次数据传输的长度
//DMA1的各通道配置
//这里的传输形式是固定的，这点要根据不同的情况来修改
//从存储器->外设模块/8位数据带宽/存储器增量模式
//DMA_CHx:DMA通道CHx
//cpar:外设地址
//cmar：存储器地址
//cndtr：数据传输量




void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	
	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//使能DMA时钟
	
	DMA_DeInit(DMA_CHx);//将DMA的通道1寄存器设置位缺省值
	DMA1_MEM_LEN=cndtr;
	
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar; //DMA 外设 ADC 基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar; //DMA 内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; //从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = cndtr; //DMA 通道的 DMA 缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //8 位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // 8 位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //工作在正常缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA 通道 x 拥有中优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //非内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure); //根据指定的参数初始化
}
//开启一次DMA传输
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
	DMA_Cmd(DMA_CHx,DISABLE);//关闭USART1 TX DMA1 所指通道
	DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMA通道的DMA缓存的大小
	DMA_Cmd(DMA_CHx,ENABLE);//使能USART TX DMA1 所指示的通道
}


