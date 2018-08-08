/*
 * NTC.h
 *
 *  Created on: 4 sty 2018
 *      Author: Vadim
 */

#ifndef NTC_H_
#define NTC_H_

#include "main.h"
#include "Other.h"

#define NTC_GPIO      	GPIOA
#define NTC_PIN  		GPIO_Pin_0

class NTC {
public:

	char Temp_out[7];
	char Temp_in[7];

	NTC();
	virtual ~NTC();

	void Init();
	float Get_temp();
	void Get_temp(char *temp);
};

#endif /* NTC_H_ */
