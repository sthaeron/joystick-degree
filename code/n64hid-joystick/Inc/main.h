/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define xb0_Pin GPIO_PIN_0
#define xb0_GPIO_Port GPIOA
#define xb1_Pin GPIO_PIN_1
#define xb1_GPIO_Port GPIOA
#define xb2_Pin GPIO_PIN_2
#define xb2_GPIO_Port GPIOA
#define xb3_Pin GPIO_PIN_3
#define xb3_GPIO_Port GPIOA
#define xb4_Pin GPIO_PIN_4
#define xb4_GPIO_Port GPIOA
#define xb5_Pin GPIO_PIN_5
#define xb5_GPIO_Port GPIOA
#define xb6_Pin GPIO_PIN_6
#define xb6_GPIO_Port GPIOA
#define xb7_Pin GPIO_PIN_7
#define xb7_GPIO_Port GPIOA
#define yb0_Pin GPIO_PIN_8
#define yb0_GPIO_Port GPIOD
#define yb1_Pin GPIO_PIN_9
#define yb1_GPIO_Port GPIOD
#define yb2_Pin GPIO_PIN_10
#define yb2_GPIO_Port GPIOD
#define yb3_Pin GPIO_PIN_11
#define yb3_GPIO_Port GPIOD
#define yb4_Pin GPIO_PIN_12
#define yb4_GPIO_Port GPIOD
#define yb5_Pin GPIO_PIN_13
#define yb5_GPIO_Port GPIOD
#define yb6_Pin GPIO_PIN_14
#define yb6_GPIO_Port GPIOD
#define yb7_Pin GPIO_PIN_15
#define yb7_GPIO_Port GPIOD
#define EOF_Pin GPIO_PIN_0
#define EOF_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
