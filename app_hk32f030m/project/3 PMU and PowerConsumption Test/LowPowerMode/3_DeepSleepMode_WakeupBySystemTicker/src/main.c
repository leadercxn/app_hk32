/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "usart.h"
#include "string.h"
#include "mcu.h"

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void led_off(void);
static void led_on(void);
static void softWareDelay(void);

uint8_t sysTickIntFlag = 0;
char dataGet;

int main(void)
{
	ledGpioInit();
	USART_Configurature();
	Systick_Init();
	printf("this is a test!\r\n"); 
	MCO_Configurature();
	PWR_EnterSleepMode(PWR_Entry_WFI);
  while (1)
  {		
		if(dataGet == 'E')
		{
			// 进入低功耗模式
			dataGet = 0;
			led_off();
			Sysclk_SwitchToLSI();
			SysTick->LOAD  = (uint32_t)((128000ul/10) - 1UL);
			SysTick->VAL   = 0UL;
			PWR_EnterSleepMode(PWR_Entry_WFI);
		}
		else
		{
			ledGpioToggle();
		}
  }
}

static void ledGpioInit(void)
{
	GPIO_InitTypeDef m_gpio;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
	m_gpio.GPIO_Mode = GPIO_Mode_OUT;
	m_gpio.GPIO_OType = GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_7;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &m_gpio);
}

static void ledGpioToggle(void)
{
	GPIOC->ODR ^= GPIO_Pin_7;
}
static void led_off(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_7);
}
static void led_on(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
}
static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<1000;j++)
		{
			__nop();
		}
	}
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


