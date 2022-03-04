/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *   该工程旨在做复位功能测试，通过设置周期为1S的IWDG，通过判断RCC->CSR可知MCU复位源
  * 
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_rcc.h"
#include "hk32f030m_iwdg.h" 
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
		else if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST))//iwdg复位
		{
     
        printf("SystemRest by IWDGRest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
		}
    else
    {
      /* code */
      printf("SystemRest by other Rest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
    }
    
    
}

// 溢出时间 Tout = prv/40 * rlv (s)
// 计数器时钟频率(40K主频) CK_CNT= 40/ 4*2^PRV，一个计数器时钟周期 计数器就减一
void IWDG_Config(uint8_t prv ,uint16_t rlv)
{
  // 使能 预分频寄存器 PR 和重装载寄存器 RLR 可写
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  // 设置预分频器值
  IWDG_SetPrescaler( prv );
  // 设置重装载寄存器值
  IWDG_SetReload( rlv );
  // 把重装载寄存器的值放到计数器中
  IWDG_ReloadCounter();  
  // 使能 IWDG
  IWDG_Enable();
}


// 可以看到,系统不断的复位,且打印出复位信息,复位源来自IWDG的复位,复位时间大概1s左右
int main(void)
{
  Uart_Config();  
  printf("\r\nMainloop--\r\nIWDG Reset Test\r\n");
  Reset_Init();
   // IWDG 1s 超时溢出，
  IWDG_Config(IWDG_Prescaler_64 ,625);
  while (1)
  {
      /* Infinite loop */
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


