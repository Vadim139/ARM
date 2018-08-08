/*
 * NET.cpp
 *
 *  Created on: 25 lis 2017
 *      Author: Vadim
 */

#include "NET.h"

extern Data_Base Base;
extern Timer timer;

NET::NET() {

	err = 0;
	TCP = 0;

	WIFI_connected = false;
	GSM_Connected = false;
}

NET::~NET() {

}

bool NET::IsWIFI(uint8_t newv)
{
	if(newv == 1)
		WIFI_connected = true;
	else if(newv == 0)
		WIFI_connected = false;
	return WIFI_connected;
}

bool NET::IsGSM(uint8_t newv)
{
	if(newv == 1)
		GSM_Connected = true;
	else if(newv == 0)
		GSM_Connected = false;
	return GSM_Connected;
}

uint8_t NET::Connect() {
	uint8_t s = Base.Get_Net_s();
	err = 0;
	if (Base.Is_Net_on()) {
		if (s == 1 || s == 3 || s == 4){
			if (!IsWIFI())
				for (int i = 0; i < 2; i++) {
					err = ESP.WIFI_Connect(Base.Get_WIFIName(),	Base.Get_WIFIPass());
					if (err == 0){
						WIFI_connected = true;
						break;
					}
				}
			else
				err = 1;
		}
		if (s == 2 || s == 3 || s == 4){
			if(s == 2)
				timer.sleep(3000);
			if (!IsGSM())
				for (int i = 0; i < 2; i++) {
					err = SIM.GSM_Connect(1);
					if (err == 0)
					{
						GSM_Connected = true;
						break;
					}
				}
			else
				err = 1;
		}
	}
	return err;
}

void NET::Connect_WIFI() {
	if(!ESP.WIFI_Connect(Base.Get_WIFIName(), Base.Get_WIFIPass()))
		WIFI_connected = true;
}

void NET::Connect_GSM() {
	if(!SIM.GSM_Connect(1))
		GSM_Connected = true;
}

uint8_t NET::Get_config() {
	uint8_t s = Base.Get_Net_s();
	err = 0;

	if (Base.Is_Net_on()) {
		if (s == 1 || s == 3 || s == 4){
			if (IsWIFI())
				for (int i = 0; i < 2; i++) {
					err = ESP.WIFI_GetConfig();
					if (err == 0)
						break;
				}
			else
				err = 1;
		}
		if (s == 2 || s == 3 || s == 4){
			if (IsGSM())
				for (int i = 0; i < 2; i++) {
					err = SIM.GSM_GetConfig();
					if (err == 0)
						break;
				}
			else
				err = 1;
		}
	}

	return err;
}

uint8_t NET::TCP_Start(char* IP, char* Port) {
	uint8_t s = Base.Get_Net_s();
	err = 0;

	if (Base.Is_Net_on()) {
		if ((s == 1 || s == 3) && TCP == 0) {
			if (IsWIFI())
				for (int i = 0; i < 2; i++) {
					err = ESP.WIFI_TCP_Start(IP, Port);
					if (err == 0) {
						TCP = 1;
						break;
					}
				}
			else
				err = 1;
			if (err && s == 3){
				if (IsGSM())
					for (int i = 0; i < 2; i++) {
						err = SIM.GSM_TCP_Start(IP, Port);
						if (err == 0) {
							TCP = 2;
							break;
						}
					}
				else
					err = 1;
			}
		}
		if ((s == 2 || s == 4) && TCP == 0) {
			if (IsGSM())
				for (int i = 0; i < 2; i++) {
					err = SIM.GSM_TCP_Start(IP, Port);
					if (err == 0) {
						TCP = 2;
						break;
					}
				}
			else
				err = 1;
			if (err && s == 4){
				if (IsWIFI())
					for (int i = 0; i < 2; i++) {
						err = ESP.WIFI_TCP_Start(IP, Port);
						if (err == 0) {
							TCP = 1;
							break;
						}
					}
				else
					err = 1;
			}
		}
	}
	return err;
}

uint8_t NET::TCP_Send(char* str) {
	err = 0;

	if (TCP == 1){
		if (IsWIFI())
			err = ESP.WIFI_TCP_Send(str);
		else
			err = 1;
	}
	if (TCP == 2){
		if (IsGSM())
			err = SIM.GSM_TCP_Send(str);
		else
			err = 1;
	}

	return err;
}

