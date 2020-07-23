#include "stm32f10x.h"


/************************************************
 ALIENTEK 战舰STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


void My_usart1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   //GPIO结构体
	USART_InitTypeDef USART_InitStruct; //USART结构体
	NVIC_InitTypeDef NVIC_InitStruct; //NVIC结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //启动外设GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); //启动外设USART1
	//启动GPIO_A.9
	//设置GPIOA.9
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_AF_PP; //推挽复用
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化GPIOA.9
	//启动GPIO_A.10
	//设置GPIOA.10
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct); //初始化GPIOA.10
	
	//设置USART
	/*--------------------------
	|  波特率：115200        	|                
	|  串口硬件流：无            |
	|  奇偶校验位：无            |   
	|  串口模式：串口收发模式		|
    |  串口字长： 8bit     		|
	 ---------------------------
	*/
	USART_InitStruct.USART_BaudRate = 115200; 
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStruct);//初始化串口1
	
	USART_Cmd(USART1,ENABLE );//开启使能串口
	//USART_ITConfig
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启接受中断
	//INTERPERTER
	//NVIC
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;   //选择外设通道：串口通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;     //开启中断使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;//设置抢占优先级 1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;      //设置子优先级1
	
	NVIC_Init(&NVIC_InitStruct);//初始化中断函数
}


//终端服务函数
//串口 1 的中断响应函数
void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)) ////接收中断
	{
		res = USART_ReceiveData(USART1);//读取接收到的数据 

		USART_SendData(USART1,res);//发送接收到的数据 
		
	}

}

	
 int main(void)
 {	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断分组 2
	My_usart1_Init();  //使用MY_USART1_INIT函数
	while(1) //循环
	{
	 
	}
 }
 
 