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
#include "hk32f030m_exti.h"

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void led_off(void);
static void led_on(void);
static void softWareDelay(void);
static void ExtiConfigurature(void);

uint8_t sysTickIntFlag = 0;
char dataGet;

int main(void)
{
	ledGpioInit();
	USART_Configurature();
	printf("this is a test!\r\n"); 
	MCO_Configurature();
	ExtiConfigurature();
	led_on();
  while (1)
  {		
		if(dataGet == 'E')
		{
			dataGet = 0;
			led_off();
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
static void ExtiConfigurature(void)
{
	GPIO_InitTypeDef m_gpio;
	EXTI_InitTypeDef m_exti;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	m_gpio.GPIO_Mode = GPIO_Mode_IN;
	m_gpio.GPIO_Pin = GPIO_Pin_4;
	m_gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	m_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &m_gpio);
	
  m_exti.EXTI_Line = EXTI_Line4;              
	m_exti.EXTI_Mode = EXTI_Mode_Interrupt;      
	m_exti.EXTI_Trigger = EXTI_Trigger_Rising;
	m_exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&m_exti);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource4);
	EXTI_ClearITPendingBit(EXTI_Line4);
	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

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


