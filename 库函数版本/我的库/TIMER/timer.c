#include "timer.h"
#include "LED.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 

//V1.1 20120904
//1,增加TIM3_PWM_Init函数。
//2,增加LED0_PWM_VAL宏定义，控制TIM3_CH2脉宽									  
//////////////////////////////////////////////////////////////////////////////////  
   	  
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	//定义结构体类型
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//外设1高速时钟使能-TIM
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	//设置时基，arr，psc，
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_Trigger,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		LED1=!LED1;
		}
}




//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	

}


//TIM_ICInitTypeDef 	TIM5_ICInitStruct;

void TIM5_Cap_Init(u16 arr,u16 psc)
{
	TIM_ICInitTypeDef 	TIM5_ICInitStruct;
	GPIO_InitTypeDef	 GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef	 TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef 	NVIC_InitStruct;
	// 注意宣告一定要放在函数头的位置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; //PA0 输入 
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//GPIO初始化
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 下拉
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // TDTS = Tck_tim
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period = arr;//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;////预分频器
	//TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);//定时器初始化
	
	TIM5_ICInitStruct.TIM_Channel = TIM_Channel_1; //选择输入端 IC1 映射到 TI1 上
	TIM5_ICInitStruct.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM5_ICInitStruct.TIM_ICPolarity =TIM_ICPolarity_Rising;//上升沿捕获
	TIM5_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//配置输入分频,不分频
	TIM5_ICInitStruct.TIM_ICSelection =TIM_ICSelection_DirectTI;//映射到 TI1 上
	TIM_ICInit(TIM5,&TIM5_ICInitStruct);//输入比较初始化
	
	NVIC_InitStruct.NVIC_IRQChannel	 =TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStruct);//中断初始化
	
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//TIM的更新中断设置
	TIM_Cmd(TIM5,ENABLE);//使能定时器
	


}

u8 TIM5CH1_CAPTURE_STA = 0 ;//输入捕获高电平时溢出次数初始化
u16 TIM5CH1_CAPTURE_VAL ;//输入捕获值
//TIM5的中断服务函数
void TIM5_IRQHandler(void)
{
	
	if((TIM5CH1_CAPTURE_STA&0X80)==0)  //未成功捕获
	{
		if(TIM_GetITStatus(TIM5,TIM_IT_Update!=RESET))	//未成功更新
		{
			if(TIM5CH1_CAPTURE_STA&0X40) //成功捕获高电平
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F) //高电平太长
				{
					TIM5CH1_CAPTURE_STA|= 0X80; //标记成功捕获
					TIM5CH1_CAPTURE_VAL = 0XFFFF;
					
				}
				else TIM5CH1_CAPTURE_STA++;
				
			}
		}
		if(TIM_GetITStatus(TIM5,TIM_IT_CC1)!=RESET) //捕获通道1发声捕获事件
		{
			if (TIM5CH1_CAPTURE_STA&0x40)//捕获到一个下降沿
			{
				TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获到一次上升沿
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);//定时器比较优先级设置为上升沿捕获
			}
			else //还没有开始第一次捕获，这是第一次捕获上升沿 
			{
				TIM5CH1_CAPTURE_STA=0; //请空
				TIM5CH1_CAPTURE_VAL=0;//请空
				TIM_SetCounter(TIM5,0); 
				TIM5CH1_CAPTURE_STA|=0X40; //标记捕获到了上升沿,也就是误差时一个时钟时间*64的时间
				TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);//设置为下降沿捕获
			}
		}
	}
	
	TIM_ClearITPendingBit(TIM5,TIM_IT_CC1|TIM_IT_Update);//清除中断标志位

}


