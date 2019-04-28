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
#include "Engine.h"
#include "5110.h"
//#include "stm32f4xx.h"

uint32_t k[10];
uint8_t i = 0;
/* Private typedef -----------------------------------------------------------*/
typedef enum {
	FAILED = 0, PASSED = !FAILED
} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO TestStatus TransferStatus = FAILED;

#define TRUE true
#define FALSE false

#define BUFFERSIZE 4 // 200KHz x2 HT/TC at 1KHz
__IO uint16_t ADCConvertedValues[BUFFERSIZE];
#include "stm32f4xx.h"
void ADC_DMA_config() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	/* ADC Channel 11 -> PC1*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2
			| GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	/* ADC Common Init */
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; // 1 Channel
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // Conversions Triggered
	ADC_InitStructure.ADC_ExternalTrigConvEdge =
	ADC_ExternalTrigConvEdge_Rising;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 4;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* ADC1 regular channel configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 4, ADC_SampleTime_15Cycles); // PC1
	/* Enable DMA request after last transfer (Single-ADC mode) */
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) &ADCConvertedValues;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = BUFFERSIZE; // Count of 16-bit words
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	/* Enable DMA Stream Half / Transfer Complete interrupt */
	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC | DMA_IT_HT, ENABLE);
	/* DMA2_Stream0 enable */
	DMA_Cmd(DMA2_Stream0, ENABLE);

	ADC_SoftwareStartConv(ADC1);

	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the DMA Stream IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void DMA2_Stream0_IRQHandler(void) // Called at 1 KHz for 200 KHz sample rate, LED Toggles at 500 Hz
		{
	/* Test on DMA Stream Half Transfer interrupt */
	if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_HTIF0)) {
		/* Clear DMA Stream Half Transfer interrupt pending bit */
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_HTIF0);
		/* Turn LED3 off: Half Transfer */
//STM_EVAL_LEDOff(LED3);
// Add code here to process first half of buffer (ping)
	}
	/* Test on DMA Stream Transfer Complete interrupt */
	if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0)) {
		/* Clear DMA Stream Transfer Complete interrupt pending bit */
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
		/* Turn LED3 on: End of Transfer */
//STM_EVAL_LEDOn(LED3);
//ADC_SoftwareStartConv(ADC1);
// Add code here to process second half of buffer (pong)
	}
}
Engine Eng_left(2);
Engine Eng_right(1);
char temp[50];
volatile bool Flag = false;

void TIM2_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* GPIOC clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* GPIOA Configuration: TIM2 CH1 (PA15) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // Input/Output controlled by peripheral
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // Button to ground expectation
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Connect TIM2 pins to AF */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TIxExternalClockConfig(TIM2, TIM_TIxExternalCLK1Source_TI1,
			TIM_ICPolarity_Falling, 15);
	TIM_Cmd(TIM2, ENABLE);
}

void TIM3_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* GPIOC clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* GPIOA Configuration: TIM3 CH1 (PC6) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // Input/Output controlled by peripheral
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // Button to ground expectation
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	/* Connect TIM3 pins to AF */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_TIxExternalClockConfig(TIM3, TIM_TIxExternalCLK1Source_TI1,
			TIM_ICPolarity_Falling, 15);
	TIM_Cmd(TIM3, ENABLE);
}

