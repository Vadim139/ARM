/*
 * DataBase.cpp
 *
 *  Created on: 9 gru 2017
 *      Author: Vadim
 */

#include "DataBase.h"
#include "EE_memory.h"

extern NET Net;
extern Timer timer;

Data_Base::Data_Base() {

	err = 0;

	ALARM = false;
	memset(WATCHING,0,5);

	settings.Alarm_ID = 1;

	settings.Net_on = 1;
	settings.Net_s = 3;

	memset(settings.WIFIName,0,19);
	memset(settings.WIFIPass,0,20);

	strcpy(settings.WIFIName,"TP-LINK");
	strcpy(settings.WIFIPass,"3671044436710");

//	settings.WIFIName = "TP-LINK";
//	settings.WIFIPass = "3671044436710";

	settings.WEB_IP = "dyskbol.000webhostapp.com";

	gsm.NoP = 0;
	users.NoU = 0;
	sensors.NoS = 0;
	outputs.NoO = 0;



}

Data_Base::~Data_Base() {

}

uint8_t Data_Base::Is_Net_on()
{
	return settings.Net_on;
}

uint8_t Data_Base::Get_Net_s()
{
	return settings.Net_s;
}

char* Data_Base::Get_WIFIName()
{
	return settings.WIFIName;
}

char* Data_Base::Get_WIFIPass()
{
	return settings.WIFIPass;
}

void  Data_Base::Change_WIFIName(char* str)
{
	memcpy(settings.WIFIName,str, 19);
}

void  Data_Base::Change_WIFIPass(char* str)
{
	memcpy(settings.WIFIPass,str, 20);
}

void  Data_Base::Change_Net_on(uint8_t newval)
{
	settings.Net_on = newval;
}

void  Data_Base::Change_Net_s(uint8_t newval)
{
	settings.Net_s = newval;
}

char* Data_Base::Get_WEB_IP()
{
	return settings.WEB_IP;
}

User* Data_Base::Get_User(uint8_t ID)
{
	return users.user[ID];
}

Sensor* Data_Base::Get_Sensor(uint8_t ID)
{
	return sensors.sensor[ID];
}

Output* Data_Base::Get_Output(uint8_t ID)
{
	return outputs.output[ID];
}

char* Data_Base::Get_GSM(uint8_t ID)
{
	return gsm.Numbers[ID];
}

uint8_t Data_Base::Get_User_num()
{
	return users.NoU;
}

uint8_t Data_Base::Get_Sensor_num()
{
	return sensors.NoS;
}

uint8_t Data_Base::Get_Output_num()
{
	return outputs.NoO;
}

uint8_t Data_Base::Get_GSM_num()
{
	return gsm.NoP;
}

uint8_t Data_Base::Clear_All()
{
	err = 0;

	for(int i = 0;i<users.NoU-1;i++)
		free(users.user[i]);
	users.NoU = 0;

	for(int i = 0;i<sensors.NoS-1;i++)
		free(sensors.sensor[i]);
	sensors.NoS = 0;

	for(int i = 0;i<gsm.NoP-1;i++)
		free(gsm.Numbers[i]);
	gsm.NoP = 0;

	return err;
}

uint8_t Data_Base::Read_Users()
{
	err = 0;
	uint16_t pos, min = 0;
	char temp[5] = {0,0,0,0,0};

	char* buffor;

	if(!(buffor = (char*)Net.HTTP_RQS(Get_WEB_IP(),"?RQS=1&SRQS=1",1)))
		return 1;

	if(!(pos = Net.Find("--",buffor,0)))
		return 2;

	min = pos;

	for(int i = 0; pos != 0;)
	{
		min = pos;

		i = users.NoU;
		users.user[i] = new User;

		for(int c = 0;c<20;c++)
			users.user[i]->User_Name[c] = 0;

		for(int c = 0;c<10;c++)
			users.user[i]->Strefy[c] = 0;

		for(int c = 0;c<35;c++)
			users.user[i]->PIN[c] = 0;

		for(int c = 0;c<35;c++)
			users.user[i]->RFID_Num[c] = 0;

		pos += 1;

		for(int k = 0;k<20;k++)
			if(buffor[pos+k] != ';')
				users.user[i]->User_Name[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				users.user[i]->User_ID = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				users.user[i]->Access_lvl = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<10;k++)
			if(buffor[pos+k] != ';')
				users.user[i]->Strefy[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				break;
			}

		for(int k = 0;k<35;k++)
			if(buffor[pos+k] != ';')
				users.user[i]->PIN[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				break;
			}

		for(int k = 0;k<35;k++)
			if(buffor[pos+k] != ';')
				users.user[i]->RFID_Num[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				break;
			}

		users.NoU++;

		pos = Net.Find("--",buffor,min);
	}

	Net.TCP_Close();
	return users.NoU;
}

