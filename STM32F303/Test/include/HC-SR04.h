/*
 * HC-SR04.h
 *
 *  Created on: 2 lis 2014
 *      Author: Dawid
 */

#ifndef HC_SR04_H_
#define HC_SR04_H_

// I wersja definicji
#define	SONAR_ECHO		GPIO_Pin_5
#define	SONAR_ECHO_P	GPIOA

#define	SONAR_TRIGGER1		GPIO_Pin_6
#define	SONAR_TRIGGER1_P	GPIOA

volatile uint8_t HC_flag = 0;
volatile uint8_t HC_count_flag = 0;

void HC_init(void);
int HC_get(void);

#endif /* HC_SR04_H_ */
