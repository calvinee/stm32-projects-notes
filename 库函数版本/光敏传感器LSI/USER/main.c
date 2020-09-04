#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "LED.h"
#include "lcd.h"
#include "adc.h"
#include "lsens.h"


 int main(void)
 {	
	 short adcx;
	 //宣告
	 delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 uart_init(115200);
	 LED_Init();
	 LCD_Init();
	 Lsens_Init();
	 
	 //设置提示信息
	 POINT_COLOR = RED;
	 LCD_ShowString(30,50,200,16,16,"LIGHT SENSOR TEST !");
	 LCD_ShowString(30,70,200,16,16,"lsens_val:");
	 
	 while(1)
	{
		adcx = Lsens_Get_Val();//获得lsens的值
		POINT_COLOR = BLUE;
		//LCD_ShowNum(30+10*8,70,adcx,3,16);//显示数值哦
		LCD_ShowxNum(30+10*8,70,adcx,3,16,0);
		LED0 = !LED0;
		delay_ms(250);//延时频率

	}
 
}
 
