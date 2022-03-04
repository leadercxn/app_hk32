/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *该工程旨在做复位功能测试，通过反复上下电，来复位MCU，通过判断RCC->CSR可知MCU复位源
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_rcc.h"
#include "uart.h"

/*************************************************************
Function : Reset_Init
Description: 复位初始化
Input : none
return :
*************************************************************/
void Reset_Init(void)
{

    if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)//上电复位
    {
      
        printf("SystemRest by power on rest ,Rcc_csr :0x%08X\r\n",RCC->CSR);
    }
		else if(RCC_GetFlagStatus(RCC_FLAG_PINRST))//pin脚复位
		{
     
        printf("SystemRest by PinRest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
		}
    else
    {
      /* code */
      printf("SystemRest by other Rest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
    }
    
    
}


int main(void)
{

  Uart_Config();
	printf("\r\nMainloop--\r\nPoweron Reset Test\r\n");
  Reset_Init();
 
  while (1)
  {
      /* Infinite loop */
  }
}



// printf redefine
int fputc(int ch,FILE *f)
{

	 USART_SendData(USART1, (uint8_t) ch);
 // while((USART1->SR&USART_FLAG_TC)==RESET);
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


