#ifndef __MOTOR_H
#define	__MOTOR_H

#include "stm32f10x.h"

void Runmotor(int pin,int speed);
void Runpwm(int pin,int speed);

#endif /* __PWM_OUTPUT_H */

