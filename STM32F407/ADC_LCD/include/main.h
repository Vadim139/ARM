#ifndef __MAIN_H
#define __MAIN_H

/* Includes ******************************************************************/

#include <stdlib.h>
#include "pwm.h"
#include "ts.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "LCD_STM32F4.h"
#include "functions.h"

//#include "hex_image.h"

/* Function Prototypes *******************************************************/

//void uint16tostr(char buf[], uint32_t d, uint8_t base);
void Demo_MMIA(void);
void Random_Lines(void);
void Random_Rect(void);
void Random_Circle(void);

#endif /* __MAIN_H */
