/**************************************************************************************************
* @file      usart.h
* @brief     �첽����ͨ������, ͨ����ѯTXE��־��������,ͨ��RXNE�жϽ�������,���жϽ��յ����ݺ�Ὣ
*            �յ�������ԭ��ͨ��TX���ŷ��ͳ�ȥ,��������ʹ���˴��ڵ�RX��TX���ŵĹ��ܻ���
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
