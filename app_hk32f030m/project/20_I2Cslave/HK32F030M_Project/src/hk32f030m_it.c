/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hk32s0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************

  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f030m_it.h"
#include "hk32f030m.h"
/* Private includes ----------------------------------------------------------*/


#define I2C_DEVICE                               I2C1

#define I2C_DEVICE_DR_NULL_R                     0xFA
#define I2C_DEVICE_DR_NULL_S                     0xFB
//TCR, TC, STOPF, NACKF, ADDR, RXNE, TXIS
#define I2C_STATUS_EVT_MASK                      (uint32_t)(0x000000FE)
//OVR-Overrun and ARLO-Arbitration lost and BERR-Bus error
#define I2C_STATUS_ERR_MASK                      (uint32_t)(0x00000700)				


/******************************************************************************
                              ����Ĵ����б��С
******************************************************************************/

#define I2C_REG_TEST_SIZE                        10

//�Ĵ���ʶ���ַ   �׵�ַ
#define I2C_REG_TEST_ADD                         (uint8_t)0x00

extern uint8_t I2C_REG_TEST[I2C_REG_TEST_SIZE];



/******************************************************************************
                              ����I2C���߲����ṹ��
******************************************************************************/
#define I2C_DEVICE_FLAG_DIR_SEND                 ((uint32_t)0x80000000)
#define I2C_DEVICE_FLAG_READ                     ((uint32_t)0x40000000)
#define I2C_DEVICE_FLAG_NACK                     ((uint32_t)0x20000000)
#define I2C_DEVICE_FLAG_WRITE                    ((uint32_t)0x10000000)
#define I2C_DEVICE_FLAG_ERROR                    ((uint32_t)0x08000000)

__packed typedef struct
{
	uint32_t I2C_DeviceFlag;  //���������и��ֱ�ʶ����	
	uint32_t I2C_EventStatus;
	uint32_t I2C_ErrorStatus;
} I2C_DEVICE_TypeDef;

//extern I2C_DEVICE_TypeDef i2c_dev;
/******************************************************************************
                                 �������
******************************************************************************/

I2C_DEVICE_TypeDef i2c_dev;
//I2C�����ж��õ�����
//
uint8_t I2CFirstByteFlag = 0;  //���յ�һ���ֽ����ݱ�־
uint8_t I2CAddressOffset = 0;  //����������ַ
uint8_t i2c_regtemp = 0;
uint8_t I2C_DEVICE_REGADDRESS = 0;
uint8_t I2C_DEVICE_REGOFFSET = 0;

