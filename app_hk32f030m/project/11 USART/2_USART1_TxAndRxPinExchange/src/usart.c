
/**************************************************************************************************
* @file      usart.c
* @brief     异步串口通信例程, 通过查询TXE标志发送数据,通过RXNE中断接收数据,当中断接收到数据后会将
*            收到的数据原样通过TX引脚发送出去,该例程中使能了串口的RX和TX引脚的功能互换
* @author    veiko.c
* @date      20200202
**************************************************************************************************/

#include "usart.h"

static void USART_GPIO_Configurature(void);
static void USART_NVIC_Configurature(void);

void USART_Configurature(void)
{
	USART_InitTypeDef m_usart;
	
	USART_GPIO_Configurature();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	m_usart.USART_BaudRate = 115200;
	m_usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	m_usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	m_usart.USART_Parity = USART_Parity_No;
	m_usart.USART_StopBits = USART_StopBits_1;
	m_usart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &m_usart);
	USART_SWAPPinCmd(USART1, ENABLE);    // 互换TX和RX引脚
	USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_NVIC_Configurature();
}

void USART_SendByte(uint8_t ch)
{
	while((USART1->ISR & USART_ISR_TXE) == 0);
	USART1->TDR = ch;
}

void USART_SendStringLen(uint8_t *p,uint16_t len)
{
	while(len--)
	{
		USART_SendByte(*(p++));
	}
}

static void USART_GPIO_Configurature(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_IOMUX,ENABLE);    //打开IOMux时钟
	GPIO_InitTypeDef m_gpio;
	
	USART1_TX_IO_CLK_EN();
	USART1_RX_IO_CLK_EN();
	
	m_gpio.GPIO_Mode = GPIO_Mode_AF;
	m_gpio.GPIO_OType = GPIO_OType_PP;
	m_gpio.GPIO_Pin = USART1_TX_PIN;
	m_gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_gpio.GPIO_Speed = GPIO_Speed_10MHz;
  
	GPIO_IOMUX_ChangePin(IOMUX_PIN5,IOMUX_PB5_SEL_PA3);// SOP8 PIN7(NRST)PA0 IO  IOMUX_NRST_SEL_NRST   IOMUX_NRST_SEL_PA0
	GPIO_Init(USART1_TX_PORT, &m_gpio);
  
	GPIO_PinAFConfig(USART1_TX_PORT,GPIO_PinSource3,GPIO_AF_1);
	
	m_gpio.GPIO_Pin = USART1_RX_PIN;
	GPIO_Init(USART1_RX_PORT, &m_gpio);
	GPIO_PinAFConfig(USART1_RX_PORT,GPIO_PinSource6,GPIO_AF_1);
}

static void USART_NVIC_Configurature(void)
{
	NVIC_SetPriority(USART1_IRQn,0);
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void)
{
	uint8_t ch_rx_test;
	if((USART1->ISR & USART_ISR_RXNE) != 0)
	{
		ch_rx_test = USART1->RDR;
		USART_SendByte(ch_rx_test);
	}
}
