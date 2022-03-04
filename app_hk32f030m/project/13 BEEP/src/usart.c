#include "usart.h"
#include <stdio.h>
#include "hk32f030m_usart.h"
#include "hk32f030m_misc.h"

void Usart_Init(void)
{
	GPIO_InitTypeDef iostruct;
	USART_InitTypeDef usart_struct;
	//开启GPIO时钟和USART外设时钟
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );
	//配置复用引脚
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_1);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_1); 

	iostruct.GPIO_Mode = GPIO_Mode_AF;
	iostruct.GPIO_OType = GPIO_OType_PP;
	iostruct.GPIO_Pin = GPIO_Pin_6;
	iostruct.GPIO_Speed = GPIO_Speed_10MHz;
	iostruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init( GPIOD, &iostruct );
	
	iostruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init( GPIOA, &iostruct );
	
	//串口配置
	usart_struct.USART_BaudRate = 115200;
	usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart_struct.USART_Parity = USART_Parity_No;
	usart_struct.USART_StopBits = USART_StopBits_1;
	usart_struct.USART_WordLength = USART_WordLength_8b;
	USART_Init( USART1,&usart_struct ); 
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd( USART1,ENABLE );
}

// printf redefine
int fputc(int ch,FILE *f)
{

	 USART_SendData(USART1, (uint8_t) ch);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {}		
  return ch;
}

