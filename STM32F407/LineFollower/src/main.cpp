/**
 *
 */
/* Includes *******************************************************************/
#include "main.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "STM32F3_my.h"
#include "tm_stm32f4_adc.h"
#include "STM32F4_my.h"
#include "tm_stm32f4_mco_output.h"
#include "Timer.h"
#include "diag/Trace.h"
#include "Sensor.h"

uint32_t k[10];
uint8_t i = 0;
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO TestStatus  TransferStatus = FAILED;

#define TRUE true
#define FALSE false

void GPIOAinit_TIM2_ETR(void) {
GPIO_InitTypeDef GPIO_InitStructure; // 2
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 4

 GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2); // PA15:TIM2_Ch1/ETR // 6
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // 8
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 9
 GPIO_Init(GPIOA, &GPIO_InitStructure); // 10
}

void TIM2init_counter(void) { // counting from ETR
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; // 2

 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 4
 TIM_TimeBaseInitStructure.TIM_Prescaler = 0; // 6
 TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 7
 TIM_TimeBaseInitStructure.TIM_Period = 100000; // 8
 TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 9

 TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure); // 10

 TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00); // 12

 TIM_Cmd(TIM2, ENABLE); // 14
}

void TIM1_ICConfig(void)

{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

//   //Time initialization

  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //Control with dead zone.

  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //Counter direction

  TIM_TimeBaseInitStructure.TIM_Prescaler = 84-1;   //Timer clock = sysclock /(TIM_Prescaler+1) = 2M

  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;

//Period = (TIM counter clock / TIM output clock) - 1 = 40Hz

  GPIO_InitTypeDef GPIO_InitStructure; // 2
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // 4

   GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1); // PA15:TIM2_Ch1/ETR // 6
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; // 8
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 9
   GPIO_Init(GPIOA, &GPIO_InitStructure); // 10

  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;

  TIM_ICInitStructure.TIM_ICFilter = 0;

  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;

  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;

  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;

  TIM_ICInit(TIM1,&TIM_ICInitStructure);

  TIM_Cmd(TIM1,ENABLE);

}

void TIM4_OCConfig(void)

{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInitStructure.TIM_Prescaler =  0;

  TIM_TimeBaseInitStructure.TIM_RepetitionCounter =0;

  TIM_TimeBaseInitStructure.TIM_Period = 42000-1;   //Cycle: 42M/(42000)= 1K

  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* GPIOD Configuration: TIM3 CH1 (PD12) and TIM3 CH2 (PD13) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 || GPIO_Pin_13 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Connect TIM3 pins to AF2 */
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);

  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);


  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

  TIM_OCInitStructure.TIM_Pulse = 10000;

  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;


  TIM_OC1Init(TIM4,&TIM_OCInitStructure);

  TIM_Cmd(TIM4,ENABLE);

}