uint8_t Data_Base::Read_GSM()
{
	err = 0;
	uint16_t pos, min = 0;

	char *buffor;

	if(!(buffor = (char*)Net.HTTP_RQS(Get_WEB_IP(),"?RQS=1&SRQS=3",1)))
		return 1;

	if(!(pos = Net.Find("--",buffor,0)))
		return 2;

	min = pos;

	for(int i = 0; pos != 0;)
	{
		min = pos;

		i = gsm.NoP;
		gsm.Numbers[i] = new char[10];

		for(int c = 0;c<10;c++)
			gsm.Numbers[i][c] = 0;

		pos += 1;

		for(int k = 0;k<10;k++)
			if(buffor[pos+k] != ';')
				gsm.Numbers[i][k] = buffor[pos+k];
			else
				break;


		gsm.NoP++;

		pos = Net.Find("--",buffor,min);
	}
	Net.TCP_Close();
	return gsm.NoP;
}

uint8_t Data_Base::Read_Sensors()
{
	err = 0;
	uint16_t pos, min = 0;
	char temp[5] = {0,0,0,0,0};

	char* buffor;

	if(!(buffor = (char*)Net.HTTP_RQS(Get_WEB_IP(),"?RQS=1&SRQS=2",1)))
		return 1;

	if(!(pos = Net.Find("--",buffor,0)))
		return 2;

	min = pos;

	for(int i = 0; pos != 0;)
	{
		min = pos;

		i = sensors.NoS;
		sensors.sensor[i] = new Sensor;

		for(int c = 0;c<20;c++)
			sensors.sensor[i]->Sensor_Name[c] = 0;

		pos += 1;

		for(int k = 0;k<20;k++)
			if(buffor[pos+k] != ';')
				sensors.sensor[i]->Sensor_Name[k] =  buffor[pos+k];
			else{
				pos = pos + k + 1;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				sensors.sensor[i]->Sensor_ID = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				sensors.sensor[i]->Strefa = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				sensors.sensor[i]->Status = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<3;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				sensors.sensor[i]->IN = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		sensors.NoS++;

		pos = Net.Find("--",buffor,min);
	}
	Net.TCP_Close();
	return sensors.NoS;
}

uint8_t Data_Base::Read_Outputs()
{
	err = 0;
	uint16_t pos, min = 0;
	char temp[5] = {0,0,0,0,0};

	char* buffor;

	if(!(buffor = (char*)Net.HTTP_RQS(Get_WEB_IP(),"?RQS=1&SRQS=4",1)))
		return 1;

	if(!(pos = Net.Find("--",buffor,0)))
		return 2;


	min = pos;

	for(int i = 0; pos != 0;)
	{
		min = pos;

		i = outputs.NoO;
		outputs.output[i] = new Output;

		pos += 1;

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Output_ID = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Type = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Schedule[0] = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Schedule[1] = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Schedule[2] = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Schedule[3] = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Schedule[4] = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Schedule[5] = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Schedule[6] = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		for(int k = 0;k<5;k++)
			if(buffor[pos+k] != ';')
				temp[k] = buffor[pos+k];
			else{
				pos = pos + k + 1;
				outputs.output[i]->Schedule[7] = atoi(temp);
				temp[0] = 0;
				temp[1] = 0;
				temp[2] = 0;
				temp[3] = 0;
				temp[4] = 0;
				break;
			}

		outputs.NoO++;

		pos = Net.Find("--",buffor,min);
	}
	Net.TCP_Close();
	return outputs.NoO;
}

uint8_t Data_Base::Read_All()
{
	err = 0;

	for(int i = 0;i<2;i++)
		if((err = Read_Users()) != 1)
			break;
		else
			timer.sleep(500);
	timer.sleep(300);
	for(int i = 0;i<2;i++)
		if((err = Read_Sensors()) != 1)
			break;
		else
			timer.sleep(500);
	timer.sleep(300);
	for(int i = 0;i<2;i++)
		if((err = Read_GSM()) != 1)
			break;
		else
			timer.sleep(500);
	timer.sleep(300);
	for(int i = 0;i<2;i++)
		if((err = Read_Outputs()) != 1)
			break;
		else
			timer.sleep(500);

	return err;
}

uint8_t Data_Base::Add_User(User usernew, uint8_t flag)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	users.user[users.NoU] = new User;

	memset(users.user[users.NoU]->PIN,0,35);
	memset(users.user[users.NoU]->RFID_Num,0,35);
	memset(users.user[users.NoU]->Strefy,0,10);
	memset(users.user[users.NoU]->User_Name,0,20);

	usernew.User_ID = users.NoU+1;

	for(int c = 0;c<20 && usernew.User_Name[c] != 0;c++)
		users.user[users.NoU]->User_Name[c] = usernew.User_Name[c];
	users.user[users.NoU]->User_ID = usernew.User_ID;
	users.user[users.NoU]->Access_lvl = usernew.Access_lvl;
	for(int c = 0;c<10 && usernew.Strefy[c] != 0;c++)
		users.user[users.NoU]->Strefy[c] = usernew.Strefy[c];
	for(int c = 0;c<35 && usernew.PIN[c] != 0;c++)
		users.user[users.NoU]->PIN[c] = usernew.PIN[c];
	for(int c = 0;c<35 && usernew.RFID_Num[c] != 0;c++)
		users.user[users.NoU]->RFID_Num[c] = usernew.RFID_Num[c];

	users.NoU++;

	if(flag)
		FEE_Add_User(*(users.user[users.NoU-1]));

	sprintf(buffor,"?RQS=1&SRQS=1&UserName=%s&Access=%d&Strefy=%s&PIN=%s&RFID=%s&ID=%d&User_ID=%d", usernew.User_Name, usernew.Access_lvl, usernew.Strefy, usernew.PIN, usernew.RFID_Num, settings.Alarm_ID, usernew.User_ID);

//	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
//		return 1;

	return err;
}

