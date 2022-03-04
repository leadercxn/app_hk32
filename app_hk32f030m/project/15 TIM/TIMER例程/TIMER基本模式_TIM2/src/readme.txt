/**
  @page TIMER基本模式_TIM6 Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER基本模式_TIM6 /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER基本模式_TIM6  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER基本模式_TIM6的功能。
用定时器6配置CNT时钟为1MHZ，配置ARR=10000则计数周期为10ms,配置Update中断，TIMER计数到ARR就会发生中断，在中断服务程序中去翻转IO每两个周期就会进中断一次则会出现频率为50HZ的IO翻转信号
例程的翻转IO配置：
PA1

初始化 
 */
