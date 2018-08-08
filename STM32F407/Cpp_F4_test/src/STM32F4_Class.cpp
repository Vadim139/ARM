///*
// * STM32F4_Class.cpp
// *
// *  Created on: 24 kwi 2016
// *      Author: Vadim
// */
//
//#include "STM32F4_Class.h"
//
//// io:  1 - Input
////      0 - Output
//GPIO_Pin::GPIO_Pin(bool io)
//{
//	if(io)
//		Mode = TM_GPIO_Mode_IN;
//	else
//		Mode = TM_GPIO_Mode_OUT;
//
//	Type = TM_GPIO_OType_PP;
//
//	Pull = TM_GPIO_PuPd_UP;
//
//	Speed = TM_GPIO_Speed_High;
//}
//
//GPIO_Pin::GPIO_Pin(GPIO_TypeDef* GPIOxc, uint16_t Pinc, bool io)
//{
//	GPIOx = GPIOxc;
//
//	Pin = Pinc;
//
//	if(io)
//		Mode = TM_GPIO_Mode_IN;
//	else
//		Mode = TM_GPIO_Mode_OUT;
//
//	Type = TM_GPIO_OType_PP;
//
//	Pull = TM_GPIO_PuPd_UP;
//
//	Speed = TM_GPIO_Speed_High;
//}
//
//void GPIO_Pin::Init()
//{
//	TM_GPIO_Init(GPIOx,Pin,Mode,Type,Pull,Speed);
//}
//
//void GPIO_Pin::Set_high()
//{
//	GPIOx->BSRR = (uint32_t)Pin;
//}
//
//void GPIO_Pin::Set_low()
//{
//	GPIOx->BSRR = (uint32_t)Pin << 16U;
//}
//
//void GPIO_Pin::Toggle()
//{
//	HAL_GPIO_TogglePin(GPIOx, Pin);
//}
//
//bool GPIO_Pin::read_state()
//{
//	return HAL_GPIO_ReadPin(GPIOx, Pin);
//}
//
//////////////////
//
//Led::Led()
//{
//	Mode = TM_GPIO_Mode_OUT;
//
//	Type = TM_GPIO_OType_PP;
//
//	Pull = TM_GPIO_PuPd_DOWN;
//
//	Speed = TM_GPIO_Speed_High;
//}
//
//Led::Led(GPIO_TypeDef* GPIOxc, uint16_t Pinc)
//{
//	GPIOx = GPIOxc;
//
//	Pin = Pinc;
//
//	Mode = TM_GPIO_Mode_OUT;
//
//	Type = TM_GPIO_OType_PP;
//
//	Pull = TM_GPIO_PuPd_DOWN;
//
//	Speed = TM_GPIO_Speed_High;
//}
//
//void Led::Init()
//{
//	TM_GPIO_Init(GPIOx,Pin,Mode,Type,Pull,Speed);
//}
//
//void Led::Turn_on()
//{
//	GPIOx->BSRR = (uint32_t)Pin;
//}
//
//void Led::Turn_off()
//{
//	GPIOx->BSRR = (uint32_t)Pin << 16U;
//}
//
//void Led::Toggle()
//{
//	HAL_GPIO_TogglePin(GPIOx, Pin);
//}