uint8_t Data_Base::Add_Sensor(Sensor sensor, uint8_t flag)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	sensors.sensor[sensors.NoS] = new Sensor;

	memset(sensors.sensor[sensors.NoS]->Sensor_Name,0,20);

	sensor.Sensor_ID = sensors.NoS+1;

	for(int c = 0;c<20 && sensor.Sensor_Name[c] != 0;c++)
		sensors.sensor[sensors.NoS]->Sensor_Name[c] = sensor.Sensor_Name[c];
	sensors.sensor[sensors.NoS]->Sensor_ID = sensor.Sensor_ID;
	sensors.sensor[sensors.NoS]->Strefa = sensor.Strefa;
	sensors.sensor[sensors.NoS]->Status = sensor.Status;
	sensors.sensor[sensors.NoS]->IN = sensor.IN;

	sensors.NoS++;

	if(flag)
		FEE_Add_Sensor(*(sensors.sensor[sensors.NoS-1]));

	sprintf(buffor,"?RQS=1&SRQS=2&SensorName=%s&ID=%d&Strefa=%d&Status=%d&AID=%d&IN=%d", sensor.Sensor_Name, sensor.Sensor_ID, sensor.Strefa, sensor.Status, settings.Alarm_ID , sensor.IN);

//	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
//		return 1;

	return err;
}


uint8_t Data_Base::Add_Output(Output output, uint8_t flag)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	outputs.output[output.Output_ID-1] = new Output;

	memset(outputs.output[output.Output_ID-1]->Schedule,0,8);
