/**
  @page TIMER输入捕获 Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER输入捕获 /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER输入捕获  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER输入捕获的功能。
初始化TIMER_CH1（PC6为IO）通道模式配置成AF模式，配置上升沿触发。
CCR1每次上升沿记录CNT值，每记录两个上升沿的值，相减得到CNT长度，用系统时钟除以CNT长度差就得到频率。 
 */
