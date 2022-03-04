/**
  @page ADC  Watchdog Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	ADC/ADC Watchdog /readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the ADC Watchdog  example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是ADC独立看门狗的功能。
初始化ADC_CH2（PC4为模拟输入IO）配置CH2为看门狗通道，配置看门狗上下阀值。
配置ADC工作在连续转换模式，ADC转换，并通过串口输出转换结果，每次ADC电压低于或者高于阀值就会进入中断。 
 */
