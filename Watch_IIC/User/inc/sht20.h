#ifndef SHT20_H
#define SHT20_H
#include "stm32f4xx.h"

#define SHT20ADDR       0x80         //SHT20д��ַ
#define ACK             0            //Ӧ���ź�
#define NACK            1            //��Ӧ���ź�
#define FAIL            1            //��ȡ��ʪ��ʧ�ܵķ���ֵ��
#define READ_TEMP_COMD  0xf3         //��ȡ�¶�����
#define READ_HUMI_COMD  0xf5         //��ȡʪ������

typedef struct
{
	float temperature; //ʪ��
	float humidity;    //�¶�
}TempHumiValue_t;
 
void SHT20_Init(void);
TempHumiValue_t * SHT20_readTemAndHum(void);



static void SHT20_setResolution(void); 
static void SHT20_softReset(void);
void SHT20_Init(void);

 
#endif


