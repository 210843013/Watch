#ifndef INCLUDES_H
#define INCLUDES_H

//存放用户自定义的.h文件

#include "stm32f4xx.h"
#include "led.h"
#include "systick.h"
#include "exti.h"
#include "motor.h"
#include "key.h"
#include "tim3_ch2_pwm.h"
#include "tim2_ch3_pwm.h"
#include "spi.h"
#include "oled.h"
#include "string.h"
#include "sht20.h"
#include  "iic.h"
#include "stdio.h"
#include "hp_6.h"
#include "rtc.h"
#include "stepAlgorithm.h"
#include "mpu6050.h"
#include "math.h"
#include "watchInfo.h"
#include "mpu_iic.h"
#include "ui.h"

  
struct KEY{
  
	int puls;
	int flag;

};
          
// 显示
struct SHOW{
	
	 int pre_flag;
	 int aft_flag;	
};



extern const unsigned char F8X16[1520];
extern const unsigned char F6x8[][6];
extern const unsigned char F16X24[];
extern char Hzk[][32];
#endif























