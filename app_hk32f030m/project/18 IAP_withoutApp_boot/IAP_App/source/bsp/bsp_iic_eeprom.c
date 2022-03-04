/*
********************************************************************************
** @file    : bsp_iic_eeprom.c
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : This file provides the functions to manage an IIC EEPROM memory 
********************************************************************************
*/

/*==============================================================================
** Includes
==============================================================================*/
#include "bsp_iic_eeprom.h"

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
uint16_t sEEAddress = 0;
uint32_t sEETimeout = sEE_LONG_TIMEOUT;
uint16_t sEEDataNum;

/*==============================================================================
** Private function prototypes
==============================================================================*/
static void sEE_LowLevel_Init(void);
static void sEE_LowLevel_DeInit(void);


/******************************************************************************/
/*                          Function Implementation                           */
/******************************************************************************/
/*******************************************************************************
** @function : sEE_LowLevel_Init
** @brief    : Initializes the I2C source clock and IOs used to drive the EEPROM
** @param    : None
** @retval   : None
*******************************************************************************/
static void sEE_LowLevel_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Configure the I2C clock source, The clock is derived from the SYSCLK */
	RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK);
	
	/* sEE_SCL_GPIO_CLK and sEE_SDA_GPIO_CLK Periph clock enable */
	RCC_AHBPeriphClockCmd(sEE_SCL_GPIO_CLK | sEE_SDA_GPIO_CLK, ENABLE);
	
	/* sEE_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(sEE_IIC_CLK, ENABLE);
	
	/* Connect PXx to I2C_SCL*/
  GPIO_PinAFConfig(sEE_SCL_GPIO_PORT, sEE_SCL_SOURCE, sEE_SCL_AF);
  
  /* Connect PXx to I2C_SDA*/
  GPIO_PinAFConfig(sEE_SDA_GPIO_PORT, sEE_SDA_SOURCE, sEE_SDA_AF);
	
	/* GPIO configuration */  
	/* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = sEE_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(sEE_SCL_GPIO_PORT, &GPIO_InitStructure);
	
	/* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = sEE_SDA_PIN;
  GPIO_Init(sEE_SDA_GPIO_PORT, &GPIO_InitStructure);
}


/*******************************************************************************
** @function : sEE_LowLevel_DeInit
** @brief    : DeInitializes peripherals used by the I2C EEPROM driver
** @param    : None
** @retval   : None
*******************************************************************************/
static void sEE_LowLevel_DeInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	
	/* sEE_I2C Peripheral Disable */
  I2C_Cmd(sEE_IIC, DISABLE);
	
	/* sEE_I2C DeInit */
  I2C_DeInit(sEE_IIC);
	
	/* sEE_I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(sEE_IIC_CLK, DISABLE);
	
	/* GPIO configuration */  
  /* Configure sEE_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = sEE_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(sEE_SCL_GPIO_PORT, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = sEE_SDA_PIN;
  GPIO_Init(sEE_SDA_GPIO_PORT, &GPIO_InitStructure);
}


/*******************************************************************************
** @function : BSP_IIC_sEE_Init
** @brief    : Initializes peripherals used by the I2C EEPROM driver
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_IIC_sEE_Init(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	
	sEE_LowLevel_Init();
	
	/* I2C configuration */
  /* sEE_I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_InitStructure.I2C_DigitalFilter = 0x00;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_Timing = sEE_I2C_TIMING;
  
  /* Apply sEE_I2C configuration after enabling it */
  I2C_Init(sEE_IIC, &I2C_InitStructure);
   
  /* sEE_I2C Peripheral Enable */
  I2C_Cmd(sEE_IIC, ENABLE);
  
  /* Select the EEPROM address */
  sEEAddress = sEE_HW_ADDRESS;      
}


