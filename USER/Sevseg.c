#include "Sevseg.h"

char SMG_Code[16]= {0x03,0x3f,0x4a,0x2a,0x36,0xa2,0x82,0x3b,0x02,0x22};

void delay_SMG(int Time)    
{
   unsigned int i;
   for ( ; Time>0; Time--)
     for ( i = 0; i < 720; i++ );
}

void LED_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE );

		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_All; 
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;										   
		GPIO_Init(GPIOE,&GPIO_InitStruct);
}

void Control_GPIO_Config(void)
{
		 GPIO_InitTypeDef GPIO_InitStruct;
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
//
		 GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_13; 
		 GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		 GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;										   
		 GPIO_Init(GPIOB,&GPIO_InitStruct);
			
	   GPIO_SetBits(GPIOB, GPIO_Pin_11 | GPIO_Pin_13);
}

void SMG_init(void)
{
	LED_GPIO_Config();
	Control_GPIO_Config();
}

void RunSevseg(int num)
{
		//pin参数作为预留值
		char num_shi=0,num_ge=0;
		num_shi=num/10;
		num_ge=num%10;
		SMG_Display(SMG_Code[num_shi],SMG_Code[num_ge]);
}

void SMG_Display(char dat_wela,char dat_dula )
{
	 Dula(0);
	 Wela(1);
	 GPIO_Write(GPIOE,dat_wela<<8);
	 delay_SMG(100);
	 Wela(0);
	 Dula(1);
	 GPIO_Write(GPIOE,dat_dula<<8);
	 delay_SMG(100);
}