/*
 * Sensor.h
 *
 *  Created on: 11 kwi 2019
 *      Author: dawid
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
//#include "tm_stm32f4_adc.h"


typedef enum {
	BACKGROUND,
	BLACK,
	BLUE,
	RED,
	WHITE

} Sensors_colors_t;

typedef enum {
	NONE,
	LEFT_S,
	RIGHT_S

} Last_side_t;


class Sensor {
public:
	Sensor();
	Sensor(uint16_t black, uint16_t blue, uint16_t red, uint16_t white, ADC_TypeDef* ADCx, uint8_t channel, volatile uint16_t* value);
	virtual ~Sensor();
	Sensors_colors_t Get_color(void);
//	uint16_t around[4] = {150,60,30,30};
//	uint16_t around[4] = {100,30,15,15};
//	uint16_t around[4] = {300,150,150,300};
	uint16_t around[4] = {200,70,70,200};
//	uint16_t around[4] = {200,50,50,200};

private:
	uint16_t color[4];
	ADC_TypeDef* ADC_x;
	uint8_t channel_x;

	volatile uint16_t* Value;
};
#ifdef __cplusplus
}
#endif

#endif /* SENSOR_H_ */
