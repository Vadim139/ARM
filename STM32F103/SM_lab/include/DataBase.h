/*
 * DataBase.h
 *
 *  Created on: 9 gru 2017
 *      Author: Vadim
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "main.h"
#include "NET.h"


struct Settings
{
	uint8_t Alarm_ID;
	uint8_t Net_on;
	uint8_t Net_s;	//1-4

	char WIFIName[19];
	char WIFIPass[20];

	char* WEB_IP;
};

struct GSM
{
	uint8_t NoP;
	char* Numbers[10];
};

struct User
{
	char User_Name[20];
	uint8_t User_ID;
	uint8_t Access_lvl;
	char Strefy[10];
	char RFID_Num[35];
	char PIN[35];
};

struct Users
{
	uint8_t NoU;
	User* user[10];
};

struct Sensor
{
	char Sensor_Name[20];
	uint8_t Sensor_ID;
	uint8_t Strefa;
	uint8_t Status;
	uint8_t IN;
};

struct Sensors
{
	uint8_t NoS;
	Sensor* sensor[10];
};

struct Output
{
	uint8_t Output_ID;
	uint8_t Type;
	uint8_t Status;
	uint8_t Schedule[8];
};

struct Outputs
{
	uint8_t NoO;
	Output* output[4];
};


class Data_Base {
	Settings settings;
	GSM gsm;
	Users users;
	Sensors sensors;
	Outputs outputs;

	uint8_t err;

public:

	bool ALARM;
	bool WATCHING[5];

	Data_Base();
	virtual ~Data_Base();

	uint8_t Is_Net_on();
	uint8_t Get_Net_s();
	char* Get_WIFIName();
	char* Get_WIFIPass();
	void  Change_WIFIName(char*);
	void  Change_WIFIPass(char*);
	void  Change_Net_on(uint8_t);
	void  Change_Net_s(uint8_t);
	char* Get_WEB_IP();
	User* Get_User(uint8_t ID);
	Sensor* Get_Sensor(uint8_t ID);
	Output* Get_Output(uint8_t ID);
	char* Get_GSM(uint8_t ID);
	uint8_t Get_User_num();
	uint8_t Get_Sensor_num();
	uint8_t Get_Output_num();
	uint8_t Get_GSM_num();

	uint8_t Clear_All();
	uint8_t Read_Users();
	uint8_t Read_GSM();
	uint8_t Read_Sensors();
	uint8_t Read_Outputs();
	uint8_t Add_User(User user, uint8_t flag = 1);
	uint8_t Add_Sensor(Sensor sensor, uint8_t flag = 1);
	uint8_t Add_GSM(char* Num, char* Num_old, uint8_t flag = 1);
	uint8_t Add_Output(Output output, uint8_t flag = 1);
	uint8_t Update_User(User user, uint8_t ID);
	uint8_t Update_Sensor(uint8_t ID,uint8_t w);
	uint8_t Update_Sensor(Sensor sensor,uint8_t ID);
	uint8_t Update_GSM(char* Num, char* Num_old);
	uint8_t Update_Output(Output output, uint8_t ID);
	uint8_t Update_Output(uint8_t ID, uint8_t w);
	uint8_t Del_User(uint8_t ID);
	uint8_t Del_Sensor(uint8_t ID);
	uint8_t Del_GSM(char* Number);
	uint8_t Del_GSM(uint8_t ID);
	uint8_t Del_Output(uint8_t ID);
	uint8_t RAM_to_DB();
	uint8_t Read_All();
	uint8_t Check_change();
};

#endif /* DATABASE_H_ */
