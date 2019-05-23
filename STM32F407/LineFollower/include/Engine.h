/*
 * Engine.h
 *
 *  Created on: 22 kwi 2019
 *      Author: dawid
 */

#ifndef ENGINE_H_
#define ENGINE_H_
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define TIMx TIM4
#define MIN_PWM 700

typedef enum {
	LEFT,
	RIGHT

} Engine_dir_t;

typedef enum {
	GENTLE,
	GENTLE_ONE,
	GENTLE_TWO,
	NORMAL,
	NORMAL_ONE,
	FAST

} Engine_turn_speed_t;

class Engine {
public:
	Engine();
	Engine(uint8_t channel);
	virtual ~Engine();
	uint8_t Get_speed(void);
	void Set_speed(int16_t speed);
	void Stop();
	void Full_speed();
	void Half_speed();

	static void Init(uint8_t channels);
	static void Turn(Engine_dir_t dir,Engine_turn_speed_t speed, Engine* left, Engine* right);

private:
	int16_t Speed;
	uint8_t Channel;

};
#ifdef __cplusplus
}
#endif

#endif /* ENGINE_H_ */
