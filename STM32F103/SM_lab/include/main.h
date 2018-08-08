/*
 * main.h
 *
 *  Created on: 28 paü 2017
 *      Author: Vadim
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_flash.h"
#include "diag/Trace.h"
#include "string.h"
#include "STM32F4_Class.h"
//#include "ESP8266.h"
//#include "Timer.h"

#define IN12_GPIO      	GPIOB
#define IN12_PIN  		GPIO_Pin_0

#define O1_GPIO      	GPIOB
#define O1_PIN  		GPIO_Pin_9
#define O2_GPIO      	GPIOB
#define O2_PIN  		GPIO_Pin_8
#define O3_GPIO      	GPIOB
#define O3_PIN  		GPIO_Pin_7
#define O4_GPIO      	GPIOB
#define O4_PIN  		GPIO_Pin_6

#define W1_GPIO      	GPIOB
#define W1_PIN  		GPIO_Pin_5
#define W2_GPIO      	GPIOB
#define W2_PIN  		GPIO_Pin_4
#define W3_GPIO      	GPIOB
#define W3_PIN  		GPIO_Pin_3
#define W4_GPIO      	GPIOA
#define W4_PIN  		GPIO_Pin_15
#define W5_GPIO      	GPIOA
#define W5_PIN  		GPIO_Pin_12

#define M1_GPIO      	GPIOA
#define M1_PIN  		GPIO_Pin_8
#define M2_GPIO      	GPIOB
#define M2_PIN  		GPIO_Pin_15
#define M3_GPIO      	GPIOB
#define M3_PIN  		GPIO_Pin_14
#define M4_GPIO      	GPIOB
#define M4_PIN  		GPIO_Pin_13
#define M5_GPIO      	GPIOB
#define M5_PIN  		GPIO_Pin_12

//Timer timer;

#ifdef __cplusplus
 extern "C" {
#endif
 void delayms(uint32_t ms);
void USART1_IRQHandler();
void USART2_IRQHandler();
void USART3_IRQHandler();
void TIM1_UP_IRQHandler();
void RTC_IRQHandler(void);
void RTCAlarm_IRQHandler(void);
void EXTI0_IRQHandler(void);
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);

#ifdef __cplusplus
}
#endif
//void USART1_IRQHandler(void);

#endif /* MAIN_H_ */
