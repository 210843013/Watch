#include "includes.h"

//PA0

void Key_Init()
{
                   //��PA��ʱ����
	RCC->AHB1ENR |=(0x1<<0);
	
   //��������ģʽ
	GPIOA->MODER &=~(0x3<<0);
	
	//������������  ����
	GPIOA->PUPDR &=~(0x3<<0);
	GPIOA->PUPDR |=(0x1<<0);
}


