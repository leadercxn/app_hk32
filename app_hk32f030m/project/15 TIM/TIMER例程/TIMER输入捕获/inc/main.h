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
#include "hk32f030m.h"
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

