/**************************************************************************************************
* @file      usart.h
* @brief     异步串口通信例程, 通过查询TXE标志发送数据,通过RXNE中断接收数据,当中断接收到数据后会将
*            收到的数据原样通过TX引脚发送出去,该例程中使能了串口的RX和TX引脚的功能互换
* @author    veiko.c
* @date      20200202
**************************************************************************************************/
#ifndef _usart_h
#define _usart_h

#ifdef __cplusplus
extern "C" {
#endif
	
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
#include "hk32f030m_usart.h"
	
#define  USART1_TX_PORT         GPIOA
#define  USART1_TX_PIN          GPIO_Pin_3
#define  USART1_TX_IO_CLK_EN()  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE)
	
#define  USART1_RX_PORT         GPIOD
#define  USART1_RX_PIN          GPIO_Pin_6
#define  USART1_RX_IO_CLK_EN()  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE)
	
void USART_Configurature(void);
void USART_SendByte(uint8_t ch);
void USART_SendStringLen(uint8_t *p,uint16_t len);
	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _usart_h */
