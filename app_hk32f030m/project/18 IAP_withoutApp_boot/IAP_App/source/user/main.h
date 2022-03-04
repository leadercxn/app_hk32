/*
********************************************************************************
** @file    : main.h
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2019-12-15
** @brief   : Head file of main 
********************************************************************************
*/

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
** Includes
==============================================================================*/
#include "hk32f030m.h"
#include "bsp_hk32f030m_eval.h"

/*==============================================================================
** Exported types
==============================================================================*/
extern uint32_t TimingDelay;

/*==============================================================================
** Exported constants
==============================================================================*/

/*==============================================================================
** Exported macros
==============================================================================*/

/*==============================================================================
** Exported functions
==============================================================================*/
void Delay_ms(uint32_t msCnt);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */


/************************************EOF***************************************/
