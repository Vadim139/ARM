/*
 * STM32F4_Class.hpp
 *
 *  Created on: 15 maj 2016
 *      Author: Vadim
 */

#ifndef STM32F4_CLASS_H_
#define STM32F4_CLASS_H_

#ifdef __cplusplus

#include "tm_stm32_gpio.h"

class GPIO_IO
{
public:

	GPIO_TypeDef* GPIOx;

	uint16_t Pin;

	TM_GPIO_Mode_t Mode;
//	TM_GPIO_Mode_IN
//	TM_GPIO_Mode_OUT
//	TM_GPIO_Mode_AF
//	TM_GPIO_Mode_AN

	TM_GPIO_OType_t Type;
//	TM_GPIO_OType_PP
//	TM_GPIO_OType_OD

	TM_GPIO_PuPd_t Pull;
//	TM_GPIO_PuPd_NOPULL
//	TM_GPIO_PuPd_UP
//	TM_GPIO_PuPd_DOWN

	TM_GPIO_Speed_t Speed;
//	TM_GPIO_Speed_Low
//	TM_GPIO_Speed_Medium
//	TM_GPIO_Speed_Fast
//	TM_GPIO_Speed_High

GPIO_IO(bool io);
GPIO_IO(GPIO_TypeDef* GPIOxc, uint16_t Pinc, bool io);

void Init();

void Set_high();

void Set_low();

void Toggle();

bool read_state();
};


class Led
{
private:

	TM_GPIO_Mode_t Mode;

	TM_GPIO_OType_t Type;

	TM_GPIO_PuPd_t Pull;

	TM_GPIO_Speed_t Speed;

Led();
Led(GPIO_TypeDef* GPIOxc, uint16_t Pinc);

public:
GPIO_TypeDef* GPIOx;

uint16_t Pin;

void Init();

void Turn_on();

void Turn_off();

void Toggle();

};


#endif
#endif /* STM32F4_CLASS_H_ */
