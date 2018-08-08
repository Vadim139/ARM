/*
 * EE_memory.h
 *
 *  Created on: 6 sty 2018
 *      Author: Vadim
 */
#include "main.h"
#include "DataBase.h"

#ifndef EE_MEMORY_H_
#define EE_MEMORY_H_

/*
 * 0 - wifi name
 * 20 - wifi pass
 * 40 - motion sensors in (5x2)
 * 50 - window sensors in (5x2)
 * 60 - schedule (4x4)
 * 76 - output function (4x1)
 * 80 - users num
 * 81 - sensors num
 * 82 - gsm num
 * 83 - net on
 * 84 - prefer net
 * 100 - users (10x110)
 * 1200 - sensors (10x25)
 * 1450 - numbers (10x10)
 */

// Adresses
#define WIFI_NAME_ADDR		1	//
#define WIFI_PASS_ADDR 		20	//
#define NET_ON_ADDR			40
#define NET_PREFER_ADDR		41
#define OUT_NUM_ADDR		44	//
#define USERS_NUM_ADDR		45	//
#define SENSORS_NUM_ADDR	46	//
#define GSM_NUM_ADDR		47	//
#define OUTPUTS_BASE_ADDR	50	//
#define USERS_BASE_ADDR		100
#define SENSORS_BASE_ADDR	1200
#define NUMBERS_BASE_ADDR	1450

#define OUTPUT_SIZE			10
#define USER_SIZE 			110
#define SENSOR_SIZE			25
#define NUMBERS_SIZE		10



// CAN BE CHANGED
	#define FEE_DENSITY_PAGES	4	    // how many pages are used
	#define FEE_PAGE_SIZE		1024	    // can be 1k or 2k check manual for used device
	#define FEE_PAGE0_BASE_ADDRESS 	0x0801D000  // choose location for the first EEPROMPage address on the top of flash
	#define FEE_PAGE1_BASE_ADDRESS 	0x0801F400

	// DONT CHANGE
	#define FEE_DENSITY_BYTES		((FEE_PAGE_SIZE / 2) * FEE_DENSITY_PAGES - 1)
	#define FEE_LAST_PAGE_ADDRESS 	(FEE_PAGE_BASE_ADDRESS + (FEE_PAGE_SIZE * FEE_DENSITY_PAGES))
	#define FEE_EMPTY_WORD			((uint16_t)0xFFFF)
	#define FEE_ADDR_OFFSET(Address)(Address * 2) // 1Byte per Word will be saved to preserve Flash

	// use this function to initialize the functionality
	uint16_t FEE_Init(void);

	void FEE_ReadAll();
	void FEE_Add_User(User user);
	void FEE_Add_Sensor(Sensor sensor);
	void FEE_Add_Output(Output out);
	void FEE_Add_Number(int ID, char* num);
	void FEE_Delete_User(uint8_t ID);
	void FEE_Delete_Sensor(uint8_t ID);
	void FEE_Delete_Output(uint8_t ID);
	void FEE_Delete_Number(int ID);
	void FEE_Write_Settings();
	void FEE_Erase (void);

	uint16_t FEE_WriteDataByte (uint16_t Address, uint8_t DataByte);
	uint16_t FEE_WriteData (uint16_t Address, uint8_t *Data, uint16_t size);
	uint8_t FEE_ReadDataByte (uint16_t Address);

	/* Exported constants --------------------------------------------------------*/
	/* Define the STM32F10Xxx Flash page size depending on the used STM32 device */


#endif /* EE_MEMORY_H_ */
