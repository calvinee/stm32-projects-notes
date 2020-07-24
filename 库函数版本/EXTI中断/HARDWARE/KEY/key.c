#include "key.h"
#include "sys.h"
#include "delay.h"
#include "stm32f10x.h"

//初始化按键函数
//初始化IO
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE); //开启时钟使能端
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_2|GPIO_Pin_3;			    //LED0-->PB.5 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	 //上拉模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz
    GPIO_Init(GPIOE, &GPIO_InitStructure);		//初始化GPIOB.5
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	   //初始化  WK_UP-->GPIOA.0  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	 //PA0 设置成输入，下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);		//初始化GPIOE.5
}
//按键处理函数 
//返回按键值 
//mode:0,不支持连续按;1,支持连续按; 
//0，没有任何按键按下;1，KEY0 按下;2，KEY1 按下;3，KEY2 按下  ;4，KEY3 按下  WK_UP 
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!! 

//支持连续按键和不连续按键
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1;//松开标准 宣告一个key_up
	if(mode)key_up=1;//条件语句，不连续按键
	if(key_up&(KEY0==0|KEY1==0|KEY2==0|WK_UP==1))
	{
		delay_ms(10);//è￥???ˉ 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)return WKUP_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	   
	return 0;//无按键按下
}
