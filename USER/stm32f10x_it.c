/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "usart1.h"

unsigned char checkbuffer[20]={0};
unsigned char checkbuffercount=0;
char head=0,bufferrecevie=0;

unsigned char Readbuffer[20]={0};
unsigned char USART_Count=1;

int Perform=0;

extern void TimingDelay_Decrement(void);

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
unsigned char  IRQ_num;
unsigned char time_exti=0;
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
	time_exti++;
	if(time_exti>=25)
	{
		IRQ_num++;
		time_exti=0;
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
	  checkbuffer[checkbuffercount]=USART1->DR;
		
		if(checkbuffer[checkbuffercount]==0x55 && checkbuffer[checkbuffercount-1]==0xff)
		{
			bufferrecevie=1;
		}
		
		if(bufferrecevie==1)
		{
			Readbuffer[USART_Count]=USART1->DR;
			USART_Count++;
		}
		
		checkbuffercount++;
		
		if(Readbuffer[USART_Count-2]==0xaa && Readbuffer[USART_Count-1]==0xbb)
		{
			bufferrecevie=0;
			checkbuffercount=0;
			USART_Count=1;
			Perform=1;
		}
		
//		printf("%c",0x11);
	}  
}
static unsigned char  i;         //���պ����źŴ���
static char flag;         			 //�ڶ��ν����ж�ʱ����ɵ�1�����ڼ�ʱ
extern char IRF_ok; 
extern unsigned char  T_num[33];
/* I/O���жϣ��ж���ΪPB0 */
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  { 	
		if(flag)                         
		{
			if(IRQ_num<50&&IRQ_num>=30)//����һ�ΰ���������һ��13.5ms(9ms+4.5ms)������
				i=0;   //�������¿�ʼ�洢��������32λ�������ڳ���
			T_num[i]=IRQ_num;  //�洢ÿ��ÿ�����ڵĳ���ʱ�䣬�����жϸߵ͵�ƽ
			//printf("%d ",IRQ_num);
			IRQ_num=0;         //��ʱ�жϴ�����0���Ա㿪ʼ������һ�����ڵĳ���ʱ��
			i++;               //i��1
			if(i==33)
			{
				IRF_ok=1;     //����1����ɣ��ñ�־λ
				i=0;          //�������¿�ʼ�洢��������32λ�������ڳ���
				flag=0;
			}
		}
		else
		{
			IRQ_num=0;             //��ʱ�жϴ�����0   
			flag=1;                //��һ�ν����ж�,�ñ�־λ
		}
/*    
		if(IRF_ok)         //������1�κ���
	  {   
	   bit_byte();     //��ȡ��32λ����
 	   IRF_ok=0;       //���־λ
	  }
*/		
		EXTI_ClearITPendingBit(EXTI_Line0);     //����жϱ�־λ
  }  
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
