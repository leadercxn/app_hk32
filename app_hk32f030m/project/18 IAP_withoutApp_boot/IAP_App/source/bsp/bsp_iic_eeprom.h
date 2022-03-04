/*
********************************************************************************
** @file    : bsp_iic_eeprom.h
** @author  : Frank.Z
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : Head file of bsp_iic_eeprom.c 
********************************************************************************
*/

#ifndef __BSP_IIC_EEPROM_H
#define __BSP_IIC_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
** Includes
==============================================================================*/
#include "bsp_hk32f030m_eval.h"

/* Select which EEPROM will be used with this driver */
//#define  sEE_HK24C02           1
#define  sEE_HK24C64           1

/*==============================================================================
** Exported types
==============================================================================*/
#define sEE_I2C_TIMING          0x0070112F
#define sEE_HW_ADDRESS          0xA0

/* Maximum Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will 
   not remain stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define sEE_FLAG_TIMEOUT        ((uint32_t)0x1000)
#define sEE_LONG_TIMEOUT        ((uint32_t)(10 * sEE_FLAG_TIMEOUT))

#if defined sEE_HK24C02
  #define sEE_PAGESIZE          8
#elif defined sEE_HK24C64
  #define sEE_PAGESIZE          32
#endif


/* Maximum number of trials for sEE_WaitEepromStandbyState() function */
#define sEE_MAX_TRIALS_NUMBER   300

#define sEE_OK                  0
#define sEE_FAIL                1

/*==============================================================================
** Exported constants
==============================================================================*/

/*==============================================================================
** Exported macros
==============================================================================*/

/*==============================================================================
** Exported functions
==============================================================================*/
void     BSP_IIC_sEE_Init(void);
void     BSP_IIC_sEE_DeInit(void);
uint32_t BSP_IIC_sEE_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t* NumByteToRead);
uint32_t BSP_IIC_sEE_WritePage(uint8_t* pBuffer, uint16_t WriteAddr, uint8_t* NumByteToWrite);
void     BSP_IIC_sEE_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
uint32_t BSP_IIC_sEE_WaitEepromStandbyState(void);

/* USER Callbacks: These are functions for which prototypes only are declared in
   EEPROM driver and that should be implemented into user application. */  
/* sEE_TIMEOUT_UserCallback() function is called whenever a timeout condition 
   occurs during communication (waiting on an event that doesn't occur, bus 
   errors, busy devices ...).
   You can use the default timeout callback implementation by uncommenting the 
   define USE_DEFAULT_TIMEOUT_CALLBACK in stm320518_eval_i2c_ee.h file.
   Typically the user implementation of this callback should reset I2C peripheral
   and re-initialize communication or in worst case reset all the application. */
uint32_t BSP_IIC_sEE_TIMEOUT_UserCallback(void);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_IIC_EEPROM_H */


/*********************************** EOF **************************************/
