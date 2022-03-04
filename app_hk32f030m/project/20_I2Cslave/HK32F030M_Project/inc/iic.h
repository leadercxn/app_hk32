#ifndef __IIC_H
#define __IIC_H

#include <stdio.h>
#include <stdint.h>

void HKIIC_Init(void);
void HKIIC_Read(uint8_t SalveAddr,uint8_t startaddr,uint8_t *buffer,uint8_t Length);
void HKIIC_Write(uint8_t SalveAddr,uint8_t startaddr,uint8_t *buffer, uint8_t Length);

#endif


