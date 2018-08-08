/*
 * STM32F3_my.c
 *
 *  Created on: Oct 23, 2013
 *      Author: Dawid
 */

//#include "stm32f4xx.h"
//#include "stm32f4_discovery.h"
//#include "stm32f4xx_it.h"
#include "STM32F3_my.h"
//#include "common.h"
//#include "stm32f4xx_syscfg.h"
//#include "stm32f4xx_exti.h"
//#include "STM32F4_Class.h"
//#include "PCF8583.h"
//#include "lcdlib.h"


void GPIO_PinInit(GPIO_TypeDef* Port, uint32_t Pin, uint32_t Mode, uint32_t PuPd, uint32_t Speed)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable the GPIO_LED Clock */
  switch ((uint32_t)Port) {
	case GPIOA_BASE :
		__HAL_RCC_GPIOA_CLK_ENABLE();
		break;
	case GPIOB_BASE :
		__HAL_RCC_GPIOB_CLK_ENABLE();
		break;
	case GPIOC_BASE :
		__HAL_RCC_GPIOC_CLK_ENABLE();
		break;
	case GPIOD_BASE :
		__HAL_RCC_GPIOD_CLK_ENABLE();
		break;
	case GPIOE_BASE :
		__HAL_RCC_GPIOE_CLK_ENABLE();
		break;
	default:
		break;
}


  /* Configure the GPIO pin */
  GPIO_InitStructure.Pin = Pin;
  GPIO_InitStructure.Mode = Mode;
  GPIO_InitStructure.Pull = PuPd;
  GPIO_InitStructure.Speed = Speed;
  HAL_GPIO_Init(Port, &GPIO_InitStructure);
}


void GPIO_PinOut(GPIO_TypeDef* Port, uint16_t Pin)
{
	GPIO_PinInit(Port,Pin,GPIO_MODE_OUTPUT_PP , GPIO_PULLUP , GPIO_SPEED_FAST);
}

void GPIO_PinIn(GPIO_TypeDef* Port, uint16_t Pin)
{
	GPIO_PinInit(Port, Pin, GPIO_MODE_INPUT , GPIO_PULLUP, GPIO_SPEED_FAST);
}

uint32_t GPIO_GetState(GPIO_TypeDef* Port, uint16_t Pin)
{
  return GPIO_ReadInputDataBit(Port,Pin);
}



//	Delay'e pod 72 MHz - nieczynne
void delay_s (uint32_t s)
{
	_delay_ms(1000 * s);
//	uint32_t i;
//	s *= 6000000;
//	for(i = 0; i < s; i++);
}

void delay_ms (uint32_t ms)
{
	uint32_t i;
	ms = 6000 * ms;
	for(i = 0; i < ms; i++);
}

void delay_qs (uint16_t qs)
{
	uint16_t i;
	qs *= 6;
	for(i = 0; i < qs; i++);
}

void delay (uint16_t qs)
{
	uint16_t i;
	for(i = 0; i < qs; i++);
}



// TIM1, TIM3, TIM4, TIM8, TIM15, TIM16, TIM17 - 16 bit prescaler, 16 bit counter
// TIM2, TIM5 - 16 bit prescaler, 32 bit counter

void TIM1_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter) //1, 4, 8 timers PWM
{

	counter--;

	TIM_HandleTypeDef htim1;
	GPIO_InitTypeDef GPIO_InitStructure;			//structure for GPIO setup
	TIM_Base_InitTypeDef TIM_TimeBaseStructure;//structure for TIM Time Base
	TIM_OC_InitTypeDef TIM_OCInitStructure;	//structure for TIM Output Compare

	__HAL_RCC_TIM1_CLK_ENABLE();  //enable the TIM4 clock
//	__HAL_RCC_GPIOA_CLK_ENABLE();	//enable the AHB Peripheral Clock to use GPIOB

	/* Pin configuration */
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Alternate = GPIO_AF1_TIM1;


	if (channel == 1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	else if (channel == 2)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);


	}
	else if (channel == 3)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_10;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);


	}
	else if (channel == 4)
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_14;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);


	}


	  __HAL_RCC_TIM1_CLK_ENABLE();
	  htim1.Instance = TIM1;
	  htim1.Init.Prescaler = prescaler;
	  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim1.Init.Period = counter;
	  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim1.Init.RepetitionCounter = 0;
	  HAL_TIM_PWM_Init(&htim1);
	/* Time base configuration */
	//The MCU on the STM32F3-Discovery board is clocked at 72Mhz and we need a 20kHz timebase (50us period)
	//Update_event = TIM_CLK /((PSC + 1)*(ARR   + 1)*(RCR + 1))
	//			 20000 = 72000000/((71  + 1)*(49    + 1)*(0   + 1))


	  TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
	  TIM_OCInitStructure.Pulse = 4000;
	  TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
	  TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;
	  TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE;
	  TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;
	  TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_SET;

		 HAL_TIM_PWM_MspInit(&htim1);
		 HAL_TIM_Base_Start(&htim1);

	if (channel == 1)
	{
		HAL_TIM_PWM_ConfigChannel(&htim1, &TIM_OCInitStructure, TIM_CHANNEL_1);
		  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	}
	else if (channel == 2)
	{
		HAL_TIM_PWM_ConfigChannel(&htim1, &TIM_OCInitStructure, TIM_CHANNEL_2);
		  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	}
	else if (channel == 3)
	{

		HAL_TIM_PWM_ConfigChannel(&htim1, &TIM_OCInitStructure, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	}
	else if (channel == 4)
	{

		HAL_TIM_PWM_ConfigChannel(&htim1, &TIM_OCInitStructure, TIM_CHANNEL_4);
		  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	}


}

