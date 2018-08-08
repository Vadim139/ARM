/*
 * OV7670_I2C.h
 *
 *  Created on: 27 sty 2015
 *      Author: Dawid
 */

#ifndef OV7670_I2C_H_
#define OV7670_I2C_H_

#include "stm32f4xx_i2c.h"

#define SCCB_Camera I2C1
#define OV7670_address 42


//uint8_t OV7670_read1(uint8_t reg);
//void OV7670_write(uint8_t reg,uint8_t data);
int SCCB_send_data(u8 slave_addr, u16 reg_addr, u8* data, u8 addr_len);
int SCCB_receive_data(u8 slave_addr, u16 reg_addr, u8* data, u8 addr_len);
int OV7670_read(u8 reg, u8* data);
int OV7670_write(u8 reg, u8* data);
//void MCO1_Init(void);

#endif /* OV7670_I2C_H_ */

/*

PA9 - DCMI_D0
PC7 - DCMI_D1
PC8 - DCMI_D2
PC9 - DCMI_D3
PE4 - DCMI_D4
PB6 - DCMI_D5
PE5 - DCMI_D6
PE6 - DCMI_D7

PB7 - VSYNC
PA6 - DCMI_PIXCLK
PA4 - HSYNC
PA8 - WEN
PA15 - OE

 */
