/*
 * STM32F3_my.h
 *     4 3 5 6 8 9 7 10
 *  Created on: Dec 30, 2012
 *      Author: Dawid
 */

//#include "stm32f30x.h"
//#include "stm32f3_discovery.h"
//#include "stm32f30x_it.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#ifndef STM32F3_MY_H_
#define STM32F3_MY_H_
#endif /* STM32F3_MY_H_ */

//	Za³¹czanie led'ów
#define LED3_on STM_EVAL_LEDOn(LED4)
#define LED4_on STM_EVAL_LEDOn(LED3)
#define LED5_on STM_EVAL_LEDOn(LED5)
#define LED6_on STM_EVAL_LEDOn(LED6)
#define LED7_on STM_EVAL_LEDOn(LED9)
#define LED8_on STM_EVAL_LEDOn(LED7)
#define LED9_on STM_EVAL_LEDOn(LED8)
#define LED10_on STM_EVAL_LEDOn(LED10)

//	Wy³¹czanie led'ów
#define LED3_off STM_EVAL_LEDOff(LED4)
#define LED4_off STM_EVAL_LEDOff(LED3)
#define LED5_off STM_EVAL_LEDOff(LED5)
#define LED6_off STM_EVAL_LEDOff(LED6)
#define LED7_off STM_EVAL_LEDOff(LED9)
#define LED8_off STM_EVAL_LEDOff(LED7)
#define LED9_off STM_EVAL_LEDOff(LED8)
#define LED10_off STM_EVAL_LEDOff(LED10)

//	Prze³¹czanie led'ów
#define LED3_T STM_EVAL_LEDToggle(LED4)
#define LED4_T STM_EVAL_LEDToggle(LED3)
#define LED5_T STM_EVAL_LEDToggle(LED5)
#define LED6_T STM_EVAL_LEDToggle(LED6)
#define LED7_T STM_EVAL_LEDToggle(LED9)
#define LED8_T STM_EVAL_LEDToggle(LED7)
#define LED9_T STM_EVAL_LEDToggle(LED8)
#define LED10_T STM_EVAL_LEDToggle(LED10)

//typedef enum
//{
//  GPIO_TypeDef*  GPIO_A  = GPIOA,
//  GPIO_B  = GPIOB_BASE,
//  GPIO_C  = GPIOC_BASE,
//  GPIO_D  = GPIOD_BASE,
//  GPIO_E  = GPIOE_BASE,
//  GPIO_F  = GPIOF_BASE
//}GPIOS_TypeDef;



void GPIO_PinInit(GPIO_TypeDef* Port, uint16_t Pin, GPIOMode_TypeDef Mode, GPIOOType_TypeDef Type, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed);
void GPIO_PinSet(GPIO_TypeDef* Port, uint16_t Pin);
void GPIO_PinRes(GPIO_TypeDef* Port, uint16_t Pin);
void GPIO_PinTog(GPIO_TypeDef* Port, uint16_t Pin);
void GPIO_PinOut(GPIO_TypeDef* Port, uint16_t Pin);
void GPIO_PinIn(GPIO_TypeDef* Port, uint16_t Pin);
uint32_t GPIO_GetState(GPIO_TypeDef* Port, uint16_t Pin);
void LED_init(void);
void LEDs_off(void);
void LEDs_on(void);
void delay_s (uint32_t s);
void delay_ms (uint32_t ms);
void delay_qs (uint16_t qs);
void EXTI_Config(GPIO_TypeDef* Port, uint16_t Pin,  EXTITrigger_TypeDef Mode);
void TIM_Config(uint32_t TIM, uint16_t prescaler, uint32_t counter);            //2, 3, 4, 6, 7 timers
void TIM1_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter);
void TIM8_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter);
void TIM4_PWM_Config(uint8_t channel, uint16_t prescaler, uint16_t counter);





/**********************************************************
 *
 *
 * 		Aby u¿yæ ledów nale¿y jenajpierw zainicjalizowaæ
 * korzystaj¹c z funkcji 'LED_init();'
 *
 *
 * 		Aby sprawdziæ status na wejciu u¿ywamy :
 *
 * 	STM_EVAL_PBInit(BUTTON_USER , BUTTON_MODE_GPI0); oraz
 *	if (STM_EVAL_PBGetState(BUTTON_USER) == 1)
 *
 *		Aby skorzystaæ z EXTI u¿ywamy :
 *
 *	STM_EVAL_PBInit(BUTTON_USER , BUTTON_MODE_EXTI);
 *	EXTI0_Config();
 *
 *********************************************************/
