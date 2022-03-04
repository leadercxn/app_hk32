/*
********************************************************************************
** @file    : bsp_hk32f030m_eval.h
** @author  : 
** @version : v0.0.1
** @date    : 2020-02-04
** @brief   : This file contains definitions for HK32S003_EVAL's Leds, push-buttons,
**            COM ports, sFLASH(on SPI), and eeprom(on IIC) hardware resources            
********************************************************************************
*/ 
  
#ifndef __BSP_HK32F030M_EVAL_H
#define __BSP_HK32F030M_EVAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
** Includes
==============================================================================*/
#include "hk32f030m.h"

/*==============================================================================
** Exported types
==============================================================================*/
typedef enum
{
  LOW = 0,
  HIGH = 1
} Gpio_State;

typedef enum 
{
	LED1 = 0,
  LED2,
	LED3,
	LED4, 
} Gpio_TypeDef;

typedef enum 
{
	KEY_OFF = 0,
  KEY_ON	
} KeyState_TypeDef;

typedef enum 
{
  KEY1UP = 0,   /* UP key */
  KEY2DOWN = 1, /* Down Key */
  KEY3WKUP = 2, /* Wakeup Key */
} Key_TypeDef;

typedef enum 
{  
  KEY_MODE_GPIO = 0,
  KEY_MODE_EXTI
} KeyMode_TypeDef;

typedef enum 
{
  BEEP_FREQ_1KHz = 0, /* BEEP_Prescaler_128 */
	BEEP_FREQ_2KHz,     /* BEEP_Prescaler_64 */	      	
	BEEP_FREQ_4KHz,     /* BEEP_Prescaler_32 */
	BEEP_FREQ_8KHz      /* BEEP_Prescaler_16 */
} BeepFreq_t; 

typedef enum 
{
  COM1 = 0
} Com_TypeDef; 

/*==============================================================================
** Exported constants
==============================================================================*/

/*==============================================================================
** Exported macros
==============================================================================*/
/* LED definitions */
#define GPIOn                            4

#define GPIO_LED1_PIN                    GPIO_Pin_2
#define GPIO_LED1_PORT                   GPIOD
#define GPIO_LED1_CLK                    RCC_AHBPeriph_GPIOD
#define GPIO_LED1_MODE                   GPIO_Mode_OUT
#define GPIO_LED1_SPEED                  GPIO_Speed_50MHz
#define GPIO_LED1_OTYPE                  GPIO_OType_PP
#define GPIO_LED1_PUPD                   GPIO_PuPd_NOPULL
#define GPIO_LED1_SCHMIT                 GPIO_Schmit_Enable
#define GPIO_LED1_INITSTATE              HIGH
  
#define GPIO_LED2_PIN                    GPIO_Pin_7
#define GPIO_LED2_PORT                   GPIOC
#define GPIO_LED2_CLK                    RCC_AHBPeriph_GPIOC
#define GPIO_LED2_MODE                   GPIO_Mode_OUT
#define GPIO_LED2_SPEED                  GPIO_Speed_50MHz
#define GPIO_LED2_OTYPE                  GPIO_OType_PP
#define GPIO_LED2_PUPD                   GPIO_PuPd_NOPULL
#define GPIO_LED2_SCHMIT                 GPIO_Schmit_Enable
#define GPIO_LED2_INITSTATE              HIGH

#define GPIO_LED3_PIN                    GPIO_Pin_6
#define GPIO_LED3_PORT                   GPIOC
#define GPIO_LED3_CLK                    RCC_AHBPeriph_GPIOC
#define GPIO_LED3_MODE                   GPIO_Mode_OUT
#define GPIO_LED3_SPEED                  GPIO_Speed_50MHz
#define GPIO_LED3_OTYPE                  GPIO_OType_PP
#define GPIO_LED3_PUPD                   GPIO_PuPd_NOPULL
#define GPIO_LED3_SCHMIT                 GPIO_Schmit_Enable
#define GPIO_LED3_INITSTATE              HIGH

#define GPIO_LED4_PIN                    GPIO_Pin_3
#define GPIO_LED4_PORT                   GPIOC
#define GPIO_LED4_CLK                    RCC_AHBPeriph_GPIOC
#define GPIO_LED4_MODE                   GPIO_Mode_OUT
#define GPIO_LED4_SPEED                  GPIO_Speed_50MHz
#define GPIO_LED4_OTYPE                  GPIO_OType_PP
#define GPIO_LED4_PUPD                   GPIO_PuPd_NOPULL
#define GPIO_LED4_SCHMIT                 GPIO_Schmit_Enable
#define GPIO_LED4_INITSTATE              HIGH

