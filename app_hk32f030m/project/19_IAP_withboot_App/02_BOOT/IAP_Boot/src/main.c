/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"


#define USER_APP_ADDRESS       (uint32_t)(0x08001280)

typedef  void (*pFunction)(void);
static void JumpToApplication(void);

static void ledGpioInit(void);
static void ledGpioToggle(void);
static void softWareDelay(void);
 
int main(void)
  /* Infinite loop */
{    // øÏ…¡
  ledGpioInit();
  GPIO_SetBits(GPIOC,GPIO_Pin_7);
  
  for( uint8_t i = 0 ; i < 20; i ++)
  {
    ledGpioToggle();
    softWareDelay(); 
  }
  
  JumpToApplication();
  while (1)
  {
  }
} 


static void JumpToApplication(void)
{
	pFunction Jump_To_Application;
	uint32_t UserAppAddr;
	
	/* Calculate the address of user application */
	UserAppAddr = *(__IO uint32_t*) (USER_APP_ADDRESS + 4);
	Jump_To_Application = (pFunction) UserAppAddr;
	
	/* Initialize user application's Stack Pointer, Disable any interrupts during SP setting */
	__set_PRIMASK(1); // Disable interrupts
	__set_MSP(*(__IO uint32_t*) USER_APP_ADDRESS);
	//__set_PRIMASK(0); // Enable interrupts
	
	/* Jump to application */
	Jump_To_Application();
}

static void ledGpioToggle(void)
{
	GPIOC->ODR ^= GPIO_Pin_7;
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

static void softWareDelay(void)
{
	uint16_t i;
	uint16_t j;
	
	for(i=0;i<500;i++)
	{
		for(j=0;j<100;j++)
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
void assert_failed(char* file , uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */	
       /* Infinite loop */
	
	while (1)
  {		
  }
}
#endif /* USE_FULL_ASSERT */


