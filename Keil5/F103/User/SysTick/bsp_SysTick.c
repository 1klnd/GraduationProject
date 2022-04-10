#include "bsp_SysTick.h"

void SysTick_Init( void )
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if ( SysTick_Config(SystemCoreClock / 100) )	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}
  
  // 关闭滴答定时器  
	//SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	
  // 使能滴答定时器  10ms中断一次
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
  
}
