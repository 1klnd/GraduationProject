#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "bsp_esp8266.h"
#include "bsp_esp8266_test.h"
#include "bsp_dht11.h"
#include "bsp_led.h"  
#include "./dwt_delay/core_delay.h"
#include "bsp_general_tim.h"
#include "bsp_basic_tim.h"
#include "bsp_fan.h"
#include "bsp_pid.h"

#define HUMI_DIFF				5				// 当前湿度低于设定湿度 (HUMI_DIFF)% 时，开始加湿

extern DHT11_Data_TypeDef DHT11_Data;

_pid* pid;
double humiSV;
// 驱动板输出为 12v
// U/12 = P/1000
uint16_t UkToPulse(double Uk){
	
	return Uk  * (TIM3_PERIOD + 1) / 12.0 - 1;
}

int main ( void )
{
	double temp, humi;
	
	/* 初始化 */
  USART_Config ();                                             //初始化串口1
  CPU_TS_TmrInit();                                            //初始化DWT计数器，用于延时函数
  LED_GPIO_Config();                                           //初始化RGB彩灯
	ESP8266_Init();                                              //初始化WiFi模块使用的接口和外设
	DHT11_Init ();                                               //初始化DHT11
	Fan_GPIO_Config();	
	PID_Init();
	//Fan_Start();
	
  ESP8266_StaTcpClient_Unvarnish_ConfigTest();                          // 初始化ESP8266
  ESP8266_GetSettingValue(&temp, &humi);
	printf("SettingValue: temp:%lf, humi:%lf\n", temp, humi);
	pid->Sv = temp;
	TIM3_PWM_Config();
	Basic_TIM_Config();

  while ( 1 )
  {
    if( read_dht11_finish == 1) // read_dht11_finish == 1 or read_dht11_finish == -1
    {
			// 温度控制		
			pid->Mv = DHT11_Data.temp_int + DHT11_Data.temp_deci / 10.0;
			PID_Calc();
			printf("\t%d\n",UkToPulse(pid->Uk));
			TIM_SetCompare1(TIM3, UkToPulse(pid->Uk));
			
			// 湿度控制
			if( DHT11_Data.humi_int + DHT11_Data.humi_deci / 10.0 < humiSV - HUMI_DIFF)
			TIM_SetCompare3(TIM3, UkToPulse(5)); // 输出 5V
			if( DHT11_Data.humi_int + DHT11_Data.humi_deci / 10.0 > humiSV)
			TIM_SetCompare3(TIM3, 0);						// 输出 0
			
			// 发送测量值，获取新设定值
			ESP8266_PostMeasuredValue(pid->Mv, 0.1);
			Delay_ms(500);
			ESP8266_GetSettingValue(&pid->Sv, &humiSV);
			if(temp != pid->Sv || humi != humiSV){
				printf("SettingValue Changed: temp:%lf humi:%lf\n", pid->Sv, humiSV);
				temp = pid->Sv;
				humi = humiSV;
			}	
      read_dht11_finish = 0;       // 清零标志位
    }
  }
}