void TIM8_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter) //1, 4, 8 timers PWM
{


	counter--;

	TIM_HandleTypeDef htim8;
	GPIO_InitTypeDef GPIO_InitStructure;			//structure for GPIO setup
	TIM_Base_InitTypeDef TIM_TimeBaseStructure;//structure for TIM Time Base
	TIM_OC_InitTypeDef TIM_OCInitStructure;	//structure for TIM Output Compare

	__HAL_RCC_TIM8_CLK_ENABLE();  //enable the TIM4 clock
//	__HAL_RCC_GPIOA_CLK_ENABLE();	//enable the AHB Peripheral Clock to use GPIOB

	/* Pin configuration */
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Alternate = GPIO_AF1_TIM1;


	if (channel == 1)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	}
	else if (channel == 2)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);


	}
	else if (channel == 3)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);


	}
	else if (channel == 4)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);


	}


	  __HAL_RCC_TIM1_CLK_ENABLE();
	  htim8.Instance = TIM8;
	  htim8.Init.Prescaler = prescaler;
	  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim8.Init.Period = counter;
	  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim8.Init.RepetitionCounter = 0;
	  HAL_TIM_PWM_Init(&htim8);
	/* Time base configuration */
	//The MCU on the STM32F3-Discovery board is clocked at 72Mhz and we need a 20kHz timebase (50us period)
	//Update_event = TIM_CLK /((PSC + 1)*(ARR   + 1)*(RCR + 1))
	//			 20000 = 72000000/((71  + 1)*(49    + 1)*(0   + 1))


	  TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM2;
	  TIM_OCInitStructure.Pulse = 4000;
	  TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
	  TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;
	  TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE;
	  TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;
	  TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_SET;

		 HAL_TIM_PWM_MspInit(&htim8);
		 HAL_TIM_Base_Start(&htim8);

	if (channel == 1)
	{
		HAL_TIM_PWM_ConfigChannel(&htim8, &TIM_OCInitStructure, TIM_CHANNEL_1);
		  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	}
	else if (channel == 2)
	{
		HAL_TIM_PWM_ConfigChannel(&htim8, &TIM_OCInitStructure, TIM_CHANNEL_2);
		  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	}
	else if (channel == 3)
	{

		HAL_TIM_PWM_ConfigChannel(&htim8, &TIM_OCInitStructure, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	}
	else if (channel == 4)
	{

		HAL_TIM_PWM_ConfigChannel(&htim8, &TIM_OCInitStructure, TIM_CHANNEL_4);
		  HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
	}


}

void TIM4_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter) //1, 4, 8 timers PWM
{

	counter--;

	TIM_HandleTypeDef htim4;
	GPIO_InitTypeDef GPIO_InitStructure;			//structure for GPIO setup
	TIM_Base_InitTypeDef TIM_TimeBaseStructure;//structure for TIM Time Base
	TIM_OC_InitTypeDef TIM_OCInitStructure;	//structure for TIM Output Compare

	__HAL_RCC_TIM4_CLK_ENABLE();  //enable the TIM4 clock
//	__HAL_RCC_GPIOA_CLK_ENABLE();	//enable the AHB Peripheral Clock to use GPIOB

	/* Pin configuration */
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Alternate = GPIO_AF1_TIM1;


	if (channel == 1)
	{
		__HAL_RCC_GPIOBCLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_6;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	else if (channel == 2)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);


	}
	else if (channel == 3)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_8;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);


	}
	else if (channel == 4)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitStructure.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);


	}


	  __HAL_RCC_TIM1_CLK_ENABLE();
	  htim4.Instance = TIM8;
	  htim4.Init.Prescaler = prescaler;
	  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim4.Init.Period = counter;
	  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim4.Init.RepetitionCounter = 0;
	  HAL_TIM_PWM_Init(&htim4);
	/* Time base configuration */
	//The MCU on the STM32F3-Discovery board is clocked at 72Mhz and we need a 20kHz timebase (50us period)
	//Update_event = TIM_CLK /((PSC + 1)*(ARR   + 1)*(RCR + 1))
	//			 20000 = 72000000/((71  + 1)*(49    + 1)*(0   + 1))


	  TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
	  TIM_OCInitStructure.Pulse = 4000;
	  TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
	  TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_LOW;
	  TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE;
	  TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;
	  TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_SET;

		 HAL_TIM_PWM_MspInit(&htim4);
		 HAL_TIM_Base_Start(&htim4);

	if (channel == 1)
	{
		  HAL_TIM_PWM_ConfigChannel(&htim4, &TIM_OCInitStructure, TIM_CHANNEL_1);
		  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	}
	else if (channel == 2)
	{
		HAL_TIM_PWM_ConfigChannel(&htim4, &TIM_OCInitStructure, TIM_CHANNEL_2);
		  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	}
	else if (channel == 3)
	{

		HAL_TIM_PWM_ConfigChannel(&htim4, &TIM_OCInitStructure, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	}
	else if (channel == 4)
	{

		HAL_TIM_PWM_ConfigChannel(&htim4, &TIM_OCInitStructure, TIM_CHANNEL_4);
		  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	}


}


