/**
  @page TIMER基本模式 Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER基本模式 /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER基本模式  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER基本模式的功能。
用定时器1配置CNT时钟为1MHZ，配置ARR=10000则计数周期为10ms，配置4个通道分别配置CCR1=5000、CCR2=2500、CCR3=1250、CCR4=625,配置4个通道捕获比较中断，TIMER工作过程中在计时到了相应的CCR，就会发生相应的中断，在中断服务程序中去翻转不同IO每两个周期就会进中断一次则会出现相位不同频率都为50HZ的IO翻转信号
例程的翻转IO配置：
CCR1IE：		PA1
CCR2IE：		PA2
CCR3IE：		PA3
CCR4IE：		PD4
初始化 
 */
