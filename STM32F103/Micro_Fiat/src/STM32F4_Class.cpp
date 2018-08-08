/*
 * STM32F4_Class.cpp
 *
 *  Created on: 24 kwi 2016
 *      Author: Vadim
 */

#include "STM32F4_Class.h"


// io:  1 - Input
//      0 - Output
GPIO_IO::GPIO_IO(bool io)
{
	if(io)
		Mode = GPIO_Mode_Out_PP;
	else
		Mode = GPIO_Mode_IPU;

//	Type = TM_GPIO_OType_PP;

//	Pull = TM_GPIO_PuPd_UP;

	Speed = GPIO_Speed_50MHz;
}

GPIO_IO::GPIO_IO(GPIO_TypeDef* GPIOxc, uint16_t Pinc, GPIOMode_TypeDef ModeIO, GPIOSpeed_TypeDef SpeedIO)
{
	GPIOx = GPIOxc;

	Pin = Pinc;

	Mode = ModeIO;

	Speed = SpeedIO;
}

GPIO_IO::GPIO_IO(GPIO_TypeDef* GPIOxc, uint16_t Pinc, bool io)
{
	GPIOx = GPIOxc;

	Pin = Pinc;

	if(io)
		Mode = GPIO_Mode_Out_PP;
	else
		Mode = GPIO_Mode_IPU;

//	Type = TM_GPIO_OType_PP;

//	Pull = TM_GPIO_PuPd_UP;

	Speed = GPIO_Speed_50MHz;
}

void GPIO_IO::Init()
{
	switch ((uint32_t)GPIOx) {
		case (uint32_t)GPIOA:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			break;
		case (uint32_t)GPIOB:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			break;
		case (uint32_t)GPIOC:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			break;
		default:
			break;
	}

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USARTy Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = Pin;
	GPIO_InitStructure.GPIO_Speed = Speed;
	GPIO_InitStructure.GPIO_Mode = Mode;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

}

void GPIO_IO::Set_high()
{
	GPIOx->BSRR = (uint32_t)Pin;
}

void GPIO_IO::Set_low()
{
	GPIOx->BRR = (uint32_t)Pin;
}

void GPIO_IO::Toggle()
{
	GPIOx->ODR ^= (uint32_t)Pin;
}

bool GPIO_IO::read_state()
{
//	GPIO_ReadInputDataBit(GPIOx,Pin);
	return GPIO_ReadInputDataBit(GPIOx,Pin);//(((GPIOx)->IDR & (Pin)) == 0 ? 0 : 1);
}

////////////////
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
//	GPIOx->BSRRL = (uint32_t)Pin;
//}
//
//void Led::Turn_off()
//{
//	GPIOx->BSRRH = (uint32_t)Pin;
//}
//
//void Led::Toggle()
//{
//	GPIOx->ODR ^= (uint32_t)Pin;
//}
