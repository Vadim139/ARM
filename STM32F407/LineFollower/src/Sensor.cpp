/*
 * Sensor.cpp
 *
 *  Created on: 11 kwi 2019
 *      Author: dawid
 */

#include <Sensor.h>
//#include <stdlib.h>

Sensor::Sensor(uint16_t black, uint16_t blue, uint16_t red, uint16_t white, ADC_TypeDef* ADCx, uint8_t channel, volatile uint16_t* value) {
	color[0] = black;
	color[1] = blue;
	color[2] = red;
	color[3] = white;

	ADC_x = ADCx;
	channel_x = channel;

	Value = value;

}

Sensor::Sensor(){

}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

Sensors_colors_t Sensor::Get_color(void){
	volatile uint16_t ADC_1 = *Value;
	int16_t a = ADC_1-color[0];
	uint16_t b = abs(a);
//	ADC_1 = TM_ADC_Read(ADC_x,channel_x);

	if(abs(*Value-color[0])<around[0])
		return BLACK;

	if(abs(*Value-color[1])<around[1])
		return BLUE;

	if(abs(*Value-color[2])<around[2])
		return RED;

	if(abs(*Value-color[3])<around[3])
		return WHITE;


	return BACKGROUND;
}