//
//�Ĵ����б�
//
uint8_t I2C_REG_SEND_TEST[I2C_REG_TEST_SIZE]={0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29};
uint8_t I2C_REG_RECEIVE_TEST[I2C_REG_TEST_SIZE]={0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
uint8_t receive_data_lens=0;
uint8_t send_data_lens=0;
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
/* hk32s0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_hk32l020.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */
void I2C1_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_IRQn 0 */
	uint32_t temp = 0;
	
	/*!< Read Event Flag */
	temp = I2C_DEVICE->ISR;
	
	//TCR, TC, STOPF, NACKF, ADDR, RXNE, TXIS; Mask=0xFE
	i2c_dev.I2C_EventStatus = (uint32_t)(temp & I2C_STATUS_EVT_MASK);
	
	//OVR-Overrun and ARLO-Arbitration lost and BERR-Bus error,Mask=0x700
	i2c_dev.I2C_ErrorStatus = (uint32_t)(temp & I2C_STATUS_ERR_MASK);	
  /* USER CODE END I2C1_IRQn 0 */

	
  /* USER CODE BEGIN I2C1_IRQn 1 */

	
	/* ==================================================== */
	/*      slave address��ַ�����ж�                       */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_ADDR) != 0)
	{
		I2C_ClearFlag(I2C1,I2C_FLAG_ADDR);
		/*!< ************************************ */
		/*!< NoStretch=0, Slave TX data is not ready in time */
		/*!< ************************************ */
			if ((I2C_DEVICE->ISR & I2C_ISR_DIR) != 0)  /*!< Slave transmitter mode, Host read data */
			{
				//I2C_DEVICE->ISR |= I2C_ISR_TXE;  /*software write 1 to TXE bit, flush TXDR */
				i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_DIR_SEND;		//Dir=1, slave send TX
				//I2C_DEVICE->TXDR = 0x55;
			}
			else  /*!< Host write data (slave receive data from host) */
			{
				i2c_dev.I2C_DeviceFlag &= ~I2C_DEVICE_FLAG_DIR_SEND;	//DIR=0, Slave receive RX
				I2CFirstByteFlag = 0;
			}
				
		//LL_I2C_ClearFlag_ADDR(I2C1);
		
	}
	
	/* ==================================================== */
	/*                   �ӻ����������ж�                    */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_TXIS) != 0)
	{
		//
		//���ݲ�ͬ�ļĴ�����ַ���������ݣ�������ȡ����
		//
		
		//
		//���ԼĴ���
		//
		if (I2C_DEVICE_REGADDRESS == I2C_REG_TEST_ADD)  //read and write
		{
			if (I2C_DEVICE_REGOFFSET < I2C_REG_TEST_SIZE)
			{
				I2C_DEVICE->TXDR = I2C_REG_SEND_TEST[I2C_DEVICE_REGOFFSET];
				I2C_DEVICE_REGOFFSET++;
				if (I2C_DEVICE_REGOFFSET >= I2C_REG_TEST_SIZE)
				{
					I2C_DEVICE_REGOFFSET = 0;
				}
			}
			else
			{
				I2C_DEVICE->TXDR = I2C_DEVICE_DR_NULL_S;
			}
		}
		else
		{
			I2C_DEVICE->TXDR = I2C_DEVICE_DR_NULL_R;
		}
	}
	
	/* ==================================================== */
	/*                   �ӻ����������ж�                    */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_RXNE) != 0)
	{
		if (I2CFirstByteFlag != 0)
		{
			//
			//���ݲ�ͬ�ļĴ���ƫ�������н����������ݣ�����д������
			//
			
			//
			//���ԼĴ���
			//
			if (I2C_DEVICE_REGADDRESS == I2C_REG_TEST_ADD)  //read and write
			{
				if (I2C_DEVICE_REGOFFSET < I2C_REG_TEST_SIZE)
				{
					I2C_REG_RECEIVE_TEST[I2C_DEVICE_REGOFFSET] = I2C_DEVICE->RXDR;
					I2C_DEVICE_REGOFFSET++;
					if (I2C_DEVICE_REGOFFSET >= I2C_REG_TEST_SIZE)
					{
						I2C_DEVICE_REGOFFSET = 0;
					}
				}
				else
				{
					i2c_regtemp = I2C_DEVICE->RXDR;
				}
			}
			else
			{
				i2c_regtemp = I2C_DEVICE->RXDR;
				i2c_regtemp = 0;
			}
		}
		else
		{
			//
			//���յ�һ����ַ�ֽ�
			//
			I2CAddressOffset = I2C_DEVICE->RXDR;
			I2C_DEVICE_REGADDRESS = I2CAddressOffset;// & 0xF0;
			I2C_DEVICE_REGOFFSET  = 0x0;//I2CAddressOffset & 0x0F;
			I2CFirstByteFlag++;
		}
	}
	
	/* ==================================================== */
	/*                      ��Ӧ���ж�                       */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_NACKF) != 0)
	{
		I2C_ClearFlag(I2C1,I2C_FLAG_NACKF);
		if (I2CFirstByteFlag != 0)
		{
			I2CFirstByteFlag = 0;
		}
		i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_NACK;
	}
	
	/* ==================================================== */
	/*                     ֹͣ�ź��ж�                      */
	/* ==================================================== */
	if ((i2c_dev.I2C_EventStatus & I2C_ISR_STOPF) != 0)
	{

		if (I2CFirstByteFlag != 0)
		{
			I2CFirstByteFlag = 0;
		}
		//send receive count
		
		if((i2c_dev.I2C_DeviceFlag & I2C_DEVICE_FLAG_DIR_SEND)==0)
		{
			//receive data;
			if(receive_data_lens==0)
				receive_data_lens=I2C_DEVICE_REGOFFSET;
		}else
		{
			//send data
			if(send_data_lens==0)
				send_data_lens=I2C_DEVICE_REGOFFSET;//
		}
		//I2C_DEVICE->ISR |= I2C_ISR_TXE;		//Add by thomas.w
		I2C_ClearFlag(I2C1,I2C_FLAG_STOPF);
	}
	
	
	/* ==================================================== */
	/*                       �����ж�                        */
	/* ==================================================== */
	//
	//���ߴ���
	//
	if ((i2c_dev.I2C_ErrorStatus & I2C_ISR_BERR) != 0)
	{
		I2C_DEVICE->ICR = I2C_ICR_BERRCF;
		i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_ERROR;
	}
	//
	//�ٲ�ʧ��
	//
	if ((i2c_dev.I2C_ErrorStatus & I2C_ISR_ARLO) != 0)
	{
		I2C_DEVICE->ICR = I2C_ICR_ARLOCF;
		i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_ERROR;
	}
	//
	//���
	//
	if ((i2c_dev.I2C_ErrorStatus & I2C_ISR_OVR) != 0)
	{
		I2C_DEVICE->ICR = I2C_ICR_OVRCF;
		i2c_dev.I2C_DeviceFlag |= I2C_DEVICE_FLAG_ERROR;
	}
  /* USER CODE END I2C1_IRQn 1 */	
	
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT HKMicroChip *****END OF FILE****/
