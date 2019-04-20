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


void GPIO_PinInit(GPIO_TypeDef* Port, uint16_t Pin, GPIOMode_TypeDef Mode, GPIOOType_TypeDef Type, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable the GPIO_LED Clock */
  switch ((uint32_t)Port) {
	case GPIOA_BASE :
		RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOA, ENABLE);
		break;
	case GPIOB_BASE :
		RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOB, ENABLE);
		break;
	case GPIOC_BASE :
		RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOC, ENABLE);
		break;
	case GPIOD_BASE :
		RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOD, ENABLE);
		break;
	case GPIOE_BASE :
		RCC_AHB1PeriphClockCmd((uint32_t)RCC_AHB1Periph_GPIOE, ENABLE);
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

void delay (uint16_t qs)
{
	uint16_t i;
	for(i = 0; i < qs; i++);
}

void EXTI_Config(GPIO_TypeDef* Port, uint16_t Pin, EXTITrigger_TypeDef Mode)
{

	  EXTI_InitTypeDef   EXTI_InitStructure;
	  GPIO_InitTypeDef   GPIO_InitStructure;
	  NVIC_InitTypeDef   NVIC_InitStructure;

	  uint8_t i = 0;
	  uint32_t PinN = 0;

	  /* Configure EXTI0 line */
		    PinN = Pin;
		    for(;PinN != 1; )
		    	{
		    	i++;
		    	PinN = PinN/2;
	//	    	Pin = i;
		    	}


	  /* Enable GPIO clock */
	  /* Connect EXTI0 Line to pin */
	    switch ((uint32_t)Port) {
	    	case GPIOA_BASE :
	    		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	  	   	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, (uint8_t)i);
	    		break;
	    	case GPIOB_BASE :
	    		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	  	   	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, (uint8_t)i);
	    		break;
	    	case GPIOC_BASE :
	    		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	  	   	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, (uint8_t)i);
	    		break;
	    	case GPIOD_BASE :
	    		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	  	   	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, (uint8_t)i);
	    		break;
	    	case GPIOE_BASE :
	    		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	  	   	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	    		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, (uint8_t)i);
	    		break;
	    	default:
	    		break;
	    }

		  /* Enable SYSCFG clock */
//		  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

//	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	  /* Configure PA0 pin as input floating */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_Pin = Pin;
	  GPIO_Init(Port, &GPIO_InitStructure);




//	  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

//	  /* Configure EXTI0 line */
//	    PinN = Pin;
//	    for(;PinN != 1; )
//	    	{
//	    	i++;
//	    	PinN = PinN/2;
////	    	Pin = i;
//	    	}

	  EXTI_InitStructure.EXTI_Line = GPIO_PinSource0;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_InitStructure.EXTI_Trigger = Mode;
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  EXTI_Init(&EXTI_InitStructure);

	  /* Enable and set EXTI0 Interrupt to the lowest priority */
	  if((uint8_t)i == 0)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	  else if((uint8_t)i == 1)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	  else if((uint8_t)i == 2)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	  else if((uint8_t)i == 3)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	  else if((uint8_t)i == 4)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	  else if((uint8_t)i == 5 || 6 || 7 || 8 || 9)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	  else if((uint8_t)i == 10 || 11 || 12 || 13 || 14 || 15)
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;

	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//enable the AHB Peripheral Clock to use GPIOB

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
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_Init(GPIOE, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);
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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//enable the AHB Peripheral Clock to use GPIOB

	/* Pin configuration */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	if (channel == 1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOC, GPIO_Pin_6, GPIO_AF_TIM8);//connect the pin to the desired peripherals' Alternate Function (AF) - TIM4 (GPIO_AF_2)
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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//enable the AHB Peripheral Clock to use GPIOB

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
	timerInitStructure.TIM_Period = counter - 1;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM, &timerInitStructure);
	TIM_Cmd(TIM, ENABLE);
	TIM_ITConfig(TIM, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef nvicStructure;
	if (TIM == TIM1)
		nvicStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
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
		nvicStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;


	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

}

void I2C_Config(I2C_TypeDef* I2Cx,uint16_t I2C_Ack)
{
	// GPIO Settings

	GPIO_InitTypeDef GPIO_InitStructure;			//structure for GPIO setup

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	switch ((uint32_t)I2Cx) {
		case I2C1_BASE:
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
//			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//			GPIO_Init(GPIOB, &GPIO_InitStructure);
//			GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
//			GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
			break;
		case I2C2_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
			GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);
			break;
		case I2C3_BASE:
//			RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
//			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//			GPIO_Init(GPIOA, &GPIO_InitStructure);
//			GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_I2C3);
//			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//			GPIO_Init(GPIOC, &GPIO_InitStructure);
//			GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_I2C3);
			break;
		default:
			break;
		}


	I2C_InitTypeDef I2C_InitStruct;

	/* initialize the I2C_ClockSpeed member */
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	/* Initialize the I2C_Mode member */
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	/* Initialize the I2C_DutyCycle member */
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	/* Initialize the I2C_OwnAddress1 member */
	I2C_InitStruct.I2C_OwnAddress1 = 0;
	/* Initialize the I2C_Ack member */
	I2C_InitStruct.I2C_Ack = I2C_Ack;
	/* Initialize the I2C_AcknowledgedAddress member */
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

//	I2C_Cmd(I2Cx, DISABLE);
	I2C_Cmd(I2Cx, ENABLE);

	I2C_Init(I2Cx, &I2C_InitStruct);
//	I2C_Cmd(I2Cx, ENABLE);
}

void USART_init(void)
{
	  GPIO_InitTypeDef     GPIO_InitStruct;

	  // Enable clock for GPIOA

	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	  // Initialize pins as alternating function
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStruct);

	  USART_InitTypeDef USART_InitStruct;
	  NVIC_InitTypeDef NVIC_InitStruct;

	  /**
	   * Enable clock for USART1 peripheral
	   */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	  /**
	   * Set Baudrate to value you pass to function
	   * Disable Hardware Flow control
	   * Set Mode To TX and RX, so USART will work in full-duplex mode
	   * Disable parity bit
	   * Set 1 stop bit
	   * Set Data bits to 8
	   *
	   * Initialize USART1
	   * Activate USART1
	   */

	  USART_InitStruct.USART_BaudRate = 1500000;
	  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	  USART_InitStruct.USART_Parity = USART_Parity_No;
	  USART_InitStruct.USART_StopBits = USART_StopBits_1;
	  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	  USART_Init(USART2, &USART_InitStruct);
	  USART_Cmd(USART2, ENABLE);

	  /**
	   * Enable RX interrupt
	   */
	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	  /**
	   * Set Channel to USART2
	   * Set Channel Cmd to enable. That will enable USART2 channel in NVIC
	   * Set Both priorities to 0. This means high priority
	   *
	   * Initialize NVIC
	   */
	  NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	  NVIC_Init(&NVIC_InitStruct);
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



