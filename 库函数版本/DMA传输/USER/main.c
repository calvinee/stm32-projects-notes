#include "LED.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "lcd.h"
#include "delay.h"
#include "key.h"


#define SEND_BUF_SIZE 4000
//������治��Ҫ��

u8 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����
const u8 TEXT_TO_SEND[]={"��ã������Ҽ�����������ϼ"};//�����ı�

int main(void)
 {	
	 u8 t=0,mask =0 ,j=sizeof(TEXT_TO_SEND);
	 u16 i ;
	 float pro=0; //����
	 
	 
	delay_init();	    	 //��ʱ������ʼ��	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD 	
	KEY_Init();				//������ʼ��		 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����SEND_BUF_SIZE.
	 //DDMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����SEND_BUF_SIZE.
	 POINT_COLOR=RED;
	 LCD_ShowString(30,50,200,16,16,"DMA test ");
	 LCD_ShowString(30,70,200,16,16,"2020/1/9");
	 LCD_ShowString(30,90,200,16,16,"KEY0:Start");
	 //��ʾ��ʾ��Ϣ

//	 printf("\r\n�ֽ���:%d\r\n",j);
//		sizeof�÷� sizeof:���ڷ���һ���������������ռ�ĵ��ڴ��ֽ�����
//		sizeof(char)==1     //���ص�������������ռ�ֽ���
//		sizeof(short)==2
//		sizeof(int)==4
//		sizeof(float)==4
//		sizeof(double)==8	   
	for(i=0;i<SEND_BUF_SIZE;i++)//������ݵ�SendBuff
    {
		if(t>=j)//���뻻�з�
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
		}else//����TEXT_TO_SEND���
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}    	   
    }		 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	i=0;
  while(1)
	{
		t=KEY_Scan(0);
		if(t==KEY0_PRES)
		{
			LCD_ShowString(30,150,200,16,16,"Start Transimit....");
			LCD_ShowString(30,170,200,16,16,"   %");//��ʾ�ٷֺ�
				printf("\r\nDMA DATA:\r\n"); 	
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //ʹ�ܴ���1��DMA����      
			MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA���䣡	  
		    //�ȴ�DMA������ɣ���ʱ������������һЩ�£����
		    //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
			while(1)
			{
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);
					break;
					
				}
					pro=DMA_GetCurrDataCounter(DMA1_Channel4);
					pro=1-pro/SEND_BUF_SIZE;//�õ��ٷֱ�	
					pro*=100;
					LCD_ShowNum(30,170,pro,3,16);
			}
			LCD_ShowNum(30,170,100,3,16);//��ʾ100%	  
			LCD_ShowString(30,150,200,16,16,"Transimit Finished!");//��ʾ�������
	
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������
			i=0;
		}
		
	}
}
 

