#include "Bport_out.h"

void Bportout_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOC的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB |  RCC_APB2Periph_GPIOD, ENABLE); 

	/*选择要控制的GPIOC引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;//GPIO_Pin_3 | 	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOC*/
  	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	/*选择要控制的GPIOC引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//GPIO_Pin_3 | 	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOC*/
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOB,  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8);//	 GPIO_Pin_3 |
	GPIO_ResetBits(GPIOD,  GPIO_Pin_7);
}

void Runbuzzer(int port,char slot)
{
	char pin;
	
	pin=port;
	
	switch(pin)
	{
		case 1:
			PortA1(slot);
		break;
		
		case 2:
			PortA2(slot);
		break;
		
		case 3:
			PortA3(slot);
		break;
		
		case 11:
			Buzzer(slot);
		break;
	}
}

void Rundigitalout(int port,char slot)
{
	char pin;
	
	pin=port;
	
	switch(pin)
	{
		case 1:
			PortA1(slot);
		break;
		
		case 2:
			PortA2(slot);
		break;
		
		case 3:
			PortA3(slot);
		break;
	}
}