/*******************************************************************************
** @function : BSP_IIC_sEE_DeInit
** @brief    : DeInitializes peripherals used by the I2C EEPROM driver
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_IIC_sEE_DeInit(void)
{
	sEE_LowLevel_DeInit(); 
}


/*******************************************************************************
** @function : BSP_IIC_sEE_ReadBuffer
** @brief    : Reads a block of data from the EEPROM
** @param    : pBuffer - Pointer to the buffer that receives the data from EEPROM
**             ReadAddr - EEPROM's internal address to start reading from
**             NumByteToRead - Pointer to the variable holding number of the bytes
**                             to be read from EEPROM
** @retval   : sEE_OK - 0 if operation is correctly performed
**             sEE_FAIL - 1 if operation is failed
**             The timeout user callback
*******************************************************************************/
uint32_t BSP_IIC_sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead)
{
	uint32_t NumbOfSingle = 0;
	uint32_t Count = 0;
	uint32_t DataNum = 0;
	uint32_t StartCom = 0;
	
  /* Get number of reload cycles */
  Count = (*NumByteToRead) / 255;  
  NumbOfSingle = (*NumByteToRead) % 255;
	
#if defined sEE_HK24C02	
	/* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(sEE_IIC, sEEAddress, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
	
	/* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0)
		{			
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }
  
  /* Send memory address */
  I2C_SendData(sEE_IIC, (uint8_t)ReadAddr);
	
#elif defined sEE_HK24C64
	/* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(sEE_IIC, sEEAddress, 2, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
	
	/* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0)
		{			
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }
	
	/* Send MSB of memory address */
  I2C_SendData(sEE_IIC, (uint8_t)((ReadAddr & 0xFF00) >> 8));
	
	/* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0)
		{			
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }
	
	/* Send LSB of memory address */
  I2C_SendData(sEE_IIC, (uint8_t)(ReadAddr & 0x00FF));	
#endif
	
	/* Wait until TC flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while (I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TC) == RESET)
  {
    if((sEETimeout--) == 0) 
		{
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }  
  
  /* If number of Reload cycles is not equal to 0 */
  if (Count != 0)
  {
    /* Starting communication */
    StartCom = 1;
    
    /* Wait until all reload cycles are performed */
    while( Count != 0)
    { 
      /* If a read transfer is performed */
      if (StartCom == 0)      
      {
        /* Wait until TCR flag is set */
        sEETimeout = sEE_LONG_TIMEOUT; 
        while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TCR) == RESET)
        {
          if((sEETimeout--) == 0)
					{
						return BSP_IIC_sEE_TIMEOUT_UserCallback();
					}
        }
      }      
      
      /* if remains one read cycle */
      if ((Count == 1) && (NumbOfSingle == 0))
      {
        /* if starting communication */
        if (StartCom != 0)
        {
          /* Configure slave address, end mode and start condition */
          I2C_TransferHandling(sEE_IIC, sEEAddress, 255, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
        }
        else
        {
          /* Configure slave address, end mode */
          I2C_TransferHandling(sEE_IIC, sEEAddress, 255, I2C_AutoEnd_Mode, I2C_No_StartStop);          
        }
      }
      else 
      {
        /* if starting communication */
        if (StartCom != 0)
        {
          /* Configure slave address, end mode and start condition */
          I2C_TransferHandling(sEE_IIC, sEEAddress, 255, I2C_Reload_Mode, I2C_Generate_Start_Read);
        }
        else
        {
          /* Configure slave address, end mode */
          I2C_TransferHandling(sEE_IIC, sEEAddress, 255, I2C_Reload_Mode, I2C_No_StartStop);          
        } 
      }
      
      /* Update local variable */
      StartCom = 0;      
      DataNum = 0;
      
      /* Wait until all data are received */
      while (DataNum != 255)
      {        
        /* Wait until RXNE flag is set */
        sEETimeout = sEE_LONG_TIMEOUT;
        while (I2C_GetFlagStatus(sEE_IIC, I2C_ISR_RXNE) == RESET)
        {
          if((sEETimeout--) == 0) 
					{
						return BSP_IIC_sEE_TIMEOUT_UserCallback();
					}
        }
        
        /* Read data from RXDR */
        pBuffer[DataNum]= I2C_ReceiveData(sEE_IIC);
        
        /* Update number of received data */
        DataNum++;
        (*NumByteToRead)--;
      }      
      /* Update Pointer of received buffer */ 
      pBuffer += DataNum;  
      
      /* update number of reload cycle */
      Count--;
    }
    
    /* If number of single data is not equal to 0 */
    if (NumbOfSingle != 0)
    {            
      /* Wait until TCR flag is set */
      sEETimeout = sEE_LONG_TIMEOUT;   
      while (I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TCR) == RESET)
      {
        if((sEETimeout--) == 0) 
				{
					return BSP_IIC_sEE_TIMEOUT_UserCallback();
				}
      }
      
      /* Update CR2 : set Nbytes and end mode */
      I2C_TransferHandling(sEE_IIC, sEEAddress, (uint8_t)(NumbOfSingle), I2C_AutoEnd_Mode, I2C_No_StartStop);
      
      /* Reset local variable */
      DataNum = 0;
      
      /* Wait until all data are received */
      while (DataNum != NumbOfSingle)
      {        
        /* Wait until RXNE flag is set */
        sEETimeout = sEE_LONG_TIMEOUT;
        while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_RXNE) == RESET)
        {
          if((sEETimeout--) == 0)
					{
						return BSP_IIC_sEE_TIMEOUT_UserCallback();
					}
        }
        
        /* Read data from RXDR */
        pBuffer[DataNum]= I2C_ReceiveData(sEE_IIC);
        
        /* Update number of received data */
        DataNum++;
        (*NumByteToRead)--;
      } 
    }
  }
  else
  {
    /* Update CR2 : set Slave Address , set read request, generate Start and set end mode */
    I2C_TransferHandling(sEE_IIC, sEEAddress, (uint32_t)(NumbOfSingle), I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
    
    /* Reset local variable */
    DataNum = 0;
    
    /* Wait until all data are received */
    while (DataNum != NumbOfSingle)
    {
      /* Wait until RXNE flag is set */
      sEETimeout = sEE_LONG_TIMEOUT; 
      while (I2C_GetFlagStatus(sEE_IIC, I2C_ISR_RXNE) == RESET)
      {
        if((sEETimeout--) == 0)
				{
					return BSP_IIC_sEE_TIMEOUT_UserCallback();
				}
      }
      
      /* Read data from RXDR */
      pBuffer[DataNum]= I2C_ReceiveData(sEE_IIC);
      
      /* Update number of received data */
      DataNum++;
      (*NumByteToRead)--;
    }    
  }  
  
  /* Wait until STOPF flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while (I2C_GetFlagStatus(sEE_IIC, I2C_ISR_STOPF) == RESET)
  {
    if((sEETimeout--) == 0) 
		{
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }
  
  /* Clear STOPF flag */
  I2C_ClearFlag(sEE_IIC, I2C_ICR_STOPCF);
  
  /* If all operations OK, return sEE_OK (0) */
  return sEE_OK;
}


