#ifndef __BEEP_H
#define __BEEP_H

#include <stdio.h>
#include <stdint.h>

void HKBEEP_Init(void);
void SetPrescaler(uint8_t BEEP_Prescaler);

#endif

