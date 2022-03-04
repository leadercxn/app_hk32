/*
********************************************************************************
** @file    : bsp_spi_flash.c
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : This file provides the functions to manage a SPI Flash memory 
********************************************************************************
*/

/*==============================================================================
** Includes
==============================================================================*/
#include "bsp_spi_flash.h"

/*==============================================================================
** Private typedef
==============================================================================*/

/*==============================================================================
** Private macro
==============================================================================*/

/*==============================================================================
** Private define
==============================================================================*/
#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

#define HK25Q_WRITEENABLE               0x06 
#define HK25Q_WRITEDISABLE              0x04 
#define HK25Q_READSTATUSREG             0x05 
#define HK25Q_WRITESTATUSREG            0x01 
#define HK25Q_READDATA                  0x03 
#define HK25Q_FASTREADDATA              0x0B 
#define HK25Q_FASTREADDUAL              0x3B 
#define HK25Q_PAGEPROGRAM 	            0x02 
#define HK25Q_BLOCKERASE  	            0xD8 
#define HK25Q_SECTORERASE 	            0x20 
#define HK25Q_CHIPERASE			            0xC7 
#define HK25Q_POWERDOWN			            0xB9 
#define HK25Q_RELEASEPOWERDOWN          0xAB 
#define HK25Q_DEVICEID		              0xAB 
#define HK25Q_MANUFACTDEVICEID   	      0x90 
#define HK25Q_JEDECDEVICEID		          0x9F 
																	      
#define WIP_FLAG                        0x01  /* Write In Progress (WIP) flag */
																	      
#define DUMMY_BYTE                      0xFF


