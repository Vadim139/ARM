/*
 * BT_HC.h
 *
 *  Created on: 30 paü 2017
 *      Author: Vadim
 */

#ifndef BT_HC_H_
#define BT_HC_H_

#include "main.h"
#include "Timer.h"

#define BT_RX		GPIO_Pin_11
#define BT_RX_P		GPIOB
#define BT_TX		GPIO_Pin_10
#define BT_TX_P		GPIOB


#define BT_GPIO_RCC RCC_APB2Periph_GPIOB
#define BT_USART_RCC RCC_APB1Periph_USART3

#define BT_USART	USART3
#define BT_USART_IRQ USART3_IRQn

#define BT_bautrate1 38400
#define BT_bautrate2 115200


class BT_HC
{
private:

	static volatile char buffer[1000];
	static volatile int buf_count;

	uint8_t err;

	uint8_t Init_usart(bool com);
	uint8_t Init_BT();
//	uint8_t BT_sendcom(char* str);
//	uint16_t BT_find(char* str);
public:

	bool State; // 0 - data 1 - command

	BT_HC();
	uint8_t BT_sendcom(char* str);
	uint8_t BT_recdata(uint8_t *c);
	uint8_t Init();
	uint8_t ShowBuf();
	uint8_t FlushBuf();
	uint16_t BT_find(char* str);





};


#endif /* BT_HC_H_ */
