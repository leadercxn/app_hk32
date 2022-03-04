/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *该工程旨在做复位功能测试，设置软件复位来复位MCU，通过判断RCC->CSR可知MCU复位源
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
    printf("SystemRest by power on reset ,Rcc_csr :0x%08X\r\n",RCC->CSR);
  }
  else if(RCC_GetFlagStatus(RCC_FLAG_SFTRST))//soft复位
  {
    
    printf("SystemRest by softReset ,Rcc_csr:0x%08X\r\n",RCC->CSR);
  }
  else
  {
    /* code */
    printf("SystemRest by other Reset ,Rcc_csr:0x%08X\r\n",RCC->CSR);
  }
    
    
}

// 软件复位
void SoftWare_RestConfig(void)
{
    /* System Reset */
  NVIC_SystemReset();
 
}
 

// 可以看到,系统不断的复位,且打印出复位信息,复位源来自IWDG的复位,复位时间大概1s左右
int main(void)
{
  uint32_t u32cnti = 0, u32cntj = 0;
  Uart_Config();
  Reset_Init();
  printf("\r\nMainloop--\r\nSoftware Reset Test\r\n");
  while (1)
  {
      /* Infinite loop */
      // 延时
    for(u32cnti = 0; u32cnti < 60; u32cnti++)
    {
      for(u32cntj = 0 ; u32cntj < 60000; u32cntj ++)
      {}
    }
    SoftWare_RestConfig();
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


