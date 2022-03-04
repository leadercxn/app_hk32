/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hk32f0301m_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************

  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m.h"
#include "hk32f030m_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
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
extern uint8_t TxBuffer[];
extern  uint8_t RxBuffer[];
extern __IO uint8_t Rx_Idx;
extern __IO uint8_t Tx_Idx;

extern __IO uint8_t CmdTransmitted;
extern __IO uint8_t CmdReceived;
extern __IO uint8_t CmdStatus;

__IO uint8_t Counter = 0x00;
extern __IO uint32_t TimeOut;
/* USER CODE BEGIN 1 */
void SPI1_IRQHandler(void)
{
	/* SPI in Slave Receiver mode--------------------------------------- */
	if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) == SET)
	{
		if (CmdReceived == 0x00)
		{
			CmdReceived = SPI_ReceiveData8(SPI1);
			if(CmdReceived==0x9f)
			{
				//Tx_Idx=0;
				SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, DISABLE);
				CmdStatus = 0x01;
			}
			//CmdStatus = 0x01;
		}
		else
		{
		  RxBuffer[Rx_Idx++] = SPI_ReceiveData8(SPI1);
		}
	} 
	
	
	/* SPI in Slave Tramitter mode--------------------------------------- */
	if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE) == SET)
	{
		if(Tx_Idx<SPI_DATA_LENS)
			SPI_SendData8(SPI1, TxBuffer[Tx_Idx++]);
		if (Tx_Idx == SPI_DATA_LENS)
		{
		  /* Disable the Tx buffer empty interrupt */
		  SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
		}
	}

  
	/* SPI Error interrupt--------------------------------------- */
	if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_OVR) == SET)
	{
		SPI_ReceiveData8(SPI1);
		SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_OVR);
	}
  
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT HKMicroChip *****END OF FILE****/
