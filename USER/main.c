#include "stm32f10x.h"
#include "SysTick.h"
#include "DHT11.h"
#include "usart1.h"
#include "pwm.h"
#include "com.h"
#include "adc.h"
#include "TIM4.h"
#include "exti.h"
#include "Bport_int.h"
#include "Bport_out.h"

int SMG_Num=0;

/* 
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
int main(void)
{
	 /*��ʼ��SysTick��ʱ��*/
	 SysTick_Init();

	 /*��ʼ������1*/
	 USART1_Config();
	 NVIC_Configuration();

	 TIM2_PWM_Init();
	 TIM4_Configuration();
	 Timer3_init();
	
	 Key_GPIO_Config();
	 Bportout_GPIO_Config();
	 SMG_init();
	
	 /*��ʼ��DTT11������*/
	 DHT11_GPIO_Config();  
	 /*��ʼ��������ģ��*/
	 UltrasonicWave_Configuration();

	 /* enable adc1 and config adc1 to dma mode */
	 ADC1_Init();	
	 
	 EXTI_PB0_Config();

	 while(1)
	 {
		if(Perform==1)
		{
				parseData();
				Perform=0;
		}
		
		RunSevseg(SMG_Num);
	 }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/