void TIM_Config(uint32_t TIM, uint16_t prescaler, uint32_t counter) //2, 3, 4, 6, 7 timers
{

	switch (TIM) {
	case TIM1_BASE:
		__HAL_RCC_TIM1_CLK_ENABLE();
		break;
	case TIM2_BASE:
		__HAL_RCC_TIM2_CLK_ENABLE();
		break;
	case TIM3_BASE:
		__HAL_RCC_TIM3_CLK_ENABLE();
		break;
	case TIM4_BASE:
		__HAL_RCC_TIM4_CLK_ENABLE();
		break;
	case TIM5_BASE:
		__HAL_RCC_TIM5_CLK_ENABLE();
		break;
	case TIM6_BASE:
		__HAL_RCC_TIM6_CLK_ENABLE();
		break;
	case TIM7_BASE:
		__HAL_RCC_TIM7_CLK_ENABLE();
		break;
	case TIM8_BASE:
		__HAL_RCC_TIM8_CLK_ENABLE();
		break;
	default:
		break;
	}

	TIM_HandleTypeDef htim;
	htim.Instance = TIM;
	htim.Init.Prescaler = prescaler;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = counter;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&htim);
	HAL_TIM_Base_Start_IT(&htim);


	if (TIM == TIM1){
		HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	}
	else if (TIM == TIM2){
		HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
	else if (TIM == TIM3){
		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
	}
	else if (TIM == TIM4){
		HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
	}
	else if (TIM == TIM5){
		HAL_NVIC_SetPriority(TIM5_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);
	}
	else if (TIM == TIM6){
		HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	}
	else if (TIM == TIM7){
		HAL_NVIC_SetPriority(TIM7_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM7_IRQn);
	}
	else if (TIM == TIM8){
		HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 0, 1);
		HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
	}


}



