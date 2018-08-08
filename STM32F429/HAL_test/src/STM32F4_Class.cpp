/*
 * STM32F4_Class.cpp
 *
 *  Created on: 24 kwi 2016
 *      Author: Vadim
 */

#include "STM32F4_Class.h"

//class GPIO_Pin
//{
//public:
//
//	GPIO_TypeDef* GPIOx;
//
//	uint16_t Pin;
//
//	TM_GPIO_Mode_t Mode;
////	TM_GPIO_Mode_IN
////	TM_GPIO_Mode_OUT
////	TM_GPIO_Mode_AF
////	TM_GPIO_Mode_AN
//
//	TM_GPIO_OType_t Type;
////	TM_GPIO_OType_PP
////	TM_GPIO_OType_OD
//
//	TM_GPIO_PuPd_t Pull;
////	TM_GPIO_PuPd_NOPULL
////	TM_GPIO_PuPd_UP
////	TM_GPIO_PuPd_DOWN
//
//	TM_GPIO_Speed_t Speed;
////	TM_GPIO_Speed_Low
////	TM_GPIO_Speed_Medium
////	TM_GPIO_Speed_Fast
////	TM_GPIO_Speed_High
//
//GPIO_Pin(bool io);
//GPIO_Pin(GPIO_TypeDef* GPIOxc, uint16_t Pinc, bool io);
//
//void Init();
//
//void Set_high();
//
//void Set_low();
//
//void Toggle();
//
//bool read_state();
//};
//
//
//class Led
//{
//private:
//
//	TM_GPIO_Mode_t Mode;
//
//	TM_GPIO_OType_t Type;
//
//	TM_GPIO_PuPd_t Pull;
//
//	TM_GPIO_Speed_t Speed;
//
//Led();
//Led(GPIO_TypeDef* GPIOxc, uint16_t Pinc);
//
//public:
//GPIO_TypeDef* GPIOx;
//
//uint16_t Pin;
//
//void Init();
//
//void Turn_on();
//
//void Turn_off();
//
//void Toggle();
//
//};

// io:  1 - Input
//      0 - Output
GPIO_IO::GPIO_IO(bool io)
{
	if(io)
		Mode = TM_GPIO_Mode_IN;
	else
		Mode = TM_GPIO_Mode_OUT;

	Type = TM_GPIO_OType_PP;

	Pull = TM_GPIO_PuPd_UP;

	Speed = TM_GPIO_Speed_High;
}

GPIO_IO::GPIO_IO(GPIO_TypeDef* GPIOxc, uint16_t Pinc, bool io)
{
	GPIOx = GPIOxc;

	Pin = Pinc;

	if(io)
		Mode = TM_GPIO_Mode_IN;
	else
		Mode = TM_GPIO_Mode_OUT;

	Type = TM_GPIO_OType_PP;

	Pull = TM_GPIO_PuPd_UP;

	Speed = TM_GPIO_Speed_High;
}

void GPIO_IO::Init()
{
	TM_GPIO_Init(GPIOx,Pin,Mode,Type,Pull,Speed);
}

void GPIO_IO::Set_high()
{
	GPIOx->BSRR = (uint32_t)(Pin);

}

void GPIO_IO::Set_low()
{
	GPIOx->BSRR = (uint32_t)(((uint32_t)Pin) << 16);
}

void GPIO_IO::Toggle()
{
	GPIOx->ODR ^= (uint32_t)Pin;
}

bool GPIO_IO::read_state()
{
	return (((GPIOx)->IDR & (Pin)) == 0 ? 0 : 1);
}

////////////////

Led::Led()
{
	Mode = TM_GPIO_Mode_OUT;

	Type = TM_GPIO_OType_PP;

	Pull = TM_GPIO_PuPd_DOWN;

	Speed = TM_GPIO_Speed_High;
}

Led::Led(GPIO_TypeDef* GPIOxc, uint16_t Pinc)
{
	GPIOx = GPIOxc;

	Pin = Pinc;

	Mode = TM_GPIO_Mode_OUT;

	Type = TM_GPIO_OType_PP;

	Pull = TM_GPIO_PuPd_DOWN;

	Speed = TM_GPIO_Speed_High;
}

void Led::Init()
{
	TM_GPIO_Init(GPIOx,Pin,Mode,Type,Pull,Speed);
}

void Led::Turn_on()
{
	GPIOx->BSRR = (uint32_t)(Pin);
}

void Led::Turn_off()
{
	GPIOx->BSRR = (uint32_t)(((uint32_t)Pin) << 16);
}

void Led::Toggle()
{
	GPIOx->ODR ^= (uint32_t)Pin;
}
