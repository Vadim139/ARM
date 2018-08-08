/*
 * ADC.cpp
 *
 *  Created on: 5 sty 2018
 *      Author: Vadim
 */
#include "ADC.h"

void ADCx_Init(ADC_TypeDef * ADC, uint8_t channel)
{

	 ADC_InitTypeDef adc;

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	switch ((uint32_t)ADC) {
		case (uint32_t)ADC1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
			break;
		case (uint32_t)ADC2:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
			break;
		case (uint32_t)ADC3:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
			break;
		default:
			break;
	}

	 RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	 ADC_StructInit(&adc);
	 adc.ADC_ContinuousConvMode = ENABLE;
	 adc.ADC_NbrOfChannel = 1;
	 adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	 ADC_Init(ADC, &adc);

	 ADC_RegularChannelConfig(ADC, channel, 1, ADC_SampleTime_71Cycles5);
	 ADC_Cmd(ADC, ENABLE);

	 ADC_ResetCalibration(ADC);
	 while (ADC_GetResetCalibrationStatus(ADC));

	 ADC_StartCalibration(ADC);
	 while (ADC_GetCalibrationStatus(ADC));

	 ADC_SoftwareStartConvCmd(ADC, ENABLE);
}

