/*
 * RS485.cpp
 *
 *  Created on: 16 gru 2017
 *      Author: Vadim
 */

#include "RS485.h"

extern Timer timer;

void RS485_Init() {
	USART_InitTypeDef USART_InitStructure;

	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RC_USART_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB2PeriphClockCmd(RS_GPIO_RCC, ENABLE);

	RCC_APB1PeriphClockCmd(RS_RCC, ENABLE);
	//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USARTy Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = RS_PIN_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(RS_GPIO, &GPIO_InitStructure);

	/* Configure USARTy Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = RS_PIN_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(RS_GPIO, &GPIO_InitStructure);
	/* Configure USARTz Tx as alternate function push-pull */

	/* Configure Max RW as output*/
	GPIO_InitStructure.GPIO_Pin = RS_PIN_WR;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(RS_GPIO, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200; //230400 /*115200*/;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USARTy */
	USART_Init(RC_USART, &USART_InitStructure);

	/* Enable the USARTy */
	USART_Cmd(RC_USART, ENABLE);

	USART_ITConfig(RC_USART, USART_IT_RXNE, ENABLE);

	while (USART_GetFlagStatus(RC_USART, USART_FLAG_TC) == RESET) {
	}

}

uint8_t RS_Transfer(uint8_t addr, uint8_t data)
{
	MAX_EnableWrite();
	delay_ms(20);

	USART_SendData(RC_USART,addr);
	while(USART_GetFlagStatus(RC_USART, USART_FLAG_TC) == RESET);

	USART_SendData(RC_USART,data);
	while(USART_GetFlagStatus(RC_USART, USART_FLAG_TC) == RESET);

	USART_SendData(RC_USART,addr);
	while(USART_GetFlagStatus(RC_USART, USART_FLAG_TC) == RESET);

	MAX_DisableWrite();
	delay_ms(20);
	return 0;

}

uint8_t RS_TransferMulti(uint8_t addr, uint8_t com, uint8_t* data, uint8_t size)
{
	MAX_EnableWrite();
	delay_ms(20);
	USART_SendData(RC_USART,addr);
	while(USART_GetFlagStatus(RC_USART, USART_FLAG_TC) == RESET);

	USART_SendData(RC_USART,com);
	while(USART_GetFlagStatus(RC_USART, USART_FLAG_TC) == RESET);

	for(int i = 0; i < size; i++){
		USART_SendData(RC_USART,data[i]);
		while(USART_GetFlagStatus(RC_USART, USART_FLAG_TC) == RESET);
	}

	USART_SendData(RC_USART,addr);
	while(USART_GetFlagStatus(RC_USART, USART_FLAG_TC) == RESET);

	MAX_DisableWrite();
	delay_ms(20);
	return 0;

}

uint8_t RS_Receive()
{
	uint8_t rec = USART_ReceiveData(USART3);
//	while(USART_GetFlagStatus(RC_USART, USART_FLAG_) == RESET);
//	delay_ms(20);

	return rec;

}

void MAX_EnableWrite()
{
    // Set slave SS pin low
	RS_GPIO->BSRR = RS_PIN_WR;
}

void MAX_DisableWrite()
{
    // Set slave SS pin high
	RS_GPIO->BRR = RS_PIN_WR;
}


