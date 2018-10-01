/*
 * RTC.cpp
 *
 *  Created on: 26 lis 2017
 *      Author: Vadim
 */

#include "RTC.h"

//extern ESP8266 ESP;
//extern SIM800L SIM;
//extern NET Net;

IRTC::IRTC() {

	err = 0;
	time = 0;
	alarm = 0;
	set = 0;
	alarm_state = 0;
	alarm_reg = 0;
	Comp_Data = 0;
}

IRTC::~IRTC() {

}

uint8_t IRTC::RTC_Config() {

	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5) {
		/* Backup data register value is not correct or not yet programmed (when
		 the first time the program is executed) */

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

		PWR_BackupAccessCmd(ENABLE);
		BKP_DeInit();

		RTC_EnterConfigMode();

		RCC_LSEConfig(RCC_LSE_ON);
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {
		};

		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
//		RTC_SetCounter(1000);
		RTC_SetPrescaler(32767);
		RTC_WaitForLastTask();
		RTC_ExitConfigMode();
		//	BKP_WriteBackupRegister(Data_Reg, 0);
//		RTC_SetCounter(BKP_ReadBackupRegister(Data_Reg));
		RTC_ClearFlag(RTC_FLAG_SEC);
		while (RTC_GetFlagStatus(RTC_FLAG_SEC) == RESET) {
		};
		RTC_WaitForLastTask();
		RTC_SetAlarm(43200); // 12:00
		RTC_WaitForLastTask();

		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}else{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

		PWR_BackupAccessCmd(ENABLE);

		Date_s = Get_Date();
	}

	return err;
}

uint8_t IRTC::IT_Config()
{

	//zdefiniowanie struktury wykorzystywanej do konfiguracji przerwani
		NVIC_InitTypeDef NVIC_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;

		//skonfigurowanie miejsca przechowywania tablicy wektorów przerwañ
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

		//konfiguracja podzia³u priorytetów przerwañ
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

		//w³¹czenie obs³ugi alarmu
		if(alarm_state == 1)
		{
			//konfiguracja przerwañ pochodz¹cych od RTC Alarm
			EXTI_ClearITPendingBit(EXTI_Line17);
			EXTI_InitStructure.EXTI_Line = EXTI_Line17;
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;
			EXTI_Init(&EXTI_InitStructure);
			//generowanie przerwania przez RTC Alarm
			RTC_ITConfig(RTC_IT_ALR, ENABLE);
			//odczekanie na zakoñczenie operacji
			RTC_WaitForLastTask();
		}
//		//wy³¹czenie obs³ugi alarmu
//		else
//		{
//			//konfiguracja przerwañ pochodz¹cych od RTC Alarm
//			EXTI_ClearITPendingBit(EXTI_Line17);
//			EXTI_InitStructure.EXTI_Line = EXTI_Line17;
//			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//			EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//			EXTI_InitStructure.EXTI_LineCmd = DISABLE;
//			EXTI_Init(&EXTI_InitStructure);
//			//generowanie przerwania przez RTC Alarm
//			RTC_ITConfig(RTC_IT_ALR, ENABLE);
//			//odczekanie na zakoñczenie operacji
//			RTC_WaitForLastTask();
//		}

		//konfiguracja przerwañ pochodz¹cych od RTC
		NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		//generowanie przerwania przez RTC co 1s
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		//odczekanie na zakoñczenie operacji
		RTC_WaitForLastTask();

		//konfiguracja przerwañ pochodz¹cych od RTC Alarm
		NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

	return err;
}

uint8_t IRTC::Set_Time(uint32_t time)
{
	set = 1;
	RTC_SetCounter(time); // 12:00
	RTC_ClearFlag(RTC_FLAG_SEC);
	while(RTC_GetFlagStatus(RTC_FLAG_SEC) == RESET){};
	RTC_WaitForLastTask();
	set = 0;
	return err;
}

uint8_t IRTC::Set_From_Net()
{
	char DataTime[30];
	char tmp[5] = {0,0,0,0,0};
	set = 1;
	time = 0;

//	Net.Get_DataTime(DataTime);
	tmp[0] = DataTime[0];
	tmp[1] = DataTime[1];
	tmp[2] = DataTime[2];
	tmp[3] = DataTime[3];

	Date_s.Year = atoi(tmp);

	tmp[0] = DataTime[5];
	tmp[1] = DataTime[6];
	tmp[2] = 0;
	tmp[3] = 0;

	Date_s.Month = atoi(tmp);

	tmp[0] = DataTime[8];
	tmp[1] = DataTime[9];

	Date_s.Day = atoi(tmp);

	tmp[0] = DataTime[11];
	tmp[1] = DataTime[12];

	Time_s.Hour = atoi(tmp);
	time += Time_s.Hour*3600;

	tmp[0] = DataTime[14];
	tmp[1] = DataTime[15];

	Time_s.Minute = atoi(tmp);
	time += Time_s.Minute*60;

	tmp[0] = DataTime[17];
	tmp[1] = DataTime[18];

	Time_s.Second = atoi(tmp);
	time += Time_s.Second;

	RTC_SetCounter(time+3);

	BKP_WriteBackupRegister(Data_Reg, Comp_Date(&Date_s));

	set = 0;

	return err;
}

uint8_t IRTC::Set_Alarm(uint32_t time)
{
	RTC_SetAlarm(time); // 12:00
	RTC_WaitForLastTask();
	return err;
}

uint8_t IRTC::Day_inc()
{
	uint8_t Day_in_Month = 0;
//	Date_str Date;

	Date_s = Get_Date();

	if((Date_s.Month == 1) || (Date_s.Month == 3) || (Date_s.Month == 5) || (Date_s.Month == 7) || (Date_s.Month == 8) || (Date_s.Month == 10) || (Date_s.Month == 12))
		Day_in_Month = 31;

	else if((Date_s.Month == 4) || (Date_s.Month == 6) || (Date_s.Month == 9) || (Date_s.Month == 11))
		Day_in_Month = 30;

	else if(Date_s.Month == 2)
	{
		if(Date_s.Year % 4 != 0)
			Day_in_Month = 28;
		else
			Day_in_Month = 29;
	}

	if(Date_s.Day < Day_in_Month)
		Date_s.Day++;
	else if(Date_s.Day == Day_in_Month)
	{
		Date_s.Day = 1;
		if(Date_s.Month < 12)
			Date_s.Month++;
		else if(Date_s.Month == 12)
		{
			Date_s.Month = 1;
			Date_s.Year++;
		}
	}

	BKP_WriteBackupRegister(Data_Reg, Comp_Date(&Date_s));
	return err;
}

/*
 * 1111111111111111
 * 11111|1111|1111111
 *   D  | M  |   Y
 *  0-31|0-12|2000-2127
 */

uint16_t IRTC::Comp_Date(const Date_str *Date)
{
	uint16_t CD = 0;

	CD = CD | (Date->Day << 11);
	CD = CD | (Date->Month << 7);
	CD = CD | (Date->Year-2000);
	return CD;
}

uint16_t IRTC::Get_Comp_Date()
{
	return BKP_ReadBackupRegister(Data_Reg);
}



Date_str IRTC::Get_Date()
{
	uint16_t Comp_Data;
	Date_str Date;
	Comp_Data = Get_Comp_Date();

	Date.Day = Comp_Data >> 11;
	Date.Month = (Comp_Data >> 7) & 0b1111;
	Date.Year = (Comp_Data & 0b1111111) + 2000;

	Date_s.Day = Date.Day;
	Date_s.Month = Date.Month;
	Date_s.Year = Date.Year;

	return Date;
}
