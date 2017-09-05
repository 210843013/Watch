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
	u8 pulseBuf[24] = {0};
  TempHumiValue_t humi_temp_val ; 	//��ʪ��	
	Delay_Init(100);
  SPI_Init();	
	LED_Init();
	LED_OFF;
	SHT20_Init();	
  OLED_Init();
	HP_Init();
	
	
	
	
	OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_PULSE);  //��ʾ���뽫�������������󱳲���ƽ�ľ�����5������ʲ����򿪡�
	delay_ms(5000);
	HP_OpenRate();   //�����ʲ���
	delay_ms(1000);	
  OLED_clear();
	
//	Motor_Init();
//  Key_Init();	
	        
//  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
//	TIM2_CH3_PWM_Init(1000,100);


    //OLED_showChString(0,2,"123ad897",16);
	  // OLED_drawBMP(0,0,54,7,(u8*)step_bmp);
	while(1)
	{		
//		 for(i=0;i<=100;i++)
//		 {
//		    TIM2->CCR3=i;
//			TIM3->CCR2=i; 
//		  delay_ms(10);
//		 }
//		 for(i=100;i>=0;i--)
//		   {
//		    TIM2->CCR3=i;
//			TIM3->CCR2=i;	 
//		  delay_ms(10);
//		 }
		
    HP_GetRateResult();
		HP_GetResultData(pulseBuf);
		
		sprintf((char*)uiBuf,"%03d",pulseBuf[7]); // //byte 7�����ʽ��
		OLED_showChString(10,6,uiBuf,16); 		
	  delay_ms(1000);
		
//		//��ȡ��ʪ��
  humi_temp_val = *SHT20_readTemAndHum();
  humi_temp_val = *SHT20_readTemAndHum();//��ȡ�¶�
  sprintf((char*)uiBuf,"Tem %.2f       RH %.2f",humi_temp_val.temperature,humi_temp_val.humidity); // ��������ʾ
	OLED_showChString(0,0,uiBuf,16); 	 	
	}            	 


}













