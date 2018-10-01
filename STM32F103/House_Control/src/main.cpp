/*
 * This file is part of the ÂµOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"
#include "RTC.h"


// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

IRTC RTC1;

GPIO_IO Led(GPIOC,GPIO_Pin_13,1);

char DataTime[30];

int main(int argc, char* argv[])
{
  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Initialization...");

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %u Hz\n", SystemCoreClock);

  memset(DataTime,0,30);

  Timer timer;
  timer.start();

  // Board LED
  Led.Init();
  Led.Set_low();

  // Init RTC
  RTC1.RTC_Config();
  RTC1.IT_Config();

  uint32_t seconds = 0;

 	trace_printf("Initialization end...\n");
  // Infinite loop
  while (1)
    {


	  timer.sleep(100);
    }

}

char buff[34];
void RTC_IRQHandler(void)
{

	if(RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		//sprawdzenie czy RTC siê nie przekrêci³ 24h
		if(RTC_GetCounter() >= (86400))
		{
			RTC_SetCounter(RTC_GetCounter() % (86400 - 1));
			RTC1.Day_inc();
		}

		//pobieranie aktualnego czasu tylko gdy nie jest przeprwadzane ustawiane czasu/alarmu
		if(RTC1.set == 0)
		{
			RTC1.time = RTC_GetCounter();
			RTC1.Time_s.Hour = (int)RTC1.time/3600;
			RTC1.Time_s.Minute = (int)(RTC1.time%3600)/60;
			RTC1.Time_s.Second = (int)(RTC1.time%3600)%60;
			//RTC1.alarm = RTC->ALRL | (RTC->ALRH << 16);

			trace_printf("Czas: %u:%u:%u\n", RTC1.Time_s.Hour, RTC1.Time_s.Minute, RTC1.Time_s.Second);

			Led.Toggle();
//			Ntc.Get_temp(temp);
//			trace_printf("Temp: %s\n\n",temp);

			//			adc = ADC_GetConversionValue(ADC1);
			//			adcv = adc * 3.3f / 4096.0f;
			//			temp = ((4148.88*298.15)/((log((21690*adcv)/((3.3-adcv)*10000))*298.15)+4148.88));
			//			sprintf(adcs,"Adc = %d %s V  T: %s\n\r", adc, floatToString(adcv,4),floatToString(temp-273.15,4));


//			sprintf(buff,"Data: %d-%d-%d Czas: %d:%d:%d\n\r", (int)RTC1.Date_s.Day, (int)RTC1.Date_s.Month, (long)RTC1.Date_s.Year,(int)RTC1.time/3600, (int)(RTC1.time%3600)/60, (int)(RTC1.time%3600)%60);
//			RS_TransferMulti(0,0,(unsigned char*)buff,strlen(buff));


		}

		RTC_WaitForLastTask();
		//wyczyszczenie bitu generujacego przerwanie

		RTC_ClearITPendingBit(RTC_IT_SEC);
	}
}

void RTCAlarm_IRQHandler(void)
{

	if(EXTI_GetITStatus(EXTI_Line17) != RESET)
	{
		//wyczyszczenie flagi przerwania
		EXTI_ClearITPendingBit(EXTI_Line17);
		//ustawienie zmiennej do ¿¹dania generowania sygna³u alarmu
		RTC1.alarm_reg = 1;

		//odczekanie na zakoñczenie operacji na RTC
		RTC_WaitForLastTask();
		//wyczyszczenie flagi przerwania
		RTC_ClearITPendingBit(RTC_IT_ALR);
		//odczekanie na zakoñczenie operacji na RTC
		RTC_WaitForLastTask();
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