//	output.Output_ID = outputs.NoO+1;

	outputs.output[output.Output_ID-1]->Output_ID = output.Output_ID;
	outputs.output[output.Output_ID-1]->Type = output.Type;
	outputs.output[output.Output_ID-1]->Status = 0;
	outputs.output[output.Output_ID-1]->Schedule[0] = output.Schedule[0];
	outputs.output[output.Output_ID-1]->Schedule[1] = output.Schedule[1];
	outputs.output[output.Output_ID-1]->Schedule[2] = output.Schedule[2];
	outputs.output[output.Output_ID-1]->Schedule[3] = output.Schedule[3];
	outputs.output[output.Output_ID-1]->Schedule[4] = output.Schedule[4];
	outputs.output[output.Output_ID-1]->Schedule[5] = output.Schedule[5];
	outputs.output[output.Output_ID-1]->Schedule[6] = output.Schedule[6];
	outputs.output[output.Output_ID-1]->Schedule[7] = output.Schedule[7];

	outputs.NoO++;

	if(flag)
		FEE_Add_Output(*(outputs.output[output.Output_ID-1]));

	sprintf(buffor,"?RQS=1&SRQS=5&ID=%d&AID=%d&Type=%d&S1_H=%d&S1_M=%d&E1_H=%d&E1_M=%d&S2_H=%d&S2_M=%d&E2_H=%d&E2_M=%d", output.Output_ID, settings.Alarm_ID, output.Type, output.Schedule[0], output.Schedule[1], output.Schedule[2] , output.Schedule[3], output.Schedule[4], output.Schedule[5], output.Schedule[6], output.Schedule[7]);

//	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
//		return 1;

	return err;
}

uint8_t Data_Base::Add_GSM(char* Num, char* Num_old, uint8_t flag)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	gsm.Numbers[gsm.NoP] = new char[10];

	memset(gsm.Numbers[gsm.NoP],0,10);

	for(int c = 0;c<10;c++)
		gsm.Numbers[gsm.NoP][c] = Num[c];

	gsm.NoP++;

	if(flag)
		FEE_Add_Number(gsm.NoP,gsm.Numbers[gsm.NoP-1]);

	sprintf(buffor,"?RQS=1&SRQS=3&Number=%s&Number_old=%s&ID=%d", Num, Num_old, settings.Alarm_ID);

//	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
//		return 1;

	return err;
}

uint8_t Data_Base::Update_User(User usernew, uint8_t ID)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	ID--;

	for(int c = 0;c<20 && usernew.User_Name[c] != 0;c++)
		users.user[ID]->User_Name[c] = usernew.User_Name[c];
	users.user[ID]->User_ID = ID+1;
	users.user[ID]->Access_lvl = usernew.Access_lvl;
	for(int c = 0;c<10 && usernew.Strefy[c] != 0;c++)
		users.user[ID]->Strefy[c] = usernew.Strefy[c];
	for(int c = 0;c<35 && usernew.PIN[c] != 0;c++)
		users.user[ID]->PIN[c] = usernew.PIN[c];
	for(int c = 0;c<35 && usernew.RFID_Num[c] != 0;c++)
		users.user[ID]->RFID_Num[c] = usernew.RFID_Num[c];

//	for(int c = 0;c<20;c++)
//		users.user[ID]->User_Name[c] = user.User_Name[c];
//	users.user[ID]->User_ID = user.User_ID;
//	users.user[ID]->Access_lvl = user.Access_lvl;
//	for(int c = 0;c<10;c++)
//		users.user[ID]->Strefy[c] = user.Strefy[c];
//	for(int c = 0;c<35;c++)
//		users.user[ID]->PIN[c] = user.PIN[c];
//	for(int c = 0;c<35;c++)
//		users.user[ID]->RFID_Num[c] = user.RFID_Num[c];

	FEE_Add_User(*(users.user[ID]));

	sprintf(buffor,"?RQS=2&SRQS=1&UserName=%s&Access=%d&Strefy=%s&PIN=%s&RFID=%s&ID=%d&User_ID=%d", usernew.User_Name, usernew.Access_lvl, usernew.Strefy, usernew.PIN, usernew.RFID_Num, settings.Alarm_ID, ID);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;

	return err;
}

uint8_t Data_Base::Update_Sensor(uint8_t ID,uint8_t w)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	sensors.sensor[ID]->Status = w;

	sprintf(buffor,"?RQS=2&SRQS=4&ID=%d&Status=%d&AID=%d", ID+1, w, settings.Alarm_ID);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;

	return err;
}

