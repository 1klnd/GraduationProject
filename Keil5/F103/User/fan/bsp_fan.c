#include "bsp_fan.h"

void Fan_GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(FAN_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = FAN_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(FAN_GPIO_PORT, &GPIO_InitStructure);
	
	Fan_Stop();
}

void Fan_Start(void) {
	GPIO_ResetBits(FAN_GPIO_PORT, FAN_GPIO_PIN);
}

void Fan_Stop(void) {
	GPIO_SetBits(FAN_GPIO_PORT, FAN_GPIO_PIN);
}

