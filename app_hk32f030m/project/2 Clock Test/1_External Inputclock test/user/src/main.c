/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *该工程为外部输入时钟测试，在system_hk32f0301m.c中，修改宏定义，配置HSI48M作为系统时钟。
   配置PC4为MCO sysclk 128分频输出，通过示波器测试频率可知道该频率是否准确。另外PC7为LED
   灯，PC3作为和MCO输出pin相邻，也配置为MCO的另一路输出，以此来看是这两路MCO输出是否会有干扰。
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "uart.h"


// MCO 时钟输出配置 gpio  Pc4
void Gpio_MCO_Config(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /*开启 GPIO 口的时钟*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
  /*---- GPIO */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  /* 配置为浮空输出 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource4,GPIO_AF_5);

}
//  gpio  Pc7 PC3
void Gpio_Config(void)
 {
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /*开启 GPIO  口的时钟*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
  /*---- GPIO PC7*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  /* 配置为浮空输出 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_5);

 
   /*---- GPIO PC3 作为MCO另一路输出*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  /* 配置为浮空输出 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource3,GPIO_AF_5);

}


int main(void)
{
	uint32_t i , j;
  Uart_Config();
	printf("\r\nMainloop--\r\nExternal Reset NRST Pin Test\r\n");
	Gpio_MCO_Config();
  Gpio_Config();
  RCC_MCOConfig(RCC_MCOSource_SYSCLK,RCC_MCOPrescaler_128);

  while (1)
  {
      /* Infinite loop */
		for(i = 0; i < 10; i++)
    	for(j = 0; j < 0x0fff; j++)
        { }
    GPIO_Toggle(GPIOC,GPIO_Pin_7);
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


