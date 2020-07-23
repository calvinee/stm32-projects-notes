#include "stm32f10x.h"


/************************************************
 ALIENTEK ս��STM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


void My_usart1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   //GPIO�ṹ��
	USART_InitTypeDef USART_InitStruct; //USART�ṹ��
	NVIC_InitTypeDef NVIC_InitStruct; //NVIC�ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //��������GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); //��������USART1
	//����GPIO_A.9
	//����GPIOA.9
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF_PP; //���츴��
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ��GPIOA.9
	//����GPIO_A.10
	//����GPIOA.10
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct); //��ʼ��GPIOA.10
	
	//����USART
	/*--------------------------
	|  �����ʣ�115200        	|                
	|  ����Ӳ��������            |
	|  ��żУ��λ����            |   
	|  ����ģʽ�������շ�ģʽ		|
    |  �����ֳ��� 8bit     		|
	 ---------------------------
	*/
	USART_InitStruct.USART_BaudRate = 115200; 
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStruct);//��ʼ������1
	
	USART_Cmd(USART1,ENABLE );//����ʹ�ܴ���
	//USART_ITConfig
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//���������ж�
	//INTERPERTER
	//NVIC
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;   //ѡ������ͨ��������ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;     //�����ж�ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;//������ռ���ȼ� 1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;      //���������ȼ�1
	
	NVIC_Init(&NVIC_InitStruct);//��ʼ���жϺ���
}


//�ն˷�����
//���� 1 ���ж���Ӧ����
void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)) ////�����ж�
	{
		res = USART_ReceiveData(USART1);//��ȡ���յ������� 

		USART_SendData(USART1,res);//���ͽ��յ������� 
		
	}

}

	
 int main(void)
 {	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����жϷ��� 2
	My_usart1_Init();  //ʹ��MY_USART1_INIT����
	while(1) //ѭ��
	{
	 
	}
 }
 
 