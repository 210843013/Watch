#include "includes.h"  

/*******************************************************************************
 * ��������SHT20_softReset
 * ����������SHT20�����λ��
 * ����˵����  ��
 * ����ֵ˵������

*******************************************************************************/
void SHT20_softReset(void)                    
{
	IIC_Start();                      //start I2C
	MCU_IIC_Senddata(SHT20_WRITEADDR);  //I2C address + write
	//MCU�ȴ�����Ӧ���ź�
	if(MCU_IIC_Receiveack())
	{
		 //��Ӧ��
		 return  ;
	}
	//MCU���͸�λָ��
	MCU_IIC_Senddata(0xfe);                 //soft reset
	//MCU�ȴ�����Ӧ���ź�
	if(MCU_IIC_Receiveack())
	{
		 //��Ӧ��
		 return  ;
	}
	IIC_Stop();                       //stop I2C
}
 /*******************************************************************************
 * ��������SHT20_Init
 * ������������SHT20������λ��ʼ�� 
 * ����˵����  
 * ����ֵ˵������
 * �޸ļ�¼��
*******************************************************************************/
void SHT20_Init(void)
{
	SHT20_softReset();
}
 
/*******************************************************************************
 * ��������SHT20_setResolution
 * ����������д�Ĵ���������֡��
 * ����˵����  
 * ����ֵ˵����
 * �޸ļ�¼��
*******************************************************************************/
void SHT20_setResolution(void)                    
{
  IIC_Start(); 	//Start I2C 
	MCU_IIC_Senddata(SHT20_WRITEADDR);  // I2C address + write
	//MCU�ȴ�����Ӧ���ź�
	if(MCU_IIC_Receiveack())
	{
		 //��Ӧ��
		 return  ;
	}
	MCU_IIC_Senddata(0xe6);  //д�Ĵ���
	//MCU�ȴ�����Ӧ���ź�
	if(MCU_IIC_Receiveack())
	{
		 //��Ӧ��
		 return  ;
	}
	MCU_IIC_Senddata(0x83);  //���÷ֱ���  
	//MCU�ȴ�����Ӧ���ź�
	if(MCU_IIC_Receiveack())
	{
		 //��Ӧ��
		 return  ;
	}
  IIC_Stop();         //Stop I2C         
}
/*******************************************************************************
 * ��������SHT20_readTemOrHum
 * ������������ȡSHT20���¶Ȼ��ȡʪ�Ȳ���ֵ  
 * ����˵����  
 * ����ֵ˵�����ɹ����ز����Ľ����
 * �޸ļ�¼��
*******************************************************************************/
float SHT20_readTemOrHum(u8 commod)
{
	float temp;                 //�¶�
	
	u8  MSB,LSB;              //�¶ȡ����ʪ�ȵļĴ�������
	float Humidity,Temperature; //��ʪ�ȵ�ת�����

	SHT20_setResolution();           //����֡��8bit,9bit,10 bit,11bit ,12bit,13bit,14bit
	IIC_Start();                 //iic��ʼ�ź�
	MCU_IIC_Senddata(SHT20_WRITEADDR&0xfe);  //I2C address + write
	//MCU�ȴ�����Ӧ���ź�
	if(MCU_IIC_Receiveack())
	{
		 //��Ӧ��
		 return  0;
	}
	MCU_IIC_Senddata(commod);  //���Ͳ����¶�/ʪ������
	//MCU�ȴ�����Ӧ���ź�
	if(MCU_IIC_Receiveack())
	{
		 //��Ӧ��
		 return 0 ;
	}
	do
	{
		delay_us(6);         //��ʱ
		IIC_Start();        //���Ϳ�ʼ�ź�
		MCU_IIC_Senddata(SHT20_READADDR|0x01);
	}while(MCU_IIC_Receiveack());  //��Ӧ�������Σ����ڲ����У������Ӧ���������ǰѭ��

	MSB = MCU_IIC_Receivedata();    //��Data(MSB)
	MCU_IIC_Sendack(0);      //��Ӧ��ACK
	
	LSB = MCU_IIC_Receivedata();  //��Data(LSB)
	MCU_IIC_Sendack(0);      //��Ӧ��ACK
	
	MCU_IIC_Receivedata();    //��Checksum ��
	MCU_IIC_Sendack(1); //����Ӧ��NACK 
	
	IIC_Stop();                //Stop I2C
	LSB &= 0xfc;      //Data (LSB) �ĺ���λ�ڽ����������ǰǰ���á�0�� 
	temp = MSB*256 + LSB;           //ʮ������ת��ʮ����
           
	if (commod==((u8)READ_HUMI_COMD))  //����Ϊ��ȡʪ�ȵ�����
	{        
	
		Humidity =(temp*125)/65536-6;                   //��ʽ: RH%= -6 + 125 * SRH/2^16
		return Humidity;                                //����ֵ��humidity
	}                                                                                                  
	else if(commod==((u8)READ_TEMP_COMD))                     //����Ϊ��ȡ�¶ȵ�����
	{        
		 /*-- calculate temperature [��C] --*/
		Temperature = (temp*175.72)/65536-46.85;       //��ʽ:T= -46.85 + 175.72 * ST/2^16
		return Temperature;                             //����ֵ��temperature
	}
   return 1;
}
 TempHumiValue_t temp_humi_Value;
TempHumiValue_t * SHT20_readTemAndHum(void)
{
	temp_humi_Value.humidity = SHT20_readTemOrHum(READ_HUMI_COMD);//��ȡʪ��
	temp_humi_Value.temperature = SHT20_readTemOrHum(READ_TEMP_COMD);//��ȡʪ��
	return &temp_humi_Value;
}



