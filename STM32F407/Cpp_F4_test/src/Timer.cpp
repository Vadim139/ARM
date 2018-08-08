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

volatile Timer::ticks_t Timer::us_delayCount;
__IO uint32_t TimingDelay = 0;
// ----------------------------------------------------------------------------

void
Timer::sleep(__IO uint32_t us)
{
	TimingDelay = us;
	while(TimingDelay != 0);
}
void
Timer::mssleep(__IO uint32_t ms)
{
	TimingDelay = ms * 1000;
	while(TimingDelay != 0);
}

// ----- SysTick_Handler() ----------------------------------------------------

extern "C" void
SysTick_Handler()
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

// ----------------------------------------------------------------------------
