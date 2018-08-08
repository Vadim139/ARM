/*
 * EE_emu.cpp
 *
 *  Created on: 6 sty 2018
 *      Author: Vadim
 */


#include <stdio.h>
#include <string.h>
//#include "stm32f10x_usart.h"
#include "EE_memory.h"
/*****************************************************************************
 * Allows to use the internal flash to store non volatile data. To initialize
 * the functionality use the FEE_Init() function. Be sure that by reprogramming
 * of the controller just affected pages will be deleted. In other case the non
 * volatile data will be lost.
******************************************************************************/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

extern Data_Base Base;

uint8_t DataBuf[FEE_PAGE_SIZE];
uint8_t DataBuf_ext[512];

uint16_t Users_addr[10];
uint16_t Sensors_addr[10];
uint16_t Numbers_addr[10];
uint16_t Outputs_addr[4];

/*****************************************************************************
*  Delete Flash Space used for user Data, deletes the whole space between
*  RW_PAGE_BASE_ADDRESS and the last uC Flash Page
******************************************************************************/
uint16_t
FEE_Init(void) {
	// unlock flash
	FLASH_Unlock();

	// Clear Flags
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);

	return FEE_DENSITY_BYTES;
}

void FEE_ReadAll() {
	uint8_t mem_byte = 0, temp = 0;

	char data[36];
	Output out;
	Sensor sen;
	User user;

	memset(data, 0, 36);

	// WIFI name
	if (FEE_ReadDataByte(WIFI_NAME_ADDR) != 0x0)
		for (int i = 0; i < 20; i++) {
			if ((mem_byte = FEE_ReadDataByte(WIFI_NAME_ADDR + i)) != 0xFF)
				data[i] = mem_byte;
			else {
				if (data[0] != 0)
					Base.Change_WIFIName(data);
				else
					Base.Change_WIFIName(WIFINAME);
				memset(data, 0, 36);
				break;
			}
		}

	// WIFI pass
	if (FEE_ReadDataByte(WIFI_PASS_ADDR) != 0x0)
		for (int i = 0; i < 20; i++) {
			if ((mem_byte = FEE_ReadDataByte(WIFI_PASS_ADDR + i)) != 0xFF)
				data[i] = mem_byte;
			else {
				if (data[0] != 0)
					Base.Change_WIFIPass(data);
				else
					Base.Change_WIFIPass(WIFIPASS);

				memset(data, 0, 36);
				break;
			}
		}

	// Net on
	if ((mem_byte = FEE_ReadDataByte(NET_ON_ADDR)) != 0xFF)
		Base.Change_Net_on(mem_byte);

	// Net prefer
	if (FEE_ReadDataByte(NET_PREFER_ADDR) != 0x0)
		if ((mem_byte = FEE_ReadDataByte(NET_PREFER_ADDR)) != 0xFF)
			Base.Change_Net_s(mem_byte);

	// Output number
	if (FEE_ReadDataByte(OUT_NUM_ADDR) != 0x0)
		if ((mem_byte = FEE_ReadDataByte(OUT_NUM_ADDR)) != 0xFF)
			temp = mem_byte;

	// Outputs
	for (int i = 0; i < 4; i++) {

//		if (FEE_ReadDataByte(Outputs_addr[i]) != 0x0) {
			if ((mem_byte = FEE_ReadDataByte(Outputs_addr[i])) != 0xFF)
				out.Output_ID = mem_byte;
			else
				break;

			if ((mem_byte = FEE_ReadDataByte(Outputs_addr[i] + 1)) != 0xFF)
				out.Type = mem_byte;
			else
				break;

			out.Status = 0;

			for (int j = 0; j < 8; j++) {
				if ((mem_byte = FEE_ReadDataByte(Outputs_addr[i] + 2 + j))
						!= 0xFF)
					out.Schedule[j] = mem_byte;
				else
					break;
			}
			if(out.Output_ID != 0)
				Base.Add_Output(out,0);
//		}
	}

	// User number
	if (FEE_ReadDataByte(USERS_NUM_ADDR) != 0x0)
		if ((mem_byte = FEE_ReadDataByte(USERS_NUM_ADDR)) != 0xFF)
			temp = mem_byte;

	// Users
	for (int i = 0; i < 10; i++) {

		if (FEE_ReadDataByte(Users_addr[i]) != 0x0) {
			for (int j = 0; j < 20; j++) {
				if ((mem_byte = FEE_ReadDataByte(Users_addr[i] + j)) != 0xFF)
					user.User_Name[j] = mem_byte;
				else
					break;
			}

			if ((mem_byte = FEE_ReadDataByte(Users_addr[i] + 20)) != 0xFF)
				user.User_ID = mem_byte;
			else
				break;

			if ((mem_byte = FEE_ReadDataByte(Users_addr[i] + 21)) != 0xFF)
				user.Access_lvl = mem_byte;
			else
				break;

			for (int j = 0; j < 10; j++) {
				if ((mem_byte = FEE_ReadDataByte(Users_addr[i] + 22 + j))
						!= 0xFF)
					user.Strefy[j] = mem_byte;
				else
					break;
			}

			for (int j = 0; j < 35; j++) {
				if ((mem_byte = FEE_ReadDataByte(Users_addr[i] + 32 + j))
						!= 0xFF)
					user.RFID_Num[j] = mem_byte;
				else
					break;
			}

			for (int j = 0; j < 35; j++) {
				if ((mem_byte = FEE_ReadDataByte(Users_addr[i] + 67 + j))
						!= 0xFF)
					user.PIN[j] = mem_byte;
				else
					break;
			}
			Base.Add_User(user,0);
		}

	}

	// Sensor number
	if (FEE_ReadDataByte(SENSORS_NUM_ADDR) != 0x0)
		if ((mem_byte = FEE_ReadDataByte(SENSORS_NUM_ADDR)) != 0xFF)
			temp = mem_byte;

	// Sensors
	for (int i = 0; i < 10; i++) {

		if (FEE_ReadDataByte(Sensors_addr[i]) != 0x0) {
			for (int j = 0; j < 20; j++) {
				if ((mem_byte = FEE_ReadDataByte(Sensors_addr[i] + j)) != 0xFF)
					sen.Sensor_Name[j] = mem_byte;
				else
					break;
			}

			if ((mem_byte = FEE_ReadDataByte(Sensors_addr[i] + 20)) != 0xFF)
				sen.Sensor_ID = mem_byte;
			else
				break;

			if ((mem_byte = FEE_ReadDataByte(Sensors_addr[i] + 21)) != 0xFF)
				sen.Strefa = mem_byte;
			else
				break;

			if ((mem_byte = FEE_ReadDataByte(Sensors_addr[i] + 22)) != 0xFF)
				sen.IN = mem_byte;
			else
				break;

			sen.Status = 0;

			Base.Add_Sensor(sen,0);
		}
	}

	// Gsm number
	if (FEE_ReadDataByte(GSM_NUM_ADDR) != 0x0)
		if ((mem_byte = FEE_ReadDataByte(GSM_NUM_ADDR)) != 0xFF)
			temp = mem_byte;

	memset(data, 0, 36);

	// Numbers
	for (int i = 0; i < 10; i++) {

		if (FEE_ReadDataByte(Numbers_addr[i]) != 0x0) {
			for (int j = 0; j < 10; j++) {
				if ((mem_byte = FEE_ReadDataByte(Numbers_addr[i] + j)) != 0xFF)
					data[j] = mem_byte;
				else
					break;
			}
			if (data[0] != 0){
				Base.Add_GSM(data, "0",0);
				memset(data, 0, 36);
			}
		}
	}

}


