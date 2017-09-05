#include "includes.h"

//PA7      ʵ�ֺ�����

void TIM3_CH2_PWM_Init(u16 psc,u16 arr)
{
       /********ͨ���ܽŸ��ù�������*****/
	//��PA������ʱ��
	RCC->AHB1ENR |=(1<<0);
	//ģʽ�Ĵ���
	GPIOA->MODER &=~(0x3<<14); //����
	GPIOA->MODER |=(0x2<<14);  //���ù���
	//���ù���ѡ��
	GPIOA->AFR[0] &=~((unsigned int)0xf<<28); //����
	GPIOA->AFR[0] |=((unsigned int )0x2<<28);   //���ó�TIM3
	
	/******TIM3��������������********/
	//�򿪶�ʱ������ʱ��
	 RCC->APB1ENR |=(1<<1);
	//ѡ���ڲ�ʱ����Ϊ������ʱ��Դ
	TIM3->SMCR &=~(0x7<<0);
	//д���Ƶֵ
	TIM3->PSC =psc-1;
	//д����װ��ֵ
	TIM3->ARR =arr;
	//ѡ�������ʽ ���ϼ���
	TIM3->CR1 &=~(1<<4);
	
	/******���ͨ����������*****/
	//д�벶��/�ȽϼĴ����е���ֵ
	TIM3->CCR2= arr/4; 
	
	//��ͨ������Ϊ���
	TIM3->CCMR1 &=~(0x3<<8);
	
	//ѡ���Ƿ��Ӱ�ӹ���
	TIM3->CCMR1 &=~(0x1<<11);
	
	//ѡ��pwm�������ģʽ
	TIM3->CCMR1 &=~(0x7<<12);
	TIM3->CCMR1 |=(0x6<<12);
	
	//ѡ��ͨ������Ч��ƽ
	TIM3->CCER &=~(0x1<<5);
	
	//ͨ��2���ʹ��
	TIM3->CCER |=(0x1<<4);
	
	//������ʹ��
	TIM3->CR1  |=(0x1<<0);

}

void TIM3_IRQHandler(void)
{	
	u8 hour,min,sec,ampm;
	u8 year,month,date,week;
	u8 tbuf[40];


	if(TIM3->SR&0X0001)//����ж�
	{
      GPIOA->ODR	^= 1 << 7; //ÿ��һ�ΰ�������ȡ��LED�Ƶ�״̬
//			RTC_Get_Time(&hour,&min,&sec,&ampm);
//			sprintf((char*)tbuf,"%02d:%02d:%02d",hour,min,sec); 
//			OLED_showChString(0,0,tbuf,16);	
//			RTC_Get_Date(&year,&month,&date,&week);
//			sprintf((char*)tbuf,"20%02d-%02d-%02d",year,month,date); 
//			OLED_showChString(0,2,tbuf,16);		
//			sprintf((char*)tbuf,"NO: %d week",week); 
//			OLED_showChString(0,4,tbuf,16);	
	

	}	
	TIM3->SR&=~(1<<0);//����жϱ�־λ		
}
//ͨ�ö�ʱ��3�жϳ�ʼ��,��ʱ����2/3/4/5��ʱ��Ϊ50M�⣬����Ϊ100M
void TIM3_Init(u16 arr,u16 psc)
{
	u32 pro;
  RCC->APB1ENR|=1<<1; //TIM3ʱ��ʹ��	  
  TIM3->ARR=arr;		//�趨�������Զ���װֵ 
  TIM3->PSC=psc;		//Ԥ��Ƶ��	 
  TIM3->CNT = 0;        //Jahol Fan ���³�ʼ���ͻ����¼���
  TIM3->DIER|=1<<0;	//��������ж�	  
  TIM3->CR1|=0x01;	//ʹ�ܶ�ʱ��3
	//��ռ���ȼ�2bit  �����ȼ�2bit
	NVIC_SetPriorityGrouping(5);//�����ж����ȼ�����
	pro = NVIC_EncodePriority(5, 2, 0);//��ռ���ȼ��ļ���2�� �������ȼ�����0��
	NVIC_SetPriority(TIM3_IRQn, pro);//�������ȼ�

	
	NVIC_EnableIRQ(TIM3_IRQn);//NVIC�ж�ͨ��ʹ�ܡ�							 
}
