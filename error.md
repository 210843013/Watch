# Watch

					watch原理图
![image](https://github.com/210843013/Watch/blob/master/watch.png)


##配置TIMx输出PWM注意事项：
				

![image](https://github.com/210843013/Watch/blob/master/afr.png)
			
			复用功能选择
			GPIOB->AFR[1] &=~((unsigned int)0xf<<8); //清零
			GPIOB->AFR[1] |= ((unsigned int)0x1<<8);   //复用成TIM2
			
			
##定时器2的通道3
			
![image](https://github.com/210843013/Watch/blob/master/ch.png)
			
			
				CCMRx的选择
			
![image](https://github.com/210843013/Watch/blob/master/ccmrx.png)
   
				当选择TIMx_ch1 TIMX_ch2时候，选择比较方式1和2即CCMR1
				
![image](https://github.com/210843013/Watch/blob/master/ccmr1.png)

				当选择TIMx_ch3 TIMX_ch4时候，选择比较方式3和4即CCMR2
				
![image](https://github.com/210843013/Watch/blob/master/ccmr2.png)
			
			
			//把通道配置为输出
			TIM2->CCMR2 &=~(0x3<<0);
			
			//选择是否打开影子功能
			TIM2->CCMR2 &=~(0x1<<3);
			
			//选择pwm波的输出模式
			TIM2->CCMR2 &=~(0x7<<4);
			TIM2->CCMR2 |=(0x6<<4);
			
			//选择通道的有效电平
			TIM2->CCER &=~(0x1<<9);
			
			//通道2输出使能
			TIM2->CCER |=(0x1<<8);
			
			//计数器使能
			TIM2->CR1  |=(0x1<<0);
			
##显示汉字字符串的注意点	

			注意：我是要在oled屏幕上显示三个汉字，结果。。看结果图
			
![image](https://github.com/210843013/Watch/blob/master/three.png)

			汉字串显示函数，调用单个字符串显示函数没毛病，匹配对应索引列表的汉字
			返回对应汉字字符所在的行，即汉字在自定义字库中的位置，调用WriteByte打印函数。

![image](https://github.com/210843013/Watch/blob/master/hz.png)
			
			如结果图所示，显示6个汉字，多次试验汉字成倍显示，bug待修复。
			
![image](https://github.com/210843013/Watch/blob/master/pic.JPG) 


##汉字显示bug修复

			原汉字字符串显示函数与修改bug后的字符串显示函数
				
![image](https://github.com/210843013/Watch/blob/master/bug.png)
			
			一个汉字占用数组的两个位，例如汉字 '将' 存放到数组str中，会占用两个数组元素的位置，
			假如是str[0]和str[1].
			
	        汉字显示bug修复， 将汉字匹配的条件改为
			
			  if((*buf==hz_index[i]) && (*(buf+1) ==hz_index[i+1]))	

![image](https://github.com/210843013/Watch/blob/master/diff.png)

			在上图中， for(i=0;i<strlen(hz_index);i+=2)，这里+2原因也是一个汉字占用数组的两个位。
			直接将汉字移动到下一个汉字的位置即可。
			
			   OLED_writeByte(Hzk[i][t],OLED_DATA)   和 OLED_writeByte(Hzk[2*no][t],OLED_DATA)的区别
			   OLED_writeByte(Hzk[i+1][t],OLED_DATA)    OLED_writeByte(Hzk[2*no][t],OLED_DATA) 
			   
			 如下： 
			 
			   OLED_writeByte(Hzk[i][t],OLED_DATA) 
			   OLED_writeByte(Hzk[i+1][t],OLED_DATA)

![image](https://github.com/210843013/Watch/blob/master/font.png)			   

			 该程序直接一个显示汉字的前半部分，一个显示汉字的后半部分. for(i=0;i<strlen(hz_index);i+=2)
			 中i+=2，直接越过前一个汉字的后半部分，跳到下一个汉字的前半部分的首行。然后调用写字节函数。
			 
			 如下：
			 
			   OLED_writeByte(Hzk[no*2][t],OLED_DATA) 
			   OLED_writeByte(Hzk[no*2+1][t],OLED_DATA)
			   
![image](https://github.com/210843013/Watch/blob/master/font.png)	
		   
			 该程序直接一个显示汉字的前半部分，一个显示汉字的后半部分,这个也是一样的。
			 分析：这里的no传入的是汉字所在数组的位置，即第几个汉字，当传入第3个汉字时，对应是第6第7行。
			 再调用写字节。
			 
			修复bug调试：
			
![image](https://github.com/210843013/Watch/blob/master/xs1.png)

			调试结果：
			
![image](https://github.com/210843013/Watch/blob/master/pic2.png)		
			
			OK，正常显示。
			
![image](https://github.com/210843013/Watch/blob/master/soft.png)

				#软件复位编程,如上图所示
					步骤：
						1、IIC_Start()
						2、I2C address + write ，发送写地址命令
						3、等待ACK应答
						4、发送复位指令0xfe
						5、等待ACK应答
						6、IIC_Stop()
						
						
		  void SHT20_softReset(void)                    
			{
				IIC_Start();                      //start I2C
				MCU_IIC_Senddata(SHT20_WRITEADDR);  //I2C address + write
				//MCU等待接收应答信号
				if(MCU_IIC_Receiveack())
				{
					 //无应答
					 return  ;
				}
				//MCU发送复位指令
				MCU_IIC_Senddata(0xfe);                 //soft reset
				//MCU等待接收应答信号
				if(MCU_IIC_Receiveack())
				{
					 //无应答
					 return  ;
				}
				IIC_Stop();                       //stop I2C
			}

![image](https://github.com/210843013/Watch/blob/master/IIC.png)


				    IIC_Start(); 	//Start I2C 
					MCU_IIC_Senddata(SHT20_WRITEADDR);  // I2C address + write
					//MCU等待接收应答信号
					if(MCU_IIC_Receiveack())
					{
						 //无应答
						 return  ;
					}
					
![image](https://github.com/210843013/Watch/blob/master/ml1.png)

					
					MCU_IIC_Senddata(0xe6);  //写寄存器
					//MCU等待接收应答信号
					if(MCU_IIC_Receiveack())
					{
						 //无应答
						 return  ;
					}
![image](https://github.com/210843013/Watch/blob/master/set.png)
					
					MCU_IIC_Senddata(0x83);  //设置分辨率  
					//MCU等待接收应答信号
					if(MCU_IIC_Receiveack())
					{
						 //无应答
						 return  ;
					}
				  IIC_Stop();         //Stop I2C         
				
				
![image](https://github.com/210843013/Watch/blob/master/ml.png)

			MCU_IIC_Senddata(SHT20_WRITEADDR&0xfe);  //I2C address + write
			//MCU等待接收应答信号
			if(MCU_IIC_Receiveack())
			{
				 //无应答
				 return  0;
			}
			
			MCU_IIC_Senddata(commod);  //发送测量温度/湿度命令
			//MCU等待接收应答信号
			if(MCU_IIC_Receiveack())
			{
				 //无应答
				 return 0 ;
			}
			do
			{
				IIC_Delay_us(6);         //延时
				IIC_Start();        //发送开始信号
				MCU_IIC_Senddata(SHT20_READADDR|0x01);
			}while(MCU_IIC_Receiveack());  //无应答则整形，还在测量中，如果有应答，则结束当前循环

![image](https://github.com/210843013/Watch/blob/master/sx.png)	
			
			MSB = MCU_IIC_Receivedata();    //读Data(MSB)
			MCU_IIC_Sendack(0);      //给应答ACK
			
			LSB = MCU_IIC_Receivedata();  //读Data(LSB)
			MCU_IIC_Sendack(0);      //给应答ACK
			
			MCU_IIC_Receivedata();    //读Checksum ，
			MCU_IIC_Sendack(1); //不给应答NACK 			
			
			
			
			
			
			
			
			

