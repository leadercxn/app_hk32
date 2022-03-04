/**
  @page ADC Diff Description
  
  ******************** (C) COPYRIGHT 2020 HKMicroelectronics *******************
  * @文件	ADC/ADC Diff/readme.txt 
  * @作者	航顺AE
  * @版本	V1.0
  * @日期	6-3-2020
  * @brief	Description of the ADC Diff example.
  ******************************************************************************
  *
  *
  ******************************************************************************
   @endverbatim

@par Example Description 
本例程介绍的是ADC差分输入的功能。
初始化ADC_CH2、ADC_CH3（PC4、PD3为模拟输入IO）,ADC CH2与CH3是一对差分输入通道。
配置ADC工作在连续转换模式，开启差分转换功能，向CH2、CH3输入一对差分信号，并通过串口输出转换结果。 
 */
