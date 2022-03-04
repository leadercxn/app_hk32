#ifndef __USART_H
#define __USART_H

#include <stdio.h>
#include <stdint.h>

void HKUsart_Init(void);
void HKUSART_SendData(char data);
void USART_NVICConfig(void);
void HKUSART_SendString(char *string,uint32_t Length);
uint8_t HKUSART_ReceiveData(void);


#endif

