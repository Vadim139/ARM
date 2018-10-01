/*
 * NTC.cpp
 *
 *  Created on: 4 sty 2018
 *      Author: Vadim
 */

#include "NTC.h"

NTC::NTC() {
	// TODO Auto-generated constructor stub
	memset(Temp_in,0,7);
	memset(Temp_out,0,7);
}

NTC::~NTC() {
	// TODO Auto-generated destructor stub
}

void NTC::Init()
{
	GPIO_IO NTC_IO(NTC_GPIO,NTC_PIN, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	NTC_IO.Init();
}

float NTC::Get_temp()
{
	uint16_t adc;
	float temp, adcv;
	adc = ADC_GetConversionValue(ADC1);
	adcv = adc * 3.3f / 4096.0f;
	temp = ((3609.73*298.15)/((log((21690*adcv)/((3.3-adcv)*2000))*298.15)+3609.73)) - 273.15;
	return temp - 0.5;
}

void NTC::Get_temp(char* temp)
{
	uint16_t adc;
	float t, adcv;
	adc = ADC_GetConversionValue(ADC1);
	adcv = adc * 3.3f / 4096.0f;
	t = ((3609.73*298.15)/((log((21690*adcv)/((3.3-adcv)*2000))*298.15)+3609.73)) - 273.15;
//	t = ((4148.88*298.15)/((log((21690*adcv)/((3.3-adcv)*10000))*298.15)+4148.88)) - 273.15;
	floatToString(t,temp,3);
}
