/**
  @page TIMER同步模式 Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER同步模式 /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER同步模式  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER同步模式 的功能。
TIMER时钟工作在48MHZ，TIM1使能主从模式，主模式选择UpdateTRGO输出，ARR配置为255，TIM1配置CCR1为64，PWM输出，TIM2；TIM2配置ARR为3，TIM2配置CCR2为1，选择门控模式，当触发输入为高时，时钟时钟开启，触发器输入为低，计数器停止（但不复位）；这样每次TIM1的UpdateTRGO输出触发TIM2 CNT计数一次产生TIM2的PWM输出

初始化 
 */
