/*
 * STM32F3_my.c
 *
 *  Created on: Oct 23, 2013
 *      Author: Dawid
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_it.h"
#include "STM32F3_my.h"
#include "common.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"

void GPIO_PinInit(GPIO_TypeDef* Port, uint16_t Pin, GPIOMode_TypeDef Mode, GPIOOType_TypeDef Type, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable the GPIO_LED Clock */
  switch ((uint32_t)Port) {
	case GPIOA_BASE :
		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOA, ENABLE);
		break;
	case GPIOB_BASE :
		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOB, ENABLE);
		break;
	case GPIOC_BASE :
		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOC, ENABLE);
		break;
	case GPIOD_BASE :
		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOD, ENABLE);
		break;
	case GPIOE_BASE :
		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOE, ENABLE);
		break;
	default:
		break;
}


  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = Pin;
  GPIO_InitStructure.GPIO_Mode = Mode;
  if (Mode == GPIO_Mode_OUT)
	  GPIO_InitStructure.GPIO_OType = Type;
  GPIO_InitStructure.GPIO_PuPd = PuPd;
  GPIO_InitStructure.GPIO_Speed = Speed;
  GPIO_Init(Port, &GPIO_InitStructure);
}


void GPIO_PinSet(GPIO_TypeDef* Port, uint16_t Pin)
{
	Port -> BSRRL = Pin;
}

void GPIO_PinRes(GPIO_TypeDef* Port, uint16_t Pin)
{
	Port -> BSRRH = Pin;
}

void GPIO_PinTog(GPIO_TypeDef* Port, uint16_t Pin)
{
	Port -> ODR ^= Pin;
}

void GPIO_PinOut(GPIO_TypeDef* Port, uint16_t Pin)
{
	GPIO_PinInit(Port,Pin,GPIO_Mode_OUT,GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_50MHz);
}

void GPIO_PinIn(GPIO_TypeDef* Port, uint16_t Pin)
{
	GPIO_PinInit(Port, Pin, GPIO_Mode_IN,GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_50MHz);
}

uint32_t GPIO_GetState(GPIO_TypeDef* Port, uint16_t Pin)
{
  return GPIO_ReadInputDataBit(Port,Pin);
}

//	Inicjalizacja led'ów
void LED_init(void) {
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);// 1s = 72000000  2s = 72000000 * 2
	STM_EVAL_LEDInit(LED5);// 1 ms = 72000  1 qs = 72
	STM_EVAL_LEDInit(LED6);


	LED3_off;
	LED4_off;
	LED5_off;
	LED6_off;

}

void LEDs_off(void) {
	LED3_off;
	LED4_off;
	LED5_off;
	LED6_off;

}

void LEDs_on(void) {
	LED3_on;
	LED4_on;
	LED5_on;
	LED6_on;

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

void EXTI_Config(GPIO_TypeDef* Port, uint16_t Pin, EXTITrigger_TypeDef Mode)
{

	  EXTI_InitTypeDef   EXTI_InitStructure;
	  GPIO_InitTypeDef   GPIO_InitStructure;
	  NVIC_InitTypeDef   NVIC_InitStructure;

	  uint8_t i = 0;
	  uint32_t PinN = 0;

	  /* Enable GPIO clock */
	  /* Connect EXTI0 Line to pin */
	    switch ((uint32_t)Port) {
	    	case GPIOA_BASE :
	    		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOA, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, Pin);
	    		break;
	    	case GPIOB_BASE :
	    		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOB, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, Pin);
	    		break;
	    	case GPIOC_BASE :
	    		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOC, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, Pin);
	    		break;
	    	case GPIOD_BASE :
	    		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOD, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, Pin);
	    		break;
	    	case GPIOE_BASE :
	    		RCC_AHBPeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOE, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, Pin);
	    		break;
	    	default:
	    		break;
	    }