void FEE_Add_User(User user)
{
	uint8_t temp;
	uint16_t offset = 0;
	memset(DataBuf_ext,0,FEE_PAGE_SIZE);
//	uint8_t data[USER_SIZE];
//	memset(data,0,USER_SIZE);


	FEE_Delete_User(user.User_ID);

	memcpy(DataBuf_ext,user.User_Name,20);
	offset += 20;

	temp = user.User_ID;
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;

	temp = user.Access_lvl;
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;

	memcpy(DataBuf_ext + offset,user.Strefy,10);
	offset += 10;

	memcpy(DataBuf_ext + offset,user.RFID_Num,35);
	offset += 35;

	memcpy(DataBuf_ext + offset,user.PIN,35);
	offset += 35;

	FEE_WriteData(Users_addr[user.User_ID-1],DataBuf_ext,offset);
}

void FEE_Add_Sensor(Sensor sensor)
{

	uint8_t temp;
	uint16_t offset = 0;
	memset(DataBuf_ext,0,FEE_PAGE_SIZE);
//	uint8_t data[USER_SIZE];
//	memset(data,0,USER_SIZE);


	FEE_Delete_Sensor(sensor.Sensor_ID);

	memcpy(DataBuf_ext,sensor.Sensor_Name,20);
	offset += 20;

	temp = sensor.Sensor_ID;
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;

	temp = sensor.Strefa;
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;

	temp = sensor.IN;
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;

	FEE_WriteData(Sensors_addr[sensor.Sensor_ID-1],DataBuf_ext,offset);
}

