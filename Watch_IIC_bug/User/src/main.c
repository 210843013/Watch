#include "includes.h"
#include "bmp.h"
/*************************************
          �����ֱ���Ŀ����
**************************************/
/************************************/

int main()
{
	//int i;
 u8 uiBuf[40];
  TempHumiValue_t humi_temp_val ; 	//��ʪ��	
  SPI_Init();	
	LED_Init();
	LED_OFF;
	SHT20_Init();
	
//	Motor_Init();
//  Key_Init();	
	        
//  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
//	TIM2_CH3_PWM_Init(1000,100);
	  OLED_Init();

    //OLED_showChString(0,2,"123ad897",16);
	  // OLED_drawBMP(0,0,54,7,(u8*)step_bmp);
	while(1)
	{		
//		 for(i=0;i<=100;i++)
//		 {
//		    TIM2->CCR3=i;
//			TIM3->CCR2=i; 
//		  Delay_ms(10);
//		 }
//		 for(i=100;i>=0;i--)
//		   {
//		    TIM2->CCR3=i;
//			TIM3->CCR2=i;	 
//		  Delay_ms(10);
//		 }
	  LED_ON;

		
		//��ȡ��ʪ��
  humi_temp_val = *SHT20_readTemAndHum();
  humi_temp_val = *SHT20_readTemAndHum();//��ȡ�¶�
	sprintf((char*)uiBuf,"%.2f  %.2f",humi_temp_val.temperature,humi_temp_val.humidity); // ��������ʾ
	OLED_showChString(0,0,uiBuf,16); 	 	
	}            	 


}













