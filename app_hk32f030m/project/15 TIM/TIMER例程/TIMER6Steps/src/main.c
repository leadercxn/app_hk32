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

void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM_Config(void);
void SysTickConfig(void);

int main(void)
  /* Infinite loop */
{
	RCC->APB2ENR |= 0x400000;
	*(uint32_t *)0x40015808 |= 0x01;
//	*(uint32_t *)0x4001580C |= 0x0800;
	SysTickConfig();
	RCC_Configuration();
	GPIO_Configuration();
	TIM_Config();
	
  while (1)
  {
		
  }
}
/*????ʱ??*/
void RCC_Configuration(void)
{
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE );
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE );
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOC, ENABLE );
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOD, ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
}
/*????GPIO*/
void GPIO_Configuration(void)
{
	//GPIOA Configuration: Channel 1N, 2N, 3N
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_3);	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_3);	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_3);	
	//GPIOC Configuration: Channel 1, 2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_3);	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_3);	
  /*PD3 = TIMER Channel 3*/
	//GPIOD Configuration: Channel 3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource3,GPIO_AF_3);	
	  /*PD4 = TIMER Channel 4*/
	//GPIOD Configuration: Channel 4
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_3);
	
//	//GPIOB Configuration: Break
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_3);	
	
//	/*PC3 = TIMER Channel 3*/
//	GPIO_IOMUX_PinAFConfig(GPIOC,GPIO_PinSource3,IOMUX_PC3_TIM1CH3);
//	//GPIOC Configuration: Channel 3 PC3
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource3,GPIO_AF_3);	

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
}
  /*----------------------------------------------------------------------------
  The HK32S0xx TIM1 peripheral offers the possibility to program in advance the 
  configuration for the next TIM1 outputs behaviour (step) and change the configuration
  of all the channels at the same time. This operation is possible when the COM 
  (commutation) event is used.
  The COM event can be generated by software by setting the COM bit in the TIM1_EGR
  register or by hardware (on TRC rising edge).
  In this example, a software COM event is generated each 100 ms: using the SysTick 
  interrupt.
  The TIM1 is configured in Timing Mode, each time a COM event occurs, a new TIM1 
  configuration will be set in advance.

  The following Table  describes the TIM1 Channels states:
              -----------------------------------------------
             | Step1 | Step2 | Step3 | Step4 | Step5 | Step6 |
   ----------------------------------------------------------
  |Channel1  |   1   |   0   |   0   |   0   |   0   |   1   |
   ----------------------------------------------------------
  |Channel1N |   0   |   0   |   1   |   1   |   0   |   0   |
   ----------------------------------------------------------
  |Channel2  |   0   |   0   |   0   |   1   |   1   |   0   |
   ----------------------------------------------------------
  |Channel2N |   1   |   1   |   0   |   0   |   0   |   0   |
   ----------------------------------------------------------
  |Channel3  |   0   |   1   |   1   |   0   |   0   |   0   |
   ----------------------------------------------------------
  |Channel3N |   0   |   0   |   0   |   0   |   1   |   1   |
   ----------------------------------------------------------
  ----------------------------------------------------------------------------*/
	/*????TIMER*/
void TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;//??CNTCLK=fck_PSC/(PSC[15:0]+1)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 3200;//????PWMƵ??Ϊ10KHZ
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1600;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 800;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = 400;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

//  TIM_OCInitStructure.TIM_Pulse = Channel4Pulse;
//  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
  /* Automatic Output enable, Break, dead time and lock configuration*/
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure.TIM_DeadTime = 1;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	TIM_CCPreloadControl(TIM1, ENABLE);
	TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);
  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	  /* Enable the TIM1 Trigger and commutation interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TRG_COM_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  

}
//SysTick????
void SysTickConfig(void)
{
  /* Setup SysTick Timer for 10 msec interrupts  */
  if (SysTick_Config((SystemCoreClock) / 1000))
  { 
    /* Capture error */ 
    while (1);
  }

  NVIC_SetPriority(SysTick_IRQn, 0x0);
}
//??תIO
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
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


