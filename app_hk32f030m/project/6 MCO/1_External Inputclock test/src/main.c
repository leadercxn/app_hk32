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

#if 0
// MCO  gpio  PD6  SSOP8
void Gpio_MCO_Config(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  /*---- GPIO */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_5);

}
 #else

// MCO  gpio  PC4  SSOP20
void Gpio_MCO_Config(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  /*---- GPIO */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource4,GPIO_AF_5);
   
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);

}
#endif
static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<1000;j++)
		{
			__NOP();
		}
	}
}
int main(void)
{
	uint32_t i , j; 
 softWareDelay();
	//printf("\r\nMainloop--\r\nMCO Test\r\n");
	Gpio_MCO_Config(); 
  RCC_MCOConfig(RCC_MCOSource_SYSCLK,RCC_MCOPrescaler_1);

  while (1)
  {
      /* Infinite loop */
    
    
		for(i = 0; i < 10; i++)
    	for(j = 0; j < 0x0fff; j++)
        { }
    //GPIO_Toggle(GPIOC,GPIO_Pin_7);
        //GPIO_ResetBits(GPIOD,GPIO_Pin_4);   
      // GPIO_SetBits(GPIOA,GPIO_Pin_1);
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


