#include "UltrasonicWave.h"
#include "TIM2.h"

#define	TRIG_PORT      GPIOC		//TRIG       
#define	ECHO_PORT      GPIOC		//ECHO 
#define	TRIG_PIN       GPIO_Pin_8   //TRIG       
#define	ECHO_PIN       GPIO_Pin_9	//ECHO   

unsigned short int UltrasonicWave_Distance;      //������ľ���    

/*
 * ��������DelayTime_us
 * ����  ��1us��ʱ����
 * ����  ��Time   	��ʱ��ʱ�� US
 * ���  ����	
 */
void DelayTime_us(int Time)    
{
   unsigned char i;
   for ( ; Time>0; Time--)
     for ( i = 0; i < 72; i++ );
}

/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
  	       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					 //PC8��TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //��ʼ������GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				     //PC9��ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						 //��ʼ��GPIOA
}

/*
 * ��������UltrasonicWave_CalculateTime
 * ����  ���������
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_CalculateTime(void)
{
   UltrasonicWave_Distance=TIM_GetCounter(TIM4)*5*34/2000;
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
unsigned short int UltrasonicWave_StartMeasure(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ
  DelayTime_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
  
  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	             //�ȴ��ߵ�ƽ
  TIM_Cmd(TIM4, ENABLE);                                             //����ʱ��
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //�ȴ��͵�ƽ
  TIM_Cmd(TIM4, DISABLE);			                                 //��ʱ��2ʧ��
  UltrasonicWave_CalculateTime();									 //�������
  TIM_SetCounter(TIM4,0);
  
	UltrasonicWave_Distance=UltrasonicWave_Distance+2;
	return UltrasonicWave_Distance;
}
