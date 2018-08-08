//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "Timer.h"
#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

#if defined(USE_HAL_DRIVER)
extern "C" void HAL_IncTick(void);
#endif

// ----------------------------------------------------------------------------

volatile Timer::ticks_t Timer::ms_delayCount;
volatile uint32_t Timer::TimeOut;
volatile bool Timer::TO_flag;
volatile bool Timer::TO_run;
// ----------------------------------------------------------------------------

void
Timer::sleep(ticks_t ticks)
{
  ms_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (ms_delayCount != 0u)
    ;
}

void Timer::set_TimeOut(uint32_t t)
{
	  TimeOut = t;
	  TO_flag = false;
	  TO_run = true;
}

// ----- SysTick_Handler() ----------------------------------------------------

extern "C" void
SysTick_Handler(void)
{
#if defined(USE_HAL_DRIVER)
  HAL_IncTick();
#endif
  Timer::tick();
  Timer::TimeOut_tick();
}

//extern Timer timer;

void delay_ms (uint32_t ms)
{
	uint32_t i;
	ms = 6000 * ms;
	for(i = 0; i < ms; i++);
}
// ----------------------------------------------------------------------------


void TIM_Config(TIM_TypeDef *TIM, uint16_t prescaler, uint32_t counter) //TIM1,2,3  72000 i 100 -> 10Hz
{

	if(TIM == TIM1)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	else if(TIM == TIM2)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	else if(TIM == TIM3)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//	else if(TIM == TIM4)
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


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
		nvicStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	else if (TIM == TIM2)
		nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
	else if (TIM == TIM3)
		nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
//	else if (TIM == TIM4)
//		nvicStructure.NVIC_IRQChannel = TIM4_IRQn;


	nvicStructure.NVIC_IRQChannelPreemptionPriority = 5;
	nvicStructure.NVIC_IRQChannelSubPriority = 5;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

}
