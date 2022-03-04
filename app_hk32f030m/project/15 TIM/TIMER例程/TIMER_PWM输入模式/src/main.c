/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include <stdio.h>
#include "stdarg.h"

USART_InitTypeDef USART_InitStructure;
void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM_Config(void);
void USART_Configuration(void);
void softWareDelay(void);
static void MCO_Configurature(void);

int main(void)
  /* Infinite loop */
{
	RCC_Configuration();
	GPIO_Configuration();
	USART_Configuration();
	TIM_Config();
	MCO_Configurature();
  while (1)
  {
		softWareDelay();
		IC1Value1 = TIM_GetCapture1(TIM2);
		IC1Value2 = TIM_GetCapture2(TIM2);
		  if (IC1Value1 != 0)
  {
    /* Duty cycle computation */
    Dutycycle = IC1Value2*100 / IC1Value1;

    /* Frequency computation */
    Frequency = 32000000 / IC1Value1;
  }
	  else
  {
    Dutycycle = 0;
    Frequency = 0;
  }
		printf("频率	%f（HZ）	占空比		%f％\r\n",Frequency,Dutycycle);
  }
}

/*配置时钟*/
void RCC_Configuration(void)
{
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE );
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE );
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC, ENABLE );
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOD, ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}
/*配置GPIO*/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	/*PD4 = TIM2 Channel 1*/
	//GPIOD Configuration: Channel 1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_4);	
	
		//初始化串口IO
	//PD6，RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_1);	
	//PA3，TX
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_1);
	
}
/*配置TIMER*/
void TIM_Config(void)
{
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	 /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	 /* --------------------------------------------------------------------------- 
    TIM2 配置: PWM Input mode
     外部信号连接至 TIM2 CH1 pin (PD4)
     TIM2 CCR2 计算频率
     TIM2 CCR1 计算占空比
		 TIM2的输入时钟是APB1 clock（PCLK），配置APB1分频系数为1.
     TIM2CLK = PCLK1 = HCLK = SystemCoreClock
    External Signal Frequency = SystemCoreClock / TIM2_CCR2 in Hz.
    External Signal DutyCycle = (TIM2_CCR1*100)/(TIM2_CCR2) in %.
  Note: 
  SystemCoreClock variable holds HCLK frequency and is defined in system_hk32xx.c file.
  Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
  function to update SystemCoreClock variable value. Otherwise, any configuration
  based on this variable will be incorrect.
  --------------------------------------------------------------------------- */
	
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//输入为上升沿
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;////通道模式选择
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//外部触发分频
  TIM_ICInitStructure.TIM_ICFilter = 0x00;//外部触发数字滤波

  TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
  
//	  /* Select the TIM2 Input Trigger: TI2FP1 */
  TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);

  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);
  
  /* TIM enable counter */
  TIM_Cmd(TIM2, ENABLE);

  /* Enable the CC1 Interrupt Request */
  // TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
}
/*配置串口*/
void USART_Configuration(void)
{
	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_SWAPPinCmd(USART1,ENABLE);
  USART_Cmd(USART1, ENABLE);	
}
/*从定义printf*/
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/*时钟输出*/
static void MCO_Configurature(void)
{
	GPIO_InitTypeDef m_gpio; 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	m_gpio.GPIO_Mode = GPIO_Mode_AF;
	m_gpio.GPIO_OType =  GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_3;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &m_gpio);
	*(uint32_t *)0x48000020=0x5000;
	RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCOPrescaler_1);
}
/*软件延时*/
void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<2000;i++)
	{
		for(j=0;j<1000;j++)
		{
			__nop();
		}
	}
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


