#include "led.h" 
#include "delay.h" 
#include "key.h" 
#include "sys.h" 
#include "beep.h" 
//ALIENTEK ս�� STM32 ������ʵ�� 3 
//��������ʵ��   
int main(void) 
  { 
	  u8 key;  
      delay_init();                        //��ʱ������ʼ��    
      LED_Init();                     //LED �˿ڳ�ʼ�� 
      KEY_Init();                            //��ʼ���밴�����ӵ�Ӳ���ӿ� 
      BEEP_Init();                            //��ʼ���������˿� 
      LED0=0;                   //�ȵ������ 
	  while(1) 
	  { 
			key =KEY_Scan(0);                //�õ���ֵ 
			  if(key) 
			   {  
				   switch(key) 
				{  
					   case WKUP_PRES:           //���Ʒ����� 
				            BEEP=!BEEP;break; 
				       case KEY2_PRES:           //���� LED0 ��ת 
				            LED0=!LED0;break; 
				       case KEY1_PRES:         //���� LED1 ��ת  
				            LED1=!LED1;break; 
				       case KEY0_PRES:           //ͬʱ���� LED0,LED1 ��ת  
				            LED0=!LED0; 
				            LED1=!LED1;break; 
				} 
			   }else delay_ms(10);  
	  }   
  } 
