/*
********************************************************************************
** @file    : bsp_spi_flash.h
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : Head file of bsp_iic_eeprom.c 
********************************************************************************
*/

#ifndef __BSP_SPI_FLASH_H
#define __BSP_SPI_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
** Includes
==============================================================================*/
#include "bsp_hk32f030m_eval.h"

/*==============================================================================
** Exported types
==============================================================================*/

/*==============================================================================
** Exported constants
==============================================================================*/

/*==============================================================================
** Exported macros
==============================================================================*/

/*==============================================================================
** Exported functions
=============================================================================*/
void BSP_SPI_FLASH_Init(void);
void BSP_SPI_FLASH_SectorErase(uint32_t SectorAddr);
void BSP_SPI_FLASH_BulkErase(void);
void BSP_SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void BSP_SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void BSP_SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t BSP_SPI_FLASH_ReadID(void);
uint32_t BSP_SPI_FLASH_ReadDeviceID(void);
void BSP_SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
void BSP_SPI_Flash_PowerDown(void);
void BSP_SPI_Flash_WAKEUP(void);
uint8_t BSP_SPI_FLASH_ReadByte(void);
uint8_t BSP_SPI_FLASH_SendByte(uint8_t byte);
uint16_t BSP_SPI_FLASH_SendHalfWord(uint16_t HalfWord);
void BSP_SPI_FLASH_WriteEnable(void);
void BSP_SPI_FLASH_WaitForWriteEnd(void);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_SPI_FLASH_H */


/*********************************** EOF **************************************/
