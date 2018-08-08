/*
 * STM32F3_my.c
 *
 *  Created on: Oct 23, 2013
 *      Author: Dawid
 */

//#include "stm32f4xx.h"
//#include "stm32f4_discovery.h"
//#include "stm32f4xx_it.h"
#include "STM32F4_my.h"
//#include "common.h"
//#include "stm32f4xx_syscfg.h"
//#include "stm32f4xx_exti.h"
//#include "STM32F4_Class.h"
//#include "PCF8583.h"
//#include "lcdlib.h"

//#include "tm_stm32f4_adc.h"
#include "tm_stm32_spi.h"
//#include "functions.h"

GPIO_IO *Eth_cs;
GPIO_IO *Eth_rst;
GPIO_IO *Eth_rdy;

void Eth_init()
{
	uint16_t ADC_1 = 0;
	char ADCs1[5] = {0,0,0,0,0};

	TM_SPI_Init(ETH_SPI,ETH_PINSPACK);

	Eth_cs = new GPIO_IO(ETH_PORT,ETH_CS,0);
	Eth_rst = new GPIO_IO(ETH_PORT,ETH_RST,0);
//	Eth_rdy = new GPIO_IO(ETH_PORT,ETH_RDY,1);

	Eth_cs->Init();
	Eth_rst->Init();
//	Eth_rdy->Init();

	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
	uint16tostr(ADCs1, ADC_1, 10);
	puts(ADCs1);

//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//		puts("Low");
//
////	Eth_cs->Set_low();
//	Eth_rst->Set_high();
//
//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//		puts("Low");
//	_delay_ms(500);

//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//		puts("Low");

	Eth_rst->Set_low();
	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
	uint16tostr(ADCs1, ADC_1, 10);
	puts(ADCs1);
//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//		puts("Low");
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//			puts("High");

	_delay_ms(1000);
	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
	uint16tostr(ADCs1, ADC_1, 10);
	puts(ADCs1);
//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//		puts("Low");
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//			puts("High");

	Eth_rst->Set_high();
	Eth_cs->Set_low();
//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//		puts("Low");
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//			puts("High");
	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
	uint16tostr(ADCs1, ADC_1, 10);
	puts(ADCs1);
	_delay_ms(1000);
	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
	uint16tostr(ADCs1, ADC_1, 10);
	puts(ADCs1);
//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//		puts("Low");
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//			puts("High");

//	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2));

//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//			puts("Low");
//
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//			puts("High");
	_delay_ms(3000);
//	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2));
	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
	uint16tostr(ADCs1, ADC_1, 10);
	puts(ADCs1);
//	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//			puts("Low");
//
//	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))
//			puts("High");
//	while(1)
//	{
//		_delay_ms(2000);
//		ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
//		uint16tostr(ADCs1, ADC_1, 10);
//		puts(ADCs1);
//	}
}

uint8_t SPI_SendByte(uint8_t byte)
{
	uint8_t data;
	while(SPI_IS_BUSY(ETH_SPI) == RESET);
	TM_SPI_Send(ETH_SPI,byte);
	while(SPI_IS_BUSY(ETH_SPI) == RESET);
	TM_SPI_ReadMulti(ETH_SPI,&data,0x00,1);
	return data;
}

void wizchip_select(void)
{
	Eth_cs->Set_low();
}

void wizchip_deselect(void)
{
	Eth_cs->Set_high();
}

void wizchip_write(uint8_t wb)
{
	SPI_SendByte(wb);
//	TM_SPI_Send(ETH_SPI,wb);
//	SPI_I2S_SendData(ETH_SPI,wb);
}

uint8_t wizchip_read()
{
	return SPI_SendByte(0x00);
//	return TM_SPI_Send(ETH_SPI,0xFF);
//	return SPI_I2S_ReceiveData(ETH_SPI);
}