/*******************************************************************************
** @function : BSP_IIC_sEE_WritePage
** @brief    : Writes more than one byte to the EEPROM with a single WRITE cycle
** @param    : pBuffer - Pointer to the buffer containing the data from EEPROM
**             ReadAddr - EEPROM's internal address to start reading from
**             NumByteToRead - Number of bytes to write to the EEPROM
** @retval   : sEE_OK - 0 if operation is correctly performed
**             sEE_FAIL - 1 if operation is failed
**             The timeout user callback
** @Note     : The number of bytes (combined to write start address) must not
**             cross the EEPROM page boundary. This function can only write into
**             the boundaries of an EEPROM page
** @Note     : This function doesn't check on boundaries condition (in this 
**             driver, the function sEE_WriteBuffer() which calls sEE_WritePage()  
**             is responsible of checking on Page boundaries)
*******************************************************************************/
uint32_t BSP_IIC_sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite)
{
	uint32_t DataNum = 0;

#if defined sEE_HK24C02	
	/* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(sEE_IIC, sEEAddress, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;  
  while (I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0) 
		{
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }
  
  /* Send memory address */
  I2C_SendData(sEE_IIC, (uint8_t)WriteAddr);
	
#elif defined sEE_HK24C64
	/* Configure slave address, nbytes, reload and generate start */
  I2C_TransferHandling(sEE_IIC, sEEAddress, 2, I2C_Reload_Mode, I2C_Generate_Start_Write);
  
  /* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;  
  while (I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0) 
		{
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }
  
  /* Send MSB of memory address */
  I2C_SendData(sEE_IIC, (uint8_t)((WriteAddr & 0xFF00) >> 8));
	
	/* Wait until TXIS flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TXIS) == RESET)
  {
    if((sEETimeout--) == 0)
		{			
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }
	
	/* Send LSB of memory address */
  I2C_SendData(sEE_IIC, (uint8_t)(WriteAddr & 0x00FF));	
#endif
	
	/* Wait until TCR flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TCR) == RESET)
  {
    if((sEETimeout--) == 0) 
		{
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }
  
  /* Update CR2 : Set Slave Address, set write request, generate Start and set end mode */
  I2C_TransferHandling(sEE_IIC, sEEAddress, (uint8_t)(*NumByteToWrite), I2C_AutoEnd_Mode, I2C_No_StartStop);
  
  while (DataNum != (*NumByteToWrite))
  {      
    /* Wait until TXIS flag is set */
    sEETimeout = sEE_LONG_TIMEOUT;
    while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_TXIS) == RESET)
    {
      if((sEETimeout--) == 0) 
			{
				return BSP_IIC_sEE_TIMEOUT_UserCallback();
			}
    }  
    
    /* Write data to TXDR */
    I2C_SendData(sEE_IIC, (uint8_t)(pBuffer[DataNum]));
    
    /* Update number of transmitted data */
    DataNum++;   
  }  
  
  /* Wait until STOPF flag is set */
  sEETimeout = sEE_LONG_TIMEOUT;
  while (I2C_GetFlagStatus(sEE_IIC, I2C_ISR_STOPF) == RESET)
  {
    if((sEETimeout--) == 0) 
		{
			return BSP_IIC_sEE_TIMEOUT_UserCallback();
		}
  }   
  
  /* Clear STOPF flag */
  I2C_ClearFlag(sEE_IIC, I2C_ICR_STOPCF);
  
  /* If all operations OK, return sEE_OK (0) */
  return sEE_OK;
}


