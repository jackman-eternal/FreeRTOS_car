#include "timer.h"

/*
TIM2 CH1--PA0 CH2--PA1  CH3--PA2  CH4--PA3  
     /REMAP->1--PA15  2--PB3  3--PB10  4--PB11
TIM3 CH1--PA6 CH2--PA7  CH3--PB0  CH4--PB1  
     /REMAP->1--PC6  2--PC7  3--PC8  4--PC9
TIM4 CH1--PB6 CH2--PB7  CH3--PB8  CH4--PB9  
     /REMAP->1--PD12  2--PD13  3--PD14   4--PD15
TIM5 CH1--PA0 CH2--PA1  CH3--PA2  CH4--PA3 
*/

// TIM2 CH1--PA0 CH2--PA1  CH3--PA2  CH4--PA3  


void TIM2_ENCODER(void)
{
	TIM_TimeBaseInitTypeDef TIM2_TIMEBASE;
	TIM_ICInitTypeDef  TIM2_ICINIT;
	GPIO_InitTypeDef TIM2_GPIO;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE );
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE );

	TIM2_GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	TIM2_GPIO.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 ;
	GPIO_Init(GPIOA ,&TIM2_GPIO);
	
    TIM2_TIMEBASE.TIM_Prescaler =0;
	TIM2_TIMEBASE.TIM_Period =0xffff;
	TIM2_TIMEBASE.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM2_TIMEBASE.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM2,&TIM2_TIMEBASE);
    
    TIM_EncoderInterfaceConfig(TIM2 ,TIM_EncoderMode_TI12 ,TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);
	//TIM_ICStructInit(&TIM2_ICINIT); 
    TIM2_ICINIT.TIM_Channel = TIM_Channel_1 |TIM_Channel_2 ;	
    TIM2_ICINIT.TIM_ICFilter = 0X06;
    TIM2_ICINIT.TIM_ICPolarity = TIM_ICPolarity_Rising ;
	TIM2_ICINIT.TIM_ICPrescaler = TIM_ICPSC_DIV1 ;
    TIM2_ICINIT.TIM_ICSelection = TIM_ICSelection_DirectTI ;
   	TIM_ICInit(TIM2 ,&TIM2_ICINIT);
	TIM_SetCounter(TIM2,0); 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2,ENABLE ); 
	
}

void TIM4_ENCODER(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PB端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // 预分频器 
  TIM_TimeBaseStructure.TIM_Period = 0xffff; //设定计数器自动重装值
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
  
  TIM_ICStructInit(&TIM_ICInitStructure);
  
  TIM_ICInitStructure.TIM_ICFilter = 0x06;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM4,0);
  TIM_Cmd(TIM4, ENABLE); 


}
//TIM3 CH1--PA6 CH2--PA7  CH3--PB0  CH4--PB1 
void TIM3_INIT(void)
{
	GPIO_InitTypeDef        GPIO_TIM3;
	TIM_TimeBaseInitTypeDef TIM3_TIMEBASE;
	TIM_OCInitTypeDef       TIM3_OCINIT;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    GPIO_TIM3.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_TIM3.GPIO_Pin =GPIO_Pin_6 |GPIO_Pin_7 ;
	GPIO_TIM3.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA ,&GPIO_TIM3);
    GPIO_TIM3.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_TIM3.GPIO_Pin =GPIO_Pin_0 |GPIO_Pin_1 ;
    GPIO_Init(GPIOB,&GPIO_TIM3);	
	
	TIM3_TIMEBASE.TIM_ClockDivision =0;
	TIM3_TIMEBASE.TIM_CounterMode =TIM_CounterMode_Up ;
	TIM3_TIMEBASE.TIM_Period = 2500-1;
	TIM3_TIMEBASE.TIM_Prescaler=72-1;
	TIM_TimeBaseInit(TIM3,&TIM3_TIMEBASE);
	
	TIM3_OCINIT.TIM_OCMode = TIM_OCMode_PWM1;
	TIM3_OCINIT.TIM_OCPolarity =TIM_OCPolarity_High ;
	
	TIM3_OCINIT.TIM_Pulse = 1250;
	TIM_OC1PreloadConfig(TIM3 ,TIM_OCPreload_Enable);
    TIM3_OCINIT.TIM_OutputState =ENABLE ;
    TIM_OC1Init(TIM3,&TIM3_OCINIT);
	
    TIM3_OCINIT.TIM_Pulse =800 ;
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable );
    TIM3_OCINIT.TIM_OutputState =ENABLE ;
    TIM_OC2Init(TIM3,&TIM3_OCINIT);

	TIM3_OCINIT.TIM_Pulse =800;
	TIM3_OCINIT.TIM_OutputState =ENABLE ;
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3Init(TIM3,& TIM3_OCINIT);

	TIM3_OCINIT.TIM_Pulse =800;
	TIM3_OCINIT.TIM_OutputState=ENABLE ;
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable); 
	TIM_OC4Init(TIM3,& TIM3_OCINIT);
   
    TIM_Cmd(TIM3 ,ENABLE );   
}


//void TIM4_INIT(void);
//void TIM5_INIT(void);

/*int16_t encoder_getCounter(void)
{
  TIM_SetCounter(TIM2,0);
  delay_ms(10);
  return (int16_t)TIM_GetCounter(TIM2);   //这里利用了原码补码的特性可以输出正负
  //printf("counter:%d\n",(int16_t)TIM_GetCounter(TIM2));
}
*/

int16_t  TIM2_Encode_Read(void)
{
    TIM_SetCounter(TIM2,0);
	delay_ms(10); 
	return (int16_t)TIM_GetCounter(TIM2);
}

int16_t TIM4_Encode_Read(void)
{
	 TIM_SetCounter(TIM4,0);
	delay_ms(10); 
	return (int16_t)TIM_GetCounter(TIM4);
}
void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001)//溢出中断
	{
	}
    TIM2->SR&=~(1<<0);//清除中断标志位
} 

void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001)//溢出中断
	{
	}
    TIM4->SR&=~(1<<0);//清除中断标志位
} 