uint8_t Data_Base::Update_Sensor(Sensor sensor,uint8_t ID)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	ID--;

	for(int c = 0;c<20 && sensor.Sensor_Name[c] != 0;c++)
		sensors.sensor[ID]->Sensor_Name[c] = sensor.Sensor_Name[c];
	sensors.sensor[ID]->Sensor_ID = ID+1;;
	sensors.sensor[ID]->Strefa = sensor.Strefa;
	sensors.sensor[ID]->Status = sensor.Status;
	sensors.sensor[ID]->IN = sensor.IN;

	FEE_Add_Sensor(*(sensors.sensor[ID]));

	sprintf(buffor,"?RQS=2&SRQS=2&SensorName=%s&ID=%d&Strefa=%d&Status=%d&AID=%d&IN=%d", sensor.Sensor_Name, sensor.Sensor_ID, sensor.Strefa, sensor.Status, settings.Alarm_ID, sensor.IN);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;

	return err;
}

uint8_t Data_Base::Update_Output(uint8_t ID, uint8_t w)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	ID--;

	outputs.output[ID]->Status = w;

	sprintf(buffor,"?RQS=2&SRQS=6&ID=%d&Status=%d&AID=%d", ID+1, w, settings.Alarm_ID);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;

	return err;
}

uint8_t Data_Base::Update_Output(Output output, uint8_t ID)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	ID--;

	outputs.output[ID]->Output_ID = output.Output_ID;
	outputs.output[ID]->Type = output.Type;
	outputs.output[ID]->Schedule[0] = output.Schedule[0];
	outputs.output[ID]->Schedule[1] = output.Schedule[1];
	outputs.output[ID]->Schedule[2] = output.Schedule[2];
	outputs.output[ID]->Schedule[3] = output.Schedule[3];
	outputs.output[ID]->Schedule[4] = output.Schedule[4];
	outputs.output[ID]->Schedule[5] = output.Schedule[5];
	outputs.output[ID]->Schedule[6] = output.Schedule[6];
	outputs.output[ID]->Schedule[7] = output.Schedule[7];

	FEE_Add_Output(*(outputs.output[ID]));

	sprintf(buffor,"?RQS=2&SRQS=5&ID=%d&AID=%d&Type=%d&S1_H=%d&S1_M=%d&E1_H=%d&E1_M=%d&S2_H=%d&S2_M=%d&E2_H=%d&E2_M=%d", output.Output_ID, settings.Alarm_ID, output.Type, output.Schedule[0], output.Schedule[1], output.Schedule[2] , output.Schedule[3], output.Schedule[4], output.Schedule[5], output.Schedule[6], output.Schedule[7]);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;

	return err;
}

uint8_t Data_Base::Update_GSM(char* Num, char* Num_old)
{
	err = 0;
	int ID = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	for(ID = 0; ID<gsm.NoP;ID++){
		for(int u = 0;gsm.Numbers[ID][u] != 0;u++)
			if(gsm.Numbers[ID][u] == Num_old[u])
			{
				if(Num_old[u+1] == 0)
				{
					err=9;
					break;
				}
			}
			else
				break;
		if(err == 9)
			break;
	}
	if(err == 9){
		err = 0;

	for(int c = 0;c<10;c++)
		gsm.Numbers[ID][c] = Num[c];

	FEE_Add_Number(ID+1, Num);

	sprintf(buffor,"?RQS=2&SRQS=3&Number=%s&Number_old=%s&ID=%d", Num, Num_old, settings.Alarm_ID);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;
	}
	return err;
}


uint8_t Data_Base::Del_User(uint8_t ID)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	if(users.NoU>1){
		free(users.user[ID-1]);
		FEE_Delete_User(ID);
		for(int c = ID-1;c<users.NoU-1;c++){
			users.user[c] = users.user[c+1];
			FEE_Delete_User(users.user[c]->User_ID);
			users.user[c]->User_ID--;
			FEE_Add_User(*(users.user[c]));
		}
		users.user[users.NoU-1] = 0;
	}
	else if(users.NoU == 1){
		free(users.user[0]);
		FEE_Delete_User(1);
		users.user[0] = 0;
	}
	users.NoU--;



	sprintf(buffor,"?RQS=3&SRQS=1&ID=%d", ID);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;

	return err;
}

