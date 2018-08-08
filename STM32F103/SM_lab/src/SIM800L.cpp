/*
 * ESP8266.cpp
 *
 *  Created on: 30 paŸ 2017
 *      Author: Vadim
 */

#include "SIM800L.h"

extern Timer timer;

volatile char SIM800L::buffer[1000];
volatile int SIM800L::buf_count;

uint8_t SIM800L::Init_usart() {
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = SIM_USART_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB2PeriphClockCmd(SIM_GPIO_RCC, ENABLE);
	RCC_APB1PeriphClockCmd(SIM_USART_RCC, ENABLE);

	/* Configure USARTy Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = SIM_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SIM_RX_P, &GPIO_InitStructure);

	/* Configure USARTy Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = SIM_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SIM_TX_P, &GPIO_InitStructure);
	/* Configure USARTz Tx as alternate function push-pull */

	GPIO_InitStructure.GPIO_Pin = SIM_RST;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SIM_RST_P, &GPIO_InitStructure);

	SIM_RST_P->BRR = SIM_RST;
	timer.sleep(700);
	SIM_RST_P->BSRR = SIM_RST;
	timer.sleep(2500);

	USART_InitStructure.USART_BaudRate = SIM_bautrate; //230400 /*115200*/;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USARTy */
	USART_Init(SIM_USART, &USART_InitStructure);

	/* Enable the USARTy */
	USART_Cmd(SIM_USART, ENABLE);

	USART_ITConfig(SIM_USART, USART_IT_RXNE, ENABLE);
	timer.set_TimeOut(200);
//	Timer::TimeOut = 200;
	while (USART_GetFlagStatus(SIM_USART, USART_FLAG_TC) == RESET)
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

	uint8_t SIM800L::Init_SIM()
	{
		timer.sleep(1000);
		SIM_sendcom("AT\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			return 1;

		SIM_sendcom("AT+CFUN=1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			return 1;

		SIM_sendcom("AT+CREG?\r\n");
		timer.sleep(300);
		if(!SIM_find("0,1\r\n") && !SIM_find("0,5\r\n"))
		    if(!SIM_find("0,2\r\n"))
		    	for(int i = 0;i<10;i++){
		    		SIM_sendcom("AT+CREG?\r\n");
		    		timer.sleep(500);
		    		if(SIM_find("0,1\r\n") || SIM_find("0,5\r\n"))
		    			return 0;
		    	}


		if(!SIM_find("OK\r\n"))
			return 1;
		timer.sleep(1000);

		return 0;
	}


	SIM800L::SIM800L()
	{
		err = 0;
		State = false;
	}

	uint8_t SIM800L::Init()
	{
		err = 0;

		for(int i = 0; i<8; i++)
			Operator[i] = 0;

		for(int i = 0; i<16; i++)
			IP_TCP[i] = 0;

		for(int i = 0; i<16; i++)
			IP_HTTP[i] = 0;


		State = true;

		if(Init_usart())
			err = 1;
		if(Init_SIM())
			err = 2;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::Get_operator()
	{
		err = 0;
		uint16_t poz = 0;
		int i = 0;

		State = true;

		SIM_sendcom("AT+COPS?\r\n");
		timer.sleep(500);
		poz = SIM_find(",\"");
		if(!poz)
			err = 1;
		else{
		poz += 1;
		while(buffer[poz+i] != '\"')
		{
			Operator[i] = buffer[poz+i];
			i++;
		}

		SIM_sendcom("AT+CPIN?\r\n");
		timer.sleep(300);
		if(!SIM_find("READY\r\n"))
			err = 2;
		}
		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::GSM_Connect(int Operator) // operator play - 1
	{

		err = 0;
		State = true;
		timer.sleep(500);

		SIM_sendcom("AT+CBAND?\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n")){
			State = false;
			return 2;
		}

//		SIM_sendcom("AT+CBAND=\"EGSM_DCS_MODE\"\r\r\n\n");
//		timer.sleep(1000);
//		if(!SIM_find("OK\r\n"))
//			err = 2;

		SIM_sendcom("AT+CSTT=\"");//,\"\",\"\"   AT+CSTT=\"internet\"
		if(Operator == 1)
			SIM_sendcom("internet");
		SIM_sendcom("\",\"");
		SIM_sendcom("\",\"");
		SIM_sendcom("\"\r\n");//\"\r\n"
		while(buffer[0] == 0);
		for(int i = 0;i<10;i++){
			err = 1;
		timer.sleep(500);
		if(SIM_find("OK\r\n")){
			err = 0;
			break;
			FlushBuf();
			State = false;
			return err;
		}
		}

		SIM_sendcom("AT+CIICR\r\n");
		timer.sleep(600);
		if(!SIM_find("OK\r\n")){
			State = false;
			return 1;
		}

		SIM_sendcom("AT+SAPBR=3,1,\"APN\",\"Internet\"\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n")){
			State = false;
			return 1;
		}

		SIM_sendcom("AT+SAPBR=3,1,\"USER\",\"\"\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n")){
			State = false;
			return 1;
		}

		SIM_sendcom("AT+SAPBR=3,1,\"PWD\",\"\"\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n")){
			State = false;
			return 1;
		}

		SIM_sendcom("AT+SAPBR=1,1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n")){
			State = false;
			return 1;
		}

		SIM_sendcom("AT+SAPBR=2,1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n")){
			State = false;
			return 1;
		}

		FlushBuf();
		State = false;
