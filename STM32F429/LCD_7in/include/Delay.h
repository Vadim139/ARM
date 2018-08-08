#ifndef __DELAY_H_
#define __DELAY_H_

#include "stm32f4xx.h"
#ifdef __cplusplus
extern "C"{
#endif
//#include "stm32f40x_systick.h"
/* Private function prototypes -----------------------------------------------*/
void delay_init(void);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);

#ifdef __cplusplus
}
#endif
#endif

