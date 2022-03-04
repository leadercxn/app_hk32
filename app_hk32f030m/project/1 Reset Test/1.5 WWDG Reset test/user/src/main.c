/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention 
  *�ù���ּ������λ���ܲ��ԣ�ͨ������WWDG����λMCU��ͨ���ж�RCC->CSR��֪MCU��λԴ
  *��ȷ�����ù���Ϊ:0x7F>=����ֵ>=����ֵ(ι��ֵ)>=0x40,�˴�Ϊ��Ҫ��WWDG��λ�����ԣ�����ֵ
  *������Ϊ���ڴ���ֵ��
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_rcc.h"
#include "hk32f030m_wwdg.h" 
#include "hk32f030m_misc.h"
#include "uart.h"

/*************************************************************
Function : Reset_Init
Description: ��λ��ʼ��
Input : none
return :
*************************************************************/
void Reset_Init(void)
{

    if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET )//�ϵ縴λ
    {
        printf("SystemRest by power on rest ,Rcc_csr :0x%08X\r\n",RCC->CSR);
    }
		else if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST))//wwdg��λ
		{
        printf("SystemRest by WWDGRest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
		}
    else
    {
      /* code */
      printf("SystemRest by other Rest ,Rcc_csr:0x%08X\r\n",RCC->CSR);
    }
    
    RCC_ClearFlag();
}

 #define WWDG_CNT  0x7F
// WWDG �ж����ȼ���ʼ��
static void WWDG_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_SetPriority(WWDG_IRQn,0);
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// ��������һ������ʱ�� T= 1/CNT_CK = Tpclk1 * 4096 * (2^WDGTB)
// ��������ʱ�� CNT_CK=PCLK1/4096/(2^WDGTB)һ��������ʱ������ �������ͼ�һ
 /* WWDG ���ú���
 * tr ���ݼ���ʱ����ֵ�� ȡֵ��ΧΪ��0x7f~0x40
 * wr ������ֵ��ȡֵ��ΧΪ��0x7f~0x40
 * prv��Ԥ��Ƶ��ֵ��ȡֵ������
 * @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1     113us
 * @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2     227us
 * @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4     455us
 * @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8     910us
 */
void WWDG_Config(uint8_t tr ,uint16_t wr, uint32_t prv)
{
// ���� WWDG ʱ��
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
 
 // ���õݼ���������ֵ
 WWDG_SetCounter( tr );
 
 // ����Ԥ��Ƶ����ֵ
 WWDG_SetPrescaler( prv );
 
 // �����ϴ���ֵ
 WWDG_SetWindowValue( wr );
 
 // ���ü�������ֵ��ʹ�� WWDG
 WWDG_Enable(WWDG_CNT);
 
 // �����ǰ�����жϱ�־λ
 WWDG_ClearFlag();

 // ���� WWDG �ж����ȼ�
 WWDG_NVIC_Config();

 // �� WWDG �ж�
 WWDG_EnableIT();
}

void WWDG_Feed(void)
 {
	// // ι����ˢ�µݼ���������ֵ�����ó���� WDG_CNT=0x7F
	WWDG_SetCounter( WWDG_CNT );
 }

// ���Կ���,ϵͳ���ϵĸ�λ,�Ҵ�ӡ����λ��Ϣ,��λԴ����IWDG�ĸ�λ,��λʱ����1s����
int main(void)
{
  uint8_t wwdg_tr, wwdg_wr;
  Uart_Config();
	  // 
  printf("\r\nMainloop--\r\nWWDG Reset Test\r\n");
  Reset_Init(); 
 
    // ��ʼ�� WWDG
  WWDG_Config(0x7F, 0x5F, WWDG_Prescaler_8);
 
  // ����ֵ�����ڳ�ʼ����ʱ�����ó� 0x5F�����ֵ����ı�
  wwdg_wr = WWDG->CFR & 0x7F;

  /* Infinite loop */
  while (1)
  {
    //-----------------------------------------------------
    // �ⲿ��Ӧ��д��Ҫ�� WWDG ��صĳ�����γ������е�ʱ��
    // �����˴���ֵӦ�����óɶ��
    //-----------------------------------------------------

    // ��ʱ��ֵ����ʼ������� 0x7F�������� WWDG ʱ�����ֵ�᲻�ϼ�С
    // ����������ֵ���ڴ���ֵʱι���Ļ����Ḵλ�������������ٵ� 0x40
    // ��û��ι���Ļ��ͷǳ��ǳ�Σ���ˣ��������ټ�һ�ε��� 0x3F ʱ�͸�λ
    // ����Ҫ����������ֵ�ڴ���ֵ�� 0x40 ֮���ʱ��ι�������� 0x40 �ǹ̶��ġ�
    wwdg_tr = WWDG->CR & 0x7F;

    if ( wwdg_tr < wwdg_wr )
     {
      // ι�����������ü�������ֵΪ��� 0x7F
      ;//WWDG_Feed();
    }
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


