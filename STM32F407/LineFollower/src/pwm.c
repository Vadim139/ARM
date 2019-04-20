/**
  * @brief  Configure the TIM4 Ouput Channels.
  * @param  None
  * @retval None
  */

#include "stm32f4xx_tim.h"
#include "pwm.h"

uint16_t PrescalerValue = 0;

void pwm_init(void);

void pwm_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Alternating functions for pins */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
//    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
//    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

    /* Set pins */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;// | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    TIM_TimeBaseInitTypeDef TIM_BaseStruct;

       /* Enable clock for TIM4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_BaseStruct.TIM_Prescaler = 84;
	/* Count up */
	TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_BaseStruct.TIM_Period = 999; /* 10kHz PWM */
	TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseStruct.TIM_RepetitionCounter = 0;
	/* Initialize TIM4 */
	TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);
	/* Start count on TIM4 */
	TIM_Cmd(TIM4, ENABLE);

	TIM_OCInitTypeDef TIM_OCStruct;

	/* Common settings */

	/* PWM mode 2 = Clear on compare match */
	/* PWM mode 1 = Set on compare match */
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OCStruct.TIM_Pulse = 0; /* 25% duty cycle */
	TIM_OC1Init(TIM4, &TIM_OCStruct);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_OCStruct.TIM_Pulse = 0; /* 50% duty cycle */
	TIM_OC2Init(TIM4, &TIM_OCStruct);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

//	TIM_OCStruct.TIM_Pulse = 6299; /* 75% duty cycle */
//	TIM_OC3Init(TIM4, &TIM_OCStruct);
//	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
//
//	TIM_OCStruct.TIM_Pulse = 8399; /* 100% duty cycle */
//	TIM_OC4Init(TIM4, &TIM_OCStruct);
//	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
}
