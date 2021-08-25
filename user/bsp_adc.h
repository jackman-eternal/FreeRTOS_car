#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_adc.h"

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADCx                          ADC1
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA

// PA2-ͨ��2 ����IO
#define    ADC_PIN                       GPIO_Pin_2
#define    ADC_CHANNEL                   ADC_Channel_2
#define    ADC_DMA_CHANNEL               DMA1_Channel1

void ADCx_Init(void);
static void ADCx_GPIO_Config(void);
static void ADCx_Mode_Config(void);

#endif /* __ADC_H */