/* KEY definitions */
#define KEYn                             3

#define KEY1UP_PIN                       GPIO_Pin_3
#define KEY1UP_GPIO_PORT                 GPIOA
#define KEY1UP_GPIO_CLK                  RCC_AHBPeriph_GPIOA
#define KEY1UP_EXTI_LINE                 EXTI_Line3
#define KEY1UP_EXTI_PORT_SOURCE          EXTI_PortSourceGPIOA
#define KEY1UP_EXTI_PIN_SOURCE           EXTI_PinSource3
#define KEY1UP_EXTI_IRQn                 EXTI3_IRQn

#define KEY2DOWN_PIN                     GPIO_Pin_3
#define KEY2DOWN_GPIO_PORT               GPIOD
#define KEY2DOWN_GPIO_CLK                RCC_AHBPeriph_GPIOD
#define KEY2DOWN_EXTI_LINE               EXTI_Line3
#define KEY2DOWN_EXTI_PORT_SOURCE        EXTI_PortSourceGPIOD
#define KEY2DOWN_EXTI_PIN_SOURCE         EXTI_PinSource3
#define KEY2DOWN_EXTI_IRQn               EXTI3_IRQn

#define KEY3WKUP_PIN                     GPIO_Pin_5
#define KEY3WKUP_GPIO_PORT               GPIOC
#define KEY3WKUP_GPIO_CLK                RCC_AHBPeriph_GPIOC
#define KEY3WKUP_EXTI_LINE               EXTI_Line5
#define KEY3WKUP_EXTI_PORT_SOURCE        EXTI_PortSourceGPIOC
#define KEY3WKUP_EXTI_PIN_SOURCE         EXTI_PinSource5
#define KEY3WKUP_EXTI_IRQn               EXTI5_IRQn

/* Beep definitions */
#define BEEP_GPIO_PIN                    GPIO_Pin_4
#define BEEP_GPIO_PORT                   GPIOD
#define BEEP_GPIO_CLK                    RCC_AHBPeriph_GPIOD
#define BEEP_GPIO_SOURCE                 GPIO_PinSource4
#define BEEP_GPIO_AF                     GPIO_AF_6

/* 74HC595 definitions for LED display */
#define LED595_SCK_PIN                   GPIO_Pin_1
#define LED595_SCK_PORT                  GPIOA
#define LED595_SCK_CLK                   RCC_AHBPeriph_GPIOA
#define LED595_SCK_MODE                  GPIO_Mode_OUT
#define LED595_SCK_SPEED                 GPIO_Speed_50MHz
#define LED595_SCK_OTYPE                 GPIO_OType_PP
#define LED595_SCK_PUPD                  GPIO_PuPd_UP

#define LED595_SI_PIN                    GPIO_Pin_1
#define LED595_SI_PORT                   GPIOD
#define LED595_SI_CLK                    RCC_AHBPeriph_GPIOD
#define LED595_SI_MODE                   GPIO_Mode_OUT
#define LED595_SI_SPEED                  GPIO_Speed_50MHz
#define LED595_SI_OTYPE                  GPIO_OType_PP
#define LED595_SI_PUPD                   GPIO_PuPd_UP

#define LED595_LATCH_PIN                 GPIO_Pin_2
#define LED595_LATCH_PORT                GPIOA
#define LED595_LATCH_CLK                 RCC_AHBPeriph_GPIOA
#define LED595_LATCH_MODE                GPIO_Mode_OUT
#define LED595_LATCH_SPEED               GPIO_Speed_50MHz
#define LED595_LATCH_OTYPE               GPIO_OType_PP
#define LED595_LATCH_PUPD                GPIO_PuPd_UP

/* COM port definitions */
#define COMn                             1

#define COM1_USART                       USART1
#define COM1_CLK                         RCC_APB2Periph_USART1
																		     
#define COM1_TX_PIN                      GPIO_Pin_3
#define COM1_TX_GPIO_PORT                GPIOA
#define COM1_TX_GPIO_CLK                 RCC_AHBPeriph_GPIOA
#define COM1_TX_SOURCE                   GPIO_PinSource3
#define COM1_TX_AF                       GPIO_AF_1
																		     
