#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"

void ADC1_Init(void);
float ReadLightsevro(char pin);
float ReadSoundsevro(char pin);
float ReadPotentionmeterRsevro(char pin);
float Readanalogvalue(char pin);

#endif /* __ADC_H */
