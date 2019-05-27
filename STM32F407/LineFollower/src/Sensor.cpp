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

	if(abs(Value[channel_x]-color[0])<around[0] || Value[channel_x]>color[0])
		return BLACK;

	if(abs(Value[channel_x]-color[1])<around[1])
		return BLUE;

	if(abs(Value[channel_x]-color[2])<around[2])
		return RED;

	if(abs(Value[channel_x]-color[3])<around[3])
		return WHITE;


	return BACKGROUND;
}

Sensors_colors_t Sensor::Get_color2(void){
	volatile uint16_t ADC_1 = *Value;
	int16_t a = ADC_1-color[0];
	uint16_t b = abs(a);
//	ADC_1 = TM_ADC_Read(ADC_x,channel_x);

//(uint16_t)(ADCConvertedValues[1]*1.01),
//(uint16_t)(ADCConvertedValues[2]*1.072),
//(uint16_t)(ADCConvertedValues[0]),
//(uint16_t)(ADCConvertedValues[3]*0.93),
//(uint16_t)(ADCConvertedValues[4]*1.5)

	switch (channel_x) {
			case 0:
				if((uint16_t) (Value[channel_x])<2290)
			if (

	//				abs((uint16_t) (Value[channel_x]) - (uint16_t) (Value[1] * 1.01)) > 70 &&
					abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[2] * 1.052)) > 25
					&& abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[3] * 0.948)) > 25)
	//				&& abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[4] * 1.5)) > 70)
					return BLUE;
				break;
	//		case 1:
	//			if((uint16_t) (Value[channel_x]*1.01)<2400)
	//		if (abs((uint16_t) (Value[channel_x]*1.01) - (uint16_t) (Value[0])) > 100
	//				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[2] * 1.072)) > 100
	//				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[3] * 0.93)) > 100
	//				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[4] * 1.5)) > 100)
	//				return BLUE;
	//			break;
			case 2:
				if((uint16_t) (Value[channel_x]*1.052)<2340)
			if (
	//				abs((uint16_t) (Value[channel_x]*1.072) - (uint16_t) (Value[1] * 1.01)) > 40 &&
					abs((uint16_t) (Value[channel_x]*1.052)-(uint16_t) (Value[0])) > 25
					&& abs((uint16_t) (Value[channel_x]*1.052)-(uint16_t) (Value[3] * 0.948)) > 25)
	//				&& abs((uint16_t) (Value[channel_x]*1.072)-(uint16_t) (Value[4] * 1.5)) > 40)
					return BLUE;
				break;
			case 3:
			if (
	//				abs((uint16_t) (Value[channel_x]*0.93) - (uint16_t) (Value[1] * 1.01)) > 100 &&
					abs((uint16_t) (Value[channel_x]*0.948)-(uint16_t) (Value[2] * 1.052)) > 25
					&& abs((uint16_t) (Value[channel_x]*0.948)-(uint16_t) (Value[0])) > 25)
	//				&& abs((uint16_t) (Value[channel_x]*0.93)-(uint16_t) (Value[4] * 1.5)) > 70)
					return BLUE;
				break;
	//		case 4:
	//			if((uint16_t) (Value[channel_x]*1.5)<2300)
	//		if (abs((uint16_t) (Value[channel_x]*1.5) - (uint16_t) (Value[1] * 1.01)) > 200
	//				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[2] * 1.072)) > 200
	//				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[3] * 0.93)) > 250
	//				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[0])) > 200)
	//				return BLUE;
	//			break;
			default:
				break;
		}

