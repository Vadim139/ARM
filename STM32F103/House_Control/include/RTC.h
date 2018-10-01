/*
 * RTC.h
 *
 *  Created on: 26 lis 2017
 *      Author: Vadim
 */

#ifndef RTC_H_
#define RTC_H_

#include "main.h"
//#include "NET.h"
//#include "ESP8266.h"
//#include "SIM800L.h"

#define Data_Reg BKP_DR2

struct Date_str
{
	uint8_t Day;
	uint8_t Month;
	uint16_t Year;
};

struct Time_str
{
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
};

class IRTC {

	uint8_t err;
	uint8_t alarm_state;
	uint16_t Comp_Data;

public:
	uint32_t time;
	uint32_t alarm;
	uint8_t set;
	uint8_t alarm_reg;
	Time_str Time_s;
	Date_str Date_s;

	IRTC();
	virtual ~IRTC();

	uint8_t RTC_Config();
	uint8_t IT_Config();
	uint8_t Set_Time(uint32_t);
	uint8_t Set_From_Net();
	uint8_t Set_Alarm(uint32_t);
	uint8_t Day_inc();
	uint16_t Comp_Date(const Date_str *Date);
	uint16_t Get_Comp_Date();
	Date_str Get_Date();
	Date_str Get_Time();
};

#endif /* RTC_H_ */
