#include "servo.h"
#include "pwm.h"

void Runservo(char pin,char slot)
{
	int port=pin;
	
	switch(port)
	{
		case 9:
			slot=slot*5/9+25;
			TIM2->CCR3 = slot;
		break;
		
		case 10:
			slot=slot*5/9+25;
			TIM2->CCR4 = slot;
		break;
		
		case 11:
			slot=slot*5/9+25;
			TIM2->CCR1 = slot;
		break;
	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
