#include "LED.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "lcd.h"
#include "delay.h"
#include "key.h"


#define SEND_BUF_SIZE 4000
//定义后面不需要；

u8 SendBuff[SEND_BUF_SIZE];	//发送数据缓冲区
const u8 TEXT_TO_SEND[]={"你好，你是我见过最美的晚霞"};//发送文本

int main(void)
 {	
	 u8 t=0,mask =0 ,j=sizeof(TEXT_TO_SEND);
	 u16 i ;
	 float pro=0; //进度
	 
	 
	delay_init();	    	 //延时函数初始化	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD 	
	KEY_Init();				//按键初始化		 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1通道4,外设为串口1,存储器为SendBuff,长度SEND_BUF_SIZE.
	 //DDMA1通道4,外设为串口1,存储器为SendBuff,长度SEND_BUF_SIZE.
	 POINT_COLOR=RED;
	 LCD_ShowString(30,50,200,16,16,"DMA test ");
	 LCD_ShowString(30,70,200,16,16,"2020/1/9");
	 LCD_ShowString(30,90,200,16,16,"KEY0:Start");
	 //显示提示信息

//	 printf("\r\n字节数:%d\r\n",j);
//		sizeof用法 sizeof:用于返回一个对象或者类型所占的的内存字节数。
//		sizeof(char)==1     //返回的是数据类型所占字节数
//		sizeof(short)==2
//		sizeof(int)==4
//		sizeof(float)==4
//		sizeof(double)==8	   
	for(i=0;i<SEND_BUF_SIZE;i++)//填充数据到SendBuff
    {
		if(t>=j)//加入换行符
		{
			if(mask)
			{
				SendBuff[i]=0x0a;//\r
				t=0;
			}else 
			{
				SendBuff[i]=0x0d;//\n
				mask++;
			}	
		}else//复制TEXT_TO_SEND语句
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}    	   
    }		 
	POINT_COLOR=BLUE;//设置字体为蓝色	  
	i=0;
  while(1)
	{
		t=KEY_Scan(0);
		if(t==KEY0_PRES)
		{
			LCD_ShowString(30,150,200,16,16,"Start Transimit....");
			LCD_ShowString(30,170,200,16,16,"   %");//显示百分号
				printf("\r\nDMA DATA:\r\n"); 	
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送      
			MYDMA_Enable(DMA1_Channel4);//开始一次DMA传输！	  
		    //等待DMA传输完成，此时我们来做另外一些事，点灯
		    //实际应用中，传输数据期间，可以执行另外的任务
			while(1)
			{
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);
					break;
					
				}
					pro=DMA_GetCurrDataCounter(DMA1_Channel4);
					pro=1-pro/SEND_BUF_SIZE;//得到百分比	
					pro*=100;
					LCD_ShowNum(30,170,pro,3,16);
			}
			LCD_ShowNum(30,170,100,3,16);//显示100%	  
			LCD_ShowString(30,150,200,16,16,"Transimit Finished!");//提示传送完成
	
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行
			i=0;
		}
		
	}
}
 

