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
	u8 BpBuf[24] = {0};
  TempHumiValue_t humi_temp_val ; 	//��ʪ��	
	Delay_Init(100);
  SPI_Init();	
	LED_Init();
	SHT20_Init();	
  OLED_Init();
	HP_Init();
	TIM3_Init(10000-1,5000-1);
	OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_PULSE);  //��ʾ���뽫�������������󱳲���ƽ�ľ�����5������ʲ����򿪡�
	delay_ms(5000);
	HP_OpenRate();   //�����ʲ���
	HP_OpenBp();
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
   HP_GetBpResult();                //��ȡѪѹ����״̬
	 HP_GetResultData(BpBuf);
   if(0 == BpBuf[7])                   //byte 7��Ѫѹ������״̬:0�����У�1������ɡ�2����ʧ��
		 OLED_showChString(10,4,"testing",16);  
	 else if(1 == BpBuf[7])  
   {
		OLED_showChString(10,4,"success",16);
		sprintf((char*)uiBuf,"%03d/%03d MMGH", BpBuf[10], BpBuf[11]);//byte 10��Ѫѹ��������ĸ�ѹ,byte 11��Ѫѹ��������ĵ�ѹ	
		OLED_showChString(10,6,uiBuf,16); 		 
	 }		 
	 else if(2 == BpBuf[7])                  
		 OLED_showChString(10,4,"fail   ",16);
	 else 
		 //do nothing
		delay_ms(1000);	
	
		
//		//��ȡ��ʪ��
  humi_temp_val = *SHT20_readTemAndHum();
  humi_temp_val = *SHT20_readTemAndHum();//��ȡ�¶�
  sprintf((char*)uiBuf,"Tem %.2f       RH %.2f",humi_temp_val.temperature,humi_temp_val.humidity); // ��������ʾ
	OLED_showChString(0,0,uiBuf,16); 	 
	
	}            	 


}













