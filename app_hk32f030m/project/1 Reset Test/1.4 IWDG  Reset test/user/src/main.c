/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *   �ù���ּ������λ���ܲ��ԣ�ͨ����������Ϊ1S��IWDG��ͨ���ж�RCC->CSR��֪MCU��λԴ
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
Description: ��λ��ʼ��
Input : none
return :
*************************************************************/
void Reset_Init(void)
{

    if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)//�ϵ縴λ
    {
      
        printf("SystemRest by power on rest ,Rcc_csr :0x%08X\r\n",RCC->CSR);
    }
		else if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST))//iwdg��λ
		{
     
        printf("SystemRest by IWDGRest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
		}
    else
    {
      /* code */
      printf("SystemRest by other Rest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
    }
    
    
}

// ���ʱ�� Tout = prv/40 * rlv (s)
// ������ʱ��Ƶ��(40K��Ƶ) CK_CNT= 40/ 4*2^PRV��һ��������ʱ������ �������ͼ�һ
void IWDG_Config(uint8_t prv ,uint16_t rlv)
{
  // ʹ�� Ԥ��Ƶ�Ĵ��� PR ����װ�ؼĴ��� RLR ��д
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  // ����Ԥ��Ƶ��ֵ
  IWDG_SetPrescaler( prv );
  // ������װ�ؼĴ���ֵ
  IWDG_SetReload( rlv );
  // ����װ�ؼĴ�����ֵ�ŵ���������
  IWDG_ReloadCounter();  
  // ʹ�� IWDG
  IWDG_Enable();
}


// ���Կ���,ϵͳ���ϵĸ�λ,�Ҵ�ӡ����λ��Ϣ,��λԴ����IWDG�ĸ�λ,��λʱ����1s����
int main(void)
{
  Uart_Config();  
  printf("\r\nMainloop--\r\nIWDG Reset Test\r\n");
  Reset_Init();
   // IWDG 1s ��ʱ�����
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


