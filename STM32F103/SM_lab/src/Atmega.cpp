/*
 * Atmega.cpp
 *
 *  Created on: 27 lis 2017
 *      Author: Vadim
 */

#include "Atmega.h"

extern Timer timer;
extern Data_Base Base;
extern MD5 Md5;;
extern NTC Ntc;
extern IRTC RTC1;

extern User* user_t;
extern Sensor* sensor_t;
extern Output* output_t;
extern char *num_t;
extern char WIFIName_t[19];
extern char WIFIPass_t[20];
extern uint8_t del_t[4];
extern uint8_t Net_s_t;
extern uint8_t Net_on_t;

volatile char Atmega::buffer[100];
volatile int Atmega::Read_point;
volatile int Atmega::Write_point;

Atmega::Atmega() {
	err = 0;
	receive = 0;
	IsConnected = false;
	proc = false;
}

Atmega::~Atmega() {

}

uint8_t Atmega::Init(){

	err = 0;

	receive = 1;
	RS_Transfer(ATM_Addr,INIT);

	timer.sleep(10);

	if(Get_data() != 250)
		err = 1;

	receive = 0;

	return err;
}

uint8_t Atmega::Send_comm(uint8_t com)
{
	err = 0;

	RS_Transfer(ATM_Addr,com);

	timer.sleep(10);

//	if(Get_data() != ATM_Addr)
//		err = 1;

	return err;

}

uint8_t Atmega::Halt()
{
	return Send_comm(HALT);
}

uint8_t Atmega::Run()
{
	return Send_comm(RUN);
}


uint8_t Atmega::LCD_Clr(){

	return Send_comm(CLR_SCREEN);
}

uint8_t Atmega::Alarm_On(){

	return Send_comm(ALARM_ON);
}

uint8_t Atmega::Alarm_Off(){

	return Send_comm(ALARM_OFF);
}

uint8_t Atmega::Send_Temp(){

	char str[5];
	memset(str,0,20);

	Ntc.Get_temp(str);
	RS_TransferMulti(ATM_Addr,TEMP,(unsigned char*)str,strlen(str));

	timer.sleep(10);


	return err;
}

uint8_t Atmega::Send_Time(){

	uint8_t data[10];
	memset(data,0,10);

	memcpy(data,&RTC1.Time_s,3);
	data[3] = 0;
	memcpy(data+4,&RTC1.Date_s,4);

	RS_TransferMulti(ATM_Addr,TIME,(unsigned char*)data,8);

	timer.sleep(10);


	return err;
}

uint8_t Atmega::LCD_Put(uint8_t x, uint8_t y, char *str){

	char str2[20];
	memset(str2,0,20);

	strcpy(str2+2,str);
	str2[0] = x;
	str2[1] = y;

	RS_TransferMulti(ATM_Addr,LCD_PUTS,(unsigned char*)str2,strlen(str2+2)+2);

	timer.sleep(10);

	if(Get_data() != ATM_Addr )
		err = 1;

	return err;
}

