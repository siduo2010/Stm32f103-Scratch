#include "pwm.h"

/*
 * ��������TIM2_GPIO_Config
 * ����  ������TIM3�������PWMʱ�õ���I/O
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void TIM2_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM2 clock enable */
	//PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM2 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * ��������TIM2_Mode_Config
 * ����  ������TIM2�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void Timer_Init(void)
{ 
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;  
	
		u16 CCR1_Val = 25;        
		u16 CCR2_Val = 0;
		u16 CCR3_Val = 25;
		u16 CCR4_Val = 0;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); 

		TIM_TimeBaseStructure.TIM_Period =999;
		TIM_TimeBaseStructure.TIM_Prescaler =1439;
		TIM_TimeBaseStructure.TIM_ClockDivision =0x00;
		TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
		TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		//ch1 
		TIM_OCInitStructure.TIM_Pulse = CCR1_Val; 
		TIM_OC1Init(TIM2, & TIM_OCInitStructure); 
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); 
		//ch2
		TIM_OCInitStructure.TIM_Pulse = CCR2_Val; 
		TIM_OC2Init(TIM2, & TIM_OCInitStructure); 
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
		//ch3 
		TIM_OCInitStructure.TIM_Pulse = CCR3_Val; 
		TIM_OC3Init(TIM2, & TIM_OCInitStructure); 
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); 
		//ch4 
		TIM_OCInitStructure.TIM_Pulse = CCR4_Val; 
		TIM_OC4Init(TIM2, & TIM_OCInitStructure);
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); 

		TIM_ARRPreloadConfig(TIM2,ENABLE); 
		TIM_ITConfig(TIM2,TIM_IT_CC1,ENABLE); 
		TIM_CtrlPWMOutputs(TIM2,ENABLE); 
		TIM_Cmd(TIM2,ENABLE);
}

/*
 * ��������TIM2_PWM_Init
 * ����  ��TIM2 ���PWM�źų�ʼ����ֻҪ�����������
 *         TIM2���ĸ�ͨ���ͻ���PWM�ź����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config();
	Timer_Init();
	//TIM2_Mode_Config();	
}
