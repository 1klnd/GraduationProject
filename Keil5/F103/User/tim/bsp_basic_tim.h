#ifndef __BSP_BASIC_TIM_H
#define __BSP_BASIC_TIM_H

#include "stm32f10x.h"

// ��ʱ��ʱ�� TIMxCLK = APB1 Ԥ��Ƶϵ��Ϊ 1 ? APB1 ʱ�� : APB1 ʱ�� * 2��һ��Ϊ 72M
// ��ʱ��Ԥ��Ƶ���� TIMxCLK ��Ƶ����ΧΪ 1-65535����Ƶ��ļ�����ʱ��Ϊ TIMxCLK / (PSC+1)
// �������ﵽ PERIOD ʱ�����ж�
#define BASIC_TIM_PERIOD							30000-1
#define BASIC_TIM_PRESCALER						7200-1
// PERIOD = 1000-1 , PRESCALER = 7200-1 ʱ��������ʱ��Ϊ 72M / 7200 = 10K��
// ����һ�ε�ʱ��Ϊ 1s / 10K = 0.1 ms = 100 us
// װ�ص� 1000-1 ���� 1000 ��ʱ�����жϣ�ʱ��Ϊ 100 ms

#define BASIC_TIM											TIM6
#define BASIC_TIM_APBxCLOCK_FUN				RCC_APB1PeriphClockCmd
#define BASIC_TIM_CLK									RCC_APB1Periph_TIM6
#define BASIC_TIM_IRQ									TIM6_IRQn
#define BASIC_TIM_IRQHANDLER					TIM6_IRQHandler

void Basic_TIM_Config(void);

#endif