//	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	  /* Configure PA0 pin as input floating */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Pin = Pin;
	  GPIO_Init(Port, &GPIO_InitStructure);

	  /* Enable SYSCFG clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);


	//  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	  /* Configure EXTI0 line */
	    PinN = Pin;
	    for(;PinN != 1; )
	    	{
	    	i++;
	    	PinN = PinN/2;
	    	Pin = i;
	    	}

	  EXTI_InitStructure.EXTI_Line = (uint32_t)i;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_InitStructure.EXTI_Trigger = Mode;
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  EXTI_Init(&EXTI_InitStructure);

	  /* Enable and set EXTI0 Interrupt to the lowest priority */
	  if(Pin == 0)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	  else if(Pin == 1)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	  else if(Pin == 2)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	  else if(Pin == 3)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	  else if(Pin == 4)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	  else if(Pin == 5 || 6 || 7 || 8 || 9)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	  else if(Pin == 10 || 11 || 12 || 13 || 14 || 15)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;

	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

}

// TIM1, TIM3, TIM4, TIM8, TIM15, TIM16, TIM17 - 16 bit prescaler, 16 bit counter
// TIM2, TIM5 - 16 bit prescaler, 32 bit counter

void TIM1_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter) //1, 4, 8 timers PWM
{

//prescaler--;
	counter--;

	GPIO_InitTypeDef GPIO_InitStructure;			//structure for GPIO setup
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//structure for TIM Time Base
	TIM_OCInitTypeDef TIM_OCInitStructure;	//structure for TIM Output Compare

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//enable the TIM4 clock
	RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//enable the AHB Peripheral Clock to use GPIOB

	/* Pin configuration */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	if (channel == 1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	}
	else if (channel == 2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	}
	else if (channel == 3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
	}
	else if (channel == 4)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);
	}


	/* Time base configuration */
	//The MCU on the STM32F3-Discovery board is clocked at 72Mhz and we need a 20kHz timebase (50us period)
	//Update_event = TIM_CLK /((PSC + 1)*(ARR   + 1)*(RCR + 1))
	//			 20000 = 72000000/((71  + 1)*(49    + 1)*(0   + 1))

	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; //PSC value; meanse that TIM register will be incremented every 1us (72000000 / (71+1) = 1000000Hz = 1us
	TIM_TimeBaseStructure.TIM_Period = counter; //ARR value - 1; create a time period of 50us (1us * 50 = 50us)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* Output Control (OC) configuration - PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//configure the PWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;

	if (channel == 1)
	{
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	}
	else if (channel == 2)
	{
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);
		TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	}
	else if (channel == 3)
	{
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);
		TIM_OC2Init(TIM1, &TIM_OCInitStructure);
		TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	}
	else if (channel == 4)
	{
		TIM_OC1Init(TIM1, &TIM_OCInitStructure);
		TIM_OC2Init(TIM1, &TIM_OCInitStructure);
		TIM_OC3Init(TIM1, &TIM_OCInitStructure);
		TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	}

	TIM_ARRPreloadConfig(TIM1, DISABLE);

	//enable the PWM output
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}

void TIM8_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter) //1, 4, 8 timers PWM
{

//prescaler--;
	counter--;

	GPIO_InitTypeDef GPIO_InitStructure;			//structure for GPIO setup
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//structure for TIM Time Base
	TIM_OCInitTypeDef TIM_OCInitStructure;	//structure for TIM Output Compare

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//enable the TIM4 clock
	RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//enable the AHB Peripheral Clock to use GPIOB

	/* Pin configuration */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	if (channel == 1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);//connect the pin to the desired peripherals' Alternate Function (AF) - TIM4 (GPIO_AF_2)
	}
	else if (channel == 2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
	}
	else if (channel == 3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
	}
	else if (channel == 4)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);
	}


	/* Time base configuration */
	//The MCU on the STM32F3-Discovery board is clocked at 72Mhz and we need a 20kHz timebase (50us period)
	//Update_event = TIM_CLK /((PSC + 1)*(ARR   + 1)*(RCR + 1))
	//			 20000 = 72000000/((71  + 1)*(49    + 1)*(0   + 1))

	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; //PSC value; meanse that TIM register will be incremented every 1us (72000000 / (71+1) = 1000000Hz = 1us
	TIM_TimeBaseStructure.TIM_Period = counter; //ARR value - 1; create a time period of 50us (1us * 50 = 50us)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	/* Output Control (OC) configuration - PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;		//configure the PWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	if (channel == 1)
	{
		TIM_OC1Init(TIM8, &TIM_OCInitStructure);

	}
	else if (channel == 2)
	{
		TIM_OC1Init(TIM8, &TIM_OCInitStructure);
		TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	}
	else if (channel == 3)
	{
		TIM_OC1Init(TIM8, &TIM_OCInitStructure);
		TIM_OC2Init(TIM8, &TIM_OCInitStructure);
		TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	}
	else if (channel == 4)
	{
		TIM_OC1Init(TIM8, &TIM_OCInitStructure);
		TIM_OC2Init(TIM8, &TIM_OCInitStructure);
		TIM_OC3Init(TIM8, &TIM_OCInitStructure);
//		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	}

	TIM_ARRPreloadConfig(TIM8, DISABLE);

	//enable the PWM output
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	TIM_Cmd(TIM8, ENABLE);
}

