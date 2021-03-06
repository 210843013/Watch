#include "includes.h" 

/*************************************
          智能手表项目开发
**************************************/
/************************************/
// 初始化为0

static struct SHOW show={0,0};
static struct KEY key={1,1};

// 置位计算

void Camp()
{ 
	if(show.aft_flag>5)
	{
   show.aft_flag=0;
   show.pre_flag=0;
	}
 if(key.flag>5)
   key.flag=1;	 
  show.pre_flag=show.aft_flag;
  show.aft_flag+=key.puls;

}

//按键值

int main()
{
 static int pre=1,aft=1;
	Delay_Init(100);
  SPI_Init();	
	LED_Init();
	SHT20_Init();	
  OLED_Init(); 
	MPU_Init();
	HP_Init();
	RTC_Init();		 			//初始化RTC
	RTC_Set_WakeUp(4,0);		//配置WAKE UP中断,1秒钟中断一次
	Motor_Init();
  Key_Init();	
	TIM3_Init(10000-1,5000-1);        
//  TIM3_CH2_PWM_Init(1000,100); // 100*10^6/1000*100 = 1000
//	TIM2_CH3_PWM_Init(1000,100);

	while(1)
	{		
		  if(Key_ON==1)
			{
				Camp();
			  aft=show.aft_flag;
				pre=show.pre_flag;
				key.flag++;

			}
          switch(aft)
					{
						case 1:
								ShowTime();
						    delay_ms(100);
						  	break;
						case 2:
							Show_Hp_Rate();
						  delay_ms(100);  
						  break;
						case 3:
							Show_Hp_Bp();
						  delay_ms(100);
						  break;
						case 4:
							Show_RH();
						  delay_ms(100);
						  break;
						case 5:
							Show_Step();
						  delay_ms(100);
	            break;
						default:
						break;
				} 
	}

}












