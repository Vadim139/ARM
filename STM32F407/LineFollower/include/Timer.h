//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef TIMER_H_
#define TIMER_H_

#include "cmsis_device.h"
#include "main.h"
// ----------------------------------------------------------------------------

class Timer
{
public:
  typedef uint32_t ticks_t;
  static constexpr ticks_t FREQUENCY_HZ = 1000u;

private:
  static volatile ticks_t ms_delayCount;
  static volatile uint32_t TimeOut;
  static volatile bool TO_run;

public:

  static volatile bool TO_flag;
  // Default constructor
  Timer() = default;

  inline void
  start(void)
  {
    // Use SysTick as reference for the delay loops.
    SysTick_Config(SystemCoreClock / FREQUENCY_HZ);

    TO_flag = false;
    TO_run = true;
  }

  static void
  sleep(ticks_t ticks);

  void set_TimeOut(uint32_t t);

  inline static void
  tick(void)
  {
    // Decrement to zero the counter used by the delay routine.
    if (ms_delayCount != 0u)
      {
        --ms_delayCount;
      }

  }
  inline static void
   TimeOut_tick(void)
   {
	    if (TimeOut != 0u){
	    	--TimeOut;
	    }
	    else if(TO_run)
	    {
	    	TO_flag = true;
	    	TO_run = false;
	    }
   }
};


// ----------------------------------------------------------------------------

void delay_ms (uint32_t ms);

//void TIM_Config(TIM_TypeDef *TIM, uint16_t prescaler, uint32_t counter);
#endif // TIMER_H_

