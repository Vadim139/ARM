/*
 * common.c
 *
 *  Created on: Nov 14, 2012
 *      Author: andrei
 */


#include "common.h"
//#include "LCD_STM32F4.h"

__IO uint32_t TimingDelay = 0;
char Prescaler = 200;

/**
 **===========================================================================
 **
 **  Abstract: SysTick interrupt handler
 **
 **===========================================================================
 */
//void SysTick_Handler(void)
//{
//	if (TimingDelay != 0x00)
//	{
//		TimingDelay--;
//	}
//}

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
		Prescaler--;
	if(Prescaler == 0)
	{
		Prescaler=200;
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	}
}

void _delay_s (uint32_t s)
{
	_delay_ms(1000 * s);
}
/**
 * @brief  Inserts a delay time.
 * @param  ms: specifies the delay time length, in ms.
 * @retval None
 */
void _delay_ms(__IO uint32_t ms)
{
	TimingDelay = ms * 1000;
	while(TimingDelay != 0);
}

/**
 * @brief  Inserts a delay time.
 * @param  ms: specifies the delay time length, in ms.
 * @retval None
 */
void _delay_us(__IO uint32_t us)
{
	TimingDelay = us;
	while(TimingDelay != 0);
}

void Delay_ms(__IO uint32_t nTime)
{
  TimingDelay = nTime*1000;

  while(TimingDelay != 0)
  {
  }
}

/*
 * Decrements the TimingDelay variable.
 * Called from interrupt.
 */

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

