
#include "mcu.h"
#include "core_cm0.h"

void Systick_Init(void)
{
	SysTick_Config(SYSCLK_FREQ/10);
	NVIC_EnableIRQ(SysTick_IRQn);
}

void MCO_Configurature(void)
{
	GPIO_InitTypeDef m_gpio; 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	m_gpio.GPIO_Mode = GPIO_Mode_AF;
	m_gpio.GPIO_OType =  GPIO_OType_PP;
	m_gpio.GPIO_Pin = GPIO_Pin_3;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &m_gpio);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource3,GPIO_AF_5);
	RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCOPrescaler_2);
}
