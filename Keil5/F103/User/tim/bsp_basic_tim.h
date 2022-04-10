#ifndef __BSP_BASIC_TIM_H
#define __BSP_BASIC_TIM_H

#include "stm32f10x.h"

// 定时器时钟 TIMxCLK = APB1 预分频系数为 1 ? APB1 时钟 : APB1 时钟 * 2，一般为 72M
// 计时器预分频器对 TIMxCLK 分频，范围为 1-65535，分频后的计数器时钟为 TIMxCLK / (PSC+1)
// 计数器达到 PERIOD 时产生中断
#define BASIC_TIM_PERIOD							30000-1
#define BASIC_TIM_PRESCALER						7200-1
// PERIOD = 1000-1 , PRESCALER = 7200-1 时，计数器时钟为 72M / 7200 = 10K，
// 计数一次的时间为 1s / 10K = 0.1 ms = 100 us
// 装载到 1000-1 即计 1000 次时产生中断，时间为 100 ms

#define BASIC_TIM											TIM6
#define BASIC_TIM_APBxCLOCK_FUN				RCC_APB1PeriphClockCmd
#define BASIC_TIM_CLK									RCC_APB1Periph_TIM6
#define BASIC_TIM_IRQ									TIM6_IRQn
#define BASIC_TIM_IRQHANDLER					TIM6_IRQHandler

void Basic_TIM_Config(void);

#endif
