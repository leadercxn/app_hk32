/*
********************************************************************************
** @file    : bsp_system.c
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : The delay functions of system
********************************************************************************
*/

/*==============================================================================
** Includes
==============================================================================*/
#include "bsp_system.h"

/*==============================================================================
** Private typedef
==============================================================================*/

/*==============================================================================
** Private macro
==============================================================================*/

/*==============================================================================
** Private define
==============================================================================*/
#define UINT24_MAX        (0xFFFFFF)

/*==============================================================================
** Private variables
==============================================================================*/

/*==============================================================================
** Private function prototypes
==============================================================================*/


/******************************************************************************/
/*                          Function Implementation                           */
/******************************************************************************/
/*******************************************************************************
** @function : BSP_SYSTEM_Delay_us
** @brief    : Inserts a delay time 
** @param    : usCnt - specifies the delay time length, in microseconds
** @retval   : None
*******************************************************************************/
void BSP_SYSTEM_Delay_us(uint32_t usCnt)
{
	/* SysTick default clock source: HCLK/8 = 32MHz/8 = 4MHz */
	SysTick->LOAD = 4 * usCnt;
	
	/* Clear SysTick current counter value */
	SysTick->VAL = 0;

	/* Enable SysTick counter */
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; 
	
  /* Wait for SysTick counter to 0 */
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
	{
	}
	
	/* Disable SysTick counter */
	SysTick->CTRL = ~SysTick_CTRL_ENABLE_Msk; 
	
	/* Clear SysTick current counter value */
	SysTick->VAL = 0;
}


/*******************************************************************************
** @function : BSP_SYSTEM_Delay_ms
** @brief    : Inserts a delay time 
** @param    : msCnt - specifies the delay time length, in milliseconds
** @retval   : None
*******************************************************************************/
void BSP_SYSTEM_Delay_ms(uint32_t msCnt)
{
	/* SysTick default clock source: HCLK/8 = 32MHz/8 = 4MHz */
	SysTick->LOAD = 4000 * msCnt;
	
	/* Clear SysTick current counter value */
	SysTick->VAL = 0;

	/* Enable SysTick counter */
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; 
	
  /* Wait for SysTick counter to 0 */
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
	{
	}
	
	/* Disable SysTick counter */
	SysTick->CTRL = ~SysTick_CTRL_ENABLE_Msk; 
	
	/* Clear SysTick current counter value */
	SysTick->VAL = 0;
}

/*********************************** EOF **************************************/
