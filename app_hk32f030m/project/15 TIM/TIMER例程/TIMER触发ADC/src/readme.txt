/**
  @page TIMER触发ADC Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER触发ADC /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER触发ADC  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER触发ADC的功能。
利用TIM1CC4事件触发ADC采样，并通过串口发送采样值。
软件配置：
TIM1 CNT时钟配置1000HZ，ARR=1000，则每个周期为1秒，CC4=500，每个周期在CNT计数到500的时刻产生事件触发ADC采样。
初始化 
 */
