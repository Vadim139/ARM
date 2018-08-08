/*
 * Atmega.h
 *
 *  Created on: 27 lis 2017
 *      Author: Vadim
 */

#ifndef ATMEGA_H_
#define ATMEGA_H_

#include "main.h"
#include "Timer.h"
#include "RS485.h"
#include "md5.h"
#include "NTC.h"
#include "RTC.h"
#include "DataBase.h"


#define ATM_Addr    	252
#define ATM_Wait		2

// Commands
#define	 INIT			254
#define  HALT			1
#define  RUN			2
#define  CLR_SCREEN 	3
#define  LCD_PUTS		4
#define  ALARM_ON		5
#define  ALARM_OFF		6
#define  DATA			7
#define  SEND			10
#define  CHECK			11
#define  ADD			12
#define  UPDATE			13
#define  SAVE			14
#define	 DELETE			15
#define  CANCEL			16
#define  TIME			17
#define  TEMP			18

// Data
#define  USER			21
#define  SENSOR			22
#define  OUTPUT			23
#define  GSM			24
#define	 NOU			25	//Numbers of users
#define  NOS			26
#define  NOG			27
#define  NOO			28
#define  U_NAME			29
#define  U_ACCESS_LVL	30
#define  U_ZONES		31
#define  U_RFID			32
#define  U_PIN			33
#define  S_NAME			34
#define  S_ZONE			35
#define  S_IN			36
#define  S_STAT			37
#define  G_NUM			38
#define  O_TYPE			39
#define  O_STATUS		40
#define  O_SCHEDULE		41
#define  WIFI_NAME		42
#define  WIFI_PASS		43
#define  NET_PR			44
#define  NET_ON			45
#define  WATCH			46



#define ATM_GPIO      GPIOA
#define ATM_PIN_SS    GPIO_Pin_4

//#define Atm_addr 0x12

class Atmega {

	uint8_t err;

//	static volatile char buffer[100];
//	static volatile int Read_point;
//	static volatile int Write_point;

	void Atm_EnableSlave();
	void Atm_DisableSlave();


public:
	static volatile char buffer[100];
	static volatile int Read_point;
	static volatile int Write_point;

	Atmega();
	virtual ~Atmega();

	bool IsConnected;
	uint8_t receive;
	bool proc;

	uint8_t Init();
	uint8_t Halt();
	uint8_t Run();
	uint8_t Atm_proc();
	uint8_t Send_comm(uint8_t com);
	uint8_t Send_data(uint8_t *data, uint8_t size);
	uint8_t Send_Temp();
	uint8_t Send_Time();
	uint8_t LCD_Clr();
	uint8_t Alarm_On();
	uint8_t Alarm_Off();
	uint8_t LCD_Put(uint8_t x, uint8_t y, char *str);
	uint8_t Is_Data();
	uint8_t Rec_data(uint8_t *c);
	uint8_t Get_data();
};

#endif /* ATMEGA_H_ */
