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
	 //初始化各个模块
	 delay_init();//初始化delay
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 uart_init(115200);//初始化串口，并设定115200
	 LED_Init();//初始化LED
	 LCD_Init();//初始化LCD
	 Adc_Init();//初始化Adc
	 
	 //LCD显示
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2015/1/14");	
	//显示提示信息
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      
	LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");	   //显示小数点    
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		LCD_ShowxNum(156,130,adcx,4,16,0);//显示ADC的值
		//计算电压值浮点数
		temp=(float)adcx*(3.3/4096);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		adcx=temp;// u16 adcx; 是整数类型，赋值给它后得到整数
		LCD_ShowxNum(156,150,adcx,1,16,0);//显示电压值整数
		temp-=adcx;//得到小数部分
		temp*=1000;//数字乘1000，将小数转换为整数
		//LCD_ShowxNum(172,150,temp,3,16,0X80);
		LCD_ShowxNum(172,150,temp,3,16,128);//*p是u8类型，所以最大数（10000000）二进制数转换成十进制是128，还可以是0X80
		LED0=!LED0;
		delay_ms(250);	//250ms变化一次
	}
 }