#define COM1_RX_PIN                      GPIO_Pin_6
#define COM1_RX_GPIO_PORT                GPIOD
#define COM1_RX_GPIO_CLK                 RCC_AHBPeriph_GPIOD
#define COM1_RX_SOURCE                   GPIO_PinSource6
#define COM1_RX_AF                       GPIO_AF_1
																		     
#define COM1_IRQn                        USART1_IRQn

/* I2C EEPROM Interface definitions */
#define sEE_IIC                          I2C1
#define sEE_IIC_CLK                      RCC_APB1Periph_I2C1
   
#define sEE_SCL_PIN                      GPIO_Pin_6
#define sEE_SCL_GPIO_PORT                GPIOC
#define sEE_SCL_GPIO_CLK                 RCC_AHBPeriph_GPIOC
#define sEE_SCL_SOURCE                   GPIO_PinSource6
#define sEE_SCL_AF                       GPIO_AF_0
																		     
#define sEE_SDA_PIN                      GPIO_Pin_5
#define sEE_SDA_GPIO_PORT                GPIOC
#define sEE_SDA_GPIO_CLK                 RCC_AHBPeriph_GPIOC
#define sEE_SDA_SOURCE                   GPIO_PinSource5
#define sEE_SDA_AF                       GPIO_AF_0

/* SPI Flash Interface definition */
#define FLASH_SPI                        SPI1
#define FLASH_SPI_CLK                    RCC_APB2Periph_SPI1

#define FLASH_SPI_SCK_PIN                GPIO_Pin_3
#define FLASH_SPI_SCK_GPIO_PORT          GPIOD
#define FLASH_SPI_SCK_GPIO_CLK           RCC_AHBPeriph_GPIOD
#define FLASH_SPI_SCK_SOURCE             GPIO_PinSource3
#define FLASH_SPI_SCK_AF                 GPIO_AF_2

#define FLASH_SPI_MISO_PIN               GPIO_Pin_6
#define FLASH_SPI_MISO_GPIO_PORT         GPIOD
#define FLASH_SPI_MISO_GPIO_CLK          RCC_AHBPeriph_GPIOD
#define FLASH_SPI_MISO_SOURCE            GPIO_PinSource6
#define FLASH_SPI_MISO_AF                GPIO_AF_2

#define FLASH_SPI_MOSI_PIN               GPIO_Pin_4
#define FLASH_SPI_MOSI_GPIO_PORT         GPIOD
#define FLASH_SPI_MOSI_GPIO_CLK          RCC_AHBPeriph_GPIOD
#define FLASH_SPI_MOSI_SOURCE            GPIO_PinSource4
#define FLASH_SPI_MOSI_AF                GPIO_AF_2

#define FLASH_SPI_CS_PIN                 GPIO_Pin_7
#define FLASH_SPI_CS_GPIO_PORT           GPIOD
#define FLASH_SPI_CS_GPIO_CLK            RCC_AHBPeriph_GPIOD
#define FLASH_SPI_CS_SOURCE              GPIO_PinSource7
#define FLASH_SPI_CS_AF                  GPIO_AF_2

/*==============================================================================
** Exported functions
==============================================================================*/
void BSP_GPIO_Init(Gpio_TypeDef Gpio);
void BSP_GPIO_SetHigh(Gpio_TypeDef Gpio);
void BSP_GPIO_SetLow(Gpio_TypeDef Gpio);
void BSP_GPIO_Toggle(Gpio_TypeDef Gpio);

void BSP_LED_Init(Gpio_TypeDef Led);
void BSP_LED_TurnOn(Gpio_TypeDef Led);
void BSP_LED_TurnOff(Gpio_TypeDef Led);
void BSP_LED_Toggle(Gpio_TypeDef Led);

void BSP_KEY_Init(Key_TypeDef Key, KeyMode_TypeDef KeyMode);
KeyState_TypeDef BSP_KEY_GetKeyState(Key_TypeDef Key);

void BSP_BEEP_Init(BeepFreq_t Freq);
void BSP_BEEP_SetFreq(BeepFreq_t Freq);
void BSP_BEEP_TurnOff(Gpio_State Output);


#ifdef __cplusplus
}
#endif

#endif /* __BSP_HK32F030M_EVAL_H */

/*********************************** EOF **************************************/