void FEE_Add_Output(Output out)
{
	uint8_t temp;
	uint16_t offset = 0;
	memset(DataBuf_ext,0,FEE_PAGE_SIZE);
//	uint8_t data[USER_SIZE];
//	memset(data,0,USER_SIZE);


	FEE_Delete_Output(out.Output_ID);

	temp = out.Output_ID;
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;

	temp = out.Type;
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;

	memcpy(DataBuf_ext + offset,out.Schedule,8);
	offset += 8;

	FEE_WriteData(Outputs_addr[out.Output_ID-1],DataBuf_ext,offset);


}

void FEE_Add_Number(int ID, char* num)
{

	memset(DataBuf_ext,0,FEE_PAGE_SIZE);

	FEE_Delete_Number(ID);

	memcpy(DataBuf_ext,num,10);

	FEE_WriteData(Numbers_addr[ID-1],DataBuf_ext,10);

}

void FEE_Delete_User(uint8_t ID)
{
	uint8_t zeros[USER_SIZE];
	memset(zeros,0,USER_SIZE);
//
	FEE_WriteData(Users_addr[ID-1],zeros,USER_SIZE);
//	for(int i = 0; i< USER_SIZE; i++)
//		FEE_WriteDataByte(Users_addr[ID-1]+i,0);
}

void FEE_Delete_Sensor(uint8_t ID)
{
	uint8_t zeros[SENSOR_SIZE];
	memset(zeros,0,SENSOR_SIZE);
//
	FEE_WriteData(Sensors_addr[ID-1],zeros,SENSOR_SIZE);
//	for(int i = 0; i< SENSOR_SIZE; i++)
//		FEE_WriteDataByte(Sensors_addr[ID-1]+i,0);
}

void FEE_Delete_Output(uint8_t ID)
{
	uint8_t zeros[OUTPUT_SIZE];
	memset(zeros,0,OUTPUT_SIZE);
//
	FEE_WriteData(Outputs_addr[ID-1],zeros,OUTPUT_SIZE);
//	for(int i = 0; i< OUTPUT_SIZE; i++)
//		FEE_WriteDataByte(Outputs_addr[ID-1]+i,0);
}

void FEE_Delete_Number(int ID)
{
	uint8_t zeros[NUMBERS_SIZE];
	memset(zeros,0,NUMBERS_SIZE);
//
	FEE_WriteData(Numbers_addr[ID-1],zeros,NUMBERS_SIZE);
//	for(int i = 0; i< NUMBERS_SIZE; i++)
//		FEE_WriteDataByte(Numbers_addr[ID-1]+i,0);
}

void FEE_Write_Settings()
{
	uint8_t temp;
	uint16_t offset = 0;
	memset(DataBuf_ext,0,FEE_PAGE_SIZE);

	//WIFI name
	memcpy(DataBuf_ext,Base.Get_WIFIName(),19);
	offset += 19;

	//WIFI pass
	memcpy(DataBuf_ext + offset,Base.Get_WIFIPass(),20);
	offset += 20;

	//Net on
	temp = Base.Is_Net_on();
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;

	//Net prefer
	temp = Base.Get_Net_s();
	memcpy(DataBuf_ext + offset,&temp,1);
	offset += 1;
//	FEE_WriteDataByte(NET_PREFER_ADDR,Base.Get_Net_s());

	FEE_WriteData(WIFI_NAME_ADDR,DataBuf_ext,offset);
}

