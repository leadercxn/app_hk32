/*
********************************************************************************
** @file    : bsp_usart.h
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : Head file of bsp_usart 
********************************************************************************
*/

#ifndef __BSP_USART_H
#define __BSP_USART_H

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
void BSP_USART_Config(Com_TypeDef Com, uint32_t Baud);
void BSP_USART_SendByte(USART_TypeDef* USARTx, uint8_t Data);
void BSP_USART_SendString(USART_TypeDef* USARTx, char* Str);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_USART_H */


/*********************************** EOF **************************************/
