#include "Bport_out.h"

void Bportout_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOC������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB |  RCC_APB2Periph_GPIOD, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;//GPIO_Pin_3 | 	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOC*/
  	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	/*ѡ��Ҫ���Ƶ�GPIOC����*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//GPIO_Pin_3 | 	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOC*/
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