/*****************************************************************************
*  Erase the whole reserved Flash Space used for user Data
******************************************************************************/
void
FEE_Erase (void) {

	int page_num = 0;

	// delete all pages from specified start page to the last page
	do {
		FLASH_ErasePage(FEE_PAGE0_BASE_ADDRESS + (page_num * FEE_PAGE_SIZE));
		page_num++;
	} while (page_num < FEE_DENSITY_PAGES);
}
/*****************************************************************************
*  Writes once data byte to flash on specified address. If a byte is already
*  written, the whole page must be copied to a buffer, the byte changed and
*  the manipulated buffer written after PageErase.
*******************************************************************************/
uint16_t
FEE_WriteDataByte (uint16_t Address, uint8_t DataByte) {

	FLASH_Status FlashStatus = FLASH_COMPLETE;

	uint32_t page;
	int i;

	// exit if desired address is above the limit (e.G. under 2048 Bytes for 4 pages)
	if (Address > FEE_DENSITY_BYTES) {
		return 0;
	}

	// calculate which page is affected (Pagenum1/Pagenum2...PagenumN)
//	page = (FEE_PAGE0_BASE_ADDRESS + FEE_ADDR_OFFSET(Address)) & 0x00000FFF;

//	if (page % FEE_PAGE_SIZE) page = 0;//page + FEE_PAGE_SIZE;
//	page = (page / FEE_PAGE_SIZE); //- 1;
	page = FEE_ADDR_OFFSET(Address) / FEE_PAGE_SIZE;


	if(page>0)
		Address -= (512*page);
	// if current data is 0xFF, the byte is empty, just overwrite with the new one
	if ((*(uint16_t*)(FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE) + FEE_ADDR_OFFSET(Address))) == FEE_EMPTY_WORD) {

		FlashStatus = FLASH_ProgramHalfWord(FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE) + FEE_ADDR_OFFSET(Address), (uint16_t)(0x00FF & DataByte));
	}
	else {

		// Copy Page to a buffer
		memcpy(DataBuf, (uint8_t*)FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE), FEE_PAGE_SIZE); // !!! Calculate base address for the desired page

		// check if new data is differ to current data, return if not, proceed if yes
		if (DataByte == *(uint8_t*)(FEE_PAGE0_BASE_ADDRESS + FEE_ADDR_OFFSET(Address))) {
			return 0;
		}

		// manipulate desired data byte in temp data array if new byte is differ to the current
		DataBuf[FEE_ADDR_OFFSET(Address)] = DataByte;

		//Erase Page
		FlashStatus = FLASH_ErasePage(FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE));

		// Write new data (whole page) to flash if data has beed changed
		for(i = 0; i < (FEE_PAGE_SIZE / 2); i++) {
			if ((uint16_t)(0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]) != 0xFFFF) {
				FlashStatus = FLASH_ProgramHalfWord((FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE)) + (i * 2), (uint16_t)(0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]));
			}
		}

	}
	return FlashStatus;
}

uint16_t FEE_WriteData(uint16_t Address, uint8_t *Data, uint16_t size) {

	FLASH_Status FlashStatus = FLASH_COMPLETE;

	uint32_t page;
	uint16_t i;

	// exit if desired address is above the limit (e.G. under 2048 Bytes for 4 pages)
	if (Address > FEE_DENSITY_BYTES) {
		return 0;
	}

	// calculate which page is affected (Pagenum1/Pagenum2...PagenumN)
//	page = (FEE_PAGE0_BASE_ADDRESS + FEE_ADDR_OFFSET(Address)) & 0x00000FFF;

//	if (page % FEE_PAGE_SIZE) page = 0;//page + FEE_PAGE_SIZE;
//	page = (page / FEE_PAGE_SIZE); //- 1;
	page = FEE_ADDR_OFFSET(Address) / FEE_PAGE_SIZE;

	if (page > 0)
		Address -= (512 * page);

	// Copy Page to a buffer
	memcpy(DataBuf, (uint8_t*) FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE),	FEE_PAGE_SIZE); // !!! Calculate base address for the desired page

	if ((512 - Address) >= size) {
		for(uint16_t i = 0;(i/2)<size;i = i+2)
			DataBuf[FEE_ADDR_OFFSET(Address)+i] = Data[i/2];
//		memcpy(DataBuf, Data, size);
		// manipulate desired data byte in temp data array if new byte is differ to the current
//		DataBuf[FEE_ADDR_OFFSET(Address)] = DataByte;

		//Erase Page
		FlashStatus = FLASH_ErasePage(FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE));

		// Write new data (whole page) to flash if data has beed changed
		for (i = 0; i < (FEE_PAGE_SIZE / 2); i++) {
			if ((uint16_t) (0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]) != 0xFFFF)
			{
				FlashStatus = FLASH_ProgramHalfWord((FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE)) + (i * 2),(uint16_t) (0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]));
			}
		}

	} else if ((512 - Address) < size) {
		for(uint16_t i = 0;(i/2)<512 - Address;i = i+2)
			DataBuf[FEE_ADDR_OFFSET(Address)+i] = Data[i/2];
//		memcpy(DataBuf, Data, 512 - Address);
		// manipulate desired data byte in temp data array if new byte is differ to the current
//		DataBuf[FEE_ADDR_OFFSET(Address)] = DataByte;

		//Erase Page
		FlashStatus = FLASH_ErasePage(
				FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE));

		// Write new data (whole page) to flash if data has beed changed
		for (i = 0; i < (FEE_PAGE_SIZE / 2); i++) {
			if ((uint16_t) (0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]) != 0xFFFF) {
				FlashStatus = FLASH_ProgramHalfWord((FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE))+ (i * 2),	(uint16_t) (0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]));
			}
		}

		size -= (512 - Address);
		Data = Data + (512 - Address);
		page++;

		memcpy(DataBuf, (uint8_t*) FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE),	FEE_PAGE_SIZE);

		for(uint16_t i = 0;(i/2)<size;i = i+2)
			DataBuf[i] = Data[i/2];

		//Erase Page
		FlashStatus = FLASH_ErasePage(FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE));

		// Write new data (whole page) to flash if data has beed changed
		for (i = 0; i < (FEE_PAGE_SIZE / 2); i++) {
			if ((uint16_t) (0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]) != 0xFFFF) {
				FlashStatus = FLASH_ProgramHalfWord((FEE_PAGE0_BASE_ADDRESS + (page * FEE_PAGE_SIZE))+ (i * 2),	(uint16_t) (0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]));
			}
		}
	}

	return FlashStatus;
}

