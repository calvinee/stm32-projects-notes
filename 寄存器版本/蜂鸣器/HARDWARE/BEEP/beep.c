#include "beep.h" 
//��ʼ�� PB8 Ϊ�����.��ʹ������ڵ�ʱ��         
//��������ʼ�� 
void beep_Init(void) 
{ 
  RCC->APB2ENR|=1<<3;       //ʹ�� PORTB ʱ��            
  GPIOB->CRH&=0XFFFFFFF0;   
  GPIOB->CRH|=0X00000003;  //PB.8  �������      
  beep = 0;       //�رշ�������� 

} 
