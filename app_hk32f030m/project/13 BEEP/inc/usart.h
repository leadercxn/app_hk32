#ifndef __USART_H
#define __USART_H

#include <stdio.h>
#include <stdint.h>

void Usart_Init(void);
void USART_NVICConfig(void);
uint8_t HKUSART_ReceiveData(void);


#endif

