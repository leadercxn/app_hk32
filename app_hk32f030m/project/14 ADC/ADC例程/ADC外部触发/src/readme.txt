/**
  @page ADC IO_TRGO Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	ADC/IO_TRGO/readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the ADC IO_TRGO example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是使用芯片外部PIN脚触发ADC转换。
初始化ADC_CH2（PC4为模拟输入IO）,ADC关闭连续转换，工作在IO事件触发模式，配置为上升沿触发。
配置PD3为外部触发IO，配置为AF（复用）模式，给PD3一个高电平，ADC触发一次，并通过串口输出转换结果。 
 */
