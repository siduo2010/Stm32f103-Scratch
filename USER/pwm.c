#include "pwm.h"

/*
 * 函数名：TIM2_GPIO_Config
 * 描述  ：配置TIM3复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void TIM2_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM2 clock enable */
	//PCLK1经过2倍频后作为TIM3的时钟源等于72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM2 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * 函数名：TIM2_Mode_Config
 * 描述  ：配置TIM2输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
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
 * 函数名：TIM2_PWM_Init
 * 描述  ：TIM2 输出PWM信号初始化，只要调用这个函数
 *         TIM2的四个通道就会有PWM信号输出
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config();
	Timer_Init();
	//TIM2_Mode_Config();	
}
