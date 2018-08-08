#include "stdlib.h"
#include "stdio.h"
#include "common.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "STM32F3_my.h"


#define Led_Port GPIOB
#define Led1 GPIO_Pin_0
#define Led2 GPIO_Pin_1
#define Led3 GPIO_Pin_2

#define SW_Port GPIOA
#define SW1 GPIO_Pin_1
#define SW2 GPIO_Pin_2
#define SW3 GPIO_Pin_3
#define SW4 GPIO_Pin_4

volatile uint8_t ext_flag = 0;
volatile uint8_t active_mot = 0;
volatile uint8_t mot_comp = 0;


int main(void)
   {
	int ii;

		unsigned int k, l;

	/* Example use SysTick timer and read System core clock */
	SysTick_Config(168);  /* 1 us if clock frequency 72 MHz */

//	SystemCoreClockUpdate();
	ii = SystemCoreClock;   /* This is a way to read the System core clock */



	GPIO_PinOut(Led_Port, Led1);
	GPIO_PinOut(Led_Port, Led2);
	GPIO_PinOut(Led_Port, Led3);


	EXTI_Config(SW_Port, SW1, EXTI_Trigger_Falling);
	EXTI_Config(SW_Port, SW2, EXTI_Trigger_Falling);
	EXTI_Config(SW_Port, SW3, EXTI_Trigger_Falling);
	EXTI_Config(SW_Port, SW4, EXTI_Trigger_Falling);



	while (1)
	{

		switch (active_mot) {
			case 1:
				TIM_SetCompare1(TIM4, mot_comp);//(0us / 50us = 0.0)
				TIM_SetCompare2(TIM4, 0);
				TIM_SetCompare3(TIM4, 0);
				TIM_SetCompare4(TIM4, 0);
				break;
			case 2:
				TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
				TIM_SetCompare2(TIM4, mot_comp);
				TIM_SetCompare3(TIM4, 0);
				TIM_SetCompare4(TIM4, 0);
				break;
			case 3:
				TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
				TIM_SetCompare2(TIM4, 0);
				TIM_SetCompare3(TIM4, mot_comp);
				TIM_SetCompare4(TIM4, 0);
				break;
			case 4:
				TIM_SetCompare1(TIM4, 0);//(0us / 50us = 0.0)
				TIM_SetCompare2(TIM4, 0);
				TIM_SetCompare3(TIM4, 0);
				TIM_SetCompare4(TIM4, mot_comp);
				break;
			default:
				break;
		}

	}

	return 0;
}
