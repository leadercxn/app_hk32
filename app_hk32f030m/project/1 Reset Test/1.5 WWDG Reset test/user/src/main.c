/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention 
  *该工程旨在做复位功能测试，通过设置WWDG来复位MCU，通过判断RCC->CSR可知MCU复位源
  *正确的配置规则为:0x7F>=窗口值>=计数值(喂狗值)>=0x40,此处为了要做WWDG复位，所以，计数值
  *会配置为大于窗口值。
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
Description: 复位初始化
Input : none
return :
*************************************************************/
void Reset_Init(void)
{

    if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET )//上电复位
    {
        printf("SystemRest by power on rest ,Rcc_csr :0x%08X\r\n",RCC->CSR);
    }
		else if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST))//wwdg复位
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
// WWDG 中断优先级初始化
static void WWDG_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_SetPriority(WWDG_IRQn,0);
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

// 计数器减一个数的时间 T= 1/CNT_CK = Tpclk1 * 4096 * (2^WDGTB)
// 计数器的时钟 CNT_CK=PCLK1/4096/(2^WDGTB)一个计数器时钟周期 计数器就减一
 /* WWDG 配置函数
 * tr ：递减计时器的值， 取值范围为：0x7f~0x40
 * wr ：窗口值，取值范围为：0x7f~0x40
 * prv：预分频器值，取值可以是
 * @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1     113us
 * @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2     227us
 * @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4     455us
 * @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8     910us
 */
void WWDG_Config(uint8_t tr ,uint16_t wr, uint32_t prv)
{
// 开启 WWDG 时钟
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
 
 // 设置递减计数器的值
 WWDG_SetCounter( tr );
 
 // 设置预分频器的值
 WWDG_SetPrescaler( prv );
 
 // 设置上窗口值
 WWDG_SetWindowValue( wr );
 
 // 设置计数器的值，使能 WWDG
 WWDG_Enable(WWDG_CNT);
 
 // 清除提前唤醒中断标志位
 WWDG_ClearFlag();

 // 配置 WWDG 中断优先级
 WWDG_NVIC_Config();

 // 开 WWDG 中断
 WWDG_EnableIT();
}

void WWDG_Feed(void)
 {
	// // 喂狗，刷新递减计数器的值，设置成最大 WDG_CNT=0x7F
	WWDG_SetCounter( WWDG_CNT );
 }

// 可以看到,系统不断的复位,且打印出复位信息,复位源来自IWDG的复位,复位时间大概1s左右
int main(void)
{
  uint8_t wwdg_tr, wwdg_wr;
  Uart_Config();
	  // 
  printf("\r\nMainloop--\r\nWWDG Reset Test\r\n");
  Reset_Init(); 
 
    // 初始化 WWDG
  WWDG_Config(0x7F, 0x5F, WWDG_Prescaler_8);
 
  // 窗口值我们在初始化的时候设置成 0x5F，这个值不会改变
  wwdg_wr = WWDG->CFR & 0x7F;

  /* Infinite loop */
  while (1)
  {
    //-----------------------------------------------------
    // 这部分应该写需要被 WWDG 监控的程序，这段程序运行的时间
    // 决定了窗口值应该设置成多大。
    //-----------------------------------------------------

    // 计时器值，初始化成最大 0x7F，当开启 WWDG 时候，这个值会不断减小
    // 当计数器的值大于窗口值时喂狗的话，会复位，当计数器减少到 0x40
    // 还没有喂狗的话就非常非常危险了，计数器再减一次到了 0x3F 时就复位
    // 所以要当计数器的值在窗口值和 0x40 之间的时候喂狗，其中 0x40 是固定的。
    wwdg_tr = WWDG->CR & 0x7F;

    if ( wwdg_tr < wwdg_wr )
     {
      // 喂狗，重新设置计数器的值为最大 0x7F
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


