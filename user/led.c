#include "led.h"
//PC 13
void LED_INIT(int flag)
{
	GPIO_InitTypeDef GPIO_LED;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC ,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE ); 
	GPIO_LED.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_LED.GPIO_Pin  = GPIO_Pin_13 ;
	GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC ,&GPIO_LED);
	GPIO_LED.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_LED.GPIO_Pin  = GPIO_Pin_8 |GPIO_Pin_2 ;
    GPIO_LED.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_LED );   	
	if(flag == 1)
	{
		GPIO_ResetBits(GPIOC ,GPIO_Pin_13 ); 
	}
	else if(flag == 0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13 ); 
	}
}

