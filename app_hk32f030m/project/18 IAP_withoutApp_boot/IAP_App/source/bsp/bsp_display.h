/*
********************************************************************************
** @file    : bsp_display.h
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : Head file of bsp_system.c 
********************************************************************************
*/

#ifndef __BSP_DISPLAY_H
#define __BSP_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
** Includes
==============================================================================*/
#include "bsp_hk32f030m_eval.h"

/*==============================================================================
** Exported types
==============================================================================*/
typedef struct
{
	uint16_t LL;
	uint16_t LH;
	uint16_t HL;
	uint16_t HH;
} display_s;

/*==============================================================================
** Exported constants
==============================================================================*/

/*==============================================================================
** Exported macros
==============================================================================*/
/* Digit definition for LED display */
#define LED595_ONE               (0x06)
#define LED595_TWO               (0x5B)
#define LED595_THREE             (0x4F)
#define LED595_FOUR              (0x66)
#define LED595_FIVE              (0x6D)
#define LED595_SIX               (0x7D)
#define LED595_SEVEN             (0x07)
#define LED595_EIGHT             (0x7F)
#define LED595_NINE              (0x67)
#define LED595_ZERO              (0x3F)
#define LED595_DOT               (0x80)

#define LED595_LL                (0xF7)
#define LED595_LH                (0xFB)
#define LED595_HL                (0xFD)
#define LED595_HH                (0xFE)

#define LED595_NO_DISPLAY        (0xFF00)
#define LED595_ALL_DISPLAY       (0xF0FF)

#define ZER                      LED595_ZERO
#define ONE                      LED595_ONE
#define TWO                      LED595_TWO   
#define THR                      LED595_THREE 
#define FOU                      LED595_FOUR  
#define FIV                      LED595_FIVE  
#define SIX                      LED595_SIX   
#define SEV                      LED595_SEVEN 
#define EIG                      LED595_EIGHT 
#define NIN                      LED595_NINE
#define DOT                      LED595_DOT

typedef enum
{
	GATE0 = LED595_LL,
	GATE1 = LED595_LH,
	GATE2 = LED595_HL,
	GATE3 = LED595_HH
} Gate_TypeDef;

/*==============================================================================
** Exported variables
==============================================================================*/
extern display_s DispBuffer;

/*==============================================================================
** Exported functions
==============================================================================*/
void BSP_DISPLAY_Led595Init(void);
void BSP_DISPLAY_Led595SendData(Gate_TypeDef Gate, uint8_t Data);
void BSP_DISPLAY_Update(void);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_DISPLAY_H */


/*********************************** EOF **************************************/
