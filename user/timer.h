#ifndef __TIMER_H
#define __TIMER_H

/*
TIM2 CH1--PA0 CH2--PA1  CH3--PA2  CH4--PA3  
     /REMAP->1--PA15  2--PB3  3--PB10  4--PB11
TIM3 CH1--PA6 CH2--PA7  CH3--PB0  CH4--PB1  
     /REMAP->1--PC6  2--PC7  3--PC8  4--PC9
TIM4 CH1--PB6 CH2--PB7  CH3--PB8  CH4--PB9  
     /REMAP->1--PD12  2--PD13  3--PD14   4--PD15
TIM5 CH1--PA0 CH2--PA1  CH3--PA2  CH4--PA3 
*/

#include "stm32f10x.h"
#include "delay.h"



void TIM2_ENCODER(void);
void TIM4_ENCODER(void);
void TIM3_INIT(void);
int16_t TIM2_Encode_Read(void);
int16_t TIM4_Encode_Read(void);

//int16_t encoder_getCounter(void);
//void TIM4_INIT(void);
//void TIM5_INIT(void);

#endif


//void TIM2_INIT(void);
/*
void TIM2_INIT(void)
{
	GPIO_InitTypeDef        GPIO_TIM2;
	TIM_TimeBaseInitTypeDef TIM2_TIMEBASE;
	TIM_OCInitTypeDef       TIM2_OCINIT;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	GPIO_TIM2.GPIO_Mode =GPIO_Mode_AF_PP;
    GPIO_TIM2.GPIO_Pin =GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 ;
	GPIO_TIM2.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA ,&GPIO_TIM2);

	TIM2_TIMEBASE.TIM_ClockDivision =0;
	TIM2_TIMEBASE.TIM_CounterMode =TIM_CounterMode_Up ;
	TIM2_TIMEBASE.TIM_Period = 1000-1;
	TIM2_TIMEBASE.TIM_Prescaler=72-1;
	TIM_TimeBaseInit(TIM2,&TIM2_TIMEBASE);

	TIM2_OCINIT.TIM_OCMode = TIM_OCMode_PWM1;
	TIM2_OCINIT.TIM_OCPolarity =TIM_OCPolarity_High ;
	
	TIM2_OCINIT.TIM_Pulse = 800;
	TIM_OC1PreloadConfig(TIM2 ,TIM_OCPreload_Enable);
    TIM2_OCINIT.TIM_OutputState =ENABLE ;
    TIM_OC1Init(TIM2,&TIM2_OCINIT);
	
    TIM2_OCINIT.TIM_Pulse =800 ;
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable );
    TIM2_OCINIT.TIM_OutputState =ENABLE ;
    TIM_OC2Init(TIM2,&TIM2_OCINIT);

	TIM2_OCINIT.TIM_Pulse =800;
	TIM2_OCINIT.TIM_OutputState =ENABLE ;
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	TIM_OC3Init(TIM2,& TIM2_OCINIT);

	TIM2_OCINIT.TIM_Pulse =800;
	TIM2_OCINIT.TIM_OutputState=ENABLE ;
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); 
	TIM_OC4Init(TIM2,& TIM2_OCINIT);
   
    TIM_Cmd(TIM2 ,ENABLE );        
}
*/


//int Read_Encoder(u8 TIMX);
/*函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
*/
/*
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	     case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
 */
 
