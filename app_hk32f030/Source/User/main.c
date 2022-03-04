/**
  ******************************************************************************
  * @file    main.c  
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "delay.h"
#include "led.h"


 
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 

/* Private function prototypes -----------------------------------------------*/
 
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
  delay_init();
  
  Led_Init();

 
    
  /* Infinite loop */
  while (1)
  {
    Led_On();
    delay_ms(50);
    Led_Off();
    delay_ms(50);
  }
}
 
  



/**
  * @}
  */

/**
  * @}
  */
 
