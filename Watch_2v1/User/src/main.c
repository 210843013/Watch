#include "includes.h" 

/*************************************
          �����ֱ���Ŀ����
**************************************/
/************************************/
// ��ʼ��Ϊ0

//static struct SHOW show={0,0};
//static struct KEY key={1,0};
       struct KEY key={1,0};
			 struct SHOW show={0,0};
// ��λ����

void Camp()
{ 
	if(show.aft_flag>5)
	{
   show.aft_flag=0;
   show.pre_flag=0;
	}	 
  show.pre_flag=show.aft_flag;
  show.aft_flag+=key.puls;

}

//����ֵ

int main()
{
 static int pre=1,aft=1;
	Delay_Init(100);
  SPI_Init();	
	LED_Init();
	SHT20_Init();	
  OLED_Init(); 
	MPU_Init();
	HP_Init();
	RTC_Init();		 			//��ʼ��RTC
	RTC_Set_WakeUp(4,0);		//����WAKE UP�ж�,1�����ж�һ��
	Motor_Init();
  Key_Init();	      
//  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
//	TIM2_CH3_PWM_Init(1000,100);

	while(1)
	{		
//		if(key.flag==10)   
//			{
//				Motor_ON;
//			}
		if(Key_ON==1)
	{
		  delay_ms(80);
		  if(Key_ON==1)
			{
				Camp();
//			  aft=show.aft_flag;
//				pre=show.pre_flag;
				key.flag++;
       	
			}
		}
		  SHOWMENU();
 
	}

}












