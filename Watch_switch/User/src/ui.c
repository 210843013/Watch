#include "includes.h"
#include "bmp.h"

//�����ֱ�UI������ת ʵ��ԭ��  �ṹ��

// ����ҳ�湦�ܺ���ʵ��

//ʱ��
static struct SHOW s;
static struct KEY k;
	
void ShowTime()
{  
  u8 hour,min,sec,ampm;
	u8 year,month,date,week;
	u8 tbuf[40];
	OLED_clear();	
      while(1)
			{				
			RTC_Get_Time(&hour,&min,&sec,&ampm);
			sprintf((char*)tbuf,"%02d:%02d:%02d",hour,min,sec); 
			OLED_showChString(0,0,tbuf,16);	
			RTC_Get_Date(&year,&month,&date,&week);
			sprintf((char*)tbuf,"20%02d-%02d-%02d",year,month,date); 
			OLED_showChString(0,2,tbuf,16);		
			sprintf((char*)tbuf,"NO: %d week",week); 
			OLED_showChString(0,4,tbuf,16);
			if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
						return;
				}		
			}
			
		
}
	//����
	void Show_Hp_Rate()
	{
		u8 uiBuf[40];
		u8 pulseBuf[24] = {0};
		OLED_clear();
		OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_BP); 
		delay_ms(1000);
		HP_OpenRate();   //�����ʲ���
		//HP_OpenBp();
		delay_ms(1000);
		OLED_clear();	
		while(1)
				{	
					HP_GetRateResult();
					HP_GetResultData(pulseBuf); 	
					sprintf((char*)uiBuf,"plus:%03d",pulseBuf[7]); // //byte 7�����ʽ��
					OLED_showChString(40,6,uiBuf,16); 
       if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
					return;
				}
			}
		
	}
//Ѫѹ
void Show_Hp_Bp()
{
   u8 BpBuf[24] = {0};
	 u8 uiBuf[40];
	  OLED_clear();
	  OLED_drawBMP(0,0,128,8,(u8*)BMP_OPEN_BP); 
		delay_ms(1000);
		//HP_OpenRate();   //�����ʲ���
		HP_OpenBp();
		delay_ms(1000);
		OLED_clear();
   while(1)
			{	
				
	 HP_GetBpResult();                //��ȡѪѹ����״̬
	 HP_GetResultData(BpBuf);
   if(0 == BpBuf[7])                   //byte 7��Ѫѹ������״̬:0�����У�1������ɡ�2����ʧ��
		 OLED_showChString(20,4,"testing",16);  
	 else if(1 == BpBuf[7])  
   {
		OLED_showChString(20,4,"success",16);
		sprintf((char*)uiBuf,"%03d/%03d MMGH", BpBuf[10], BpBuf[11]);//byte 10��Ѫѹ��������ĸ�ѹ,byte 11��Ѫѹ��������ĵ�ѹ	
		OLED_showChString(20,6,uiBuf,16); 		 
	 }		 
	 else if(2 == BpBuf[7])                  
		 OLED_showChString(20,4,"fail   ",16);
				if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
					return;
				}
 }
	
}

//��ʪ��

void Show_RH()
{
	
	TempHumiValue_t humi_temp_val ; 	//��ʪ��	
   u8 uiBuf[40];
	 OLED_clear();	
	while(1)
			{	
	//��ȡ��ʪ��
  humi_temp_val = *SHT20_readTemAndHum();
  humi_temp_val = *SHT20_readTemAndHum();//��ȡ�¶�
  sprintf((char*)uiBuf,"Tem %.2f       RH %.2f",humi_temp_val.temperature,humi_temp_val.humidity); // ��������ʾ
	OLED_showChString(0,0,uiBuf,16);
			
			 if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
					return;
				}
			}

}
 //�Ʋ�
void Show_Step()
{
	
	u8 err;
	u8 hour,min,sec,ampm;
  u8 uiBuf[40];
  accValue_t accValue;
	static sportsInfo_t userSportsInfo;
	static u8 time_cnt;
	static timeStamp_t timeStamp;
	static u8 tempSecond;
	short aacx,aacy,aacz;
  OLED_clear();		
										//���ٶȴ�����ԭʼ����
	while(1)
			{	  
	 MPU_Get_Accelerometer(&aacx,&aacy,&aacz);			  //�õ����ٶȴ���������

	
//		 sprintf((char*)uiBuf,"cx:%d",aacx); // ��ʾ������������
//		 OLED_showChString(0,2,uiBuf,16);
//		 sprintf((char*)uiBuf,"cy:%d",aacy); // ��ʾ������������
//		 OLED_showChString(0,4,uiBuf,16);
//		 sprintf((char*)uiBuf,"cz:%d",aacz); // ��ʾ������������
//		 OLED_showChString(0,6,uiBuf,16);

	  RTC_Get_Time(&hour,&min,&sec,&ampm);		//��ȡ��ǰRTC��ֵ

		//OLED_drawBMP(0,0,54,7,(u8*)gImage_step);

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
		
		sprintf((char*)uiBuf,"sp:%04d ",userSportsInfo.stepCount); // ��ʾ����
		OLED_showChString(64,0,uiBuf,16); 
		
		
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
      if(Key_ON==1)
				{
					delay_ms(50);
					if(Key_ON==1)
					return;
				}
	}


}
