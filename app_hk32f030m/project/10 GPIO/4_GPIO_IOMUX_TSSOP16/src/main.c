/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * @func   请根据数据手册，来选择自己需要交换的引脚
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"

static void GpioInit(void);
static void GpioToggle(void);
static void softWareDelay(void);
static void IOMUXpioInit(void);
int main(void)
  /* Infinite loop */
{
   softWareDelay();
	GpioInit();
	IOMUXpioInit();
  while (1)
  {
		GpioToggle();
		softWareDelay();
  }
}
static void GpioInit(void)
{
	GPIO_InitTypeDef m_gpio;
	

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	
	m_gpio.GPIO_Mode = GPIO_Mode_OUT;
	m_gpio.GPIO_OType = GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_7;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOC, &m_gpio);
	
}

static void IOMUXpioInit(void)
{
	GPIO_InitTypeDef m_gpio; 
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_IOMUX,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE); 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
//	PD5 as GPIO
	m_gpio.GPIO_Mode = GPIO_Mode_OUT;
	m_gpio.GPIO_OType = GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_5;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_Level_2;
//	GPIO_IOMUX_ChangePin(IOMUX_PIN15,IOMUX_PD5_SEL_PD5);// TSSOP16 PIN15(PD5) PD5 IO
//	GPIO_Init(GPIOD, &m_gpio);
	
//		//	PD5 TO PD1 as GPIO 
	m_gpio.GPIO_Pin = GPIO_Pin_1;  
	GPIO_IOMUX_ChangePin(IOMUX_PIN15,IOMUX_PD5_SEL_PD1);// TSSOP16 PIN15(PD5) PD1 IO
	GPIO_Init(GPIOD, &m_gpio);
	
			//	PD6 TO PD4 as GPIO 
//	m_gpio.GPIO_Pin = GPIO_Pin_4; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN1,IOMUX_PD6_SEL_PD4);// TSSOP16 PIN1(PD6) PD4 IO
//	GPIO_Init(GPIOD, &m_gpio);
//	
			//	PC4 TO PC7 as GPIO
	m_gpio.GPIO_Mode = GPIO_Mode_OUT;
	m_gpio.GPIO_OType = GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_7;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_IOMUX_ChangePin(IOMUX_PIN12,IOMUX_PC4_SEL_PC7);// TSSOP16 PIN12(PC4) PC7 IO
	GPIO_Init(GPIOC, &m_gpio);
//	
 //	Pb5 as GPIO 
//  m_gpio.GPIO_Pin = GPIO_Pin_5; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN11,IOMUX_PB5_SEL_PB5);//TSSOP16 PIN11(PB5)PB5 IO
//	GPIO_Init(GPIOB, &m_gpio);
 
//	Pb5 TO PD2 as GPIO 
 //  m_gpio.GPIO_Pin = GPIO_Pin_2; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN9,IOMUX_PB5_SEL_PD2);//TSSOP16 PIN9(PB5)PD2 IO
//	GPIO_Init(GPIOD, &m_gpio);
 
 
	//	nrst -- pa0  
//	m_gpio.GPIO_Pin = GPIO_Pin_0; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN2,IOMUX_NRST_SEL_NRST);// TSSOP16 PIN2(NRST)PA0 IO  IOMUX_NRST_SEL_NRST   IOMUX_NRST_SEL_PA0
//	GPIO_Init(GPIOA, &m_gpio);
}

static void GpioToggle(void)
{
	GPIOC->ODR ^= GPIO_Pin_4;
	GPIOC->ODR ^= GPIO_Pin_5;
	GPIOC->ODR ^= GPIO_Pin_3;
	GPIOC->ODR ^= GPIO_Pin_6;
	GPIOC->ODR ^= GPIO_Pin_7;
	GPIOD->ODR ^= GPIO_Pin_1;
	GPIOD->ODR ^= GPIO_Pin_2;
	GPIOD->ODR ^= GPIO_Pin_3;
	GPIOD->ODR ^= GPIO_Pin_4;
	GPIOD->ODR ^= GPIO_Pin_5;
	GPIOD->ODR ^= GPIO_Pin_6;	
	GPIOD->ODR ^= GPIO_Pin_7;
	GPIOB->ODR ^= GPIO_Pin_5; 
	GPIOB->ODR ^= GPIO_Pin_4; 
	GPIOA->ODR ^= GPIO_Pin_1;
	GPIOA->ODR ^= GPIO_Pin_2;
	GPIOA->ODR ^= GPIO_Pin_3; 
}
static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<500;i++)
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