int main (void)
{

  /* Initialization */

	RCC_HSEConfig(RCC_HSE_ON);
	while(!RCC_WaitForHSEStartUp())
	{
	}

//
//  Init_SysTick();
//  SysTick_Config(168);

	printf("Timer initialization...");
	Timer timer;
	timer.start();
	printf(" Succeed\n");

    TM_ADC_Init(ADC1,TM_ADC_Channel_10);//PC0
    TM_ADC_Init(ADC1,TM_ADC_Channel_11);//PC1
    TM_ADC_Init(ADC1,TM_ADC_Channel_12);//PC2
    TM_ADC_Init(ADC1,TM_ADC_Channel_13);//PC3

    pwm_init(); //PD12

    //	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_1);

//    GPIOAinit_TIM2_ETR(); // GPIO clock enable, digital pin definitions // 8
//    TIM2init_counter(); // Timer 2 as counter: ETR input // 9
//    TIM1_ICConfig();
//	TIM4_OCConfig();
    TIM_SetCompare1(TIM4, 0);
    TIM_SetCompare2(TIM4, 0);

    GPIO_InitTypeDef GPIO_InitStruct;
     EXTI_InitTypeDef EXTI_InitStruct;
     NVIC_InitTypeDef NVIC_InitStruct;

     /* Enable clock for GPIOD */
     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
     /* Enable clock for SYSCFG */
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

     /* Set pin as input */
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
     GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
     GPIO_Init(GPIOA, &GPIO_InitStruct);

     /* Tell system that you will use PD0 for EXTI_Line0 */
     SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

     /* PD0 is connected to EXTI_Line0 */
     EXTI_InitStruct.EXTI_Line = EXTI_Line0;
     /* Enable interrupt */
     EXTI_InitStruct.EXTI_LineCmd = ENABLE;
     /* Interrupt mode */
     EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
     /* Triggers on rising and falling edge */
     EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
     /* Add to EXTI */
     EXTI_Init(&EXTI_InitStruct);

     /* Add IRQ vector to NVIC */
     /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
     NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
     /* Set priority */
     NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
     /* Set sub priority */
     NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
     /* Enable interrupt */
     NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
     /* Add to NVIC */
     NVIC_Init(&NVIC_InitStruct);


//    EXTI_Config(GPIOA,GPIO_Pin_0,EXTI_Trigger_Rising);
    uint32_t CaptureNumber = 0;
    uint32_t counter = 0;
    uint32_t Time = 0;
    uint32_t freq = 0;

	uint16_t ADC_1 = 0;
	char ADCs1[5] = {0,0,0,0,0};
	uint16_t ADC_2 = 0;
	char ADCs2[5] = {0,0,0,0,0};
	uint16_t ADC_3 = 0;
	char ADCs3[5] = {0,0,0,0,0};
	uint16_t ADC_4 = 0;
	char ADCs4[5] = {0,0,0,0,0};

//	Sensor LZ(3900,3650,3570,3555,ADC1,TM_ADC_Channel_10);
//	Sensor LS(3630,3000,3110,2860,ADC1,TM_ADC_Channel_11);
//	Sensor PS(3900,3500,3560,3400,ADC1,TM_ADC_Channel_12);
//	Sensor PZ(3480,2930,3000,2865,ADC1,TM_ADC_Channel_13);

//	Sensor LZ(3900,3650,3580,3630,ADC1,TM_ADC_Channel_10);
//	Sensor LS(3890,2990,2930,3058,ADC1,TM_ADC_Channel_11);
//	Sensor PS(4050,3505,3475,3520,ADC1,TM_ADC_Channel_12);
//	Sensor PZ(3580,3090,2940,3110,ADC1,TM_ADC_Channel_13);


//	Sensor LZ(3790,2250,2200,1900,ADC1,TM_ADC_Channel_10);
//	Sensor LS(3750,300,400,50,ADC1,TM_ADC_Channel_11);
//	Sensor PS(4060,2000,2220,1500,ADC1,TM_ADC_Channel_12);
//	Sensor PZ(3400,1500,1205,600,ADC1,TM_ADC_Channel_13);

	Sensor LZ(4000,3400,3200,3150,ADC1,TM_ADC_Channel_10);
	Sensor LS(3800,1850,1750,1150,ADC1,TM_ADC_Channel_11);
	Sensor PS(4000,3100,2900,2550,ADC1,TM_ADC_Channel_12);
	Sensor PZ(3500,1900,1800,1350,ADC1,TM_ADC_Channel_13);

    while(1){

    	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_10);
    	uint16tostr(ADCs1, ADC_1, 10);
//    	trace_printf("ADC1: %s\n",ADCs1);
//    	puts(ADCs1);

    	ADC_2 = TM_ADC_Read(ADC1,TM_ADC_Channel_11);
    	uint16tostr(ADCs2, ADC_2, 10);
//    	trace_printf("ADC2: %s\n",ADCs2);

    	ADC_3 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
    	uint16tostr(ADCs3, ADC_3, 10);
//    	trace_printf("ADC3: %s\n",ADCs3);

    	ADC_4 = TM_ADC_Read(ADC1,TM_ADC_Channel_13);
    	uint16tostr(ADCs4, ADC_4, 10);
//    	trace_printf("ADC4: %s\n",ADCs4);
    	trace_printf("ADC1: %s   ADC2: %s   ADC3: %s   ADC4: %s   \n",ADCs1,ADCs2,ADCs3,ADCs4);
//    	trace_printf("LZ: %d   LS: %d   PS: %d   PZ: %d   \n",LZ.Get_color(),LS.Get_color(),PS.Get_color(),PZ.Get_color());
//    	if(LZ.Get_color() == BLACK)
//    	{
//    	    TIM_SetCompare1(TIM4, 0);
//    	    TIM_SetCompare2(TIM4, 0);
//    	}
//    	if(LS.Get_color() == BLUE)
//    	{
//    	    TIM_SetCompare1(TIM4, 0);
//    	    TIM_SetCompare2(TIM4, 0);
//    	}
//    	if(PS.Get_color() == BLUE)
//    	{
//    	    TIM_SetCompare1(TIM4, 0);
//    	    TIM_SetCompare2(TIM4, 0);
//    	}
//    	if(PZ.Get_color() == BLACK)
//    	{
//    	    TIM_SetCompare1(TIM4, 0);
//    	    TIM_SetCompare2(TIM4, 0);
//    	}

    	timer.sleep(100);
//
//    if(TIM_GetFlagStatus(TIM1,TIM_FLAG_CC1)==SET)
//
//    {
//
//    TIM_ClearFlag(TIM1,TIM_FLAG_CC1);
//
//    if(CaptureNumber == 0)
//
//    {
//
//    counter = TIM_GetCapture1(TIM1);  //The first capture
//
//    CaptureNumber = 1;
//
//    }
//
//    else if(CaptureNumber == 1)  //Treatment of second capture
//
//    {
//
//    if(TIM_GetFlagStatus(TIM1,TIM_FLAG_Update) != SET)//Treatment of two capture no overflow occurs
//
//    {
//
//    Time = TIM_GetCapture1(TIM1);
//
//    Time = Time - counter;
//
//    }
//
//    else
//
//    {
//
//    TIM_ClearFlag(TIM1,TIM_FLAG_Update);   //The update event
//
//    Time = 0xFFFF - counter + TIM_GetCapture1(TIM1)+1;  //If the calculation mode update events
//
//    }
//
//    CaptureNumber = 0;
//
//    if(Time!=0)
//
//    {
//
//    freq= 2000000/Time;  //Calculation of frequency
//    if(i<10){
//    	k[i] = freq;
//    	i++;
//    } else
//    	k[1] = 10;
////    printf("Counter: %d, Time: %d, freq:%d\n", counter,Time,freq);
//
//    }
////    printf("Counter: %d, Time: %d, freq:%d\n", counter,Time,freq);
////    freq = freq;  //To avoid the freq variable is compiler optimization.
//
//    }
//
//    }

    }

//  while (1) {
//		printf("%d\n", (uint32_t) TIM2->CNT); // show counts // 14
//		for (int i = 0; i < 1000000; i++) {
//		}; // waste time
//
//	}

}


void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {

//	  puts("hi");
	  delay_ms(500);
	    TIM_SetCompare1(TIM4, 900);
	    TIM_SetCompare2(TIM4, 900);


    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}
#endif

/**
  * @}
  */

/**
  * @}
  */

///******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

