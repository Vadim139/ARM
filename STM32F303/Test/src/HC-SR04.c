/*
 * HC-SR04.c
 *
 *  Created on: 2 lis 2014
 *      Author: Dawid
 */
#include "common.h"
#include "STM32F3_my.h"
#include "stm32f30x.h"
#include "stm32f30x_conf.h"
#include "stm32f3_discovery.h"
#include "lcdlib.h"
#include "HC-SR04.h"


void HC_init(void)
{
	GPIO_PinInit(SONAR_TRIGGER1_P, SONAR_TRIGGER1,GPIO_Mode_OUT,GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Level_3);
	EXTI_Config(SONAR_ECHO_P, SONAR_ECHO, EXTI_Trigger_Rising_Falling);
	TIM_Config(TIM7, 72, 10000);
	TIM_Cmd(TIM7, DISABLE);
	TIM_SetCounter(TIM7,0);
//	GPIO_PinSet(SONAR_TRIGGER1_P,SONAR_TRIGGER1);

}

int HC_get(void)
{
	TIM_SetCounter(TIM7,0);
	GPIO_PinSet(SONAR_TRIGGER1_P,SONAR_TRIGGER1);
		_delay_us(10);
	GPIO_PinRes(SONAR_TRIGGER1_P,SONAR_TRIGGER1);

	HC_flag = 1;
	while(HC_flag);

	return (TIM_GetCounter(TIM7) / 58);

}


void EXTI9_5_IRQHandler(void)
//void EXTI4_IRQHandler(void)
{
	GPIOB -> BSRR = GPIO_Pin_1;
	if(!HC_count_flag)
	{
		TIM_Cmd(TIM7, ENABLE);
		HC_count_flag = 1;
	}else
	{
		TIM_Cmd(TIM7, DISABLE);
		HC_count_flag = 0;
		HC_flag = 0;

	}

	EXTI_ClearITPendingBit(EXTI_Line5);

}

void TIM7_IRQHandler()
{
    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		TIM_Cmd(TIM7, DISABLE);
		TIM_SetCounter(TIM7,0);

		LCDPutStr("Fail in get distance", 10, 30, MEDIUM, WIB, RED, BLACK);

    }
}

