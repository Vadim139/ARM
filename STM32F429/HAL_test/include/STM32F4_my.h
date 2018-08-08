/*
 * STM32F3_my.h
 *     4 3 5 6 8 9 7 10
 *  Created on: Dec 30, 2012
 *      Author: Dawid
 */

#include "STM32F4_Class.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "common.h"
#include "stm32f4xx.h"
#include "tm_stm32_adc.h"
#include "tm_stm32_spi.h"
#include "stm32f4xx_hal.h"

extern "C"{
#include "functions.h"
}


#ifndef STM32F4_MY_H_
#define STM32F4_MY_H_

void Eth_init();
void wizchip_write(uint8_t wb);
uint8_t wizchip_read();
void wizchip_select(void);
void wizchip_deselect(void);


#endif /* STM32F3_MY_H_ */
