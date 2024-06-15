/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal_gpio.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct Data{
    uint32_t time;
    float x;
    float y;
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t n64_get_x();
uint8_t n64_get_y();
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  uint8_t min_x = 0x6E;
  uint8_t max_x = 0x92;
  uint8_t min_y = 0x6E;
  uint8_t max_y = 0x92;

  uint8_t x_val = 0x80;
  uint8_t y_val = 0x80;

  struct Data *data_ptr = (struct Data*)malloc(sizeof(struct Data)*2000);
  uint16_t i = 0;
  uint16_t reached = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    x_val = n64_get_x();
    y_val = n64_get_y(); 
    // if (x_val < min_x) {
    //   min_x = x_val;
    // }
    // if (x_val > max_x) {
    //   max_x = x_val;
    // }
    // if (y_val < min_y) {
    //   min_y = y_val;
    // }
    // if (y_val > max_y) {
    //   max_y = y_val;
    // }
    float out_x = (float) ((float)((x_val - min_x) * (2)) / (max_x - min_x)) - (float)1;
    float out_y = (float) ((float)((y_val - min_y) * (2)) / (max_y - min_y)) - (float)1;
    data_ptr[i].time = get_time_ms();
    data_ptr[i].x = out_x;
    data_ptr[i].y = out_y;
    i++;
    if (i >= 2000) 
    {
      i = 0;
      reached = 1;
    }
    if(HAL_GPIO_ReadPin(EOF_GPIO_Port, EOF_Pin) == GPIO_PIN_SET){
      if (reached == 1) reached = 2000;
      else {
        reached = i;
        i = 0;
      }
      for(int j = 0; j < reached; j++)
      {
        printf("%d,%f,%f\r\n", data_ptr[i].time, data_ptr[i].x, data_ptr[i].y);
        i++;
        if (i >= 2000) i = 0;
      }
      printf("End of Transmission\r\n");
    }
    delay_ms(10);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
* @brief This function gets the value of the binary counter respoinsible for keeping track of the x-axis of a n64 joystick
* @retval X-axis value, signed 8-bit int
*/
uint8_t n64_get_x()
{
  uint8_t returval = 0;
  returval = returval | (HAL_GPIO_ReadPin(xb0_GPIO_Port, xb0_Pin));
  returval = returval | (HAL_GPIO_ReadPin(xb1_GPIO_Port, xb1_Pin)<<1);
  returval = returval | (HAL_GPIO_ReadPin(xb2_GPIO_Port, xb2_Pin)<<2);
  returval = returval | (HAL_GPIO_ReadPin(xb3_GPIO_Port, xb3_Pin)<<3);
  returval = returval | (HAL_GPIO_ReadPin(xb4_GPIO_Port, xb4_Pin)<<4);
  returval = returval | (HAL_GPIO_ReadPin(xb5_GPIO_Port, xb5_Pin)<<5);
  returval = returval | (HAL_GPIO_ReadPin(xb7_GPIO_Port, xb7_Pin)<<6);
  returval = returval | ((HAL_GPIO_ReadPin(xb7_GPIO_Port, xb7_Pin)^0x1)<<7);
  return returval;
}

uint8_t n64_get_y()
{
  uint8_t returval = 0;
  returval = returval | (HAL_GPIO_ReadPin(yb0_GPIO_Port, yb0_Pin));
  returval = returval | (HAL_GPIO_ReadPin(yb1_GPIO_Port, yb1_Pin)<<1);
  returval = returval | (HAL_GPIO_ReadPin(yb2_GPIO_Port, yb2_Pin)<<2);
  returval = returval | (HAL_GPIO_ReadPin(yb3_GPIO_Port, yb3_Pin)<<3);
  returval = returval | (HAL_GPIO_ReadPin(yb4_GPIO_Port, yb4_Pin)<<4);
  returval = returval | (HAL_GPIO_ReadPin(yb5_GPIO_Port, yb5_Pin)<<5);
  returval = returval | (HAL_GPIO_ReadPin(yb6_GPIO_Port, yb6_Pin)<<6);
  returval = returval | ((HAL_GPIO_ReadPin(yb7_GPIO_Port, yb7_Pin)^0x1)<<7);
  return returval;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
