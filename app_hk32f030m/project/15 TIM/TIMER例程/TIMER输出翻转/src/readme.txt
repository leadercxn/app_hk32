/**
  @page TIMER输出翻转 Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	TIMER/TIMER输出翻转 /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the TIMER输出翻转  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是TIMER输出翻转的功能。
定时器2配置翻转PWM波形，ARR配置480，CNT频率为48MHZ，则向上计数周期为1/(100KHZ),配置CCR1=ARR/2；则每次CNT到CCR1，CH1产生翻转，每2个计数周期翻转一次，CH1产生50KHZ信号。

初始化 
 */