//void puttime(char x, char y, char i, int size,char back, int fcolor, int bcolor) {
//	uint8_t godz, min, sek, hsek;
////	lcd_putchar('a');
//	PCF8583_get_time(&godz, &min, &sek, &hsek);
////	lcd_putchar('b');
//	if (i == 1 || i == 2 || i == 3 || i == 4) {
//		LCDSetXY(x, y);
//		if (godz <= 9)
//		{
//			LCDPutChar('0',x,y,size,back,fcolor,bcolor);
//			if (size == SMALL)
//			y = y + 6;
//			else
//			y = y + 8;
//			LCDPutInt(godz,x,y,size,back,fcolor,bcolor);
//			if (size == SMALL)
//			y = y + 6;
//			else
//			y = y + 8;
//		} else
//		{
//			LCDPutInt(godz,x,y,size,back,fcolor,bcolor);
//			if (size == SMALL)
//			y = y + 12;
//			else
//			y = y + 16;
//		}
//		if (i == 2 || i == 3 || i == 4) {
//			LCDPutChar(':',x,y,size,back,fcolor,bcolor);
//			if (size == SMALL)
//			y = y + 6;
//			else
//			y = y + 8;
//
//			if (min <= 9)
//			{
//				LCDPutChar('0',x,y,size,back,fcolor,bcolor);
//				if (size == SMALL)
//				y = y + 6;
//				else
//				y = y + 8;
//				LCDPutInt(min,x,y,size,back,fcolor,bcolor);
//				if (size == SMALL)
//				y = y + 6;
//				else
//				y = y + 8;
//			} else
//			{
//				LCDPutInt(min,x,y,size,back,fcolor,bcolor);
//				if (size == SMALL)
//				y = y + 12;
//				else
//				y = y + 16;
//			}
//			if (i == 3 || i == 4) {
//				LCDPutChar(':',x,y,size,back,fcolor,bcolor);
//				if (size == SMALL)
//				y = y + 6;
//				else
//				y = y + 8;
//
//				if (sek <= 9)
//				{
//					LCDPutChar('0',x,y,size,back,fcolor,bcolor);
//					if (size == SMALL)
//					y = y + 6;
//					else
//					y = y + 8;
//					LCDPutInt(sek,x,y,size,back,fcolor,bcolor);
//					if (size == SMALL)
//					y = y + 6;
//					else
//					y = y + 8;
//				} else
//				{
//					LCDPutInt(sek,x,y,size,back,fcolor,bcolor);
//					if (size == SMALL)
//					y = y + 12;
//					else
//					y = y + 16;
//				}
//				if (i == 4) {
//					LCDPutChar(':',x,y,size,back,fcolor,bcolor);
//					if (size == SMALL)
//					y = y + 6;
//					else
//					y = y + 8;
//
//					if (hsek <= 9)
//					{
//						LCDPutChar('0',x,y,size,back,fcolor,bcolor);
//						if (size == SMALL)
//						y = y + 6;
//						else
//						y = y + 8;
//						LCDPutInt(hsek,x,y,size,back,fcolor,bcolor);
//						if (size == SMALL)
//						y = y + 6;
//						else
//						y = y + 8;
//					} else
//					{
//						LCDPutInt(hsek,x,y,size,back,fcolor,bcolor);
//						if (size == SMALL)
//						y = y + 12;
//						else
//						y = y + 16;
//					}
//				}
//
//			}
//
//		}
//
//	}
////	lcd_putchar('c');
//}
//
//void putdate(char x, char y, char i, int size,char back, int fcolor, int bcolor) {
//	uint8_t mounth, day;
//	uint16_t year;
//
//	PCF8583_get_date(&day, &mounth, &year);
//
////	if (i == 1 || i == 2 || i == 3 || i == 4) {
////		LCDSetXY(x, y);
////		if (day <= 9)
////			lcd_putchar('0');
////		lcd_number(day);
////		if (i == 2 || i == 3 || i == 4) {
////			lcd_putchar('.');
////			if (mounth <= 9)
////				lcd_putchar('0');
////			lcd_number(mounth);
////			if (i == 3 || i == 4) {
////				lcd_putchar('.');
////				lcd_lnumber(year);
//////				lcd_puts(' r');
////				}
////
////		}
////
////	}
//
//	if (i == 1 || i == 2 || i == 3 || i == 4) {
//		LCDSetXY(x, y);
//		if (day <= 9)
//		{
//			LCDPutChar('0',x,y,size,back,fcolor,bcolor);
//			if (size == SMALL)
//			y = y + 6;
//			else
//			y = y + 8;
//			LCDPutInt(day,x,y,size,back,fcolor,bcolor);
//			if (size == SMALL)
//			y = y + 6;
//			else
//			y = y + 8;
//		} else
//		{
//			LCDPutInt(day,x,y,size,back,fcolor,bcolor);
//			if (size == SMALL)
//			y = y + 12;
//			else
//			y = y + 16;
//		}
//		if (i == 2 || i == 3 || i == 4) {
//			LCDPutChar('.',x,y,size,back,fcolor,bcolor);
//			if (size == SMALL)
//			y = y + 6;
//			else
//			y = y + 8;
//
//			if (mounth <= 9)
//			{
//				LCDPutChar('0',x,y,size,back,fcolor,bcolor);
//				if (size == SMALL)
//				y = y + 6;
//				else
//				y = y + 8;
//				LCDPutInt(mounth,x,y,size,back,fcolor,bcolor);
//				if (size == SMALL)
//				y = y + 6;
//				else
//				y = y + 8;
//			} else
//			{
//				LCDPutInt(mounth,x,y,size,back,fcolor,bcolor);
//				if (size == SMALL)
//				y = y + 12;
//				else
//				y = y + 16;
//			}
//			if (i == 3 || i == 4) {
//				LCDPutChar('.',x,y,size,back,fcolor,bcolor);
//				if (size == SMALL)
//				y = y + 6;
//				else
//				y = y + 8;
//
//				if (year <= 9)
//				{
//					LCDPutChar('0',x,y,size,back,fcolor,bcolor);
//					if (size == SMALL)
//					y = y + 6;
//					else
//					y = y + 8;
//					LCDPutInt(year,x,y,size,back,fcolor,bcolor);
//					if (size == SMALL)
//					y = y + 6;
//					else
//					y = y + 8;
//				} else
//				{
//					LCDPutInt(year,x,y,size,back,fcolor,bcolor);
//					if (size == SMALL)
//					y = y + 12;
//					else
//					y = y + 16;
//				}
//
//
//			}
//
//		}
//
//	}
//
//}



