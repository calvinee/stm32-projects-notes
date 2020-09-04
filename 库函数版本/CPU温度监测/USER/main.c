//#include "stm32f10x.h"
#include "LED.h"
#include "lcd.h"
#include "adc.h"
//#include "key.h"
#include "tsensor.h"
#include "delay.h"
#include "sys.h"
//#include "sys.h"
#include "usart.h"

 int main(void)
 {	
    //��ʼ������
	 u16 adcx;
	 short temp;
	 delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж�������2
	 uart_init(115200);//���ô���Ƶ��
	 //��ʼ��ģ��
	 LCD_Init();
	 LED_Init();
	 Adc_Init();
	// KEY_Init();
	
	 T_Adc_Init();
	
	 //�ж������������


	//������ʾLCD
	//����������ɫ
	POINT_COLOR=RED;
	LCD_ShowString(30,50,300,16,16,"SHANXIKEJIDAXUE");
	LCD_ShowString(30,70,300,16,16,"2020/8/28");
	
	//��ʾ��ʾ��Ϣ
	//������ʾ��Ϣ��ɫ
	POINT_COLOR=BLUE;  
	LCD_ShowString(30,100,300,16,16,"CPU_TEMP_VAL:0000");
	LCD_ShowString(30,120,200,16,16,"CPU_TEMP_VOL:00.0000V");
	LCD_ShowString(30,140,200,16,16,"TEMPERATE: 00.00C");//�ϸ����趨��д�Ϳո�
	
	 
	 while(1)
	{
		
		float temp1;
		
		temp=Get_Temprate();//����¶�ֵ
		adcx=Get_Adc_Average(ADC_Channel_16,10);
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowString(30+10*8,140,16,16,16,"-");//��ʾ����
		}			
		else
			LCD_ShowString(30+10*8,140,16,16,16," ");//��ʾ�޷���
		//temperate
		LCD_ShowxNum(30+11*8,140,temp/100,2,16,0);//��ʾ��������
		LCD_ShowxNum(30+14*8,140,temp%100,2,16,0X80);//��ʾС������
		//val
		LCD_ShowxNum(30+13*8,100,adcx,6,16,0);//��ʾcpu�¶ȵ�ADCֵ
		//vol
	    temp1 = (float)adcx*(3.3/4096);
		adcx=temp1;
		LCD_ShowxNum(30+13*8,120,adcx,2,16,0);//��ʾ��������
		temp1-=adcx;
		temp1*=1000;
		LCD_ShowxNum(30+16*8,120,temp1,4,16,0x80);//��ʾС������

		LED0=!LED0;
		delay_ms(250);//����Ƶ��Ϊ1s�Ĵ�
		
		

		
	}
 }



