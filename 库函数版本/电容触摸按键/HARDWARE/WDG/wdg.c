#include "wdg.h"

void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//ȡ��д��������ʹ��
	IWDG_SetPrescaler(prer);//���ÿ��Ź�Ԥ��Ƶϵ��
	IWDG_SetReload(rlr);//���ÿ��Ź���װ��ֵ
	IWDG_ReloadCounter();//���Ź�ι��
	IWDG_Enable();//���Ź�ʹ��
}
