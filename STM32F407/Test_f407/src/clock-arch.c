//#include "global-conf.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//#include <avr/interrupt.h>
//#include <avr/io.h>
//#include <avr/sfr_defs.h>
#include "STM32F3_my.h"
#include "clock-arch.h"

//Counted time
clock_time_t clock_datetime = 0;

//Overflow itnerrupt
//ISR(TIMER0_OVF_vect)
//{
//	clock_datetime += 1;
////	TIFR0 |= (1<<TOV0);
//}

void TIM7_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        clock_datetime += 1;
    }
}

//Initialise the clock
void clock_init(){
	//Activate overflow interrupt for timer0
//	TIMSK0 |= (1<<TOIE0);
TIM_Config(TIM7,1024,84);
	//Use prescaler 1024
//	TCCR0A |= ((1<<CS02)|(1<<CS00));

	//Activate interrupts
//	sei();
}

//Return time
clock_time_t clock_time(){
	clock_time_t time;

//	cli();
	time = clock_datetime;
//	sei();

	return time;
}
