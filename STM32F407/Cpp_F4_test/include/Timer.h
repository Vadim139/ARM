//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef TIMER_H_
#define TIMER_H_

#include "cmsis_device.h"

// ----------------------------------------------------------------------------

class Timer
{
public:
  typedef uint32_t ticks_t;
  static constexpr ticks_t FREQUENCY_HZ = 1000u;

private:
  static volatile ticks_t us_delayCount;

public:
  // Default constructor
  Timer() = default;

  inline void
  start(void)
  {
    // Use SysTick as reference for the delay loops.
    SysTick_Config(168);//FREQUENCY_HZ);
  }

  static void
  sleep(__IO uint32_t us);
  void
  mssleep(__IO uint32_t ms);

  inline static void
  tick(void)
  {
    // Decrement to zero the counter used by the delay routine.
    if (us_delayCount != 0u)
      {
        --us_delayCount;
      }
  }
};

// ----------------------------------------------------------------------------

#endif // TIMER_H_
