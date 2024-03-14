/*
 * n64_functions.c
 *
 *  Created on: Mar 14, 2024
 *      Author: dapper_penguin
 */
#include "stm32f0xx_it.h"
#include "gpio.h"
#include "usart.h"
#include <stdio.h>

uint8_t x_pos = 0;
uint8_t y_pos = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == xA_pin_Pin)
    {
        uint8_t xa_val = HAL_GPIO_ReadPin(xA_pin_GPIO_Port, xA_pin_Pin);
        uint8_t xb_val = HAL_GPIO_ReadPin(xB_pin_GPIO_Port, xB_pin_Pin);
        if (xa_val != xb_val)
            x_pos++;
        else
            x_pos--;
    }
    if (GPIO_Pin == yA_pin_Pin)
    {
        uint8_t ya_val = HAL_GPIO_ReadPin(yA_pin_GPIO_Port, yA_pin_Pin);
        uint8_t yb_val = HAL_GPIO_ReadPin(yB_pin_GPIO_Port, yB_pin_Pin);
        if (ya_val != yb_val)
            y_pos++;
        else
            y_pos--;
    }
}

void write_coords()
{
    printf("X pos is %d, and Y pos is %d\r\n", x_pos, y_pos);
}

void n64_loop()
{
    while (1)
    {
        write_coords();
    }
}
