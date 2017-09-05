#include "includes.h"
#include "bmp.h"
/*************************************
          �����ֱ���Ŀ����
**************************************/
/************************************/

int main()
{
	u8 err;
  u8 uiBuf[40];
	u8 hour,min,sec,ampm;
	u8 pulseBuf[24] = {0};
	u8 BpBuf[24] = {0};
  TempHumiValue_t humi_temp_val ; 	//��ʪ��	
	accValue_t accValue;
	static sportsInfo_t userSportsInfo;
	static u8 time_cnt;
	static timeStamp_t timeStamp;
	static u8 tempSecond;
	short aacx,aacy,aacz;	
										//���ٶȴ�����ԭʼ����
	Delay_Init(100);
  SPI_Init();	
	LED_Init();
	SHT20_Init();	
  OLED_Init(); 
	MPU_Init();
	HP_Init();
	TIM3_Init(10000-1,5000-1);
	RTC_Init();		 			//��ʼ��RTC
	RTC_Set_WakeUp(4,0);		//����WAKE UP�ж�,1�����ж�һ��
//	OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_BP); 
//	delay_ms(5000);
//	HP_OpenRate();   //�����ʲ���
//	HP_OpenBp();
//	delay_ms(1000);	
  OLED_clear();

	
//	Motor_Init();
//  Key_Init();	
	        
//  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
//	TIM2_CH3_PWM_Init(1000,100);


    //OLED_showChString(0,2,"123ad897",16);
	  // OLED_drawBMP(0,0,54,7,(u8*)step_bmp);
	while(1)
	{		
//   HP_GetBpResult();                //��ȡѪѹ����״̬
//	 HP_GetResultData(BpBuf);
//   if(0 == BpBuf[7])                   //byte 7��Ѫѹ������״̬:0�����У�1������ɡ�2����ʧ��
//		 OLED_showChString(10,4,"testing",16);  
//	 else if(1 == BpBuf[7])  
//   {
//		OLED_showChString(10,4,"success",16);
//		sprintf((char*)uiBuf,"%03d/%03d MMGH", BpBuf[10], BpBuf[11]);//byte 10��Ѫѹ��������ĸ�ѹ,byte 11��Ѫѹ��������ĵ�ѹ	
//		OLED_showChString(10,6,uiBuf,16); 		 
//	 }		 
//	 else if(2 == BpBuf[7])                  
//		 OLED_showChString(10,4,"fail   ",16);
//	 else 
//		 //do nothing
//		delay_ms(1000);	
//	
//		
////		//��ȡ��ʪ��
//  humi_temp_val = *SHT20_readTemAndHum();
//  humi_temp_val = *SHT20_readTemAndHum();//��ȡ�¶�
//  sprintf((char*)uiBuf,"Tem %.2f       RH %.2f",humi_temp_val.temperature,humi_temp_val.humidity); // ��������ʾ
//	OLED_showChString(0,0,uiBuf,16); 	 


     MPU_Get_Accelerometer(&aacx,&aacy,&aacz);			  //�õ����ٶȴ���������
		 
		 sprintf((char*)uiBuf,"cx:%d",aacx); // ��ʾ������������
		 OLED_showChString(0,2,uiBuf,16);
		 sprintf((char*)uiBuf,"cy:%d",aacy); // ��ʾ������������
		 OLED_showChString(0,4,uiBuf,16);
		 sprintf((char*)uiBuf,"cz:%d",aacz); // ��ʾ������������
		 OLED_showChString(0,6,uiBuf,16);
		 RTC_Get_Time(&hour,&min,&sec,&ampm); 					  //��ȡ��ǰRTC��ֵ
		
		if(tempSecond != timeStamp.second)					 //�����
		{
			tempSecond = timeStamp.second;
			timeStamp.twentyMsCount = 0 ;//20ms������������
		}
		else												  //�벻���£�1�����50*20ms
		{
			timeStamp.twentyMsCount ++;//20ms��������++
		}
		
		timeStamp.hour	 = hour;
		timeStamp.minute = min;
		timeStamp.second = sec;
		
		
		if(tempSecond != timeStamp.second)					 //�����
		{
			tempSecond = timeStamp.second;
			timeStamp.twentyMsCount = 0 ;//20ms������������
		}
		else												  //�벻���£�1�����50*20ms
		{
			timeStamp.twentyMsCount ++;//20ms��������++
		}
		
		timeStamp.hour	 = hour;
		timeStamp.minute = min;
		timeStamp.second = sec;
		
		//����������ת��Ϊ��gΪ��λ������
		accValue.accX = ((float)(int)aacx/16384) *10;
		accValue.accY = ((float)(int)aacy/16384) *10;
		accValue.accZ = ((float)(int)aacz/16384) *10; 
		userSportsInfo = *onSensorChanged(&accValue,&timeStamp,WatchInfo_getUserInfo(&err)); //���ü����㷨
		
		sprintf((char*)uiBuf,"Step:%05d ",userSportsInfo.stepCount); // ��ʾ����
		OLED_showChString(0,0,uiBuf,16); 
		
		
		if(accValue.accX>=0)
		{ 
			sprintf((char*)uiBuf,"X:%02d ",(char)accValue.accX); // ��������ʾ
			OLED_showChString(88,2,uiBuf,16);				
		}
	  else
		{
			sprintf((char*)uiBuf,"X:-%02d",(char)(-accValue.accX)); // ��������ʾ
			OLED_showChString(88,2,uiBuf,16);				
		}

		
		if(accValue.accY>=0)
		{
			sprintf((char*)uiBuf,"Y:%02d ",(char)accValue.accY); // ��������ʾ
			OLED_showChString(88,4,uiBuf,16);				
		}
	  else
		{
			sprintf((char*)uiBuf,"Y:-%02d",(char)(-accValue.accY)); // ��������ʾ
			OLED_showChString(88,4,uiBuf,16);				
		}
		
		
		if(accValue.accZ>=0)
		{
			sprintf((char*)uiBuf,"Z:%02d ",(char)accValue.accZ); // ��������ʾ
			OLED_showChString(88,6,uiBuf,16);				
		}
	  else
		{
			sprintf((char*)uiBuf,"Z:-%02d",(char)(-accValue.accZ)); // ��������ʾ
			OLED_showChString(88,6,uiBuf,16);				
		}		

		
		delay_ms(20);  //��50Hz��Ƶ��ȥ��ȡ������ٶȵ�XYZ����ٶ�ֵ
	
	}            	 


}













