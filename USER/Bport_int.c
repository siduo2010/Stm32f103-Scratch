#include "Bport_int.h"

/*
 * ��������Key_GPIO_Config
 * ����  �����ð����õ���I/O��
 * ����  ����
 * ���  ����
 */
void Key_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*���������˿ڣ�PB0����ʱ��*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_4 | GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 

	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
 /*
 * �������� Delay
 * ����  ������ȷ����ʱ
 * ����  ����ʱ������
 * ���  ����
 */
void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
}
 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
u8 GPIO_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*����Ƿ��а������� */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*��ʱ����*/
	  	Delay(10000);		
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*�ȴ������ͷ�
						while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);  */  
			 			return 	KEY_ON;	 
					}
			else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}