uint8_t NET::TMode_ON() {
	uint8_t s = Base.Get_Net_s();
	err = 0;

	if (s == 1 || s == 3){
		if (IsWIFI())
			err = ESP.WIFI_TMode_On();
		else
			err = 1;
	}
	if (s == 2 || s == 4){
		if (IsGSM())
			err = SIM.GSM_TMode_On();
		else
			err = 1;
	}

	return err;
}

uint8_t NET::TMode_OFF() {
	uint8_t s = Base.Get_Net_s();
	err = 0;

	if (s == 1 || s == 3){
		if (IsWIFI())
			err = ESP.WIFI_TMode_Off();
		else
			err = 1;
	}
	if (s == 2 || s == 4){
		if (IsGSM())
			err = SIM.GSM_TMode_Off();
		else
			err = 1;
	}

	return err;
}

uint8_t NET::TCP_Close(uint8_t f) {
	err = 0;

	if (TCP == 1){
		if (IsWIFI())
			err = ESP.WIFI_TCP_Close(f);
		else
			err = 1;
	}
	if (TCP == 2){
		if (IsGSM())
			err = SIM.GSM_TCP_Close(f);
		else
			err = 1;
	}
	TCP = 0;
	return err;
}

uint8_t NET::Get_DataTime(char* DataTime) {
	uint8_t s = Base.Get_Net_s();
	err = 0;

	if (Base.Is_Net_on()) {
		if ((s == 1 || s == 3) && TCP == 0) {
			if (IsWIFI())
				for (int i = 0; i < 2; i++) {
					err = ESP.WIFI_Get_DataTime(DataTime);
					if (err == 0) {
						TCP = 1;
						break;
					}
				}
			else
				err = 1;
			if (err && s == 3){
				if (IsGSM())
					for (int i = 0; i < 2; i++) {
						err = SIM.GSM_Get_DataTime(DataTime);
						if (err == 0) {
							TCP = 2;
							break;
						}
					}
				else
					err = 1;
			}
		}
		if ((s == 2 || s == 4) && TCP == 0) {
			if (IsGSM())
				for (int i = 0; i < 2; i++) {
					err = SIM.GSM_Get_DataTime(DataTime);
					if (err == 0) {
						TCP = 2;
						break;
					}
				}
			else
				err = 1;
			if (err && s == 4){
				if (IsWIFI())
					for (int i = 0; i < 2; i++) {
						err = ESP.WIFI_Get_DataTime(DataTime);
						if (err == 0) {
							TCP = 1;
							break;
						}
					}
				else
					err = 1;
			}
		}
	}
	TCP = 0;
	return err;
}

volatile char* NET::HTTP_RQS(char* IP, char* Request, uint8_t dir) {
	uint8_t s = Base.Get_Net_s();
	volatile char *Rec_Buf = 0;

	if (Base.Is_Net_on()) {
		if ((s == 1 || s == 3) && (IsWIFI())) {
			for (int i = 0; i < 3; i++) {
				Rec_Buf = ESP.WIFI_HTTP_RQS(IP, Request, dir);
				if (Rec_Buf != 0) {
					break;
				}
			}

			if (!Rec_Buf && s == 3) {
				if (IsGSM()) {
					for (int i = 0; i < 2; i++) {
						Rec_Buf = SIM.GSM_HTTP_RQS(IP, Request, dir);
						timer.sleep(100);
						if (Rec_Buf != 0) {
							break;
						}

					}
				} else
					err = 1;
			}

		} else if ((s == 2 || s == 4) && (IsGSM())) {
			for (int i = 0; i < 2; i++) {
				Rec_Buf = SIM.GSM_HTTP_RQS(IP, Request, dir);
				if (Rec_Buf != 0) {
					break;
				}
			}

			if (!Rec_Buf && s == 4) {
				if (IsWIFI()) {
					for (int i = 0; i < 3; i++) {
						Rec_Buf = ESP.WIFI_HTTP_RQS(IP, Request, dir);
						timer.sleep(100);
						if (Rec_Buf != 0) {
							break;
						}
					}
				} else
					err = 1;
			}
		}
	}

	timer.sleep(200);
	if (Rec_Buf == 0)
		return 0;
	else
		return Rec_Buf;
}

uint16_t NET::Find(char* str, char* buffer, uint16_t min) {
	int len = strlen(str);
	for (int i = 0; i < 1000;) {
		for (int j = 0; j < len;) {
			if (buffer[i] == str[j] && i > min) {
				if (i == 1000)
					break;
				i++;
				j++;
				if (j == len)
					return i - len + 1;
			} else {
				if (i == 1000)
					break;
				i++;
				j = 0;
			}
		}

	}
	return 0;
}