//uint16_t
//FEE_WriteDataByte (uint16_t Address, uint8_t DataByte) {
//
//	uint32_t *dest_addr;
//
//	if(Address<1024)
//		dest_addr = (uint32_t *) FEE_PAGE0_BASE_ADDRESS;
//	else{
//		dest_addr = (uint32_t *) FEE_PAGE1_BASE_ADDRESS;
//		Address -= 1024;
//	}
//
//	FLASH_Status FlashStatus = FLASH_COMPLETE;
//
//	uint32_t page = 0;
//	int i;
////
////	// exit if desired address is above the limit (e.G. under 2048 Bytes for 4 pages)
////	if (Address > FEE_DENSITY_BYTES) {
////		return 0;
////	}
//
////	// calculate which page is affected (Pagenum1/Pagenum2...PagenumN)
////	page = (FEE_PAGE_BASE_ADDRESS + FEE_ADDR_OFFSET(Address)) & 0x00000FFF;
////
////	if (page % FEE_PAGE_SIZE) page = page + FEE_PAGE_SIZE;
////	page = (page / FEE_PAGE_SIZE) - 1;
//
//	// if current data is 0xFF, the byte is empty, just overwrite with the new one
//	if ((*(uint32_t*)(dest_addr + FEE_ADDR_OFFSET(Address))) == FEE_EMPTY_WORD) {
//
//		FlashStatus = FLASH_ProgramHalfWord((uint32_t)dest_addr + FEE_ADDR_OFFSET(Address), (uint16_t)(0x00FF & DataByte));
//	}
//	else {
//
//		// Copy Page to a buffer
//		memcpy(DataBuf, (uint16_t*)dest_addr + (page * FEE_PAGE_SIZE), FEE_PAGE_SIZE); // !!! Calculate base address for the desired page
//
//		// check if new data is differ to current data, return if not, proceed if yes
//		if (DataByte == *(uint16_t*)(dest_addr + FEE_ADDR_OFFSET(Address))) {
//			return 0;
//		}
//
//		// manipulate desired data byte in temp data array if new byte is differ to the current
//		DataBuf[FEE_ADDR_OFFSET(Address)] = DataByte;
//
//		//Erase Page
//		FlashStatus = FLASH_ErasePage((uint32_t)dest_addr + page);
//
//		// Write new data (whole page) to flash if data has beed changed
//		for(i = 0; i < (FEE_PAGE_SIZE / 2); i++) {
//			if ((uint16_t)(0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]) != 0xFFFF) {
//				FlashStatus = FLASH_ProgramHalfWord(((uint32_t)dest_addr + (page * FEE_PAGE_SIZE)) + (i * 2), (uint16_t)(0xFF00 | DataBuf[FEE_ADDR_OFFSET(i)]));
//			}
//		}
//
//	}
//	return FlashStatus;
//}
/*****************************************************************************
*  Read once data byte from a specified address.
*******************************************************************************/
uint8_t
FEE_ReadDataByte (uint16_t Address) {

	uint8_t DataByte = 0xFF;

	// Get Byte from specified address
	DataByte = (*(uint8_t*)(FEE_PAGE0_BASE_ADDRESS + FEE_ADDR_OFFSET(Address)));

	return DataByte;
}
