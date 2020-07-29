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
	 LED0 = 0;//�������
	 BEEP = 0;//�رշ�����
	 //���ʱ�乫ʽ�� tout= (4*2^prer*rlr)/40
	 IWDG_Init(4,1250); //�����������ʱ��Ϊ2s��Ԥ��Ƶϵ��Ϊ4����rlrΪ625
	 while(1)
	 {
		if(KEY_Scan(0)==WKUP_PRES)
		{
			IWDG_ReloadCounter();
			BEEP=1;
			
		}
	 }
 }
