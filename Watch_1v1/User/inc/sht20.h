#ifndef SHT20_H
#define SHT20_H

#include "stm32f4xx.h"

#define SHT20_WRITEADDR       0x80   //SHT20д��ַ
#define SHT20_READADDR       0x81    //SHT20����ַ
#define READ_TEMP_COMD  0xf3         //��ȡ�¶�����
#define READ_HUMI_COMD  0xf5         //��ȡʪ������

typedef struct
{
	float temperature; //ʪ��
	float humidity;    //�¶�
}TempHumiValue_t;
 

void SHT20_Init(void);
void SHT20_softReset(void);
void SHT20_setResolution(void);
float SHT20_readTemOrHum(u8 commod);
TempHumiValue_t * SHT20_readTemAndHum(void);
#endif /* SHT20_H */
