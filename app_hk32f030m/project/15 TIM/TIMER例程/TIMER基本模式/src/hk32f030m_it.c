/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hk32f030m_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************

  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
uint16_t capture = 0;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  ///HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}
void USART1_IRQHandler(void)
{


}

void TIM1_CC_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);

    /* PA1 toggling */
		GPIO_TogglePin(GPIOA ,GPIO_Pin_1);
		capture = TIM_GetCapture1(TIM1);
    TIM_SetCompare1(TIM1, capture);
  }
   if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);

    /* PA2 toggling  */
		GPIO_TogglePin(GPIOA ,GPIO_Pin_2);
    capture = TIM_GetCapture2(TIM1);
    TIM_SetCompare2(TIM1, capture);
  }
   if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);

    /* PA3 toggling */
		GPIO_TogglePin(GPIOA ,GPIO_Pin_3);
    capture = TIM_GetCapture3(TIM1);
    TIM_SetCompare3(TIM1, capture);
  }
 if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)
  {
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);

    /* PD4 toggling  */
		GPIO_TogglePin(GPIOD ,GPIO_Pin_4);
    capture = TIM_GetCapture4(TIM1);
    TIM_SetCompare4(TIM1, capture);
  }
}
/******************************************************************************/
/* hk32f0301m Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_hk32f0301m.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT HKMicroChip *****END OF FILE****/
