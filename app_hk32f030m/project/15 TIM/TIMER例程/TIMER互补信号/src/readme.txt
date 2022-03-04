/**
  @page TIMER互补信号 Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER互补信号 /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER互补信号  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER互补信号的功能。
高级定时器有3对互补Channel，可以同时输出3对互补的PWM波形
配置PWM输出10KHZ带死区的互补信号，他们每对占空比一致，极性相反
例程的IO配置：
TIM1_CH1		PC6；
TIM1_CH2		PC7；
TIM1_CH3		PD3；
TIM1_CH1N	PA1；
TIM1_CH2N	PA2；
TIM1_CH3N	PA3；
TIM1_Break	PB5；

初始化 
 */
