#include "led.h"
#include "hk32f0xx_gpio.h"
#include "hk32f0xx_rcc.h"

void Led_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  Led_Off();
}

void Led_On(void)
{
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void Led_Off(void)
{
    GPIO_SetBits(GPIOC,GPIO_Pin_13);
}