/*******************************************************************************
** @function : BSP_IIC_sEE_WriteBuffer
** @brief    : Writes buffer of data to the I2C EEPROM
** @param    : pBuffer - Pointer to the buffer containing the data from EEPROM
**             WriteAddr - EEPROM's internal address to start writing from
**             NumByteToWrite - Number of bytes to write to the EEPROM
** @retval   : None
*******************************************************************************/
void BSP_IIC_sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
	uint16_t NumOfPage = 0;
	uint16_t NumOfSingle = 0;
	uint16_t Count = 0;
	uint16_t Addr = 0;
	
	Addr = WriteAddr % sEE_PAGESIZE;
	Count = sEE_PAGESIZE - Addr;
	NumOfPage = NumByteToWrite / sEE_PAGESIZE;
	NumOfSingle = NumByteToWrite % sEE_PAGESIZE;
	
	/* If WriteAddr is sEE_PAGESIZE aligned */
	if (Addr == 0)
	{
		/* If NumByteToWrite < sEE_PAGESIZE */
		if(NumOfPage == 0)
		{
			/* Store the number of data to be written */
		  sEEDataNum = NumOfSingle;
		
		  /* Start writing data */
		  BSP_IIC_sEE_WritePage(pBuffer, WriteAddr, (uint8_t*)(&sEEDataNum));
		  BSP_IIC_sEE_WaitEepromStandbyState();
    }
    /* If NumByteToWrite > sEE_PAGESIZE */
    else
	  {
		  while (NumOfPage--)
		  {
			  /* Store the number of data to be written */
			  sEEDataNum = sEE_PAGESIZE;
			  BSP_IIC_sEE_WritePage(pBuffer, WriteAddr, (uint8_t*)(&sEEDataNum));
		    BSP_IIC_sEE_WaitEepromStandbyState();
				WriteAddr += sEE_PAGESIZE;
				pBuffer += sEE_PAGESIZE;
		  }
		
		  if (NumOfSingle!=0)
		  {
			  /* Store the number of data to be written */
			  sEEDataNum = NumOfSingle;
        BSP_IIC_sEE_WritePage(pBuffer, WriteAddr, (uint8_t*)(&sEEDataNum));
		    BSP_IIC_sEE_WaitEepromStandbyState();			
		  }
	  }
	}
	/* If WriteAddr is not sEE_PAGESIZE aligned  */
  else 
  {
    /* If NumByteToWrite < sEE_PAGESIZE */
    if (NumOfPage== 0) 
    {
      /* If the number of data to be written is more than the remaining space 
      in the current page: */
      if (NumByteToWrite > Count)
      {
        /* Store the number of data to be written */
        sEEDataNum = Count;        
        /* Write the data contained in same page */
        BSP_IIC_sEE_WritePage(pBuffer, WriteAddr, (uint8_t*)(&sEEDataNum));
        BSP_IIC_sEE_WaitEepromStandbyState();      
        
        /* Store the number of data to be written */
        sEEDataNum = (NumByteToWrite - Count);          
        /* Write the remaining data in the following page */
        BSP_IIC_sEE_WritePage((uint8_t*)(pBuffer + Count), (WriteAddr + Count), (uint8_t*)(&sEEDataNum));
        BSP_IIC_sEE_WaitEepromStandbyState();        
      }      
      else      
      {
        /* Store the number of data to be written */
        sEEDataNum = NumOfSingle;         
        BSP_IIC_sEE_WritePage(pBuffer, WriteAddr, (uint8_t*)(&sEEDataNum));
        BSP_IIC_sEE_WaitEepromStandbyState();        
      }     
    }
    /* If NumByteToWrite > sEE_PAGESIZE */
    else
    {
      NumByteToWrite -= Count;
      NumOfPage =  NumByteToWrite / sEE_PAGESIZE;
      NumOfSingle = NumByteToWrite % sEE_PAGESIZE;
      
      if (Count != 0)
      {  
        /* Store the number of data to be written */
        sEEDataNum = Count;         
        BSP_IIC_sEE_WritePage(pBuffer, WriteAddr, (uint8_t*)(&sEEDataNum));
        BSP_IIC_sEE_WaitEepromStandbyState();
        WriteAddr += Count;
        pBuffer += Count;
      } 
      
      while (NumOfPage--)
      {
        /* Store the number of data to be written */
        sEEDataNum = sEE_PAGESIZE;          
        BSP_IIC_sEE_WritePage(pBuffer, WriteAddr, (uint8_t*)(&sEEDataNum));
        sEETimeout = sEE_LONG_TIMEOUT;
        BSP_IIC_sEE_WaitEepromStandbyState();
        WriteAddr +=  sEE_PAGESIZE;
        pBuffer += sEE_PAGESIZE;  
      }
			
      if (NumOfSingle != 0)
      {
        /* Store the number of data to be written */
        sEEDataNum = NumOfSingle;           
        BSP_IIC_sEE_WritePage(pBuffer, WriteAddr, (uint8_t*)(&sEEDataNum)); 
        BSP_IIC_sEE_WaitEepromStandbyState();
      }
    }
  }  		
}





