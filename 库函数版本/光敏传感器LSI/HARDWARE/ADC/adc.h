#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//ADC 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/7 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved					   
//////////////////////////////////////////////////////////////////////////////////	 
 
void T_Adc_Init(void); //ADC通道初始化
u16 T_Get_Adc(u8 ch) ;
u16 T_Get_Temp(void);
u16 T_Get_Adc_Average(u8 ch,u8 times);
short Get_Temprate(void);	//获取内部温度传感器温度值
 void  Adc3_Init(void);//初始化ADC3
 u16 Get_Adc3(u8 ch)  ;////获得ADC3某个通道的值




#endif 
