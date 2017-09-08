#include "includes.h"

//SPI PB3 PB4 PB5

void SPI_Init()
{
//  //��SPI��ʱ����
	RCC->APB2ENR |=(0x1<<12);
	//��PB��ʱ����
	RCC->AHB1ENR |=(0x1<<1);
	
	//����Ϊ���
	GPIOB->MODER &=~(0x3f<<6);
	GPIOB->MODER |=(0x2a<<6);
	
	GPIOB->OSPEEDR &=~(0x3f<<6);
	GPIOB->OSPEEDR |=(0x2a<<6);
	
	GPIOB->AFR[0] &= ~(0xfff<< 12);
	GPIOB->AFR[0] |=  0x555 << 12; // af5����
		
	//����SPI��������ģʽ
	SPI1->CR1 |=(0x1<<2);
	//����SPI��������豸����
	SPI1->CR1 |=(0x1<<9);
	SPI1->CR1 |=(0x1<<8);
	//���ò�����
	SPI1->CR1 |=(0x4<<3);
	//����λ��
	SPI1->CR1 &= ~(0x1<<11);
	//MSB��ǰ
	SPI1->CR1 &=~(0x1<<7);
	//ʱ�Ӽ��� ��λ
	SPI1->CR1 &=~(0x3<<0);
	//SPIʹ��
	SPI1->CR1 |=(0x1<<6);


}
u8 SPI_ReceiveByte(u8 data)
{
	//�ȴ����ͻ�����Ϊ��
  while((SPI1->SR &(0x1<<1))==0);
	
	SPI1->DR = data;
	//�ȴ����ջ�����Ϊ��
  while((SPI1->SR &(0x1<<0))==0);
	
	return (SPI1->DR);

}

