/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * 	注释掉第 35 行和 46 行并在main()内部的for之前打断点可检测看门狗配置
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "hk32f030m_iwdg.h"
#include "tim.h"

static void IWDG_Configurature(void);
static void ledGpioInit(void);
static void ledGpioToggle(void);
static void softWareDelay(void);

int main(void)
{
	uint8_t i;
	ledGpioInit();
	IWDG_Configurature();
	softTimer_Init();
  
	/* 开机20秒内闪灯状态切换时间间隔为1秒 */
 	for(i = 0; i < 20; i++)
	{
		softTimerStart(COM_DELAY_TIM_ID,1000);
		while(softTimerIsRunning(COM_DELAY_TIM_ID) == 1)
		{
			IWDG_ReloadCounter();
		}
		ledGpioToggle();
	}

	/* 正常情况下灯状态切换时间为3秒 */
  while (1)
  {
		softTimerStart(COM_DELAY_TIM_ID,3000);
		while(softTimerIsRunning(COM_DELAY_TIM_ID) == 1)
		{
			IWDG_ReloadCounter();   
		}
		
		ledGpioToggle();  
     
  }
}

static void IWDG_Configurature(void)
{
  
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_8);
	IWDG_SetReload(1140);   // (8 * 1140)/114 = 100ms 左右
	IWDG_ReloadCounter();
	IWDG_Enable();
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
static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<10;j++)
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