//		err = 1;
		return err;
	}

	uint8_t SIM800L::GSM_Connect(int Operator, char* User ,char* Pass) // operator play - 1
	{

		err = 0;
		State = true;

		SIM_sendcom("AT+CSTT=\"");
		if(Operator == 1)
			SIM_sendcom("internet");
		SIM_sendcom("\",\"");
		SIM_sendcom(User);
		SIM_sendcom("\",\"");
		SIM_sendcom(Pass);
		SIM_sendcom("\"\r\n");
		while(buffer[0] == 0);
		for(int i = 0;i<10;i++){
		timer.sleep(500);
		if(SIM_find("OK\r\n")){
			SIM_sendcom("AT+CIICR\r\n");
			timer.sleep(300);
			if(!SIM_find("OK\r\n"))
				err = 1;
			FlushBuf();
			State = false;
			return err;
		}

		}
		FlushBuf();
		State = false;
		err = 1;
		return err;
	}


	uint8_t SIM800L::GSM_GetConfig()
	{
		uint16_t poz = 0;
		int i = 0;

		err = 0;
		State = true;

		Get_operator();

		State = true;
		i = 0;
		SIM_sendcom("AT+CIFSR\r\n");
		timer.sleep(300);
		poz = SIM_find(".");
		if(!poz)
			return 1;
		poz -= 3;
		while(buffer[poz+i] != '\r')
		{
			IP_TCP[i] = buffer[poz+i];
			i++;
		}

		i = 0;
		SIM_sendcom("AT+SAPBR=2,1\r\n");
		timer.sleep(300);
		poz = SIM_find(".");
		if(!poz)
			return 1;
		poz -= 3;
		while(buffer[poz+i] != '\"')
		{
			IP_HTTP[i] = buffer[poz+i];
			i++;
		}


		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::GSM_SendSMS(char* number, char* str)
	{
		err = 0;
		State = true;

		SIM_sendcom("AT+CMGF=1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+CMGS=\"");
		SIM_sendcom(number);
		SIM_sendcom("\"\r\n");
		timer.sleep(100);
		if(!SIM_find(">"))
			err = 1;
		SIM_sendcom(str);
		SIM_sendcom("\032");
		for(int i = 0;i<10;i++){
			timer.sleep(500);
			if(SIM_find("OK\r\n")){
				timer.sleep(300);
				if(!SIM_find("OK\r\n"))
					err = 1;
				FlushBuf();
				State = false;
				return err;
				}
		}
//		timer.sleep(3000);
//		if(!SIM_find("OK\r\n"))
//			err = 1;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::GSM_Call(char* number)
	{
		err = 0;
		State = true;

		SIM_sendcom("ATD");
		SIM_sendcom(number);
		SIM_sendcom(";\r\n");
		for(int i = 0;i<10;i++){
			timer.sleep(500);
			if(SIM_find("OK\r\n")){
				timer.sleep(300);
				if(!SIM_find("OK\r\n"))
					err = 1;
				FlushBuf();
				State = false;
				return err;
				}
		}

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::GSM_Cancel_call()
	{
		err = 0;
		State = true;

		SIM_sendcom("ATH");
		SIM_sendcom("\r\n");
		for(int i = 0;i<10;i++){
			timer.sleep(500);
			if(SIM_find("OK\r\n")){
				timer.sleep(300);
				if(!SIM_find("OK\r\n"))
					err = 1;
				FlushBuf();
				State = false;
				return err;
				}
		}

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::GSM_TCP_Start(char* IP, char* Port)
	{
		err = 0;
		State = true;

//		SIM_sendcom("AT+CIPMUX=0\r\n");
//		timer.sleep(300);
//		if(!SIM_find("OK\r\n"))
//			err = 1;

//		SIM_sendcom("AT+CIPMODE=0\r\n");
//		timer.sleep(300);
//		if(!SIM_find("OK\r\n"))
//			err = 1;

		SIM_sendcom("AT+CIPSTART=\"TCP\",\"");
		SIM_sendcom(IP);
		SIM_sendcom("\",");
		SIM_sendcom(Port);
		SIM_sendcom("\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			if(SIM_find("ALREADY"))
				err = 2;
			else
				err = 1;

		FlushBuf();
		State = false;
		return err;
	}


	uint8_t SIM800L::GSM_TCP_Send(char* str)
	{
		uint16_t len = strlen(str);
		char len_s[5] = {0,0,0,0,0};

		err = 0;
		State = true;

		sprintf(len_s, "%u", len);

		SIM_sendcom("AT+CIPSEND=");
		SIM_sendcom(len_s);
		SIM_sendcom("\r\n");
		timer.sleep(300);
		if(!SIM_find(">"))
			err = 1;
		SIM_sendcom(str);
		SIM_sendcom("\r\n");
		timer.sleep(1000);
		if(!SIM_find("SEND OK\r\n"))
			err = 1;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::GSM_TMode_On()
	{
		err = 0;
		State = true;

		SIM_sendcom("AT+CGATT=0\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+CGATT=1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+CIPMODE=1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		GSM_Connect(1);

		SIM_sendcom("ATO\r\n");
		timer.sleep(300);
		if(!SIM_find("CONNECT\r\n"))
			err = 1;

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::GSM_TMode_Off()
	{
		err = 0;
		State = true;

		timer.sleep(500);
		SIM_sendcom("+++");
		timer.sleep(500);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+CGATT=0\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+CGATT=1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+CIPMODE=0\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		GSM_Connect(1);

		FlushBuf();
		State = false;
		return err;
	}

	uint8_t SIM800L::GSM_TCP_Close(uint8_t f)
	{
		err = 0;
		State = true;

		SIM_sendcom("AT+CIPCLOSE\r\n");
		timer.sleep(300);
		if(!SIM_find("CLOSE OK\r\n"))
			err = 1;

		if(f)
			FlushBuf();
		State = false;
		return err;
	}

	volatile int8_t err2;

	uint8_t SIM800L::GSM_Get_DataTime(char* DataTime)// DataTime min 25 char
	{
		err = 0;
		State = true;

		uint16_t poz = 0;
		int i = 0;


		SIM_sendcom("AT+HTTPINIT\r\n");
		timer.sleep(300);
//		if(!SIM_find("OK\r\n"))
//			err = 1;

		SIM_sendcom("AT+HTTPPARA=\"CID\",1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+HTTPPARA=\"URL\",\"http://dyskbol.000webhostapp.com/get.php/:80/?RQS=2&SRQS=1\"\r\n");
		timer.sleep(100);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+HTTPACTION=0\r\n");
//		timer.sleep(5000);
		for(int i = 0;i<10;i++){
		timer.sleep(500);
		if(SIM_find("OK\r\n") && SIM_find(",200,"))
			break;
		else if(i == 9)
			err = 1;
		}

//		if(!SIM_find("OK\r\n"))
//			err = 1;
//		if(!SIM_find(",200,"))
//					err = 1;


		SIM_sendcom("AT+HTTPREAD\r\n");
//		timer.sleep(1000);
		for(int i = 0;i<10;i++){
		timer.sleep(100);
		if((poz = SIM_find("Data i czas: ")))
			break;
		else if(i == 9)
			err = 1;
		}
//		if(!SIM_find(",200,"))
//			err = 1;

//		timer.sleep(600);
//		poz = SIM_find("Data i czas: ");
		if(!poz)
			err = 1;
		else{
			poz += 12;
			while(buffer[poz+i] != '\r')
			{
				DataTime[i] = buffer[poz+i];
				i++;
			}

		}

	FlushBuf();
	State = false;
	return err;
	}

	volatile char* SIM800L::GSM_HTTP_RQS(char* IP, char* Request, uint8_t dir)
	{
		//IP: dyskbol.000webhostapp.com
		//Request: ?text=test&num=123
		err = 0;
		State = true;


		SIM_sendcom("AT+HTTPINIT\r\n");
		timer.sleep(300);
//		if(!SIM_find("OK\r\n"))
//			err = 1;

		SIM_sendcom("AT+HTTPPARA=\"CID\",1\r\n");
		timer.sleep(300);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+HTTPPARA=\"URL\",\"http://");
		SIM_sendcom(IP);//http://dyskbol.000webhostapp.com
		if(dir == 0)
			SIM_sendcom("/store.php/:80/");
		else
			SIM_sendcom("/get.php/:80/");
		SIM_sendcom(Request);///store.php/:80/?text=test&num=123
		SIM_sendcom("\"\r\n");
		//AT+HTTPPARA=\"URL\",\"http://dyskbol.000webhostapp.com/store.php/:80/?text=test&num=123\"\r\n"
		timer.sleep(200);
		if(!SIM_find("OK\r\n"))
			err = 1;

		SIM_sendcom("AT+HTTPACTION=0\r\n");
//		timer.sleep(5000);
		for(int i = 0;i<20;i++){
		timer.sleep(600);
		if(SIM_find("OK\r\n") && SIM_find(",200,"))
			break;
		else if(i == 9)
			err = 1;
		}

//		if(!err)
//			err = 1;
//		if(!SIM_find("OK\r\n"))
//			err = 1;
//		if(!SIM_find(",200,\r\n"))
//			err = 1;


		SIM_sendcom("AT+HTTPREAD\r\n");
//		timer.sleep(1000);
		for(int i = 0;i<20;i++){
		timer.sleep(100);
		if(SIM_find("OK\r\n"))
			break;
		else if(i == 9)
			err = 1;
		}
		timer.sleep(200);

//		SIM_sendcom("AT+HTTPTERM\r\n");
//		timer.sleep(500);
//		if(!SIM_find("OK\r\n"))
//			err = 1;


//		ShowBuf();
//		FlushBuf();
		State = false;
		if(err == 0)
			return buffer;
		else
			return 0;

//		return buffer;
	}

	uint8_t SIM800L::SIM_sendcom(char* str)
	{
		/*for(int i = 0;i<100;i++)
			buffer[i] = 0;
		buf_count = 0;*/

		FlushBuf();

		int len = 0;
		len = strlen(str);
		for(int i = 0;i<len;i++){
			USART_SendData(SIM_USART, str[i]);
		    while(USART_GetFlagStatus(SIM_USART, USART_FLAG_TC) == RESET)
		    {
		    }
		}
		return 0;
	}

	uint8_t SIM800L::SIM_recdata(uint8_t *c)
	{
		buffer[buf_count++] = *c;
		return 0;
	}

	uint16_t SIM800L::SIM_find(char* str)
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

	uint8_t SIM800L::ShowBuf()
	{
		trace_puts((const char*)buffer);
		return 0;
	}

	uint8_t SIM800L::FlushBuf()
	{
		for(uint16_t i = 0;i<1000;i++)
			buffer[i] = 0;
		buf_count = 0;

		return 0;
	}
