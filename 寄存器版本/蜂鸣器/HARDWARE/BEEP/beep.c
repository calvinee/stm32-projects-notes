#include "beep.h" 
//初始化 PB8 为输出口.并使能这个口的时钟         
//蜂鸣器初始化 
void beep_Init(void) 
{ 
  RCC->APB2ENR|=1<<3;       //使能 PORTB 时钟            
  GPIOB->CRH&=0XFFFFFFF0;   
  GPIOB->CRH|=0X00000003;  //PB.8  推挽输出      
  beep = 0;       //关闭蜂鸣器输出 

} 
