#include "wdg.h"

void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//取消写保护并且使能
	IWDG_SetPrescaler(prer);//设置看门狗预分频系数
	IWDG_SetReload(rlr);//设置看门狗重装载值
	IWDG_ReloadCounter();//看门狗喂狗
	IWDG_Enable();//看门狗使能
}
