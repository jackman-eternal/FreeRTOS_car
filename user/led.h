#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#define LED0 PAout(8)	// PA8
#define LED1 PAout(2)	// PD2	

void LED_INIT(int flag);
 

#endif
