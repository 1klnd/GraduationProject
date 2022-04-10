#ifndef __BSP_FAN_H
#define __BSP_FAN_H

#include "stm32f10x.h"

#define FAN_GPIO_PORT		GPIOB
#define FAN_GPIO_CLK		RCC_APB2Periph_GPIOB
#define FAN_GPIO_PIN		GPIO_Pin_7


void Fan_GPIO_Config(void);
void Fan_Start(void);
void Fan_Stop(void);


#endif
