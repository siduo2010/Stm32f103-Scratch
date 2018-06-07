#include "button.h"
#include "Bport_int.h"

char read_botton_status(char pin)
{
	char button_status;
	
	int port=0;
	port=pin;
	
	switch(port)
	{
		case 4:
			if( GPIO_Scan(GPIOB,GPIO_Pin_9) == KEY_ON  ){button_status=0;}
		  else{button_status=1;}
		break;
			
		case 5:
			if( GPIO_Scan(GPIOB,GPIO_Pin_10) == KEY_ON  ){button_status=0;}
		  else{button_status=1;}
		break;
			
		case 6:
			if( GPIO_Scan(GPIOB,GPIO_Pin_4) == KEY_ON  ){button_status=0;}
		  else{button_status=1;}
		break;
			
		case 11:
			if( GPIO_Scan(GPIOB,GPIO_Pin_5) == KEY_ON  ){button_status=1;}
		  else{button_status=0;}
		break;
	}
	
	return button_status;
}

char read_digial_status(char pin)
{
	char digial_status;
	
	int port=0;
	port=pin;
	
	switch(port)
	{
		case 4:
			if( GPIO_Scan(GPIOB,GPIO_Pin_9) == KEY_ON  ){digial_status=0;}
		  else{digial_status=1;}
		break;
			
		case 5:
			if( GPIO_Scan(GPIOB,GPIO_Pin_10) == KEY_ON  ){digial_status=0;}
		  else{digial_status=1;}
		break;
			
		case 6:
			if( GPIO_Scan(GPIOB,GPIO_Pin_4) == KEY_ON  ){digial_status=0;}
		  else{digial_status=1;}
		break;
	}
	
	return digial_status;
}
