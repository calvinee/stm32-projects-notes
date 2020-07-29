//#include "sys.h"
#include "LED.h"
#include "exti.h"
#include "BEEP.h"
#include "key.h"
#include "usart.h"
#include "delay.h"

 int main(void)
{	
	 //初始化外设
	 LED_Init(); //LED初始化
	 EXTIX_Init();//中断初始化
	 uart_init(115200); //串口初始化
	 delay_init();
	 KEY_Init();
	 BEEP_Init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//设置LED为低电平，开启
	 LED0=1;
	 LED1=0;
	 
	 while(1)
	{
		printf("完成\r\n");
		delay_ms(1000);
	}
	
}
