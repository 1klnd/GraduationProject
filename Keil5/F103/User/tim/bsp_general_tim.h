#ifndef __BSP_GENERAL_TIM_H
#define __BSP_GENERAL_TIM_H

#include "stm32f10x.h"

// 输出频率为 1kHZ 的PWM波，
// 参考基础定时器，定时器时钟为 72M / 72 = 1M
// ARR 为 1000，频率为 1K
#define TIM3_PERIOD				1000-1
#define TIM3_PRESCALER		72-1

void TIM3_PWM_Config(void);
//void TIM3_PWM_Init(uint16_t arr, uint16_t psc);

#endif
