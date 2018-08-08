/*
 * ESP8266.h
 *
 *  Created on: 30 paü 2017
 *      Author: Vadim
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "main.h"
#include "Timer.h"

#define ESP_RX		GPIO_Pin_10
#define ESP_RX_P	GPIOA
#define ESP_TX		GPIO_Pin_9
#define ESP_TX_P	GPIOA
#define ESP_RS   	GPIO_Pin_11
#define ESP_RS_P	GPIOA

#define ESP_GPIO_RCC RCC_APB2Periph_GPIOA
#define ESP_USART_RCC RCC_APB2Periph_USART1

#define ESP_USART	USART1
#define ESP_USART_IRQ USART1_IRQn

#define ESP_bautrate 115200


class ESP8266
{
private:

	static volatile char buffer[1000];
	static volatile int buf_count;

	uint8_t err;

	uint8_t Init_usart();
	uint8_t Init_ESP();
	uint8_t ESP_sendcom(char* str);
	uint16_t ESP_find(char* str);
public:
	char Name[21];
	char IP[16];
	char MAC[18];

	bool State; // 0 - data 1 - command

	ESP8266();
	uint8_t ESP_recdata(uint8_t *c);
	uint8_t Init();
	uint8_t WIFI_Connect(char* SSID, char* Pass);
	uint8_t WIFI_Disconnect();
	uint8_t WIFI_GetConfig();
	uint8_t WIFI_TCP_Start(char* IP, char* Port);
	uint8_t WIFI_TCP_Start(char* IP, char* Port, char* ka);
	uint8_t WIFI_TCP_Send(char* str, uint8_t f = 0);
	uint8_t WIFI_TMode_On();
	uint8_t WIFI_TMode_Off();
	uint8_t WIFI_TCP_Close(uint8_t f = 1);
	uint8_t WIFI_Get_DataTime(char* DataTime);
	volatile char*	WIFI_HTTP_RQS(char* IP, char* Request, uint8_t dir);
	uint8_t ShowBuf();
	uint8_t FlushBuf();





};


#endif /* ESP8266_H_ */
