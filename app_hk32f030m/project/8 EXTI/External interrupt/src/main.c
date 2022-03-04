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
#include "uart.h"
#include "hk32f030m_exti.h"
//  gpio  Pc7 PA3
void Gpio_Config(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /*GPIO  ±÷” πƒ‹*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  /*---- GPIO PC7*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
   
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*---- GPIO PA3*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;   //|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  /*---- GPIO PB4*/
  //GPIO_Init(GPIOB, &GPIO_InitStructure);
  	  /*---- GPIO PC4*/
   //GPIO_Init(GPIOC, &GPIO_InitStructure);
  	  /*---- GPIO PD4*/
  //GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* ≈‰÷√EXTI */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource2);
	// EXTI_ClearITPendingBit(EXTI_Line2);

  // SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);
	// EXTI_ClearITPendingBit(EXTI_Line1);

  // SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource2);
	// EXTI_ClearITPendingBit(EXTI_Line2);

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource3);
	EXTI_ClearITPendingBit(EXTI_Line3);

  // SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource4);
	// EXTI_ClearITPendingBit(EXTI_Line4);

  // SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource5);
	// EXTI_ClearITPendingBit(EXTI_Line5);

  // SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource6);
	// EXTI_ClearITPendingBit(EXTI_Line6);

  // SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource7);
	// EXTI_ClearITPendingBit(EXTI_Line7);

  // NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);

  // NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);

  // NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);

  // NVIC_InitStructure.NVIC_IRQChannel = EXTI5_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);

  // NVIC_InitStructure.NVIC_IRQChannel = EXTI6_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);

  // NVIC_InitStructure.NVIC_IRQChannel = EXTI7_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);
}

 
int main(void)
{
  Uart_Config();
  Gpio_Config();
	printf("\r\nMainloop--\r\nEXTI Test\r\n");
  while (1)
  {
  }
}



// printf redefine
int fputc(int ch,FILE *f)
{

	USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {}		
  return ch;
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


