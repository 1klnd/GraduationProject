#ifndef __BSP_GENERAL_TIM_H
#define __BSP_GENERAL_TIM_H

#include "stm32f10x.h"

// ���Ƶ��Ϊ 1kHZ ��PWM����
// �ο�������ʱ������ʱ��ʱ��Ϊ 72M / 72 = 1M
// ARR Ϊ 1000��Ƶ��Ϊ 1K
#define TIM3_PERIOD				1000-1
#define TIM3_PRESCALER		72-1

void TIM3_PWM_Config(void);
//void TIM3_PWM_Init(uint16_t arr, uint16_t psc);

#endif