uint8_t Atmega::Atm_proc()
{
	Sensor *sensor;
	User *user;
	Output *output;
	char *buf_p;

	uint8_t buf[35];

//	memset(num,0,10);
	memset(buf,0,35);


	if(Is_Data())
	{
		Get_data();
		switch (Get_data()) {
			case TEMP:
				if(Is_Data())
				{
					for(int i = 0; i<10;i++)
					{
						buf[i] = Get_data();
					}
					strcpy(Ntc.Temp_in,(char *)buf);
				}
			break;
			case SEND:
				if(Is_Data())
					switch (Get_data()) {
						case NOU:
							buf[0] = Base.Get_User_num();
							Send_data(buf,1);
							break;
						case NOS:
							buf[0] = Base.Get_Sensor_num();
							Send_data(buf,1);
							break;
						case NOG:
							buf[0] = Base.Get_GSM_num();
							Send_data(buf,1);
							break;
						case NOO:
							buf[0] = Base.Get_Output_num();
							Send_data(buf,1);
							break;
						case U_NAME:
							if(Is_Data())
							{
								user = Base.Get_User(Get_data());
								Send_data((uint8_t*)user->User_Name,20);
							}
							break;
						case U_ZONES:
							if(Is_Data())
							{
								user = Base.Get_User(Get_data());
								Send_data((uint8_t*)user->Strefy,10);
							}
							break;
						case U_ACCESS_LVL:
							if(Is_Data())
							{
								user = Base.Get_User(Get_data());
								Send_data(&(user->Access_lvl),1);
							}
							break;
						case S_NAME:
							if(Is_Data())
							{
								sensor = Base.Get_Sensor(Get_data());
								Send_data((uint8_t*)sensor->Sensor_Name,20);
							}
							break;
						case S_ZONE:
							if(Is_Data())
							{
								sensor = Base.Get_Sensor(Get_data());
								Send_data(&(sensor->Strefa),1);
							}
							break;
						case S_IN:
							if(Is_Data())
							{
								sensor = Base.Get_Sensor(Get_data());
								Send_data(&(sensor->IN),1);
							}
							break;
						case S_STAT:
							if(Is_Data())
							{
								sensor = Base.Get_Sensor(Get_data());
								Send_data(&(sensor->Status),1);
							}
							break;
						case G_NUM:
							if(Is_Data())
							{
								buf_p = Base.Get_GSM(Get_data());
								Send_data((uint8_t*)buf_p,10);
							}
							break;
						case O_TYPE:
							if(Is_Data())
							{
								output = Base.Get_Output(Get_data());
								Send_data(&(output->Type),1);
							}
							break;
						case O_STATUS:
							if(Is_Data())
							{
								output = Base.Get_Output(Get_data());
								Send_data(&(output->Status),1);
							}
							break;
						case O_SCHEDULE:
							if(Is_Data())
							{
								output = Base.Get_Output(Get_data());
								Send_data((output->Schedule),8);
							}
							break;
						case WIFI_NAME:
							buf_p = Base.Get_WIFIName();
							Send_data((uint8_t*)buf_p,20);
							break;
						case WIFI_PASS:
							buf_p = Base.Get_WIFIPass();
							Send_data((uint8_t*)buf_p,20);
							break;
						case NET_PR:
								buf[0] = Base.Get_Net_s();
								Send_data(buf,1);
							break;
						case NET_ON:
								buf[0] = Base.Is_Net_on();
								Send_data(buf,1);
							break;
						case WATCH:
								Send_data((uint8_t*)Base.WATCHING,5);
							break;
						default:
							break;
					}
				break;
			case CHECK:
				if(Is_Data())
					switch (Get_data()) {
						case U_RFID:
							for(int i = 0; i<15;i++)
							{
								buf[i] = Get_data();
							}
							Md5.Get_MD5((char*)buf,(char*)buf);
							buf[33] = Get_data();
							buf[34] = 0;

							for(int i = 0; i<Base.Get_User_num();i++)
							{
								user = Base.Get_User(i);
								for(int j = 0; j<32;j++)
								{
									if(user->RFID_Num[j] != buf[j])
										break;
									if(j == 31)
										buf[34] = i;

								}
								if(buf[34] != 0){
									Send_data(&buf[34],1);
									Send_data((uint8_t*)user->User_Name,21);

									if(buf[33] == 1)
									{
										for(int k = 0; user->Strefy[k] != 0; k++)
										{
											if(user->Strefy[k] != 44)
												Base.WATCHING[user->Strefy[k]-48] = true;
										}
									}else if(buf[33] == 0)
									{
										for(int k = 0; user->Strefy[k] != 0; k++)
										{
											if(user->Strefy[k] != 44)
												Base.WATCHING[user->Strefy[k]-48] = false;
										}
									}

									break;
								}else if(i == Base.Get_User_num()-1){
									Send_data(buf,1);
								}
							}
							break;
						case U_PIN:
							for(int i = 0; i<5;i++)
							{
								buf[i] = Get_data();
							}
							Md5.Get_MD5((char*)buf,(char*)buf);
							buf[33] = Get_data();
							buf[34] = 0;

							for(int i = 0; i<Base.Get_User_num();i++)
							{
								user = Base.Get_User(i);
								for(int j = 0; j<32;j++)
								{
									if(user->PIN[j] != buf[j])
										break;
									if(j == 31)
										buf[34] = i;

								}
								if(buf[34] != 0){
									buf[33] = user->Access_lvl;
									Send_data(&buf[33],2);
									Send_data((uint8_t*)user->User_Name,21);
									break;
								}else if(i == Base.Get_User_num()-1){
									Send_data(buf,1);
								}
							}
							break;
						default:
							break;
					}

				break;
			case UPDATE:
				if(Is_Data())
				{
					for(int i = 0; i<35;i++)
					{
						buf[i] = Get_data();
					}

					switch (buf[33]) {
						case U_NAME:
							if(user_t == 0){
//								user_t = Base.Get_User(buf[34]);
								user_t = new User;
								memcpy(user_t,Base.Get_User(buf[34]),102);
							}

							for(int j = 0; j<20;j++)
							{
								user_t->User_Name[j] = buf[j];
							}

							break;
						case U_ZONES:
							if(user_t == 0){
								user_t = new User;
								memcpy(user_t,Base.Get_User(buf[34]),102);
							}

							for(int j = 0; j<10;j++)
							{
								user_t->Strefy[j] = buf[j];
							}

							break;
						case U_ACCESS_LVL:
							if(user_t == 0){
								user_t = new User;
								memcpy(user_t,Base.Get_User(buf[34]),102);
							}

							user_t->Access_lvl = buf[0];

							break;
						case U_RFID:
							if(user_t == 0){
								user_t = new User;
								memcpy(user_t,Base.Get_User(buf[34]),102);
							}

							buf[33] = 0;
							buf[34] = 0;

							Md5.Get_MD5((char *)buf,(char *)buf);

							for(int j = 0; j<32;j++)
							{
								user_t->RFID_Num[j] = buf[j];
							}

							break;
						case U_PIN:
							if(user_t == 0){
								user_t = new User;
								memcpy(user_t,Base.Get_User(buf[34]),102);
							}

							buf[33] = 0;
							buf[34] = 0;

							Md5.Get_MD5((char *)buf,(char *)buf);

							for(int j = 0; j<32;j++)
							{
								user_t->PIN[j] = buf[j];
							}

							break;
						case S_NAME:
							if(sensor_t == 0){
								sensor_t = new Sensor;
								memcpy(sensor_t,Base.Get_Sensor(buf[34]),24);
							}
								//sensor_t = Base.Get_Sensor(buf[34]);

							for(int j = 0; j<20;j++)
							{
								sensor_t->Sensor_Name[j] = buf[j];
							}

							break;
						case S_ZONE:
							if(sensor_t == 0){
								sensor_t = new Sensor;
								memcpy(sensor_t,Base.Get_Sensor(buf[34]),24);
							}

							sensor_t->Strefa = buf[0];

							break;
						case S_IN:
							if(sensor_t == 0){
								sensor_t = new Sensor;
								memcpy(sensor_t,Base.Get_Sensor(buf[34]),24);
							}

							sensor_t->IN = buf[0];

							break;
						case G_NUM:
							if(num_t == 0){
								num_t = new char[11];
								memset(num_t,0,11);
								num_t[10] = buf[34];
							}

							memcpy(num_t,buf,9);


							break;
						case O_TYPE:
							if(output_t == 0){
								output_t = new Output;
								memcpy(output_t,Base.Get_Output(buf[34]),11);
							}

							output_t->Type = buf[0];

							break;
						case O_STATUS:
							if(output_t == 0){
								output_t = new Output;
								memcpy(output_t,Base.Get_Output(buf[34]),11);
							}

							output_t->Status = buf[0];

							break;
						case O_SCHEDULE:
							if(output_t == 0){
								output_t = new Output;
								memcpy(output_t,Base.Get_Output(buf[34]),11);
							}

							for(int j = 0; j<8;j++)
							{
								output_t->Schedule[j] = buf[j];
							}

							break;
						case WIFI_NAME:
							strcpy(WIFIName_t,(char *)buf);

							break;
						case WIFI_PASS:
							strcpy(WIFIName_t,(char *)buf);

							break;
						case NET_PR:
							Net_s_t = buf[0];

							break;
						case NET_ON:
							Net_on_t = buf[0];

							break;
						default:
							break;
					}
				}
				break;
			case ADD:
				if(Is_Data())
				{
					switch (Get_data()) {
						case USER:
							if(user_t == 0){
								user_t = new User;
							}
							break;
						case SENSOR:
							if(sensor_t == 0){
								sensor_t = new Sensor;
							}
							break;
						case GSM:
							if(num_t == 0){
								num_t = new char[11];
								memset(num_t,0,11);
							}
							break;
						case OUTPUT:
							if(output_t == 0){
								output_t = new Output;
							}
							break;
						default:
							break;
					}
				}
				break;
			case DELETE:
				if(Is_Data())
				{
					switch (Get_data()) {
						case USER:
							if(user_t == 0){
								del_t[0] = Get_data();
							}
							break;
						case SENSOR:
							if(sensor_t == 0){
								del_t[1] = Get_data();;
							}
							break;
						case GSM:
							if(num_t == 0){
								del_t[2] = Get_data();
							}
							break;
						case OUTPUT:
							if(output_t == 0){
								del_t[3] = Get_data();
							}
							break;
						default:
							break;
					}
				}
				break;
			case CANCEL:
				if(del_t[0] != 0)
				{
					del_t[0] = 0;
				}else if(user_t != 0)
				{
					delete(user_t);
					user_t = 0;
				}

				if(del_t[1] != 0)
				{
					del_t[1] = 0;
				}else if(sensor_t != 0)
				{
					delete(sensor_t);
					sensor_t = 0;
				}

				if(del_t[3] != 0)
				{
					del_t[3] = 0;
				}else if(output_t != 0)
				{
					delete(output_t);
					output_t = 0;
				}

				if(del_t[2] != 0)
				{
					del_t[2] = 0;
				}else if(num_t != 0)
				{
					delete(num_t);
					num_t = 0;
				}

				if(WIFIName_t[0] != 0)
				{
					memset(WIFIName_t,0,19);
				}

				if(WIFIPass_t[0] != 0)
				{
					memset(WIFIPass_t,0,20);
				}

				if(Net_on_t != 2)
				{
					Net_on_t = 0;
				}

				if(Net_s_t != 0)
				{
					Net_s_t = 0;
				}
				break;
			case SAVE:
				if(del_t[0] != 0)
				{
					Base.Del_User(del_t[0]);
				}else if(user_t != 0)
				{
					if(user_t->User_ID == 0)
						Base.Add_User(*user_t);
					else
						Base.Update_User(*user_t,user_t->User_ID);

					delete(user_t);
					user_t = 0;
				}

				if(del_t[1] != 0)
				{
					Base.Del_Sensor(del_t[1]);
				}else if(sensor_t != 0)
				{
					if(sensor_t->Sensor_ID == 0)
						Base.Add_Sensor(*sensor_t);
					else
						Base.Update_Sensor(*sensor_t,sensor_t->Sensor_ID);

					delete(sensor_t);
					sensor_t = 0;
				}

				if(del_t[3] != 0)
				{
					Base.Del_Output(del_t[3]);
				}else if(output_t != 0)
				{
					if(Base.Get_Output(output_t->Output_ID) == 0)
						Base.Add_Output(*output_t);
					else
						Base.Update_Output(*output_t,output_t->Output_ID);

					delete(output_t);
					output_t = 0;
				}

				if(del_t[2] != 0)
				{
					Base.Del_GSM(del_t[2]);
				}else if(num_t != 0)
				{
					if(num_t[10] == 0)
						Base.Add_GSM(num_t,"0");
					else
						Base.Update_GSM(num_t,Base.Get_GSM(num_t[10]));

					delete(num_t);
					num_t = 0;
				}

				if(WIFIName_t[0] != 0)
				{
					Base.Change_WIFIName(WIFIName_t);
					memset(WIFIName_t,0,19);
				}

				if(WIFIPass_t[0] != 0)
				{
					Base.Change_WIFIPass(WIFIPass_t);
					memset(WIFIPass_t,0,20);
				}

				if(Net_on_t != 2)
				{
					Base.Change_Net_on(Net_on_t);
					Net_on_t = 0;
				}

				if(Net_s_t != 0)
				{
					Base.Change_Net_s(Net_s_t);
					Net_s_t = 0;
				}
				break;
			default:
				break;
		}
	}
	proc = false;
	return 0;
}

uint8_t Atmega::Send_data(uint8_t *data, uint8_t size)
{
	RS_TransferMulti(ATM_Addr,DATA,(unsigned char*)data,size);

	timer.sleep(10);

//	if(Get_data() != ATM_Addr )
//		err = 1;

	return err;
}



uint8_t Atmega::Is_Data()
{
	if(Read_point != Write_point)
		return 1;
	else
		return 0;
}

uint8_t Atmega::Get_data()
{
	uint8_t c = 0;
		if(Is_Data())
		{
			c = buffer[Read_point];

			Read_point++;

			if(Read_point >= 100)
				Read_point = 0;


		}
	return c;
}

uint8_t Atmega::Rec_data(uint8_t *c)
{
	Write_point++;

	if(Write_point >= 100)
		Write_point = 0;

	if(Write_point == Read_point){
		Write_point--;
		return 1;
	}
	else
		{
		buffer[Write_point] = *c;

		return 0;
		}
}
