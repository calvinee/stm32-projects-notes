#include "delay.h"
#include "key.h"
#include "sys.h"
#include "BEEP.h"
#include "LED.h"



 int main(void)
 {	
	u8 key;
	 delay_init();
	 LED_Init();
	 KEY_Init();
	 BEEP_Init();
	
	 delay_ms(200);
	 LED0 = 0;//点亮红灯
	 BEEP = 0;//关闭蜂鸣器
	 //溢出时间公式： tout= (4*2^prer*rlr)/40
	 IWDG_Init(4,1250); //我们设置溢出时间为2s，预分频系数为4，则rlr为625
	 while(1)
	 {
		if(KEY_Scan(0)==WKUP_PRES)
		{
			IWDG_ReloadCounter();
			BEEP=1;
			
		}
	 }
 }
