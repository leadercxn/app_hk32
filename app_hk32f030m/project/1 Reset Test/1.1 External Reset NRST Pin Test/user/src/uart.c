#define _UART_C_
#include "uart.h"
#include "hk32f030m_gpio.h"

#define  USART1_TX_PORT         GPIOA
#define  USART1_TX_PIN          GPIO_Pin_3
#define  USART1_TX_PIN_SOURCE		GPIO_PinSource3
#define  USART1_TX_IO_CLK_EN()  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE)
	
#define  USART1_RX_PORT         GPIOD
#define  USART1_RX_PIN          GPIO_Pin_6
#define  USART1_RX_PIN_SOURCE		GPIO_PinSource6
#define  USART1_RX_IO_CLK_EN()  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE)
	
	
void Uart_Config(void)
{   
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* config GPIO clock And config USART1 clock */
	USART1_TX_IO_CLK_EN();
	USART1_RX_IO_CLK_EN();
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE);

	/* USART1 GPIO config */
	/* Configure USART1 Tx  as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);    
	GPIO_PinAFConfig(USART1_TX_PORT,USART1_TX_PIN,GPIO_AF_1);
	
	/* Configure USART1 Rx  as input floating */
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
	GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);	
	GPIO_PinAFConfig(USART1_RX_PORT,USART1_RX_PIN_SOURCE,GPIO_AF_1);
	
	/* USART1  mode config */
  USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 	USART_Init(USART1 , &USART_InitStructure); 
 	
	//如果配置的TX和RX脚与实际硬件需要交换,则调用下面语句
	USART_SWAPPinCmd(USART1, ENABLE);    // 互换TX和RX引脚
	 	
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);
  /* Enable the USARTy Interrupt */
	
	
}


