//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "diag/Trace.h"
#include "tm_stm32_gpio.h"
#include "tm_stm32_rcc.h"
#include "Timer.h"
#include "BlinkLed.h"

// ----------------------------------------------------------------------------
//
// STM32F4 led blink sample (trace via ITM).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// To demonstrate POSIX retargetting, reroute the STDOUT and STDERR to the
// trace device and display messages on both of them.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// On DEBUG, the uptime in seconds is also displayed on the trace device.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the ITM output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// Definitions visible only within this translation unit.
//namespace
//{
//  // ----- Timing definitions -------------------------------------------------
//
//  // Keep the LED on for 2/3 of a second.
//  constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
//  constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ
//      - BLINK_ON_TICKS;
//}

// ----- LED definitions ------------------------------------------------------


//#elif defined(STM32F407xx)
//
//#warning "Assume a STM32F4-Discovery board, PC12-PC15, active high."
//
//#define BLINK_PORT_NUMBER         GPIOA
//#define BLINK_PIN_NUMBER_GREEN    GPIO_PIN_0
//#define BLINK_PIN_NUMBER_ORANGE   GPIO_PIN_1
//#define BLINK_PIN_NUMBER_RED      GPIO_PIN_2
//#define BLINK_PIN_NUMBER_BLUE     GPIO_PIN_3
//#define BLINK_ACTIVE_LOW          (false)



// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	TM_RCC_InitSystem();


}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------

////BlinkLed blinkLeds[4] =
////  {
////    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_GREEN, BLINK_ACTIVE_LOW },
////    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_ORANGE, BLINK_ACTIVE_LOW },
////    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_RED, BLINK_ACTIVE_LOW },
////    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_BLUE, BLINK_ACTIVE_LOW },
////  };
//
//#elif defined(STM32F411xE)
//
//#warning "Assume a NUCLEO-F411RE board, PA5, active high."
//
//#define BLINK_PORT_NUMBER         (0)
//#define BLINK_PIN_NUMBER          (5)
//#define BLINK_ACTIVE_LOW          (false)
//
//BlinkLed blinkLeds[1] =
//  {
//    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER, BLINK_ACTIVE_LOW },
//  };
//
//#elif defined(STM32F429xx)
//
//#warning "Assume a STM32F429I-Discovery board, PG13-PG14, active high."
//
//#define BLINK_PORT_NUMBER         (6)
//#define BLINK_PIN_NUMBER_GREEN    (13)
//#define BLINK_PIN_NUMBER_RED      (14)
//#define BLINK_ACTIVE_LOW          (false)
//
//BlinkLed blinkLeds[2] =
//  {
//    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_GREEN, BLINK_ACTIVE_LOW },
//    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_RED, BLINK_ACTIVE_LOW },
//  };
//
//#else
//
//#warning "Unknown board, assume PA5, active high."
//
//#define BLINK_PORT_NUMBER         (0)
//#define BLINK_PIN_NUMBER          (5)
//#define BLINK_ACTIVE_LOW          (false)
//
//BlinkLed blinkLeds[1] =
//  {
//    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER, BLINK_ACTIVE_LOW },
//  };
//
//#endif

//TM_GPIO_Init(GPIOA,GPIO_PIN_0,TM_GPIO_Mode_OUT,TM_GPIO_OType_PP,TM_GPIO_PuPd_UP,TM_GPIO_Speed_Fast);
//	TM_GPIO_Init(GPIOA,GPIO_PIN_1,TM_GPIO_Mode_OUT,TM_GPIO_OType_PP,TM_GPIO_PuPd_UP,TM_GPIO_Speed_Fast);
//	TM_GPIO_Init(GPIOA,GPIO_PIN_2,TM_GPIO_Mode_OUT,TM_GPIO_OType_PP,TM_GPIO_PuPd_UP,TM_GPIO_Speed_Fast);
//	TM_GPIO_Init(GPIOA,GPIO_PIN_3,TM_GPIO_Mode_OUT,TM_GPIO_OType_PP,TM_GPIO_PuPd_UP,TM_GPIO_Speed_Fast);
//  // By customising __initialize_args() it is possible to pass arguments,
//  // for example when running tests with semihosting you can pass various
//  // options to the test.
//  // trace_dump_args(argc, argv);
//
//  // Send a greeting to the trace device (skipped on Release).
//  trace_puts("Hello ARM World!");
//
//  // The standard output and the standard error should be forwarded to
//  // the trace device. For this to work, a redirection in _write.c is
//  // required.
//  puts("Standard output message.");
////  fprintf(stderr, "Standard error message.\n");
//
//  // At this stage the system clock should have already been configured
//  // at high speed.
//  trace_printf("System clock: %u Hz\n", SystemCoreClock);
//
//  Timer timer;
//  timer.start ();
//
////  Led Led1(GPIOA, GPIO_PIN_0);
////
////  Led1.Init();
////  Led1.Turn_on();
//
////  for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
////    {
////      blinkLeds[i].powerUp ();
////    }
////cout << "";
////  uint32_t seconds = 0;
//  while(1){
//    // Perform all necessary initialisations for the LEDs.
//    TM_GPIO_SetPinHigh(GPIOA, GPIO_PIN_0);
////  for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
////    {
////      blinkLeds[i].turnOn ();
////    }
//
//  // First second is long.
//  timer.mssleep (750);
//  TM_GPIO_SetPinLow(GPIOA, GPIO_PIN_0);
////  for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
////    {
////      blinkLeds[i].turnOff ();
////    }
//
//  timer.mssleep (250);
//
////  ++seconds;
////  trace_printf ("Second %u\n", seconds);
//}
////  if ((sizeof(blinkLeds) / sizeof(blinkLeds[0])) > 1)
////    {
////      // Blink individual LEDs.
////      for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
////        {
////    	  TM_GPIO_SetPinHigh(GPIOA, GPIO_PIN_0);
//////          blinkLeds[i].turnOn ();
////          timer.sleep (BLINK_ON_TICKS);
////          TM_GPIO_SetPinLow(GPIOA, GPIO_PIN_0);
//////          blinkLeds[i].turnOff ();
////          timer.sleep (BLINK_OFF_TICKS);
////
////          ++seconds;
////          trace_printf ("Second %u\n", seconds);
////        }
////
////      // Blink binary.
////      while (1)
////        {
////          for (size_t l = 0; l < (sizeof(blinkLeds) / sizeof(blinkLeds[0]));
////              ++l)
////            {
////              blinkLeds[l].toggle ();
////              if (blinkLeds[l].isOn ())
////                {
////                  break;
////                }
////            }
////          timer.sleep (Timer::FREQUENCY_HZ);
////
////          ++seconds;
////          trace_printf ("Second %u\n", seconds);
////        }
////      // Infinite loop, never return.
////    }
////  else
////    {
////      while (1)
////        {
////          blinkLeds[0].turnOn ();
////          timer.sleep (BLINK_ON_TICKS);
////
////          blinkLeds[0].turnOff ();
////          timer.sleep (BLINK_OFF_TICKS);
////
////          ++seconds;
////          trace_printf ("Second %u\n", seconds);
////        }
////      // Infinite loop, never return.
////    }
