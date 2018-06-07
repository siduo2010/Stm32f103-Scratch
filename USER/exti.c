#include "exti.h"

unsigned char  T_num[33];
unsigned char decode[4];
/*
 * ��������NVIC_Configuration
 * ����  ������Ƕ�������жϿ�����NVIC
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* ����P[A|B|C|D|E]1Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI_PB0_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline(PB0) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);

	/* config the NVIC(PB0) */
	NVIC_Configuration();

	/* EXTI line gpio config(PB0) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // ��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* EXTI line(PC1) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}
//**************************************************************************************************
//32λ�����Ƶ�4�ֽ�����
//**************************************************************************************************
void bit_byte(void) 
{ 
  unsigned char i, j, k=1;
  unsigned char temp,value;
  for(i=0;i<4;i++)        //ѭ��4�ε�4�ֽ�
  {
     for(j=1;j<=8;j++)   //ѭ��ȡ8λ��1�ֽ�
     {
         value>>=1;      //����1λ,���δӵ�λ����λ
         temp=T_num[k];  //���ڵ�1������Ϊ�����룬��ȥ�����Դӵ�2��������ȡ�����32λ
         if(temp>7)      //����7*0.256=1.8msΪ1,����1.125ms��ʾ"0"������2.25ms��ʾ"1"
            value|=0x80; //Ϊ1�����λ��1
         k++;            //k��1��׼����ȡ��1λ
     }
     decode[i]=value;     //��ȡ��1�ֽ�
     value=0;             //��0��׼����ȡ��1�ֽ�        
  } 
}
