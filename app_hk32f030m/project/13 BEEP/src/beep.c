#include "beep.h"
#include "hk32f030m_beep.h" 



void HKBEEP_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BEEPER, ENABLE ); 
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOD, ENABLE);
	
	RCC_LSICmd(ENABLE);
	while(!(RCC->CSR & RCC_CSR_LSIRDY));
	
	GPIO_InitTypeDef GPIO_InitStructure;
	BEEP_InitTypeDef BEEP_InitStructure;
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_6); 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init( GPIOD, &GPIO_InitStructure );
	 
	BEEP_InitStructure.BEEP_Prescaler = BEEP_Prescaler_32;
	BEEP_InitStructure.BEEP_Clock = BEEP_CLOCK_LSI;
	BEEP_InitStructure.BEEP_TRGOCmd = ENABLE;
	BEEP_Init(&BEEP_InitStructure);
	BEEP_Cmd(ENABLE);	
	
}
void SetPrescaler(uint8_t BEEP_Prescaler)
{
	BEEP_SetPrescaler(BEEP_Prescaler);
}

