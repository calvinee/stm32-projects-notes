#include "sys.h"
#include "usart.h"
#include "tpad.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
//#include ""
/************************************************
功能：触碰触摸按键后打印缺省值,
当触摸按键时ds0灯会灭，
经历采集了15次的时间后，DS1会灭。
没进行一次循环灯ds0都会闪烁
************************************************/



 int main(void)
 {	
	 u8 t=0;
	 delay_init(); //初始化延时函数
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断分组2
	 uart_init(115200);
	 LED_Init(); //初始化led
	 TPAD_Init(6);//初始化触摸按键并以72分频，最后以1MHZ的速度计数
  while(1)
	{
		if(TPAD_Scan(0))////mode:0,不支持连续触发(按下一次必须松开才能按下一次);
		{
			LED1=!LED1;
			
		}
		t++;
		if(t==15)
		{
			t=0;
			LED0=!LED0;
		
		}
		delay_ms(10);
	}
 }
