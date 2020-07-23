#include "led.h" 
#include "delay.h" 
//#include "sys.h" 
#include "stm32f10x.h"
//ALIENTEK 战舰 STM32 开发板实验 1 
//跑马灯实验   
int main(void) 
 {  
  delay_init();                //延时函数初始化    
  LED_Init();               //初始化与 LED 连接的硬件接口 
  while(1) 
	  {    
		
		//LED0 =0;    
		//LED1 =1; 
		//delay_ms(1000);             //延时 300ms 
		//LED0 =1; 
		//LED1 =0; 
		//delay_ms(300);             //延时 300ms 
		
		GPIO_SetBits(GPIOB,GPIO_Pin_5);//置高电平
		GPIO_SetBits(GPIOE,GPIO_Pin_5);//同上
		delay_ms(3000);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);//置低电平
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		delay_ms(1000);
	} 
} 
