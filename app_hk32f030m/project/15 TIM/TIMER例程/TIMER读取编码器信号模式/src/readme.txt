/**
  @page TIMER读取编码器信号	Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER读取编码器信号 /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER读取编码器信号  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER读取编码器信号的功能。
初始化TIM2的两个通道TIMER2_CH1（PD4）TIMER2_CH2（PD3）通道模式配置成AF模式，配置上升沿触发。
选择编码器模式1，根据TIFP1的电平，计数器在TI2FP2的边沿上下计数。 计数到ARR，UPdate中断，翻转IO，查看是否记到相应位数
 **/
