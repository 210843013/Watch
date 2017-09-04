#include "includes.h"

 TempHumiValue_t temp_humi_Value;

static void SHT20_softReset(void)                    
{
	IIC_Start();                      //start I2C
	
	 IIC_Senddate(SHT20ADDR&0xfe);  //I2C address + write	
	if(IIC_Receiveack())
		return ;
	
	 IIC_Senddate(0xfe);                         //soft reset
		if(IIC_Receiveack())
		  return ;
		
	IIC_Stop();                       //stop I2C
}
 /*******************************************************************************
 * ��������SHT20_Init
 * ������������ʼ��iic����
 * ���ߣ�Jahol Fan  
 * ����˵����  
 * ����ֵ˵�����ɹ����ز����Ľ����ʧ�ܷ��� 1
 * �޸ļ�¼��
*******************************************************************************/
 void SHT20_Init(void)
{
	SHT20_softReset();
}

/*******************************************************************************
 * ��������SHT20_setResolution
 * ����������д�Ĵ���������֡��
 * ���ߣ�Jahol Fan  
 * ����˵����  
 * ����ֵ˵����
 * �޸ļ�¼��
*******************************************************************************/
static void SHT20_setResolution(void)                    
{
  IIC_Start();                                                                        //Start I2C 
   
	 IIC_Senddate(SHT20ADDR&0xfe);            //I2C address + write + ACK
	 if(IIC_Receiveack())
		  return ;
  
	  IIC_Senddate(0xe6);                               //д�û��Ĵ���
    if(IIC_Receiveack())
		  return ;
  
		 IIC_Senddate(0x83);  //���÷ֱ���   11bit RH% ����ʱ�䣺12ms(typ.) & 11bit T�� ����ʱ�䣺9ms(typ.) 
    if(IIC_Receiveack())
		  return ;
   
		IIC_Stop();                                  //Stop I2C         
}
/*******************************************************************************
 * ��������SHT20_readTemOrHum
 * ������������ȡSHT20���¶Ȼ��ȡʪ�Ȳ���ֵ  
 * ���ߣ�Jahol Fan  
 * ����˵����  
 * ����ֵ˵�����ɹ����ز����Ľ����ʧ�ܷ��� 1
 * �޸ļ�¼��
*******************************************************************************/
float SHT20_readTemOrHum(u8 commod)
{
	float temp;                 //�¶�
	u8  MSB,LSB;              //�¶ȡ����ʪ�ȵļĴ�������
	float Humidity,Temperature; //��ʪ�ȵ�ת�����

	SHT20_setResolution();           //����֡��8bit,9bit,10 bit,11bit ,12bit,13bit,14bit
	IIC_Start();                 //iic��ʼ�ź�
	
    IIC_Senddate(SHT20ADDR&0xfe);   //д��ַ
     if(IIC_Receiveack())
		   return 0; 
		 
	  IIC_Senddate(commod);
     if(IIC_Receiveack())
		   return 0 ;  		 //д����
		  do{
				IIC_Delay_us(6);                                    //��ʱ
				IIC_Start();                                    //���Ϳ�ʼ�ź�
			  IIC_Senddate(SHT20ADDR|0x01);      //��Ӧ�������Σ����ڲ����У������Ӧ���������ǰѭ��
      
			}while(IIC_Receiveack());
			
			MSB = IIC_Receivedate();                          //��Data(MSB)����Ӧ��ACK
      IIC_Sendack(0);	
			
			LSB = IIC_Receivedate();                          //��Data(LSB)����Ӧ��ACK
			IIC_Sendack(0);
			
		   IIC_Receivedate();                               //��Checksum ������Ӧ��NACK 
			IIC_Sendack(1);	
			
			IIC_Stop();                                         //Stop I2C
			LSB &= 0xfc;                                       //Data (LSB) �ĺ���λ�ڽ����������ǰǰ���á�0�� 
			temp = MSB*256 + LSB;                              //ʮ������ת��ʮ����

			if (commod==((u8)READ_HUMI_COMD))                         //����Ϊ��ȡʪ�ȵ�����
			{        
				/*-- calculate relative humidity [%RH] --*/ 
				Humidity =(temp*125)/65536-6;                   //��ʽ: RH%= -6 + 125 * SRH/2^16
				return Humidity;                                //����ֵ��humidity
			}                                                                                                  
			else if(commod==((u8)READ_TEMP_COMD))                     //����Ϊ��ȡ�¶ȵ�����
			{        
				 /*-- calculate temperature [��C] --*/
				Temperature = (temp*175.72f)/65536-46.85f;       //��ʽ:T= -46.85 + 175.72 * ST/2^16
				return Temperature;                             //����ֵ��temperature
			}
  return FAIL;
}
/*******************************************************************************
 * ��������SHT20_readTemAndHum
 * ������������ȡSHT20���¶Ⱥ�ʪ�Ȳ���ֵ  
 * ���ߣ�Jahol Fan  
 * ����˵����  
 * ����ֵ˵�����ɹ����ز����Ľ����ʧ�ܷ��� 1
 * �޸ļ�¼��
*******************************************************************************/

TempHumiValue_t * SHT20_readTemAndHum(void)
{
	temp_humi_Value.humidity = SHT20_readTemOrHum(READ_HUMI_COMD);//��ȡʪ��
	temp_humi_Value.temperature = SHT20_readTemOrHum(READ_TEMP_COMD);//��ȡʪ��
	return &temp_humi_Value;
}

