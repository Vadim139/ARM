/*
 * ESP8266.cpp
 *
 *  Created on: 30 paü 2017
 *      Author: Vadim
 */

#include "ESP8266.h"

extern Timer timer;
/*
uint8_t (*WIFI_TCP_Start_p)(char* IP, char* Port);
uint8_t (*WIFI_TCP_Close_p)(uint8_t f);
volatile char* (*WIFI_HTTP_RQS_p)(char* IP, char* Request, uint8_t dir);

char* char_arg[5];
uint8_t int_arg[5];
uint16_t times[10];

char* char_arg2[5];
uint8_t int_arg2[5];
uint16_t times2[10];
*/
volatile char ESP8266::buffer[1000];
volatile int ESP8266::buf_count;

uint8_t ESP8266::Init_usart() {
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ESP_USART_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* Configure USARTy Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = ESP_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(ESP_RX_P, &GPIO_InitStructure);

	/* Configure USARTy Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = ESP_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(ESP_TX_P, &GPIO_InitStructure);
	/* Configure USARTz Tx as alternate function push-pull */

	USART_InitStructure.USART_BaudRate = ESP_bautrate; //230400 /*115200*/;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USARTy */
	USART_Init(ESP_USART, &USART_InitStructure);

	/* Enable the USARTy */
	USART_Cmd(ESP_USART, ENABLE);

	USART_ITConfig(ESP_USART, USART_IT_RXNE, ENABLE);
	timer.set_TimeOut(200);
//	Timer::TimeOut = 200;
	while (USART_GetFlagStatus(ESP_USART, USART_FLAG_TC) == RESET)
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

	uint8_t ESP8266::Init_ESP()
	{
		ESP_sendcom("AT\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			return 1;

		ESP_sendcom("AT+RST\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			return 1;
		if(!ESP_find("ready\r"))
			return 1;

		ESP_sendcom("AT+CWAUTOCONN=0\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			return 1;

		return 0;
	}


	ESP8266::ESP8266()
	{
		err = 0;
		State = false;
//
//		WIFI_TCP_Start_p = 0;//&WIFI_TCP_Start;
//		WIFI_TCP_Close_p = 0;//&WIFI_TCP_Close;
//		WIFI_HTTP_RQS_p = 0;//&WIFI_HTTP_RQS;
	}

	uint8_t ESP8266::Init()
	{
		err = 0;
		State = true;

		for(int i = 0; i<21; i++)
			Name[i] = 0;

		for(int i = 0; i<16; i++)
			IP[i] = 0;

		for(int i = 0; i<18; i++)
			MAC[i] = 0;

		if(Init_usart())
			err = 1;
		if(Init_ESP())
			err = 2;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_Connect(char* SSID, char* Pass)
	{
		err = 0;
		State = true;

		ESP_sendcom("AT+CWMODE=1\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
		{
			State = false;
			return 1;
		}

		ESP_sendcom("AT+CWJAP=\"");
		ESP_sendcom(SSID);
		ESP_sendcom("\",\"");
		ESP_sendcom(Pass);
		ESP_sendcom("\"\r\n");
		while(buffer[0] == 0);
		for(int i = 0;i<15;i++){
		timer.sleep(500);
		if(ESP_find("OK\r\n")){
			FlushBuf();
			State = false;
			return err;
		}
		}
		err = 1;
		FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_Disconnect()
	{
		err = 0;
		State = true;

		ESP_sendcom("AT+CWQAP\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			err = 1;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_GetConfig()
	{
		uint16_t poz = 0;
		int i = 0;

		err = 0;
		State = true;

		i = 0;
		ESP_sendcom("AT+CIPSTA?\r\n");
		timer.sleep(300);
		poz = ESP_find("+CIPSTA:");
		if(!poz)
			err = 1;
		poz += 11;
		while(buffer[poz+i] != '\"')
		{
			IP[i] = buffer[poz+i];
			i++;
		}

		i = 0;
		ESP_sendcom("AT+CIPSTAMAC?\r\n");
		timer.sleep(300);
		poz = ESP_find("+CIPSTAMAC:");
		if(!poz)
			err = 1;
		poz += 11;
		while(buffer[poz+i] != '\"')
		{
			MAC[i] = buffer[poz+i];
			i++;
		}

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_TCP_Start(char* IP, char* Port)
	{

		err = 0;
		State = true;

		ESP_sendcom("AT+CIPMUX=0\r\n");
		timer.sleep(300);
//		if(!ESP_find("OK\r\n"))
//			err = 1;


		ESP_sendcom("AT+CIPMODE=0\r\n");

		timer.sleep(300);

		ESP_find("OK\r\n");
		if(!ESP_find("OK\r\n"))
			err = 1;

		ESP_sendcom("AT+CIPSTART=\"TCP\",\"");
		ESP_sendcom(IP);
		ESP_sendcom("\",");
		ESP_sendcom(Port);
		ESP_sendcom("\r\n");

		timer.sleep(400);
		if(!ESP_find("OK\r\n"))
			if(ESP_find("ALREADY"))
				err = 2;
			else
				err = 1;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_TCP_Start(char* IP, char* Port, char* ka)
	{
		err = 0;
		State = true;

		ESP_sendcom("AT+CIPMUX=0\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			err = 1;

		ESP_sendcom("AT+CIPMODE=0\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			err = 1;

		ESP_sendcom("AT+CIPSTART=\"TCP\",\"");
		ESP_sendcom(IP);
		ESP_sendcom("\",");
		ESP_sendcom(Port);
		ESP_sendcom(",");
		ESP_sendcom(ka);
		ESP_sendcom("\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			if(ESP_find("ALREADY"))
				err = 2;
			else
				err = 1;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_TCP_Send(char* str, uint8_t f)
	{
		err = 0;
		State = true;

		uint16_t len = strlen(str);
		char len_s[5] = {0,0,0,0,0};

		sprintf(len_s, "%u", len);

		ESP_sendcom("AT+CIPSEND=");
		ESP_sendcom(len_s);
		ESP_sendcom("\r\n");
		timer.sleep(300);
		if(!ESP_find(">"))
			err = 1;
		ESP_sendcom(str);
		ESP_sendcom("\r\n");
		timer.sleep(1000);
		if(!ESP_find("OK\r\n"))
			err = 1;

		if(f)
			FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_TMode_On()
	{
		err = 0;
		State = true;

		ESP_sendcom("AT+CIPMODE=1\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			err = 1;

		ESP_sendcom("ATO\r\n");
		timer.sleep(300);
		if(!ESP_find("CONNECT\r\n"))
			err = 1;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_TMode_Off()
	{
		err = 0;
		State = true;

		timer.sleep(500);
		ESP_sendcom("+++");
		timer.sleep(500);
		if(!ESP_find("OK\r\n"))
			err = 1;

		ESP_sendcom("AT+CIPMODE=0\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			err = 1;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t ESP8266::WIFI_TCP_Close(uint8_t f)
	{

		err = 0;
		State = true;

		ESP_sendcom("AT+CIPCLOSE\r\n");
		timer.sleep(300);
		if(!ESP_find("OK\r\n"))
			err = 1;

		if(f)
			FlushBuf();
		State = false;
		return err;
	}

//volatile int8_t err3;

	uint8_t ESP8266::WIFI_Get_DataTime(char* DataTime)// DataTime min 25 char
	{
		err = 0;
		State = true;

		uint16_t poz = 0;
		int i = 0;
/*
	if ((err = WIFI_TCP_Start("google.com", "80")))// time.jsontest.com
		trace_printf("TCP connection failed!! Error code: %u\n", err);
	else {

		WIFI_TCP_Send("HEAD / HTTP/1.1\r\n\r\n");//
		*/
		if((err = WIFI_TCP_Start("dyskbol.000webhostapp.com","80")))
		    trace_printf("TCP connection failed!! Error code: %u\n", err);
	    else
	    	trace_printf("TCP connected!\n");

		if((err = WIFI_TCP_Send("GET /get.php?RQS=2&SRQS=1 HTTP/1.1\r\nHost: dyskbol.000webhostapp.com\r\n\r\n")))
			trace_printf("TCP send failed!! Error code: %u\n", err);
		else
		   	trace_printf("Send successful!\n");
		//timer.sleep(1000);
		//ESP.ShowBuf();
		//ESP.WIFI_TCP_Close();
		timer.sleep(300);
		poz = ESP_find("Data i czas: ");
		if(!poz)
			err = 1;
		else{
		poz += 12;
		while(buffer[poz+i] != '\r')
		{
			DataTime[i] = buffer[poz+i];
			i++;
		}
		if ((err = WIFI_TCP_Close()))
				trace_printf("TCP closing failed!! Error code: %u\n", err);
		}


	FlushBuf();
	State = false;
	return err;
	}


	volatile char* ESP8266::WIFI_HTTP_RQS(char* IP, char* Request, uint8_t dir)
	{
		// IP: dyskbol.000webhostapp.com
		// Request: ?text=\"test\"&num=123
		err = 0;
		State = true;

		uint16_t poz = 0;
		int i = 0;

		uint16_t len = strlen(Request);
		len += strlen(IP);
		if(dir == 0)
			len += 35;
		else
			len += 33;


		char len_s[5] = {0,0,0,0,0};

		sprintf(len_s, "%u", len);

//		if((WIFI_TCP_Start(IP,"80") == 1)){ //
//			WIFI_TCP_Close();
//			timer.sleep(250);
//			trace_printf("TCP connection failed!! Error code: %u\n", err);
//			if((WIFI_TCP_Start(IP,"80") == 1)){ //
//				WIFI_TCP_Close();
//				timer.sleep(250);
//				trace_printf("TCP connection failed!! Error code: %u\n", err);
//				if((WIFI_TCP_Start(IP,"80") == 1)) //
//				    trace_printf("TCP connection failed!! Error code: %u\n", err);
//			    else{
//			    	trace_printf("TCP connected!\n");
//			    }
//			}else{
//		    	trace_printf("TCP connected!\n");
//		    }
//		}else
//	    	trace_printf("TCP connected!\n");

//		if((err = WIFI_TCP_Start(IP,"80"))){ //
//			WIFI_TCP_Close();
//			timer.sleep(250);
//			trace_printf("TCP connection failed!! Error code: %u\n", err);
////			return buffer;
//		}else
//	    	trace_printf("TCP connected!\n");
		FlushBuf();
		if((err = WIFI_TCP_Start(IP,"80"))){ //
			WIFI_TCP_Close();
			timer.sleep(400);
			trace_printf("TCP connection failed!! Error code: %u\n", err);
			if((err = WIFI_TCP_Start(IP,"80"))){ //
				WIFI_TCP_Close();
				timer.sleep(400);
				trace_printf("TCP connection failed!! Error code: %u\n", err);
				if((err = WIFI_TCP_Start(IP,"80"))) //
				    trace_printf("TCP connection failed!! Error code: %u\n", err);
			    else{
			    	trace_printf("TCP connected!\n");
			    }
			}else{
		    	trace_printf("TCP connected!\n");
		    }
		}else
	    	trace_printf("TCP connected!\n");

		if(!err){
		ESP_sendcom("AT+CIPSEND=");
		ESP_sendcom(len_s);
		ESP_sendcom("\r\n");
		timer.sleep(300);
		if(!ESP_find(">"))
			err = 1;
		ESP_sendcom("GET ");
		if(dir == 0)
			ESP_sendcom("/store.php");
		else
			ESP_sendcom("/get.php");
		ESP_sendcom(Request);
		ESP_sendcom(" HTTP/1.1\r\nHost: ");
		ESP_sendcom(IP);
		ESP_sendcom("\r\n\r\n");
		for(int i = 0;i<20;i++){
		timer.sleep(200);
		if(ESP_find("OK\r\n")){
//			FlushBuf();
			break;
		}
		}
//		timer.sleep(2000);
//		if(!err)
//			err = 1;
//		else
//			err = 0;
		timer.sleep(500);
//		ShowBuf();

//		if(!ESP_find("OK\r\n"))
//			err = 1;
		}
//		if((err = WIFI_TCP_Send(Request)))//("GET /store.php?text=\"test\"&num=123 HTTP/1.1\r\nHost: dyskbol.000webhostapp.com\r\n\r\n"
//			trace_printf("TCP send failed!! Error code: %u\n", err); //GET /get.php?num=1 HTTP/1.1\r\nHost: dyskbol.000webhostapp.com\r\n\r\n"
//		else
//		   	trace_printf("Send successful!\n");
//
//		timer.sleep(300);

//		if ((err = WIFI_TCP_Close()))
//				trace_printf("TCP closing failed!! Error code: %u\n", err);

trace_puts(Request);
ShowBuf();
//	FlushBuf();
	State = false;
	if(err == 0)
		return buffer;
	else
		return 0;
	}



	uint8_t ESP8266::ESP_sendcom(char* str)
	{

		FlushBuf();
		int len = 0;
		len = strlen(str);
		for(int i = 0;i<len;i++){
			USART_SendData(ESP_USART, str[i]);
		    while(USART_GetFlagStatus(ESP_USART, USART_FLAG_TC) == RESET)
		    {
		    }
		}
		return 0;
	}

	uint8_t ESP8266::ESP_recdata(uint8_t *c)
	{
		buffer[buf_count++] = *c;
		return 0;
	}

	uint16_t ESP8266::ESP_find(char* str)
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

	uint8_t ESP8266::ShowBuf()
	{
		trace_puts((const char*)buffer);
		return 0;
	}

	uint8_t ESP8266::FlushBuf()
	{
		for(uint16_t i = 0;i<1000;i++)
			buffer[i] = 0;
		buf_count = 0;

		return 0;
	}
