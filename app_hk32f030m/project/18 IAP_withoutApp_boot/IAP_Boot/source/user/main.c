/*
********************************************************************************
** @file    : main.c
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : main program
********************************************************************************
*/

/*==============================================================================
** Includes
==============================================================================*/
#include <string.h>
#include "main.h"

/*==============================================================================
** Private typedef
==============================================================================*/
typedef  void (*pFunction)(void);

/*==============================================================================
** Private macro
==============================================================================*/

/*==============================================================================
** Private define
==============================================================================*/
#define USER_APP_ADDRESS       (uint32_t)(0x08001000)

/*==============================================================================
** Private variables
==============================================================================*/

/*==============================================================================
** Private function prototypes
==============================================================================*/
static void JumpToApplication(void);

/******************************************************************************/
/*                          Function Implementation                           */
/******************************************************************************/
/*******************************************************************************
** @function : main
** @brief    :   
** @param    : None
** @retval   : None
*******************************************************************************/
int main(void)
{	
	/* Boot program */
	// ”√ªßbootload≥Ã–Ú
	
	/* Jump to user application */
	JumpToApplication();
	
	while(1)
	{
	}
}


static void JumpToApplication(void)
{
	pFunction Jump_To_Application;
	uint32_t UserAppAddr;
	
	/* Calculate the address of user application */
	UserAppAddr = *(__IO uint32_t*) (USER_APP_ADDRESS + 4);
	Jump_To_Application = (pFunction) UserAppAddr;
	
	/* Initialize user application's Stack Pointer, Disable any interrupts during SP setting */
	__set_PRIMASK(1); // Disable interrupts
	__set_MSP(*(__IO uint32_t*) USER_APP_ADDRESS);
	__set_PRIMASK(0); // Enable interrupts
	
	/* Jump to application */
	Jump_To_Application();
}

#ifdef  USE_FULL_ASSERT
/*******************************************************************************
** @function : assert_failed
** @brief    : Reports the name of the source file and the source line number
**             where the assert_param error has occurred
** @param    : file - pointer to the source file name
**             line - assert_param error line source number
** @retval   : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */


/*********************************** EOF **************************************/
