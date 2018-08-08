/*
 * NET.h
 *
 *  Created on: 25 lis 2017
 *      Author: Vadim
 */

#ifndef NET_H_
#define NET_H_

#include "main.h"
#include "ESP8266.h"
#include "SIM800L.h"
#include "DataBase.h"

//#define WIFINAME            "Vadim123"
//#define WIFIPASS            "12345678qwertyui"
#define WIFINAME            "TP-LINK"
#define WIFIPASS            "3671044436710"

extern ESP8266 ESP;
extern SIM800L SIM;

//Data i czas: 2017-12-02 17:53:35
class NET {
	uint8_t err;
	uint8_t TCP;

	bool WIFI_connected;
	bool GSM_Connected;
public:
	NET();
	virtual ~NET();

	bool IsWIFI(uint8_t newv = 2);
	bool IsGSM(uint8_t newv = 2);

	uint8_t Connect(); // s -> 0 - WIFI, 1 - GSM, 2 - both
	void Connect_WIFI();
	void Connect_GSM();
	uint8_t Get_config();
	uint8_t TCP_Start(char* IP, char* Port);
	uint8_t TCP_Send(char* str);
	uint8_t TMode_ON();
	uint8_t TMode_OFF();
	uint8_t TCP_Close(uint8_t f = 1);
	uint8_t Get_DataTime(char* DataTime);
	volatile char* HTTP_RQS(char* IP, char* Request, uint8_t dir);
	uint16_t Find(char* str, char* buffer, uint16_t min);

};

#endif /* NET_H_ */
