
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
	RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCOPrescaler_1);
}

void Sysclk_SwitchToLSI(void)
{
	RCC_LSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
	
	/* Flash wait state */
	FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
	FLASH->ACR |= (uint32_t)FLASH_Latency_0;	
	
	/* Select LSI as system clock source */
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_LSI; 
	/* Wait till LSI is used as system clock source */
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_LSI);
	
	/* HCLK = SYSCLK */
	RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;

	/* PCLK = HCLK */
	RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE_DIV1;
	
	// config the Flash Erase and program time
	RCC->CFGR4 |= RCC_RCC_CFGR4_FLITFCLK_PRE;
	RCC->CFGR4 &= ~(((uint32_t)0x0F) << RCC_RCC_CFGR4_FLITFCLK_PRE_Pos);
	
	// close HSI
	RCC_HSICmd(DISABLE);

}