void TIM4_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter) //1, 4, 8 timers PWM
{

//prescaler--;
	counter--;

	GPIO_InitTypeDef GPIO_InitStructure;			//structure for GPIO setup
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//structure for TIM Time Base
	TIM_OCInitTypeDef TIM_OCInitStructure;	//structure for TIM Output Compare

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//enable the TIM4 clock
	RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//enable the AHB Peripheral Clock to use GPIOB

	/* Pin configuration */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	if (channel == 1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);//connect the pin to the desired peripherals' Alternate Function (AF) - TIM4 (GPIO_AF_2)
	}
	else if (channel == 2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
	}
	else if (channel == 3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
	}
	else if (channel == 4)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);
	}


	/* Time base configuration */
	//The MCU on the STM32F3-Discovery board is clocked at 72Mhz and we need a 20kHz timebase (50us period)
	//Update_event = TIM_CLK /((PSC + 1)*(ARR   + 1)*(RCR + 1))
	//			 20000 = 72000000/((71  + 1)*(49    + 1)*(0   + 1))

	TIM_TimeBaseStructure.TIM_Prescaler = prescaler; //PSC value; meanse that TIM register will be incremented every 1us (72000000 / (71+1) = 1000000Hz = 1us
	TIM_TimeBaseStructure.TIM_Period = counter; //ARR value - 1; create a time period of 50us (1us * 50 = 50us)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* Output Control (OC) configuration - PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//configure the PWM
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	if (channel == 1)
	{
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);

	}
	else if (channel == 2)
	{
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	}
	else if (channel == 3)
	{
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	}
	else if (channel == 4)
	{
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	}

	TIM_ARRPreloadConfig(TIM4, DISABLE);

	//enable the PWM output
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}


void TIM_Config(uint32_t TIM, uint16_t prescaler, uint32_t counter) //2, 3, 4, 6, 7 timers
{

	switch (TIM) {
	case TIM1_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		break;
	case TIM2_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		break;
	case TIM3_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		break;
	case TIM4_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		break;
	case TIM5_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		break;
	case TIM6_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
		break;
	case TIM7_BASE:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
		break;
	case TIM8_BASE:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		break;
	default:
		break;
	}

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = prescaler - 1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = counter;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM, &timerInitStructure);
	TIM_Cmd(TIM, ENABLE);
	TIM_ITConfig(TIM, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef nvicStructure;
	if (TIM == TIM1)
		nvicStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	else if (TIM == TIM2)
		nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
	else if (TIM == TIM3)
		nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
	else if (TIM == TIM4)
		nvicStructure.NVIC_IRQChannel = TIM4_IRQn;
	else if (TIM == TIM5)
		nvicStructure.NVIC_IRQChannel = TIM5_IRQn;
	else if (TIM == TIM6)
		nvicStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
	else if (TIM == TIM7)
		nvicStructure.NVIC_IRQChannel = TIM7_IRQn;
	else if (TIM == TIM8)
		nvicStructure.NVIC_IRQChannel = TIM8_CC_IRQn;


	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

}

