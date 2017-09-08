#include "includes.h"
//PB10
void Motor_Init()
{
	//��PBʱ����
	RCC->AHB1ENR |=(0x1<<1);
	
	//����PB�����ģʽ
	GPIOB->MODER &=~(0x3<<20);
	GPIOB->MODER |=(0x1<<20);
	
	//�����������
	GPIOB->OTYPER &=~(0x1<<10);
	
	//�����������
	GPIOB->OSPEEDR &=~(0x3<<20);
	GPIOB->OSPEEDR |=(0x2<<20);
	
	//������������
	GPIOB->PUPDR &=~(0x3<<20);
	GPIOB->PUPDR |=(0x1<<20);
	
}



