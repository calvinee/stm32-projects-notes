#include "stm32f10x.h"
#include "adc.h"
#include "LED.h"
#include "delay.h"
#include "lcd.h"
#include "usart.h"


 int main(void)
 {	
	 u16 adcx;
	 float temp;
	 //��ʼ������ģ��
	 delay_init();//��ʼ��delay
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 uart_init(115200);//��ʼ�����ڣ����趨115200
	 LED_Init();//��ʼ��LED
	 LCD_Init();//��ʼ��LCD
	 Adc_Init();//��ʼ��Adc
	 
	 //LCD��ʾ
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2015/1/14");	
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      
	LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");	   //��ʾС����    
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		LCD_ShowxNum(156,130,adcx,4,16,0);//��ʾADC��ֵ
		//�����ѹֵ������
		temp=(float)adcx*(3.3/4096);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		adcx=temp;// u16 adcx; ���������ͣ���ֵ������õ�����
		LCD_ShowxNum(156,150,adcx,1,16,0);//��ʾ��ѹֵ����
		temp-=adcx;//�õ�С������
		temp*=1000;//���ֳ�1000����С��ת��Ϊ����
		//LCD_ShowxNum(172,150,temp,3,16,0X80);
		LCD_ShowxNum(172,150,temp,3,16,128);//*p��u8���ͣ������������10000000����������ת����ʮ������128����������0X80
		LED0=!LED0;
		delay_ms(250);	//250ms�仯һ��
	}
 }