uint8_t Data_Base::Del_Sensor(uint8_t ID)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	if(sensors.NoS>1){
		free(sensors.sensor[ID-1]);
		FEE_Delete_Sensor(ID);
		for(int c = ID-1;c<sensors.NoS-1;c++){
			sensors.sensor[c] = sensors.sensor[c+1];
			FEE_Delete_Sensor(sensors.sensor[c]->Sensor_ID);
			sensors.sensor[c]->Sensor_ID--;
			FEE_Add_Sensor(*(sensors.sensor[c]));
		}
		sensors.sensor[sensors.NoS-1] = 0;
	}
	else if(sensors.NoS == 1){
		free(sensors.sensor[0]);
		FEE_Delete_Sensor(1);
		sensors.sensor[0] = 0;
	}
	sensors.NoS--;

	sprintf(buffor,"?RQS=3&SRQS=2&ID=%d", ID);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;

	return err;
}

uint8_t Data_Base::Del_Output(uint8_t ID)
{
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

	if(outputs.output[ID-1] != 0){
		free(outputs.output[ID-1]);
		FEE_Delete_Output(ID);
	}

	outputs.NoO--;

	sprintf(buffor,"?RQS=3&SRQS=4&ID=%d", ID);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;

	return err;
}

uint8_t Data_Base::Del_GSM(char* Number)
{
	int ID = 0;
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

//	gsm.Numbers[gsm.NoP] = new char[10];

	for(ID = 0; ID<gsm.NoP;ID++){
		for(int u = 0;gsm.Numbers[ID][u] != 0;u++)
			if(gsm.Numbers[ID][u] == Number[u])
			{
				if(Number[u+1] == 0)
				{
					err=9;
					break;
				}
			}
			else
				break;
		if(err == 9)
			break;
	}
	if(err == 9){
		err = 0;
	if(gsm.NoP>1){
		free(gsm.Numbers[ID]);
		FEE_Delete_Number(ID+1);
		for(int c = ID;c<gsm.NoP-1;c++){
			gsm.Numbers[c] = gsm.Numbers[c+1];
			FEE_Delete_Number(c+2);
			FEE_Add_Number(c+1,gsm.Numbers[c]);
		}
		gsm.Numbers[gsm.NoP-1] = 0;
	}
	else if(gsm.NoP == 1){
		free(gsm.Numbers[0]);
		FEE_Delete_Number(1);
		gsm.Numbers[0] = 0;
	}
	gsm.NoP--;

	sprintf(buffor,"?RQS=3&SRQS=3&Number=%s", Number);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;
	}
	return err;
}

uint8_t Data_Base::Del_GSM(uint8_t ID)
{
	char* Number = 0;
	err = 0;

	char buffor[150];
	for(int i = 0;i<150;i++)
		buffor[i] = 0;

//	gsm.Numbers[gsm.NoP] = new char[10];
	ID--;

	Number = Get_GSM(ID);

	if(Number != 0){
		err = 0;
	if(gsm.NoP>1){
		free(gsm.Numbers[ID]);
		FEE_Delete_Number(ID+1);
		for(int c = ID;c<gsm.NoP-1;c++){
			gsm.Numbers[c] = gsm.Numbers[c+1];
			FEE_Delete_Number(c+2);
			FEE_Add_Number(c+1,gsm.Numbers[c]);
		}
		gsm.Numbers[gsm.NoP-1] = 0;
	}
	else if(gsm.NoP == 1){
		free(gsm.Numbers[0]);
		FEE_Delete_Number(1);
		gsm.Numbers[0] = 0;
	}
	gsm.NoP--;

	sprintf(buffor,"?RQS=3&SRQS=3&Number=%s", Number);

	if(!(Net.HTTP_RQS(Get_WEB_IP(),buffor,0)))
		return 1;
	}
	return err;
}

uint8_t Data_Base::RAM_to_DB()
{
	err = 0;

	return err;
}

uint8_t Data_Base::Check_change()
{
	err = 0;

	return err;
}
