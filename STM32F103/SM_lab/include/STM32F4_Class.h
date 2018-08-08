/*
 * STM32F4_Class.hpp
 *
 *  Created on: 15 maj 2016
 *      Author: Vadim
 */

#ifndef STM32F4_CLASS_H_
#define STM32F4_CLASS_H_

#ifdef __cplusplus

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

class GPIO_IO
{
public:

	GPIO_TypeDef* GPIOx;

	uint16_t Pin;

	GPIOMode_TypeDef Mode;
//	TM_GPIO_Mode_IN
//	TM_GPIO_Mode_OUT
//	TM_GPIO_Mode_AF
//	TM_GPIO_Mode_AN

//	TM_GPIO_OType_t Type;
////	TM_GPIO_OType_PP
////	TM_GPIO_OType_OD
//
//	TM_GPIO_PuPd_t Pull;
////	TM_GPIO_PuPd_NOPULL
////	TM_GPIO_PuPd_UP
////	TM_GPIO_PuPd_DOWN

	GPIOSpeed_TypeDef Speed;
//	TM_GPIO_Speed_Low
//	TM_GPIO_Speed_Medium
//	TM_GPIO_Speed_Fast
//	TM_GPIO_Speed_High

GPIO_IO(bool io);
GPIO_IO(GPIO_TypeDef* GPIOxc, uint16_t Pinc, bool io);
GPIO_IO(GPIO_TypeDef* GPIOxc, uint16_t Pinc, GPIOMode_TypeDef ModeIO, GPIOSpeed_TypeDef SpeedIO);

void Init();

void Set_high();

void Set_low();

void Toggle();

bool read_state();
};


class Led
{
private:

	GPIOMode_TypeDef Mode;

	GPIOSpeed_TypeDef Speed;

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