/*******************************************************************************
** @function : BSP_IIC_sEE_WaitEepromStandbyState
** @brief    : Wait for EEPROM Standby state
** @param    : None
** @retval   : sEE_OK - 0 if operation is correctly performed
**             sEE_FAIL - 1 if operation is failed
**             The timeout user callback
** @Note     : This function allows to wait and check that EEPROM has finished
**             the last operation. It is mostly used after Write operation: 
**             after receiving the buffer to be written, the EEPROM may need 
**             additional time to actually perform the write operation. During 
**             this time, it doesn't answer to I2C packets addressed to it. Once
**             the write operation is complete Once the write operation is 
**             complete the EEPROM responds to its address.
*******************************************************************************/
uint32_t BSP_IIC_sEE_WaitEepromStandbyState(void)
{
	uint32_t sEETrials = 0;
	
	/* Keep looping till the slave acknowledge his address or maximum number 
  of trials is reached (this number is defined by sEE_MAX_TRIALS_NUMBER define
  in stm32373c_eval_i2c_ee.h file) */
  
  /* Configure CR2 register : set Slave Address and end mode */
  I2C_TransferHandling(sEE_IIC, sEEAddress, 0, I2C_AutoEnd_Mode, I2C_No_StartStop);  
  
  do
  { 
    /* Initialize sEETimeout */
    sEETimeout = sEE_FLAG_TIMEOUT;
    
    /* Clear NACKF */
    I2C_ClearFlag(sEE_IIC, I2C_ICR_NACKCF | I2C_ICR_STOPCF);
    
    /* Generate start */
    I2C_GenerateSTART(sEE_IIC, ENABLE);
    
    /* Wait until timeout elapsed */
    while (sEETimeout-- != 0); 
    
    /* Check if the maximum allowed number of trials has bee reached */
    if (sEETrials++ == sEE_MAX_TRIALS_NUMBER)
    {
      /* If the maximum number of trials has been reached, exit the function */
      return BSP_IIC_sEE_TIMEOUT_UserCallback();
    }
  }
  while(I2C_GetFlagStatus(sEE_IIC, I2C_ISR_NACKF) != RESET);
  
  /* Clear STOPF */
  I2C_ClearFlag(sEE_IIC, I2C_ICR_STOPCF);
  
  /* Return sEE_OK if device is ready */
  return sEE_OK;
}


/*******************************************************************************
** @function : BSP_IIC_sEE_TIMEOUT_UserCallback
** @brief    : Basic management of the timeout situation
** @param    : None
** @retval   : 0
*******************************************************************************/
uint32_t BSP_IIC_sEE_TIMEOUT_UserCallback(void)
{
	/* The following code allows I2C error recovery and return to normal communication
     if the error source doesn't still exist (ie. hardware issue..) */
	printf("IIC communication timeout, please check the IIC hardware!\n\r");
  
  /* Reinitialize all resources */
  BSP_IIC_sEE_DeInit();
  BSP_IIC_sEE_Init();

  /* At this stage the I2C error should be recovered and device can communicate
     again (except if the error source still exist).
     User can implement mechanism (ex. test on max trial number) to manage situation
     when the I2C can't recover from current error. */
  return 0;
}


/*********************************** EOF **************************************/
