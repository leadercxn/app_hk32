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
uint32_t DeviceUID[2] = {0};
void Get64BIT_UID(void)
{ 
    Sys_GetDevice64BitUID(&DeviceUID[0]);
    printf("DeviceUID UID[0]:0x%08x\r\n",DeviceUID[0]);
    printf("DeviceUID UID[1]:0x%08x\r\n",DeviceUID[1]);
}

int main(void)
{
	uint32_t i , j;
  Uart_Config();
	printf("\r\nMainloop--\r\n64BIT_UID Test\r\n");
  while (1)
  {
      /* Infinite loop */
		for(i = 0; i < 10; i++)
    	for(j = 0; j < 0x0fff; j++)
      
        { }
    Get64BIT_UID();

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


