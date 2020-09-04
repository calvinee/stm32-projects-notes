#include "dma.h"
#include "sys.h"

DMA_InitTypeDef DMA_InitStructure;
u16 DMA1_MEM_LEN;//����DMA ÿ�����ݴ���ĳ���
//DMA1�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶��ģ����Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģ��/8λ���ݴ���/�洢������ģʽ
//DMA_CHx:DMAͨ��CHx
//cpar:�����ַ
//cmar���洢����ַ
//cndtr�����ݴ�����




void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	
	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//ʹ��DMAʱ��
	
	DMA_DeInit(DMA_CHx);//��DMA��ͨ��1�Ĵ�������λȱʡֵ
	DMA1_MEM_LEN=cndtr;
	
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar; //DMA ���� ADC ����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar; //DMA �ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; //���ڴ��ȡ���͵�����
	DMA_InitStructure.DMA_BufferSize = cndtr; //DMA ͨ���� DMA ����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //8 λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // 8 λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //��������������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA ͨ�� x ӵ�������ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //���ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure); //����ָ���Ĳ�����ʼ��
}
//����һ��DMA����
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{
	DMA_Cmd(DMA_CHx,DISABLE);//�ر�USART1 TX DMA1 ��ָͨ��
	DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMAͨ����DMA����Ĵ�С
	DMA_Cmd(DMA_CHx,ENABLE);//ʹ��USART TX DMA1 ��ָʾ��ͨ��
}


