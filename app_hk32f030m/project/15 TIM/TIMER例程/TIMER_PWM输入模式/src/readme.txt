/**
  @page TIMER_PWM输入模式 Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER_PWM输入模式 /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER_PWM输入模式  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER_PWM输入模式的功能。
初始化TIMER_CH1（PD4为PWM输入IO）通道模式配置成输入，IC1和IC2映射在TI1上，配置CC1P为0（上升延有效）CC2P为1（下降沿有效），TS[2:0]配置TI1FP1，从模式选择复位模式SMS配置100。
这样频率Frequency = SystemCoreClock / TIM2_CCR1 单位Hz，占空比DutyCycle = (TIM2_CCR2*100)/(TIM2_CCR1)  单位 %。
外部PWM信号输入PD4，通过串口打印信号的频率，占空比等信息。 
 */