#define SPI_FLASH_CS_LOW()    GPIO_ResetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN)
#define SPI_FLASH_CS_HIGH()   GPIO_SetBits(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN)

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
** @function : BSP_SPI_FLASH_Init
** @brief    : Initializes the peripherals used by the SPI FLASH driver
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;
	
	/* SPI GPIO Periph clock enable */
	RCC_AHBPeriphClockCmd(FLASH_SPI_SCK_GPIO_CLK | FLASH_SPI_MISO_GPIO_CLK | \
	                      FLASH_SPI_MOSI_GPIO_CLK | FLASH_SPI_CS_GPIO_CLK , ENABLE);
	
	/* SPI1 Periph clock enable */
	RCC_APB2PeriphClockCmd(FLASH_SPI_CLK, ENABLE);
	
	/* Configure SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; 
  GPIO_Init(FLASH_SPI_SCK_GPIO_PORT , &GPIO_InitStructure);
	
	/* Configure SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
  GPIO_Init(FLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /* Configure SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin =FLASH_SPI_MOSI_PIN;
  GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
  
  /* Connect PXx to FLASH_SPI_SCK */
  GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT, FLASH_SPI_SCK_SOURCE, FLASH_SPI_SCK_AF);

  /* Connect PXx to FLASH_SPI_MISO */
  GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT, FLASH_SPI_MISO_SOURCE, FLASH_SPI_MISO_AF); 

  /* Connect PXx to FLASH_SPI_MOSI */
  GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT, FLASH_SPI_MOSI_SOURCE, FLASH_SPI_MOSI_AF);
	
	/* Configure FLASH_SPI_CS_PIN pin: FLASH CS pin */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(FLASH_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
	
	/* Connect PXx to FLASH_SPI_MOSI */
	
	SPI_FLASH_CS_HIGH();
	
	/* SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
  SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
	
	/* SPI enable */
  SPI_Cmd(SPI1, ENABLE); 
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_SectorErase
** @brief    : Erases the specified FLASH sector
** @param    : SectorAddr - Address of the sector to erase
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
	/* Send write enable instruction */
  BSP_SPI_FLASH_WriteEnable();
  BSP_SPI_FLASH_WaitForWriteEnd();
	
  /* Sector Erase */
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
	
  /* Send Sector Erase instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_SECTORERASE);
	
  /* Send SectorAddr high nibble address byte */
  BSP_SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
	
  /* Send SectorAddr medium nibble address byte */
  BSP_SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
	
  /* Send SectorAddr low nibble address byte */
  BSP_SPI_FLASH_SendByte(SectorAddr & 0xFF);
	
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
	
  /* Wait the end of Flash writing */
  BSP_SPI_FLASH_WaitForWriteEnd();
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_BulkErase
** @brief    : Erases the entire FLASH
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_BulkErase(void)
{
	/* Send write enable instruction */
  BSP_SPI_FLASH_WriteEnable();

  /* Bulk Erase */
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
	
  /* Send Bulk Erase instruction  */
  BSP_SPI_FLASH_SendByte(HK25Q_CHIPERASE);
	
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  BSP_SPI_FLASH_WaitForWriteEnd();
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_PageWrite
** @brief    : Writes more than one byte to the FLASH with a single WRITE
**             cycle(Page WRITE sequence). The number of byte can't exceed
**             the FLASH page size
** @param    : pBuffer - Pointer to the buffer  containing the data to be
**                       written to the FLASH.
**             WriteAddr - FLASH's internal address to write to
**             NumByteToWrite - number of bytes to write to the FLASH, must be 
**                              equal or less than "SPI_FLASH_PageSize" value
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	/* Enable the write access to the FLASH */
  BSP_SPI_FLASH_WriteEnable();

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
	
  /* Send "Write to Memory " instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_PAGEPROGRAM);
	
  /* Send WriteAddr high nibble address byte to write to */
  BSP_SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
	
  /* Send WriteAddr medium nibble address byte to write to */
  BSP_SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
	
  /* Send WriteAddr low nibble address byte to write to */
  BSP_SPI_FLASH_SendByte(WriteAddr & 0xFF);

  if (NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
  }

  /* while there is data to be written on the FLASH */
  while (NumByteToWrite--)
  {
    /* Send the current byte */
    BSP_SPI_FLASH_SendByte(*pBuffer);
		
    /* Point on the next byte to be written */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  BSP_SPI_FLASH_WaitForWriteEnd();
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_BufferWrite
** @brief    : Writes block of data to the FLASH. In this function, the number 
**             of WRITE cycles are reduced, using Page WRITE sequence
** @param    : pBuffer - Pointer to the buffer  containing the data to be
**                       written to the FLASH.
**             WriteAddr - FLASH's internal address to write to
**             NumByteToWrite - number of bytes to write to the FLASH
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % SPI_FLASH_PageSize;
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

	/* WriteAddr is SPI_FLASH_PageSize aligned  */
  if (Addr == 0) 
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0) 
    {
      BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
		/* NumByteToWrite > SPI_FLASH_PageSize */
    else 
    {
      while (NumOfPage--)
      {
        BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
			
      BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
	/* WriteAddr is not SPI_FLASH_PageSize aligned  */
  else 
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0) 
    {
			/* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      if (NumOfSingle > count) 
      {
        temp = NumOfSingle - count;

        BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
		/* NumByteToWrite > SPI_FLASH_PageSize */
    else 
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        BSP_SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_BufferRead
** @brief    : Reads a block of data from the FLASH 
** @param    : pBuffer - Pointer to the buffer that receives the data read
**                       from the FLASH
**             ReadAddr - FLASH's internal address to read from
**             NumByteToRead - number of bytes to read from the FLASH
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	/* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_READDATA);

  /* Send ReadAddr high nibble address byte to read from */
  BSP_SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	
  /* Send ReadAddr medium nibble address byte to read from */
  BSP_SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
	
  /* Send ReadAddr low nibble address byte to read from */
  BSP_SPI_FLASH_SendByte(ReadAddr & 0xFF);

	/* while there is data to be read */
  while (NumByteToRead--) 
  {
    /* Read a byte from the FLASH */
    *pBuffer = BSP_SPI_FLASH_SendByte(DUMMY_BYTE);
		
    /* Point to the next location where the byte read will be saved */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_ReadID
** @brief    : Reads FLASH identification 
** @param    : None
** @retval   : FLASH identification
*******************************************************************************/
uint32_t BSP_SPI_FLASH_ReadID(void)
{
	uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "RDID " instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_JEDECDEVICEID);

  /* Read a byte from the FLASH */
  Temp0 = BSP_SPI_FLASH_SendByte(DUMMY_BYTE);

  /* Read a byte from the FLASH */
  Temp1 = BSP_SPI_FLASH_SendByte(DUMMY_BYTE);

  /* Read a byte from the FLASH */
  Temp2 = BSP_SPI_FLASH_SendByte(DUMMY_BYTE);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_ReadDeviceID
** @brief    : Reads FLASH identification 
** @param    : None
** @retval   : FLASH identification
*******************************************************************************/
uint32_t BSP_SPI_FLASH_ReadDeviceID(void)
{
	uint32_t Temp = 0;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "RDID " instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_DEVICEID);
  BSP_SPI_FLASH_SendByte(DUMMY_BYTE);
  BSP_SPI_FLASH_SendByte(DUMMY_BYTE);
  BSP_SPI_FLASH_SendByte(DUMMY_BYTE);
  
  /* Read a byte from the FLASH */
  Temp = BSP_SPI_FLASH_SendByte(DUMMY_BYTE);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  return Temp;
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_StartReadSequence
** @brief    : Initiates a read data byte (READ) sequence from the Flash.
**             This is done by driving the /CS line low to select the device,
**             then the READ instruction is transmitted followed by 3 bytes
**             address. This function exit and keep the /CS line low, so the
**             Flash still being selected. With this technique the whole
**             content of the Flash is read with a single READ instruction. 
** @param    : ReadAddr - FLASH's internal address to read from
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
	/* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_READDATA);

  /* Send the 24-bit address of the address to read from -----------------------*/
  /* Send ReadAddr high nibble address byte */
  BSP_SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	
  /* Send ReadAddr medium nibble address byte */
  BSP_SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
	
  /* Send ReadAddr low nibble address byte */
  BSP_SPI_FLASH_SendByte(ReadAddr & 0xFF);
}


/*******************************************************************************
** @function : BSP_SPI_Flash_PowerDown
** @brief    : Power down the FLASH 
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_SPI_Flash_PowerDown(void)
{
	/* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Power Down" instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_POWERDOWN);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}


/*******************************************************************************
** @function : BSP_SPI_Flash_WAKEUP
** @brief    : Wake up the FLASH 
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_SPI_Flash_WAKEUP(void)
{
	/* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Release Power Down" instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_RELEASEPOWERDOWN);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_ReadByte
** @brief    : Reads a byte from the SPI Flash
**             This function must be used only if the Start_Read_Sequence
**             function has been previously called.
** @param    : None
** @retval   : Byte Read from the SPI Flash
*******************************************************************************/
uint8_t BSP_SPI_FLASH_ReadByte(void)
{
	return (BSP_SPI_FLASH_SendByte(DUMMY_BYTE));
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_SendByte
** @brief    : Sends a byte through the SPI interface and return the byte
**             received from the SPI bus.
** @param    : byte - byte to send
** @retval   : The value of the received byte
*******************************************************************************/
uint8_t BSP_SPI_FLASH_SendByte(uint8_t byte)
{
	/* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_SendData8(FLASH_SPI, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_ReceiveData8(FLASH_SPI);
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_SendHalfWord
** @brief    : Sends a Half Word through the SPI interface and return the
**             Half Word received from the SPI bus
** @param    : Half Word - Half Word to send
** @retval   : The value of the received Half Word
*******************************************************************************/
uint16_t BSP_SPI_FLASH_SendHalfWord(uint16_t HalfWord)
{
	/* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /* Send Half Word through the SPI1 peripheral */
  SPI_SendData8(FLASH_SPI, HalfWord);

  /* Wait to receive a Half Word */
  while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the Half Word read from the SPI bus */
  return SPI_ReceiveData8(FLASH_SPI);
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_WriteEnable
** @brief    : Enables the write access to the FLASH
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_WriteEnable(void)
{
	/* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Write Enable" instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_WRITEENABLE);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}


/*******************************************************************************
** @function : BSP_SPI_FLASH_WaitForWriteEnd
** @brief    : Polls the status of the Write In Progress (WIP) flag in the
**             FLASH's status  register  and  loop  until write  opertaion
**             has completed
** @param    : None
** @retval   : None
*******************************************************************************/
void BSP_SPI_FLASH_WaitForWriteEnd(void)
{
	uint8_t FLASH_Status = 0;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read Status Register" instruction */
  BSP_SPI_FLASH_SendByte(HK25Q_READSTATUSREG);

  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status = BSP_SPI_FLASH_SendByte(DUMMY_BYTE);

  }
  while ((FLASH_Status & WIP_FLAG) == SET); /* Write in progress */

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}


/*********************************** EOF **************************************/
