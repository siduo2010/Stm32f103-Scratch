#include "motor.h"
#include "pwm.h"
#include "usart1.h"

void Runmotor(int pin,int speed)
{
	int port=pin;
	
	speed=speed/2;   //此处用于调节电机的转速上限
	
	switch(port)
	{
		case 9:
			speed=speed*3.9;
			TIM2->CCR3 = speed;
		break;
		
		case 10:
			speed=speed*3.9;
			TIM2->CCR4 = speed;
		break;
		
		case 11:
			speed=speed*3.9;
			TIM2->CCR2 = speed;
		break;
	}
}

void Runpwm(int pin,int speed)
{
	int port;
	port=pin;
	
	switch(port)
	{
		case 9:
			speed=speed*3.9;
			TIM2->CCR3 = speed;
		break;
		
		case 10:
			speed=speed*3.9;
			TIM2->CCR4 = speed;
		break;
	}
}
