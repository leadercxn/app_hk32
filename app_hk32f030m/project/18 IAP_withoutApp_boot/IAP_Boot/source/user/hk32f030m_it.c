/*
********************************************************************************
** @file    : hk32f030m_it.c
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : Interrupt Service Routines
********************************************************************************
*/	

/*==============================================================================
** Includes
==============================================================================*/
#include "main.h"
#include "hk32f030m_it.h"

/*==============================================================================
** Private typedef
==============================================================================*/

/*==============================================================================
** Private macro
==============================================================================*/

/*==============================================================================
** Private define
==============================================================================*/

/*==============================================================================
** Private variables
==============================================================================*/

/*==============================================================================
** Private function prototypes
==============================================================================*/


/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
}


/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {
  }
}


/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}


/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}


/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
}


/******************************************************************************/
/* hk32f030m Peripheral Interrupt Handlers                                     */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_hk32f030m.s).                     */
/******************************************************************************/
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/*********************************** EOF **************************************/
