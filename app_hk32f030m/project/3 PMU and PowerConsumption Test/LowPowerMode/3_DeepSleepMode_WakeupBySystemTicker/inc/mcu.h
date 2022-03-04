
#ifndef _mcu_h
#define _mcu_h

#ifdef __cplusplus
extern "C" {
#endif
	
#include "hk32f030m.h"
#include "hk32f030m_gpio.h"
	
#define  SYSCLK_FREQ     48000000ul
	
void Systick_Init(void);
void MCO_Configurature(void);
void Sysclk_SwitchToLSI(void);

	
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _mcu_h */
