#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ADC ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/7 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved					   
//////////////////////////////////////////////////////////////////////////////////	 
 
void T_Adc_Init(void); //ADCͨ����ʼ��
u16 T_Get_Adc(u8 ch) ;
u16 T_Get_Temp(void);
u16 T_Get_Adc_Average(u8 ch,u8 times);
short Get_Temprate(void);	//��ȡ�ڲ��¶ȴ������¶�ֵ
 void  Adc3_Init(void);//��ʼ��ADC3
 u16 Get_Adc3(u8 ch)  ;////���ADC3ĳ��ͨ����ֵ




#endif 
