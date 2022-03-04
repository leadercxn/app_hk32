/*
********************************************************************************
** @file    : main.c
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : main program
********************************************************************************
*/

/*
  1. 本例程用户APP应用程序起始地址：0x08001000
	2. 注意：030M/0301M中断向量可以映射到SRAM或者FLASH中去，推荐映射到FLASH中去，因为
     只需要重新设置中断向量表偏移地址就可以了，比映射到SRAM中要简单方便。
	   中断向量表偏移地址设置在system_hk32f030m.c文件中定义VECT_TAB_OFFSET。      
*/

/*==============================================================================
** Includes
==============================================================================*/
#include "main.h"

/*==============================================================================
** Private typedef
==============================================================================*/

/*==============================================================================
** Private macro
==============================================================================*/

/*==============================================================================
** Private define
==============================================================================*/

/*==============================================================================
** Private variables
==============================================================================*/
uint32_t TimingDelay;

/*==============================================================================
** Private function prototypes
==============================================================================*/


/******************************************************************************/
/*                          Function Implementation                           */
/******************************************************************************/
/*******************************************************************************
** @function : main
** @brief    :   
** @param    : None
** @retval   : None
*******************************************************************************/
int main(void)
{
	/* Setup SysTick Timer for 1 msec interrupts.
    ------------------------------------------
   1. The SysTick_Config() function is a CMSIS function which configure:
      - The SysTick Reload register with value passed as function parameter.
      - Configure the SysTick IRQ priority to the lowest value (0x0F).
      - Reset the SysTick Counter register.
      - Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
      - Enable the SysTick Interrupt.
      - Start the SysTick Counter.
   
   2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
      SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
      SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
      inside the misc.c file.
   
   3. You can change the SysTick IRQ priority by calling the
      NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function 
      call. The NVIC_SetPriority() is defined inside the core_cm0.h file.
   
   4. To adjust the SysTick time base, use the following formula:                   
      Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
      - Reload Value is the parameter to be passed for SysTick_Config() function
      - Reload Value should not exceed 0xFFFFFF
  */
  SysTick_Config(SystemCoreClock / 1000);
	
	/* LED initialization */
	BSP_GPIO_Init(LED1);
	BSP_GPIO_Init(LED2);
	BSP_GPIO_Init(LED3);
	BSP_GPIO_Init(LED4);
		
	while(1)
	{
		BSP_GPIO_Toggle(LED1);
		Delay_ms(500);
		BSP_GPIO_Toggle(LED2);
		Delay_ms(500);
		BSP_GPIO_Toggle(LED3);
		Delay_ms(500);
		BSP_GPIO_Toggle(LED4);
		Delay_ms(500);
	}
}


/*******************************************************************************
** @function : Delay_ms
** @brief    : Inserts a delay time 
** @param    : msCnt - specifies the delay time length, in milliseconds
** @retval   : None
*******************************************************************************/
void Delay_ms(uint32_t msCnt)
{
  TimingDelay = msCnt;

  while(TimingDelay != 0);
}


#ifdef  USE_FULL_ASSERT
/*******************************************************************************
** @function : assert_failed
** @brief    : Reports the name of the source file and the source line number
**             where the assert_param error has occurred
** @param    : file - pointer to the source file name
**             line - assert_param error line source number
** @retval   : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


/*********************************** EOF **************************************/
