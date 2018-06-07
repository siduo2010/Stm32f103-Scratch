#ifndef __BPORT_INT_H
#define	__BPORT_INT_H

#include "stm32f10x.h"

#define KEY_ON 1
#define KEY_OFF 0

void Key_GPIO_Config(void);
void Delay(__IO u32 nCount);
u8 GPIO_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif 
