/**
  ******************************************************************************
  * @file    stm32303c_eval.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    02-October-2012
  * @brief   This file contains definitions for STM32303C_EVAL's Leds, push-buttons
  *          and COM ports hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32303C_EVAL_H
#define __STM32303C_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"
#include "stm32_eval_legacy.h"

/** 
  * @brief  Define for STM32303C_EVAL board  
  */ 
#if !defined (USE_STM32303C_EVAL)
 #define USE_STM32303C_EVAL
#endif


/** @addtogroup STM32303C_EVAL_LOW_LEVEL_SD_SPI
  * @{
  */
/**
  * @brief  SD SPI Interface pins
  */
#define SD_SPI                           SPI2
#define SD_SPI_CLK                       RCC_APB1Periph_SPI2

#define SD_SPI_SCK_PIN                   GPIO_Pin_9                  /* PF.09 */
#define SD_SPI_SCK_GPIO_PORT             GPIOF                       /* GPIOF */
#define SD_SPI_SCK_GPIO_CLK              RCC_AHBPeriph_GPIOF
#define SD_SPI_SCK_SOURCE                GPIO_PinSource9
#define SD_SPI_SCK_AF                    GPIO_AF_5

#define SD_SPI_MISO_PIN                  GPIO_Pin_14                  /* PB.14 */
#define SD_SPI_MISO_GPIO_PORT            GPIOB                       /* GPIOB */
#define SD_SPI_MISO_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define SD_SPI_MISO_SOURCE               GPIO_PinSource14
#define SD_SPI_MISO_AF                   GPIO_AF_5

#define SD_SPI_MOSI_PIN                  GPIO_Pin_15                  /* PB.15 */
#define SD_SPI_MOSI_GPIO_PORT            GPIOB                       /* GPIOB */
#define SD_SPI_MOSI_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define SD_SPI_MOSI_SOURCE               GPIO_PinSource15
#define SD_SPI_MOSI_AF                   GPIO_AF_5

#define SD_CS_PIN                        GPIO_Pin_15                  /* PE.15 */
#define SD_CS_GPIO_PORT                  GPIOE                       /* GPIOE */
#define SD_CS_GPIO_CLK                   RCC_AHBPeriph_GPIOF

   
#define SD_DETECT_PIN                    GPIO_Pin_6                 /* PC.06 */
#define SD_DETECT_EXTI_LINE              EXTI_Line6
#define SD_DETECT_EXTI_PIN_SOURCE        EXTI_PinSource6
#define SD_DETECT_GPIO_PORT              GPIOC                       /* GPIOC */
#define SD_DETECT_GPIO_CLK               RCC_AHBPeriph_GPIOC
#define SD_DETECT_EXTI_PORT_SOURCE       EXTI_PortSourceGPIOC
#define SD_DETECT_EXTI_IRQn              EXTI9_5_IRQn

void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void); 



#endif /* __STM32303C_EVAL_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
