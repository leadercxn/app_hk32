/*
********************************************************************************
** @file    : bsp_display.c
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : The LED display functions of system
********************************************************************************
*/

/*==============================================================================
** Includes
==============================================================================*/
#include "bsp_display.h"

/*==============================================================================
** Private typedef
==============================================================================*/

/*==============================================================================
** Private macro
==============================================================================*/

/*==============================================================================
** Private define
==============================================================================*/
#define LED595_SCK_SET        GPIO_SetBits(LED595_SCK_PORT, LED595_SCK_PIN)
#define LED595_SCK_RESET      GPIO_ResetBits(LED595_SCK_PORT, LED595_SCK_PIN)
#define LED595_SI_SET         GPIO_SetBits(LED595_SI_PORT, LED595_SI_PIN)
#define LED595_SI_RESET       GPIO_ResetBits(LED595_SI_PORT, LED595_SI_PIN)
#define LED595_LATCH_SET      GPIO_SetBits(LED595_LATCH_PORT, LED595_LATCH_PIN)
#define LED595_LATCH_RESET    GPIO_ResetBits(LED595_LATCH_PORT, LED595_LATCH_PIN)

/*==============================================================================
** Private variables
==============================================================================*/
display_s DispBuffer;
uint8_t   Led595Flag = 0;

/*==============================================================================
** Private function prototypes
==============================================================================*/


/******************************************************************************/
/*                          Function Implementation                           */
/******************************************************************************/
/*******************************************************************************
** @function : BSP_DISPLAY_Led595Init
** @brief    : Initializates 74HC595 interface
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_DISPLAY_Led595Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(LED595_SCK_CLK | LED595_SI_CLK | LED595_LATCH_CLK, ENABLE);

  /* Configure and initialize SCK pin */
  GPIO_InitStructure.GPIO_Pin = LED595_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = LED595_SCK_MODE;
  GPIO_InitStructure.GPIO_Speed = LED595_SCK_SPEED;
  GPIO_InitStructure.GPIO_OType = LED595_SCK_OTYPE;
  GPIO_InitStructure.GPIO_PuPd = LED595_SCK_PUPD;
  GPIO_Init(LED595_SCK_PORT, &GPIO_InitStructure);
	
	/* Configure and initialize SI pin */
  GPIO_InitStructure.GPIO_Pin = LED595_SI_PIN;
  GPIO_InitStructure.GPIO_Mode = LED595_SI_MODE;
  GPIO_InitStructure.GPIO_Speed = LED595_SI_SPEED;
  GPIO_InitStructure.GPIO_OType = LED595_SI_OTYPE;
  GPIO_InitStructure.GPIO_PuPd = LED595_SI_PUPD;
  GPIO_Init(LED595_SI_PORT, &GPIO_InitStructure);
	
	/* Configure and initialize LATCH pin */
  GPIO_InitStructure.GPIO_Pin = LED595_LATCH_PIN;
  GPIO_InitStructure.GPIO_Mode = LED595_LATCH_MODE;
  GPIO_InitStructure.GPIO_Speed = LED595_LATCH_SPEED;
  GPIO_InitStructure.GPIO_OType = LED595_LATCH_OTYPE;
  GPIO_InitStructure.GPIO_PuPd = LED595_LATCH_PUPD;
  GPIO_Init(LED595_LATCH_PORT, &GPIO_InitStructure);
}


/*******************************************************************************
** @function : BSP_DISPLAY_Led595SendData
** @brief    : Send data to 74HC595 to be diaplayed
** @param    : Gate - which LED to be turned on
**             Data - data to 74HC595 to be diaplayed
** @retval   : None
*******************************************************************************/
void BSP_DISPLAY_Led595SendData(Gate_TypeDef Gate, uint8_t Data)
{
	uint8_t i;
	uint16_t OutData;
	
	OutData = ((uint16_t)Gate << 8) + Data;
	for (i = 0; i < 16; i++)
	{
		/* Set Clock to Low level, the data is kept in the shift register */
		LED595_SCK_RESET;
		
		/* Send the MSB */
		if ((OutData & 0x8000) == 0x8000)
		{
			/* Set High level */
			LED595_SI_SET;
		}
		else
		{
			/* Set Low level */
			LED595_SI_RESET;
		}
		
		/* Set Clock to High level, the data is sent out to latch register */
		LED595_SCK_SET;
		
		/* Next bit to be sent */
		OutData = OutData << 1;
	}
	
	/* Set Latch signal to Low level, the data is kept in the latch register */
	LED595_LATCH_RESET;
	
	/* Set Latch signal to HIGH level, the data is sent tou for displaying */
	LED595_LATCH_SET;
}


/*******************************************************************************
** @function : BSP_DISPLAY_Update
** @brief    : Update LED displaying
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_DISPLAY_Update(void)
{
	switch (Led595Flag)
	{
		case 0:
			BSP_DISPLAY_Led595SendData(GATE0, DispBuffer.LL);
		  Led595Flag++;
			break;
		case 1:
			BSP_DISPLAY_Led595SendData(GATE1, DispBuffer.LH);
		  Led595Flag++;
			break;
		case 2:
			BSP_DISPLAY_Led595SendData(GATE2, DispBuffer.HL);
		  Led595Flag++;
			break;
		case 3:
			BSP_DISPLAY_Led595SendData(GATE3, DispBuffer.HH);
		  Led595Flag = 0;
			break;
		default:
			Led595Flag = 0;
			break;
	}
}



/*********************************** EOF **************************************/
