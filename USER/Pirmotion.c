#include "Pirmotion.h"
#include "Bport_int.h"

char read_PIRmotion_status(char pin)
{
	char ir_status;
	
	int port=0;
	port=pin;
	
	switch(port)
	{
		case 4:
			if( GPIO_Scan(GPIOB,GPIO_Pin_9) == KEY_ON  ){ir_status=0;}
		  else{ir_status=1;}
		break;
			
		case 5:
			if( GPIO_Scan(GPIOB,GPIO_Pin_10) == KEY_ON  ){ir_status=0;}
		  else{ir_status=1;}
		break;
			
		case 6:
			if( GPIO_Scan(GPIOB,GPIO_Pin_4) == KEY_ON  ){ir_status=0;}
		  else{ir_status=1;}
		break;
			
		case 11:
			if( GPIO_Scan(GPIOB,GPIO_Pin_1) == KEY_ON  ){ir_status=1;}
		  else{ir_status=0;}
		break;
	}
	
	return ir_status;
}
