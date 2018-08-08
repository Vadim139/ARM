/*
 * SIM800L.h
 *
 *  Created on: 30 paü 2017
 *      Author: Vadim
 */

#ifndef SIM800L_H_
#define SIM800L_H_

#include "main.h"
#include "Timer.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"

#define SIM_RX		GPIO_Pin_3
#define SIM_RX_P	GPIOA
#define SIM_TX		GPIO_Pin_2
#define SIM_TX_P	GPIOA
#define SIM_RST		GPIO_Pin_1
#define SIM_RST_P	GPIOA

#define SIM_GPIO_RCC RCC_APB2Periph_GPIOA
#define SIM_USART_RCC RCC_APB1Periph_USART2

#define SIM_USART	USART2
#define SIM_USART_IRQ USART2_IRQn

#define SIM_bautrate 115200

class SIM800L
{
private:

	static volatile char buffer[1000];
	static volatile int buf_count;

	uint8_t err;

	uint8_t Init_usart();
	uint8_t Init_SIM();
	uint8_t SIM_sendcom(char* str);
	uint16_t SIM_find(char* str);
public:
	char Operator[8];
	char IP_TCP[16];
	char IP_HTTP[16];

	bool State; // 0 - data 1 - command

	SIM800L();
	uint8_t SIM_recdata(uint8_t *c);
	uint8_t Init();
	uint8_t Get_operator();
	uint8_t GSM_Connect(int Operator);
	uint8_t GSM_Connect(int Operator, char* User ,char* Pass);
	uint8_t GSM_GetConfig();
	uint8_t GSM_SendSMS(char* number, char* str);
	uint8_t GSM_Call(char* number);
	uint8_t GSM_Cancel_call();
	uint8_t GSM_TCP_Start(char* IP, char* Port);
	uint8_t GSM_TCP_Send(char* str);
	uint8_t GSM_TMode_On();
	uint8_t GSM_TMode_Off();
	uint8_t GSM_TCP_Close(uint8_t f = 1);
	uint8_t GSM_Get_DataTime(char* DataTime);
	volatile char*   GSM_HTTP_RQS(char* IP, char* Request, uint8_t dir);
	uint8_t ShowBuf();
	uint8_t FlushBuf();





};


#endif /* SIM800L_H_ */
