/*
********************************************************************************
** @file    : bsp_system.h
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : Head file of bsp_system.c 
********************************************************************************
*/

#ifndef __BSP_SYSTEM_H
#define __BSP_SYSTEM_H

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

/*==============================================================================
** Exported constants
==============================================================================*/

/*==============================================================================
** Exported macros
==============================================================================*/

/*==============================================================================
** Exported functions
==============================================================================*/
void BSP_SYSTEM_Delay_us(uint32_t usCnt);
void BSP_SYSTEM_Delay_ms(uint32_t msCnt);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_SYSTEM_H */


/*********************************** EOF **************************************/
