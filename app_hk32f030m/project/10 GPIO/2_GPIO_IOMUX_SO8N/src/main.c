/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * @func  请根据数据手册，来选择自己需要交换的引脚
  * note   在将和系统紧密相关的pin脚复用为IO口时，需要注意，最好在main函数开始处加上100MS以上的软件延时。
  *        这是因为 这类pin脚复用成IO之前，为默认的功能，一旦复用为IO之后，默认功能变为复用之后的IO功能。
  *        如果不加延时，可能pin脚的默认功能会很快被配置为了IO功能，会导致默认功能还没执行完。
  *        比如 NRTS--PA0    SWCLK--IO  SWD--IO  都最好在前面加一段延时，在产品量产时确定不改软件之后，
  *        可将该延时去掉。
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"

static void GpioInit(void);
static void GpioToggle(void);
static void softWareDelay(void);
static void IOMUXGpioInit(void);
int main(void)
  /* Infinite loop */
{
	softWareDelay();
	GpioInit();
	IOMUXGpioInit();
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
// SO8N PIN:  参考数据手册中SO8N的封装来选择须要交换的pin
static void IOMUXGpioInit(void)
{
	GPIO_InitTypeDef m_gpio; 
	// 使能IOMUX时钟
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
//	GPIO_IOMUX_ChangePin(IOMUX_PIN8,IOMUX_PD5_SEL_PD5);// SOP8  PIN8(PD5) PD5 IO
//	GPIO_Init(GPIOD, &m_gpio);

		//	PD5 TO PD1 as GPIO 
//	m_gpio.GPIO_Pin = GPIO_Pin_1;  
//	GPIO_IOMUX_ChangePin(IOMUX_PIN8,IOMUX_PD5_SEL_PD1);// TSOP8  PIN8(PD5) PD1 IO
//	GPIO_Init(GPIOD, &m_gpio);
//	
   //	PD5 TO PD3 as GPIO 
//	m_gpio.GPIO_Pin = GPIO_Pin_3;  
//	GPIO_IOMUX_ChangePin(IOMUX_PIN8,IOMUX_PD5_SEL_PD3);// SOP8  PIN8(PD5) PD3 IO
//	GPIO_Init(GPIOD, &m_gpio);
	
//	PD5 TO PC6 as GPIO 
//	m_gpio.GPIO_Pin = GPIO_Pin_6;  
//	GPIO_IOMUX_ChangePin(IOMUX_PIN8,IOMUX_PD5_SEL_PC6);// SOP8 PIN8(PD5) PC6 IO
//	GPIO_Init(GPIOC, &m_gpio);
	
 
	//PD6 TO PA1 as GPIO 
	m_gpio.GPIO_Pin = GPIO_Pin_1; 
	GPIO_IOMUX_ChangePin(IOMUX_PIN1,IOMUX_PD6_SEL_PA1);//SOP8  PIN1(PD6) PA1 IO
	GPIO_Init(GPIOA, &m_gpio);
	
	//	PD6 TO PD4 as GPIO 
//	m_gpio.GPIO_Pin = GPIO_Pin_4; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN1,IOMUX_PD6_SEL_PD4);// SOP8  PIN1(PD6) PD4 IO
//	GPIO_Init(GPIOD, &m_gpio);
	
	//	PD6 TO PD4 as GPIO 
//	m_gpio.GPIO_Pin = GPIO_Pin_2; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN1,IOMUX_PD6_SEL_PA2);// SOP8  PIN1(PD6) PA2 IO
//	GPIO_Init(GPIOA, &m_gpio);

 //	Pb5 as GPIO 
//  m_gpio.GPIO_Pin = GPIO_Pin_5; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN5,IOMUX_PB5_SEL_PB5);//SOP8  PIN5(PB5)PB5 IO
//	GPIO_Init(GPIOB, &m_gpio);
 
//  //	Pb5 TO PD2 as GPIO 
//   m_gpio.GPIO_Pin = GPIO_Pin_2; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN5,IOMUX_PB5_SEL_PD2);//SOP8  PIN5(PB5)PD2 IO
//	GPIO_Init(GPIOD, &m_gpio);
 
  // //	Pb5 TO PA3 as GPIO 
//   m_gpio.GPIO_Pin = GPIO_Pin_3; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN5,IOMUX_PB5_SEL_PA3);//SOP8 PIN5(PB5)PA3 IO
//	GPIO_Init(GPIOA, &m_gpio);
		 
 //	Pc4 as GPIO 
  m_gpio.GPIO_Pin = GPIO_Pin_5; 
	GPIO_IOMUX_ChangePin(IOMUX_PIN6,IOMUX_PC4_SEL_PC5);//SOP8  PIN6(PC4)PC5 IO
	GPIO_Init(GPIOC, &m_gpio);
 
  //	PC4 TO PC3 as GPIO 
//  m_gpio.GPIO_Pin = GPIO_Pin_3; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN6,IOMUX_PC4_SEL_PC3);//SOP8  PIN6(PC4)PC3 IO
//	GPIO_Init(GPIOC, &m_gpio);

  // //	PC4 TO PC7 as GPIO 
//   m_gpio.GPIO_Pin = GPIO_Pin_7; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN6,IOMUX_PC4_SEL_PC7);//SOP8 PIN6(PC4)PC7 IO
//	GPIO_Init(GPIOC, &m_gpio);

	//	nrst -- pa0 
//	m_gpio.GPIO_Pin = GPIO_Pin_0; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN7,IOMUX_NRST_SEL_PA0);// SOP8 PIN7(NRST)PA0 IO  IOMUX_NRST_SEL_NRST   IOMUX_NRST_SEL_PA0
//	GPIO_Init(GPIOA, &m_gpio);
	
//	m_gpio.GPIO_Pin = GPIO_Pin_4; 
//	GPIO_IOMUX_ChangePin(IOMUX_PIN7,IOMUX_NRST_SEL_PB4);//  IOMUX_NRST_SEL_PB4
//	GPIO_Init(GPIOB, &m_gpio);
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
  GPIOA->ODR ^= GPIO_Pin_0;
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