void TIM5_INT_Init() {
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	// (Hz) = 84MHz / ((839 + 1) * (9999 + 1)) = 10 Hz
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 9999;
	TIM_TimeBaseInitStruct.TIM_Period = 8399;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

	// TIM2 initialize
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
	// Enable TIM2 interrupt
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	// Start TIM2
	TIM_Cmd(TIM5, ENABLE);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI_Conf() {
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
}
volatile u16 RPM_L = 0;
volatile u16 RPM_P = 0;

int main(void) {

	/* Initialization */

	RCC_HSEConfig(RCC_HSE_ON);
	while (!RCC_WaitForHSEStartUp()) {
	}

//
//  Init_SysTick();
//  SysTick_Config(168);

	trace_printf("Timer initialization...");
	Timer timer;
	timer.start();
	trace_printf(" Succeed\n");

	ADC_DMA_config();

	LCD5110_init();

	TIM2_Configuration();
	TIM3_Configuration();
	TIM5_INT_Init();

	EXTI_Conf();
//	LCD5110_write_string("1234567890");

	Engine::Init(2);
//	Eng_left.Set_speed(20);
//	Eng_right.Set_speed(20);

//    EXTI_Config(GPIOA,GPIO_Pin_0,EXTI_Trigger_Rising);
	uint32_t CaptureNumber = 0;
	uint32_t counter = 0;
	uint32_t Time = 0;
	uint32_t freq = 0;

	uint16_t ADC_1 = 0;
	char ADCs1[5] = { 0, 0, 0, 0, 0 };
	uint16_t ADC_2 = 0;
	char ADCs2[5] = { 0, 0, 0, 0, 0 };
	uint16_t ADC_3 = 0;
	char ADCs3[5] = { 0, 0, 0, 0, 0 };
	uint16_t ADC_4 = 0;
	char ADCs4[5] = { 0, 0, 0, 0, 0 };

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

//	Sensor LZ(4000, 3400, 3200, 3150, ADC1, TM_ADC_Channel_10, &ADCConvertedValues[0]);
//	Sensor LS(3800, 1850, 1750, 1150, ADC1, TM_ADC_Channel_11, &ADCConvertedValues[1]);
//	Sensor PS(4000, 3100, 2900, 2550, ADC1, TM_ADC_Channel_12, &ADCConvertedValues[2]);
//	Sensor PZ(3500, 1900, 1800, 1350, ADC1, TM_ADC_Channel_13, &ADCConvertedValues[3]);

	Sensor LZ(3700, 3400, 3200, 3150, ADC1, TM_ADC_Channel_10,
			&ADCConvertedValues[0]);
	Sensor LS(3700, 1850, 1750, 1150, ADC1, TM_ADC_Channel_11,
			&ADCConvertedValues[1]);
	Sensor PS(4000, 3100, 2900, 2550, ADC1, TM_ADC_Channel_12,
			&ADCConvertedValues[2]);
	Sensor PZ(3300, 1900, 1800, 1350, ADC1, TM_ADC_Channel_13,
			&ADCConvertedValues[3]);

	uint8_t Last_inner = 0, Last_outer = 0;
	while (1) {
		if (Flag) {

			if (LZ.Get_color() == BLACK) {
//				Last_outer = LEFT_S;
//				if(last != 4){
//					last = 3;
//					Engine::Turn(LEFT, NORMAL_ONE, &Eng_left, &Eng_right);
//					timer.sleep(100);
//				}
////				Eng_left.Stop();
////				Eng_right.Stop();
////				Flag = false;
			}
			if (PZ.Get_color() == BLACK) {
//				Last_outer = RIGHT_S;
//				if(last != 3){
//					last = 4;
//					Engine::Turn(RIGHT, NORMAL_ONE, &Eng_left, &Eng_right);
//					timer.sleep(100);
//				}
////				Eng_left.Stop();
////				Eng_right.Stop();
////				Flag = false;
			}
			if (LS.Get_color() == BLACK && PS.Get_color() == BLACK) {
//				Eng_left.Set_speed(100);
//				Eng_right.Set_speed(100);
//				timer.sleep(30);
				Eng_left.Set_speed(5);
				Eng_right.Set_speed(5);
			} else if (LS.Get_color() == BLACK && PS.Get_color() != BLACK) {
//				if(Last_inner < 3){
				Last_inner = LEFT_S;
				Engine::Turn(LEFT, GENTLE_ONE, &Eng_left, &Eng_right);
//				}
			} else if (LS.Get_color() != BLACK && PS.Get_color() == BLACK) {
//				if(Last_inner < 3){
				Last_inner = RIGHT_S;
				Engine::Turn(RIGHT, GENTLE_ONE, &Eng_left, &Eng_right);
//				}
			} else if (LS.Get_color() != BLACK && PS.Get_color() != BLACK) {
				if (Last_outer == 0) {
					if (Last_inner == LEFT_S)
						Engine::Turn(LEFT, GENTLE_ONE, &Eng_left, &Eng_right);
					if (Last_inner == RIGHT_S)
						Engine::Turn(RIGHT, GENTLE_ONE, &Eng_left, &Eng_right);
				} else if (Last_outer < 3) {
					if (Last_outer == LEFT_S) {
						Engine::Turn(LEFT, NORMAL_ONE, &Eng_left, &Eng_right);
//						Last_outer = 3;
					}
					if (Last_outer == RIGHT_S) {
						Engine::Turn(RIGHT, NORMAL_ONE, &Eng_left, &Eng_right);
//						Last_outer = 4;
					}
				} else {
//					Eng_left.Set_speed(100);
//					Eng_right.Set_speed(100);
//					timer.sleep(30);
//					Eng_left.Set_speed(5);
//					Eng_right.Set_speed(5);
//					Last_outer = 0;
////					if(Last_outer == 3){
////
////					}else
////					{
//
////					}
				}
			}
		}
		LCD5110_set_XY(0, 0);
		sprintf(temp, "LZ: %d   LS: %d PS: %d   PZ: %d", LZ.Get_color(),
				LS.Get_color(), PS.Get_color(), PZ.Get_color());
		LCD5110_write_string(temp);
//		LCD5110_set_XY(0,3);
//		LCD5110_write_Dec(TIM_GetCounter(TIM2));
//		LCD5110_set_XY(5,3);
//		LCD5110_write_Dec(TIM_GetCounter(TIM3));
		LCD5110_set_XY(0, 3);
		LCD5110_write_Dec(RPM_L);
		LCD5110_set_XY(5, 3);
		LCD5110_write_Dec(RPM_P);
//		trace_printf("Counter: %d\n",TIM_GetCounter(TIM3));
		timer.sleep(100);
//		trace_printf("LZ: %d   LS: %d   PS: %d   PZ: %d   \n", LZ.Get_color(),
//				LS.Get_color(), PS.Get_color(), PZ.Get_color());
//		trace_printf("LZ: %d   LS: %d   PS: %d   PZ: %d   \n", ADCConvertedValues[0],
//				ADCConvertedValues[1], ADCConvertedValues[2], ADCConvertedValues[3]);
//    	ADC_1 = TM_ADC_Read(ADC1,TM_ADC_Channel_10);
//    	ADC_1 = ADC_GetConversionValue(ADC2);
//    	uint16tostr(ADCs1, ADC_1, 10);
////    	trace_printf("ADC1: %s\n",ADCs1);
////    	puts(ADCs1);
//
//    	ADC_2 = TM_ADC_Read(ADC1,TM_ADC_Channel_11);
//    	uint16tostr(ADCs2, ADC_2, 10);
////    	trace_printf("ADC2: %s\n",ADCs2);
//
//    	ADC_3 = TM_ADC_Read(ADC1,TM_ADC_Channel_12);
//    	uint16tostr(ADCs3, ADC_3, 10);
////    	trace_printf("ADC3: %s\n",ADCs3);
//
////    	ADC_4 = TM_ADC_Read(ADC1,TM_ADC_Channel_13);
//    	ADC_4 = ADC_GetConversionValue(ADC3);
//    	uint16tostr(ADCs4, ADC_4, 10);
////    	trace_printf("ADC4: %s\n",ADCs4);
//    	trace_printf("ADC2: %d\n",ADCConvertedValues[0]);
//    	trace_printf("LZ: %d   LS: %d   PS: %d   PZ: %d   \n",ADCConvertedValues[0],ADCConvertedValues[1],ADCConvertedValues[2],ADCConvertedValues[3]);
//    	trace_printf("ADC1: %s   ADC2: %s   ADC3: %s   ADC4: %s   \n",ADCs1,ADCs2,ADCs3,ADCs4);
//		trace_printf("LZ: %d   LS: %d   PS: %d   PZ: %d   \n", LZ.Get_color(),
//				LS.Get_color(), PS.Get_color(), PZ.Get_color());
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

//		timer.sleep(500);

	}

}
volatile u16 sec = 0;
void TIM5_IRQHandler(void) {
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

		RPM_L = TIM_GetCounter(TIM2)*3;
		RPM_P = TIM_GetCounter(TIM3)*3;

		TIM_SetCounter(TIM2, 0);
		TIM_SetCounter(TIM3, 0);
//		sec++;
//		trace_printf("Sec: %d",sec);
	}
}
volatile u8 f = 0;
void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
//	  puts("hi");
		delay_ms(1000);
//		Eng_left.Set_speed(70);
//		Eng_right.Set_speed(70);
//		delay_ms(10);
//		Eng_left.Set_speed(5);
//		Eng_right.Set_speed(5);
//		Flag = true;

		switch (f) {
		case 0:
			Eng_left.Set_speed(-50);
			Eng_right.Set_speed(-50);
			f++;
			break;
		case 1:
			Eng_left.Set_speed(-20);
			Eng_right.Set_speed(0xFF);
			f++;
			break;
		case 2:
			Eng_left.Set_speed(0xFF);
			Eng_right.Set_speed(-20);
			f++;
			break;
		case 3:
			Eng_left.Set_speed(5);
			Eng_right.Set_speed(5);
			f++;
			break;
		case 4:
			Eng_left.Set_speed(50);
			Eng_right.Set_speed(50);
			f++;
			break;
		case 5:
			Eng_left.Set_speed(100);
			Eng_right.Set_speed(100);
			f++;
			break;
		case 6:
			Eng_left.Set_speed(0xFF);
			Eng_right.Set_speed(0xFF);
			f = 0;
			break;
		default:
			break;
		}
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
