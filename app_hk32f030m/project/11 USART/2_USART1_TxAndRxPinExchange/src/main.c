/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @author         : veiko.c
  *	@date           : 20200203
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "usart.h"
#include "string.h"

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void softWareDelay(void);




void Config_Rst_As_Gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_IOMUX,ENABLE);    //打开IOMux时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);     //使能PORTA时钟
	//	nrst -- pa0 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_IOMUX_ChangePin(IOMUX_PIN7,IOMUX_NRST_SEL_PA0);// SOP8 PIN7(NRST)PA0 IO  IOMUX_NRST_SEL_NRST   IOMUX_NRST_SEL_PA0
	GPIO_Init(GPIOA, &GPIO_InitStructure);
   
  
}
int main(void)
  /* Infinite loop */
{
 	softWareDelay();
	//ledGpioInit();
  Config_Rst_As_Gpio();
	USART_Configurature();

	USART_SendStringLen((uint8_t *)"this is a Test!\r\n",strlen("this is a Test!\r\n"));
  while (1)
  {
		softWareDelay();
    USART_SendStringLen((uint8_t *)"LOOP\r\n",strlen("LOOP\r\n"));
		ledGpioToggle();
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
   GPIOA->ODR ^= GPIO_Pin_0;
  GPIOA->ODR ^= GPIO_Pin_3;
}
static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000;j++)
		{
			__NOP();
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


