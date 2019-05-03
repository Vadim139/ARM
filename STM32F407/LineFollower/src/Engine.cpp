/*
 * Engine.cpp
 *
 *  Created on: 11 kwi 2019
 *      Author: dawid
 */

#include <Engine.h>
#include "Timer.h"
extern Timer timer;
//#include <stdlib.h>

Engine::Engine(uint8_t channel) {

	Channel = channel;

	Speed = 0;

}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

uint8_t Engine::Get_speed(void){

	return Speed;
}

void Engine::Set_speed(int16_t speed){

	uint16_t offset;

	if(speed>0){
		offset = MIN_PWM;
		Speed = speed;

		if(speed == 0xFF)
		{
			offset = 0;
			speed = 0;
			Speed = 0;
		}

		switch (Channel) {
			case 1:
				TIM_SetCompare1(TIMx, (uint16_t)(offset + ((float)((float)speed/100) * (1000 - offset))));
				break;
			case 2:
				TIM_SetCompare2(TIMx, (uint16_t)(offset + ((float)((float)speed/100) * (1000 - offset))));
				break;
			case 3:
				TIM_SetCompare3(TIMx, (uint16_t)(offset + ((float)((float)speed/100) * (1000 - offset))));
				break;
			case 4:
				TIM_SetCompare4(TIMx, (uint16_t)(offset + ((float)((float)speed/100) * (1000 - offset))));
				break;
			default:
				break;
		}
	}else
	{
		offset = MIN_PWM - (uint16_t)(((float)abs(speed)/100) * MIN_PWM);
		Speed = speed;
		speed = 0;

		switch (Channel) {
			case 1:
				TIM_SetCompare1(TIMx, offset);
				break;
			case 2:
				TIM_SetCompare2(TIMx, offset);
				break;
			case 3:
				TIM_SetCompare3(TIMx, offset);
				break;
			case 4:
				TIM_SetCompare4(TIMx, offset);
				break;
			default:
				break;
		}

	}
}

void Engine::Stop(){
	Speed = 0;

	Set_speed(0xFF);

}

void Engine::Full_speed(){
	Speed = 100;
	Set_speed(100);
}

void Engine::Half_speed(){
	Speed = 50;

	Set_speed(50);
}


void Engine::Init(uint8_t channels){

    GPIO_InitTypeDef GPIO_InitStruct;

    /* Clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* Alternating functions for pins */
    if(channels>0)
    	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    if(channels>1)
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    if(channels>2)
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
    if(channels>3)
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

    /* Set pins */
	switch (channels) {
		case 1:
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
			break;
		case 2:
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
			break;
		case 3:
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
			break;
		case 4:
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
			break;
		default:
			break;
	}
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;// | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    TIM_TimeBaseInitTypeDef TIM_BaseStruct;

       /* Enable clock for TIM4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_BaseStruct.TIM_Prescaler = 84;
	/* Count up */
	TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_BaseStruct.TIM_Period = 999; /* 10kHz PWM */
	TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseStruct.TIM_RepetitionCounter = 0;
	/* Initialize TIM4 */
	TIM_TimeBaseInit(TIMx, &TIM_BaseStruct);
	/* Start count on TIM4 */
	TIM_Cmd(TIMx, ENABLE);

	TIM_OCInitTypeDef TIM_OCStruct;

	/* Common settings */

	/* PWM mode 2 = Clear on compare match */
	/* PWM mode 1 = Set on compare match */
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;

    if(channels>0){
    	TIM_OCStruct.TIM_Pulse = 0; /* 25% duty cycle */
    	TIM_OC1Init(TIMx, &TIM_OCStruct);
    	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    if(channels>1){
    	TIM_OCStruct.TIM_Pulse = 0; /* 25% duty cycle */
    	TIM_OC2Init(TIMx, &TIM_OCStruct);
    	TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    if(channels>2){
    	TIM_OCStruct.TIM_Pulse = 0; /* 25% duty cycle */
    	TIM_OC3Init(TIMx, &TIM_OCStruct);
    	TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }
    if(channels>3){
    	TIM_OCStruct.TIM_Pulse = 0; /* 25% duty cycle */
    	TIM_OC4Init(TIMx, &TIM_OCStruct);
    	TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
    }

}

void Engine::Turn(Engine_dir_t dir,Engine_turn_speed_t speed, Engine* left, Engine* right){

	switch (dir) {
		case LEFT:
			switch (speed) {
				case GENTLE:
					left->Set_speed(-80);
//					left->Set_speed(0xFF);
					right->Set_speed(100);
					timer.sleep(30);
					right->Set_speed(20);
					break;
				case GENTLE_ONE:
//					left->Set_speed(-50);
					left->Set_speed(0xFF);
					right->Set_speed(100);
					timer.sleep(50);
					right->Set_speed(20);
					break;
				case NORMAL_ONE:
//					left->Set_speed(-50);
					left->Set_speed(0xFF);
					right->Set_speed(100);
					timer.sleep(50);
					right->Set_speed(95);
					break;
				case NORMAL:
					if(left->Get_speed() >= 15 && right->Get_speed() <= 85){
						left->Set_speed(left->Get_speed()-15);
						right->Set_speed(right->Get_speed()+15);
					}else{
						left->Set_speed(10);
						right->Set_speed(40);
					}

					break;
				case FAST:
					if(left->Get_speed() >= 35 && right->Get_speed() <= 65){
						left->Set_speed(left->Get_speed()-35);
						right->Set_speed(right->Get_speed()+35);
					}else{
						left->Set_speed(30);
						right->Set_speed(100);
					}
					break;
				default:
					break;
			}
			break;
		case RIGHT:
			switch (speed) {
				case GENTLE:
					right->Set_speed(-80);
//					right->Set_speed(0xFF);
					left->Set_speed(100);
					timer.sleep(30);
					left->Set_speed(20);
					break;
				case GENTLE_ONE:
//					right->Set_speed(-50);
					right->Set_speed(0xFF);
					left->Set_speed(100);
					timer.sleep(50);
					left->Set_speed(20);
					break;
				case NORMAL_ONE:
//					left->Set_speed(-50);
					right->Set_speed(0xFF);
					left->Set_speed(100);
					timer.sleep(50);
					left->Set_speed(95);
					break;
				case NORMAL:
					if(right->Get_speed() >= 15 && left->Get_speed() <= 85){
						right->Set_speed(right->Get_speed()-15);
						left->Set_speed(left->Get_speed()+15);
					}else{
						right->Set_speed(10);
						left->Set_speed(40);
					}

					break;
				case FAST:
					if(right->Get_speed() >= 35 && left->Get_speed() <= 65){
						right->Set_speed(right->Get_speed()-35);
						left->Set_speed(left->Get_speed()+35);
					}else{
						right->Set_speed(30);
						left->Set_speed(100);
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}


}

