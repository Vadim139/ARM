/*
 * BT_HC.cpp
 *
 *  Created on: 30 paü 2017
 *      Author: Vadim
 */

#include "BT_HC.h"

extern Timer timer;

volatile char BT_HC::buffer[1000];
volatile int BT_HC::buf_count;

uint8_t BT_HC::Init_usart(bool com) {
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	USART_DeInit(BT_USART);

	/* Enable the USARTy */
	USART_Cmd(BT_USART, DISABLE);

	USART_ITConfig(BT_USART, USART_IT_RXNE, DISABLE);

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = BT_USART_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB2PeriphClockCmd(BT_GPIO_RCC, ENABLE);
	RCC_APB1PeriphClockCmd(BT_USART_RCC, ENABLE);

	/* Configure USARTy Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = BT_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(BT_RX_P, &GPIO_InitStructure);

	/* Configure USARTy Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = BT_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(BT_TX_P, &GPIO_InitStructure);
	/* Configure USARTz Tx as alternate function push-pull */


	if(com)
		USART_InitStructure.USART_BaudRate = BT_bautrate1; //230400 /*115200*/;
	else
		USART_InitStructure.USART_BaudRate = BT_bautrate2;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USARTy */
	USART_Init(BT_USART, &USART_InitStructure);

	/* Enable the USARTy */
	USART_Cmd(BT_USART, ENABLE);

	USART_ITConfig(BT_USART, USART_IT_RXNE, ENABLE);
	timer.set_TimeOut(200);
//	Timer::TimeOut = 200;
	while (USART_GetFlagStatus(BT_USART, USART_FLAG_TC) == RESET)
	{
		if(!timer.TO_flag)
		{
			 trace_puts("Error in ESP USART init!");
			 return 1;
		}
	}
//	Timer::TimeOut = 0;
	return 0;
}

	uint8_t BT_HC::Init_BT()
	{

//		BT_sendcom("AT\r\n");
//		timer.sleep(300);
//		if(!BT_find("OK\r\n"))
//			return 1;
//
//		BT_sendcom("AT+UART=115200,1,0\r\n");
//		timer.sleep(300);
//		if(!BT_find("OK\r\n"))
//			return 1;
//
//		BT_sendcom("AT+RESET\r\n");
//		timer.sleep(1000);
//		if(!BT_find("OK\r\n"))
//			return 1;
//
		BT_sendcom("AT\r\n");
		timer.sleep(300);
		if(!BT_find("OK\r\n"))
			return 1;

		BT_sendcom("AT+CMODE=1\r\n");
		timer.sleep(300);
		if(!BT_find("OK\r\n"))
			return 1;

		BT_sendcom("AT+ROLE=1\r\n");
		timer.sleep(300);
		if(!BT_find("OK\r\n"))
			return 1;

		BT_sendcom("AT+INQM=1,5,24\r\n");
		timer.sleep(300);
		if(!BT_find("OK\r\n"))
			return 1;

		BT_sendcom("AT+CLASS=0\r\n");
		timer.sleep(300);
		if(!BT_find("OK\r\n"))
			return 1;

		BT_sendcom("AT+INIT\r\n");
		timer.sleep(500);
		if(!BT_find("OK\r\n"))
			return 1;

		BT_sendcom("AT+INQ\r\n");
		timer.sleep(2000);
		if(!BT_find("OK\r\n"))
			return 1;
//
//		BT_sendcom("AT+RESET\r\n");
//		timer.sleep(1000);
//		if(!BT_find("OK\r\n"))
//			return 1;

		return 0;
	}


	BT_HC::BT_HC()
	{
		err = 0;
		State = false;
//
//		WIFI_TCP_Start_p = 0;//&WIFI_TCP_Start;
//		WIFI_TCP_Close_p = 0;//&WIFI_TCP_Close;
//		WIFI_HTTP_RQS_p = 0;//&WIFI_HTTP_RQS;
	}

	uint8_t BT_HC::Init()
	{
		err = 0;
		State = true;

		if(Init_usart(1))
			err = 1;


//		if(Init_BT())
//			err = 2;
//		timer.sleep(300);
//		BT_sendcom("AT+UART?\r\n");
//		timer.sleep(300);
//		USART_DeInit(BT_USART);
		USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = BT_bautrate2;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USARTy */
	USART_Init(BT_USART, &USART_InitStructure);
//		if(Init_usart(0))
//			err = 3;


		FlushBuf();
		State = false;
		return err;
	}


	uint8_t BT_HC::BT_sendcom(char* str)
	{

		FlushBuf();
		int len = 0;
		len = strlen(str);
		for(int i = 0;i<len;i++){
			USART_SendData(BT_USART, str[i]);
		    while(USART_GetFlagStatus(BT_USART, USART_FLAG_TC) == RESET)
		    {
		    }
		}
		return 0;
	}

	uint8_t BT_HC::BT_recdata(uint8_t *c)
	{
		buffer[buf_count++] = *c;
		return 0;
	}

	uint16_t BT_HC::BT_find(char* str)
	{
		int len = strlen(str);
		for(int i = 0; i<buf_count;)
		{
			for(int j = 0; j<len;)
			{
				if(buffer[i] == str[j])
				{
					if(i == buf_count)
						break;
					i++;
					j++;
					if(j == len)
						return i-len+1;
				}else{
					if(i == buf_count)
						break;
					i++;
					j = 0;
				}
			}

		}
		return 0;
	}

	uint8_t BT_HC::ShowBuf()
	{
		trace_puts((const char*)buffer);
//		BT_sendcom((char*)buffer);
		return 0;
	}

	uint8_t BT_HC::FlushBuf()
	{
		for(uint16_t i = 0;i<1000;i++)
			buffer[i] = 0;
		buf_count = 0;

		return 0;
	}
