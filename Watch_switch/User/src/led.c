#include "includes.h"

//PA7
void LED_Init(void)
{
	//��PA��ʱ����
	RCC->AHB1ENR |=(0x1<<0);
	
   //�������ģʽ
	GPIOA->MODER &=~(0x3<<14);
	GPIOA->MODER |=(0x1<<14);
	
	//�����������
	GPIOA->OTYPER &=~(0x1<<7);
	
	//�����������
	GPIOA->OSPEEDR &=~(0x3<<14);
	GPIOA->OSPEEDR |=(0x2<<14);
	
	//������������  ����
	GPIOA->PUPDR &=~(0x3<<14);
	GPIOA->PUPDR |=(0x1<<14);
}


