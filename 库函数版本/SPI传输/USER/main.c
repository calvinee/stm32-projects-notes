#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "w25qxx.h"	 

//要写入到W25Q64的字符串数组
const  u8  TEXT_Buffer[]={"i haven't Chinese font.h,wuwuwuwuuwu "};
//onst u8 TEXT_Buffer[]={"WarShipSTM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)

int main(void)
{
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;
//	u8 b;
	
	//初始化部件
		delay_init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		uart_init(115200);
		LED_Init();
		LCD_Init();
		KEY_Init();
		W25QXX_Init();
		
	//设置显示
			//POINT_COLOR = RED ;
	 POINT_COLOR = BLUE;
	 LCD_ShowString(30,50,200,16,16,"SPI测试");
	 LCD_ShowString(30,70,200,16,16,"2020/9/2");
	 LCD_ShowString(30,90,200,16,16,"KEY1:Write  KEY0:Read");	//显示提示信息	
	//#define W25Q80 	0XEF13 	
//#define W25Q16 	0XEF14
//#define W25Q32 	0XEF15
//#define W25Q64 	0XEF16
//#define W25Q128	0XEF17

	while(W25QXX_ReadID()!=W25Q128)								//检测不到W25Q128
	{
		switch (W25QXX_ReadID())
		{
			case W25Q128:
				{
					LCD_ShowString(30,110,200,16,16,"W25Q128 CHECK SUCCESSFUL");
					delay_ms(500);
					LED0=0;	
				}
			case W25Q16:			
				{
					LCD_ShowString(30,110,200,16,16,"W25Q16 CHECK FAILED");
					delay_ms(250);
					LED0=!LED0;	
				}
			case W25Q32:
				{
					LCD_ShowString(30,110,200,16,16,"W25Q32 CHECK FAILED");
					delay_ms(250);
					LED0=!LED0;	
				}
			case W25Q64:			
				{
					LCD_ShowString(30,110,200,16,16,"W25Q64 CHECK FAILED");
					delay_ms(250);
					LED0=!LED0;	
				}
			default: 
				{
						LCD_ShowString(30,110,200,16,16," CHECK FAILED");
						delay_ms(250);
						LCD_ShowString(30,130,200,16,16,"please check");
						delay_ms(250);
						LED0=!LED0;		
					
				}
		}
	
//		LCD_ShowString(30,150,200,16,16,"W25Q128 Check Failed!");
//		delay_ms(500);
//		LCD_ShowString(30,150,200,16,16,"Please Check!        ");
//		delay_ms(500);
//		LED0=!LED0;//DS0闪烁
	}
    LCD_ShowString(30,110,200,16,16,"W25Q128 CHECK SUCCESSFUL");
	LCD_ShowString(30,150,200,16,16,"W25Q128 Ready!");    
	FLASH_SIZE=128*1024*1024;	//FLASH 大小为16M字节
	//	
 	POINT_COLOR=BLUE;//设置字体为蓝色	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)	//KEY1按下,写入W25QXX
		{
			LCD_Fill(0,170,239,319,WHITE);//清除半屏    
 			LCD_ShowString(30,170,200,16,16,"Start Write W25Q128...."); 
			W25QXX_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);			//从倒数第100个地址处开始,写入SIZE长度的数据
			LCD_ShowString(30,170,200,16,16,"W25Q128 Write Finished!");	//提示传送完成
		}
		if(key==KEY0_PRES)	//KEY0按下,读取字符串并显示
		{
 			LCD_ShowString(30,170,200,16,16,"Start Read W25Q128.... ");
			W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);					//从倒数第100个地址处开始,读出SIZE个字节
			LCD_ShowString(30,170,200,16,16,"The Data Readed Is:  ");	//提示传送完成
			LCD_ShowString(30,190,200,16,16,datatemp);//显示读到的字符串
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED1=!LED1;//提示系统正在运行	
			i=0;
		}		   
	}


}

