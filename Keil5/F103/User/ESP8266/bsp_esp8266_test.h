#ifndef  __ESP8266_TEST_H
#define	 __ESP8266_TEST_H

#include "stm32f10x.h"
//#define 		USE_HOTSPOT

#ifdef			USE_HOTSPOT

#define      macUser_ESP8266_ApSsid                       "rk4"                
#define      macUser_ESP8266_ApPwd                        "123245657898"      
#define      macUser_ESP8266_TcpServer_IP                 "192.168.255.45"   

#else

#define      macUser_ESP8266_ApSsid                       "JNWA"             
#define      macUser_ESP8266_ApPwd                        "qwert@12345"       
#define      macUser_ESP8266_TcpServer_IP                 "192.168.1.108"     

#endif

#define      macUser_ESP8266_TcpServer_Port               "13465"            

extern volatile uint8_t ucTcpClosedFlag;
extern int read_dht11_finish;

void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
//void ESP8266_SendDHT11DataTest(void);

void ESP8266_GetSettingValue(double* temp, double* humi);
void ESP8266_PostMeasuredValue(double temp, double humi);
void ESP8266_ReconnectWhenDisconnected(void);

#endif
