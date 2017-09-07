#ifndef HP_6
#define HP_6
#include "includes.h"
#include <stdbool.h>
#include <stdint.h>

#define HP_FAILURE			0x00
#define HP_SUCCESS			0x01

#define HP_IIC_ADDRESS 		0x66
#define HP_READ_BIT       (0x01) 


#define Hp_PowerON()           GPIOB->ODR &= ~(1<<15)			  //PB15����͵�ƽ
#define Hp_PowerOFF()      		 GPIOB->ODR |=  (1<<15)			  //PB15����ߵ�ƽ


void HP_Init(void);

//CRCУ��

uint16_t Crc16(uint8_t *data,uint16_t len);

//HP_Write

bool Hp_Write(uint8_t Hp_6_address, uint8_t *pData, uint8_t bytes);
bool Hp_Read(uint8_t Hp_6_address, uint8_t *pData, uint8_t bytes);

void HP_Delay_ms(uint16_t ms);
uint16_t HP_GetResultData(uint8_t *data);
uint8_t HP_SendCmd(uint8_t *tx_buf, uint8_t *rx_buf);

// �������ʲ���

uint8_t HP_OpenRate(void);

//�ر����ʲ���

uint8_t HP_CloseRate(void);

//��ȡ���ʲ������

uint8_t HP_GetRateResult(void);

// ��ȡѪѹ�������

uint8_t HP_GetBpResult(void);

// ����Ѫѹ�ʲ���
 
uint8_t HP_OpenBp(void);

// �ر�Ѫѹ����
 
uint8_t HP_CloseBp(void);     

uint8_t HP_GetADC(uint8_t num, uint8_t id);


//���õ͹���

uint8_t HP_PowerSaving(void);

 //��ȡ�汾��Ϣ

uint8_t HP_6_VersionInfo(void);




#endif



