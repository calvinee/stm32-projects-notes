#include "sys.h"
#include "LED.h"
#include "lcd.h"
#include "adc.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "usmart.h"
#include "dac.h"


 int main(void)
 {	
	 u8 t = 0;
	 u16 adcx;
	 float temp;
	 u16 dacval=0;
	 u8 key;
	 
	 
	 
	 delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 uart_init(115200);
	 LED_Init();
	 KEY_Init();
	 Adc_Init();
	 LCD_Init();
	 usmart_dev.init(72);
	 Adc_Init();
	 Dac1_Init();
	 
	 POINT_COLOR = RED ;
	 LCD_ShowString(30,50,200,16,16,"DAC TEST");
	 LCD_ShowString(30,70,200,16,16,"2020.8.31");
	 LCD_ShowString (30,90,200,16,16,"WK_UP:+  KEY1:-");
	 //显示提示信息
	 POINT_COLOR = BLUE ; 
	 LCD_ShowString(60,110,200,16,16,"DAC VAL;");
	 LCD_ShowString(60,130,200,16,16,"DAC VOL:0.000V");
	 LCD_ShowString(60,150,200,16,16,"ADC VOL:0.000V");
	 
	 DAC_SetChannel1Data(DAC_Align_12b_R,0);//DAC通道1初始值设定0
	 
  while(1)
	{
	
		t++;
		key = KEY_Scan(0);//不连续按
		if(key==WKUP_PRES)
		{
			if(dacval<4000)
				dacval+=200;
			DAC_SetChannel1Data(DAC_Align_12b_R,dacval);//设置DAC值
		}
		else if (key==KEY1_PRES)
		{
			if(dacval>200)
			{
				dacval-=200;
			}
			else dacval = 0;
		DAC_SetChannel1Data(DAC_Align_12b_R,dacval);
		}
		if(t==10||key==KEY1_PRES||key==WKUP_PRES)
		{
			adcx=DAC_GetDataOutputValue(DAC_Channel_1);//读取前面设置的DAC值
			LCD_ShowxNum(60+8*8,110,adcx,4,16,0);
			temp = (float)adcx*(3.3/4096);
			LCD_ShowxNum(60+8*8,130,temp,1,16,0);
			adcx=temp;
			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(60+10*8,130,temp,3,16,0x80);
			//ADC获取DAC发送的值
			//TEMP是float类型，所以赋值也要是float
			adcx=Get_Adc_Average(ADC_Channel_1,10);		//得到ADC转换值	  
			temp = (float)adcx*(3.3/4096);
			adcx=temp;
			LCD_ShowxNum(124,150,temp,1,16,0);
			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(140,150,temp,3,16,0x80);
			LED0 = !LED0;
			t =0;
		}
		delay_ms(10);
		
		
	}
 }
