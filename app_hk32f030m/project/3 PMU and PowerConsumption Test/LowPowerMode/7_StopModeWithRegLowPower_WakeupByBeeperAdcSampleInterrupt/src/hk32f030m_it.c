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
#include "hk32f030m_exti.h"
#include "hk32f030m_adc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

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
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* hk32f0301m Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_hk32f0301m.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

void EXTI4_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4);
}
void EXTI11_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line11);
}
void ADC1_IRQHandler(void)
{
    if((ADC1->ISR & ADC_ISR_AWD) == ADC_ISR_AWD) {
      ADC1->ISR = ADC_ISR_AWD;
      ADC1->IER &= ~ADC_IER_AWDIE;
    } else if((ADC1->ISR & ADC_ISR_OVR) == ADC_ISR_OVR) {
      ADC1->ISR = ADC_ISR_OVR;
      ADC1->IER &= ~ADC_IER_OVRIE;
    } else if((ADC1->ISR & ADC_ISR_EOSEQ) == ADC_ISR_EOSEQ) {
      ADC1->ISR = ADC_ISR_EOSEQ;
      ADC1->IER &= ~ADC_IER_EOSEQIE;
    } else if((ADC1->ISR & ADC_ISR_EOC) == ADC_ISR_EOC) {
      ADC1->ISR = ADC_ISR_EOC;
      ADC1->IER &= ~ADC_IER_EOCIE;
    } else if((ADC1->ISR & ADC_ISR_EOSMP) == ADC_ISR_EOSMP) {
      ADC1->ISR = ADC_ISR_EOSMP;
      ADC1->IER &= ~ADC_IER_EOSMPIE;
    } else if((ADC1->ISR & ADC_ISR_ADRDY) == ADC_ISR_ADRDY) {
      ADC1->ISR = ADC_ISR_ADRDY;
      ADC1->IER &= ~ADC_IER_ADRDYIE;
    } 
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT HKMicroChip *****END OF FILE****/
