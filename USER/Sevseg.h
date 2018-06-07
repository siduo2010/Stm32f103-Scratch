#ifndef __SEVSEG_H
#define	__SEVSEG_H

#include "stm32f10x.h"

#define Dula(a) if(a) GPIO_SetBits(GPIOB,GPIO_Pin_11);else  GPIO_ResetBits(GPIOB,GPIO_Pin_11)	;
#define Wela(a) if(a) GPIO_SetBits(GPIOB,GPIO_Pin_13);else  GPIO_ResetBits(GPIOB,GPIO_Pin_13)	;

void LED_GPIO_Config(void );
void Control_GPIO_Config(void );
void SMG_init(void);
void SMG_Display(char dat_wela,char dat_dula );
void RunSevseg(int num);

#endif 

