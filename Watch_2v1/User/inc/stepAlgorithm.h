#ifndef STEPALGORITHM_H
#define STEPALGORITHM_H
#include "includes.h"
#include "mpu6050.h"
 typedef struct 
{
	float calories; //��·��
	float distance;//��··�̣���λΪm
	u32 stepCount;	//����
}sportsInfo_t;

typedef struct 
{
	float height;
	float weight;
}personInfo_t;

sportsInfo_t *onSensorChanged(accValue_t *pAccValue,timeStamp_t *timeStamp_p,personInfo_t * personInfo);

sportsInfo_t *DetectorNewStep(float values,timeStamp_t *timeStamp_p,personInfo_t * personInfo)  ; 
u8 DetectorPeak(float newValue, float oldValue);
float Peak_Valley_Thread(float value) ;
float averageValue(float value[], int n);
u32 * getCount(void);

#endif


