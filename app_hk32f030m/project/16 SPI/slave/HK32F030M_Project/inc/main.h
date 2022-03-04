/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************

  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
#define SPI_DATA_LENS	3


#define  SPI_CS_PORT      GPIOD
#define  SPI_CS_Pin       GPIO_Pin_7
#define  SPI_CS_CLK_EN()  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE)
#define  SPI_CS_PinSource GPIO_PinSource7


#define  SPI_CLK_PORT      GPIOA
#define  SPI_CLK_Pin       GPIO_Pin_2
#define  SPI_CLK_CLK_EN()  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE)
#define  SPI_CLK_PinSource GPIO_PinSource2
	
#define  SPI_MOSI_PORT      GPIOD
#define  SPI_MOSI_Pin       GPIO_Pin_4
#define  SPI_MOSI_CLK_EN()  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE)
#define  SPI_MOSI_PinSource GPIO_PinSource4
	
#define  SPI_MISO_PORT      GPIOB
#define  SPI_MISO_Pin       GPIO_Pin_4
#define  SPI_MISO_CLK_EN()  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE)
#define  SPI_MISO_PinSource GPIO_PinSource4


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

