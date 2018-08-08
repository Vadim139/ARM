/*
 * RS485.h
 *
 *  Created on: 16 gru 2017
 *      Author: Vadim
 */

#include "main.h"
#include "Timer.h"

#ifndef RS485_H_
#define RS485_H_

#define RS_RCC      	RCC_APB1Periph_USART3
#define RC_USART        USART3
#define RC_USART_IRQ    USART3_IRQn
#define RS_GPIO_RCC  	RCC_APB2Periph_GPIOB
#define RS_GPIO      	GPIOB
#define RS_PIN_TX  		GPIO_Pin_10
#define RS_PIN_RX  		GPIO_Pin_11
#define RS_PIN_WR    	GPIO_Pin_1

void RS485_Init();
uint8_t RS_Transfer(uint8_t addr, uint8_t data);
uint8_t RS_TransferMulti(uint8_t addr, uint8_t com, uint8_t* data, uint8_t size);
uint8_t RS_Receive();
void MAX_EnableWrite();
void MAX_DisableWrite();


#endif /* RS485_H_ */
