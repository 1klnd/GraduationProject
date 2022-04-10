#include "bsp_esp8266_test.h"
#include "bsp_esp8266.h"
#include "./dwt_delay/core_delay.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "bsp_dht11.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include <string.h>

char* strrchr(const char* s, int i);

DHT11_Data_TypeDef DHT11_Data;

volatile uint8_t ucTcpClosedFlag = 0;


void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void)
{
  printf( "\r\n正在配置 ESP8266 ......\r\n" );
  printf( "\r\n使能 ESP8266 ......\r\n" );
	macESP8266_CH_ENABLE();
	//while( ! ESP8266_AT_Test() );
  
  printf( "\r\n正在配置工作模式 STA ......\r\n" );
	while( ! ESP8266_Net_Mode_Choose ( STA ) );

  printf( "\r\n正在连接 WiFi ......\r\n" );
  while( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );	
	
  printf( "\r\n禁止多连接 ......\r\n" );
	while( ! ESP8266_Enable_MultipleId ( DISABLE ) );
	
  printf( "\r\n正在连接 Server ......\r\n" );
	while( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
  printf( "\r\n进入透传发送模式 ......\r\n" );
	while( ! ESP8266_UnvarnishSend () );
	
	printf( "\r\n配置 ESP8266 完毕\r\n" );
  
}


void ESP8266_SendDHT11DataTest(void)
{
  char cStr [ 100 ] = { 0 };
  uint8_t ucStatus;
  
  if( 1 == read_dht11_finish )
    sprintf ( cStr, "\r\n\r\n读取DHT11成功!\r\n湿度为%d.%d ％RH ，温度为 %d.%d℃ \r\n", 
              DHT11_Data.humi_int, DHT11_Data.humi_deci, DHT11_Data.temp_int, DHT11_Data.temp_deci );
  else
		sprintf ( cStr, "Read DHT11 ERROR!\r\n" );
  
  printf ( "%s", cStr );                                             //打印读取 DHT11 温湿度信息

  ESP8266_SendString ( ENABLE, cStr, 0, Single_ID_0 );               //发送 DHT11 温湿度信息到网络调试助手
  
  
  if ( ucTcpClosedFlag )                                             //检测是否失去连接
  {
    ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
    
    do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
    while ( ! ucStatus );
    
    if ( ucStatus == 4 )                                             //确认失去连接后重连
    {
      printf ( "\r\n正在重连热点和服务器 ......\r\n" );
      
      while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
      while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
      printf ( "\r\n重连热点和服务器成功\r\n" );

    }
    
    while ( ! ESP8266_UnvarnishSend () );		
    
  }
}


void ESP8266_PostMeasuredValue(double temp, double humi) {
	
	char str[200] = {0};
	
	sprintf(str, 
		"POST /api/MeasuredValue?temperature=%lf&humidity=%lf HTTP/1.1\r\n"
		"Host: " macUser_ESP8266_TcpServer_IP ":" macUser_ESP8266_TcpServer_Port "\r\n"
		"accept: text/plain\r\n"
		"Content-Length: 0\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n\r\n", 
			temp, humi);
	
	ESP8266_SendString ( ENABLE, str, 0, Single_ID_0 );

	ESP8266_ReconnectWhenDisconnected();
	
}


void ESP8266_ReconnectWhenDisconnected(void){
	
	uint8_t ucStatus;
  
  if ( ucTcpClosedFlag )                                             //检测是否失去连接
  {
    ESP8266_ExitUnvarnishSend ();                                    //退出透传模式
    
    do ucStatus = ESP8266_Get_LinkStatus ();                         //获取连接状态
    while ( ! ucStatus );
    
    if ( ucStatus == 4 )                                             //确认失去连接后重连
    {
      printf ( "\r\n正在重连热点和服务器 ......\r\n" );
      
      while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );
      
      while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
      
      printf ( "\r\n重连热点和服务器成功\r\n" );

    }
    
    while ( ! ESP8266_UnvarnishSend () );		
    
  }
}


void ESP8266_GetSettingValue(double* temp, double* humi) {
	char* str;
	
	ESP8266_SendString ( ENABLE, 
		"GET /api/SettingValue HTTP/1.1\r\n"
		"Host: " macUser_ESP8266_TcpServer_IP ":" macUser_ESP8266_TcpServer_Port "\r\n"
		"accept: */*\r\n\r\n"
		, 0, Single_ID_0 );
	
	str = ESP8266_ReceiveString( ENABLE );	// str is the whole http response
	
	str = strrchr(str, '{');								//{"temperature":30,"humidity":50}

	//printf("%s\n",str);
	sscanf(str, "{\"temperature\":%lf,\"humidity\":%lf}", temp, humi);

	ESP8266_ReconnectWhenDisconnected();		
}

