#ifndef __BPORT_OUT_H
#define	__BPORT_OUT_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

//带参宏，可以像内联函数一样使用
#define PortA1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define PortA2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define PortA3(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_8)
					
#define Buzzer(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_7)

void Bportout_GPIO_Config(void);
void Rundigitalout(int port,char slot);
void Runbuzzer(int port,char slot);

#endif 