//	switch (channel_x) {
//		case 0:
//			if((uint16_t) (Value[channel_x])<2290)
//		if (
//
////				abs((uint16_t) (Value[channel_x]) - (uint16_t) (Value[1] * 1.01)) > 70 &&
//				abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[2] * 1.052)) > 60
//				&& abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[3] * 0.948)) > 60)
////				&& abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[4] * 1.5)) > 70)
//				return BLUE;
//			break;
////		case 1:
////			if((uint16_t) (Value[channel_x]*1.01)<2400)
////		if (abs((uint16_t) (Value[channel_x]*1.01) - (uint16_t) (Value[0])) > 100
////				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[2] * 1.072)) > 100
////				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[3] * 0.93)) > 100
////				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[4] * 1.5)) > 100)
////				return BLUE;
////			break;
//		case 2:
//			if((uint16_t) (Value[channel_x]*1.052)<2340)
//		if (
////				abs((uint16_t) (Value[channel_x]*1.072) - (uint16_t) (Value[1] * 1.01)) > 40 &&
//				abs((uint16_t) (Value[channel_x]*1.052)-(uint16_t) (Value[0])) > 40
//				&& abs((uint16_t) (Value[channel_x]*1.052)-(uint16_t) (Value[3] * 0.948)) > 25)
////				&& abs((uint16_t) (Value[channel_x]*1.072)-(uint16_t) (Value[4] * 1.5)) > 40)
//				return BLUE;
//			break;
//		case 3:
//		if (
////				abs((uint16_t) (Value[channel_x]*0.93) - (uint16_t) (Value[1] * 1.01)) > 100 &&
//				abs((uint16_t) (Value[channel_x]*0.948)-(uint16_t) (Value[2] * 1.052)) > 40
//				&& abs((uint16_t) (Value[channel_x]*0.948)-(uint16_t) (Value[0])) > 50)
////				&& abs((uint16_t) (Value[channel_x]*0.93)-(uint16_t) (Value[4] * 1.5)) > 70)
//				return BLUE;
//			break;
////		case 4:
////			if((uint16_t) (Value[channel_x]*1.5)<2300)
////		if (abs((uint16_t) (Value[channel_x]*1.5) - (uint16_t) (Value[1] * 1.01)) > 200
////				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[2] * 1.072)) > 200
////				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[3] * 0.93)) > 250
////				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[0])) > 200)
////				return BLUE;
////			break;
//		default:
//			break;
//	}

//	switch (channel_x) {
//		case 0:
//		if (abs((uint16_t) (Value[channel_x]) - (uint16_t) (Value[1] * 1.01)) > 70
//				&& abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[2] * 1.072)) > 70
//				&& abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[3] * 0.93)) > 70
//				&& abs((uint16_t) (Value[channel_x])-(uint16_t) (Value[4] * 1.5)) > 70)
//				return BLUE;
//			break;
//		case 1:
//			if((uint16_t) (Value[channel_x]*1.01)<2400)
//		if (abs((uint16_t) (Value[channel_x]*1.01) - (uint16_t) (Value[0])) > 100
//				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[2] * 1.072)) > 100
//				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[3] * 0.93)) > 100
//				&& abs((uint16_t) (Value[channel_x]*1.01)-(uint16_t) (Value[4] * 1.5)) > 100)
//				return BLUE;
//			break;
//		case 2:
//			if((uint16_t) (Value[channel_x]*1.072)<2380)
//		if (abs((uint16_t) (Value[channel_x]*1.072) - (uint16_t) (Value[1] * 1.01)) > 40
//				&& abs((uint16_t) (Value[channel_x]*1.072)-(uint16_t) (Value[0])) > 60
//				&& abs((uint16_t) (Value[channel_x]*1.072)-(uint16_t) (Value[3] * 0.93)) > 40
//				&& abs((uint16_t) (Value[channel_x]*1.072)-(uint16_t) (Value[4] * 1.5)) > 40)
//				return BLUE;
//			break;
//		case 3:
//		if (abs((uint16_t) (Value[channel_x]*0.93) - (uint16_t) (Value[1] * 1.01)) > 100
//				&& abs((uint16_t) (Value[channel_x]*0.93)-(uint16_t) (Value[2] * 1.072)) > 100
//				&& abs((uint16_t) (Value[channel_x]*0.93)-(uint16_t) (Value[0])) > 70
//				&& abs((uint16_t) (Value[channel_x]*0.93)-(uint16_t) (Value[4] * 1.5)) > 70)
//				return BLUE;
//			break;
//		case 4:
//			if((uint16_t) (Value[channel_x]*1.5)<2300)
//		if (abs((uint16_t) (Value[channel_x]*1.5) - (uint16_t) (Value[1] * 1.01)) > 200
//				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[2] * 1.072)) > 200
//				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[3] * 0.93)) > 250
//				&& abs((uint16_t) (Value[channel_x]*1.5)-(uint16_t) (Value[0])) > 200)
//				return BLUE;
//			break;
//		default:
//			break;
//	}



	return BACKGROUND;
}
