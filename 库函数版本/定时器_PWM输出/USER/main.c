#include "stm32f10x.h"
#include "LED.h"
#include "timer.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

/************************************************
实验结果：led0按照72M/900=8
************************************************/


 int main(void)
 {	
  u16 led0pwm=0; //设置led0的初始化状态为0   
  //u32 bound1=115200;
  u8 dir =1; //
	 delay_init(); ////初始化延时器
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级2
	 uart_init(115200); // 设置串口频率
	 
	 LED_Init();//初始化led
	 TIM3_PWM_Init(899,0); //初始化定时器TIM3-pwm设置，设置PWM的频率，我计算得适用范围为100<=f<=72	M (HZ)
  while(1)
	{
		delay_ms(10);  //每个循环延时10ms，人眼连续时间最大间隔为20ms，所以是连续的
		if (dir)led0pwm++;  
		else led0pwm--;
		if(led0pwm>300)
			dir=0;
		if(led0pwm==0)dir=1;
		TIM_SetCompare2(TIM3,led0pwm); //修改 TIM3_CCR2 来控制占空比
	}
 }
