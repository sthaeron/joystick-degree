/*
 * usart_test.c
 *
 *  Created on: Mar 14, 2024
 *      Author: dapper_penguin
 */
#include "usart.h"
#include "gpio.h"

void uart_testing()
{
    int data[] = {65,
                  66,
                  67,
                  68,
                  69,
                  70,
                  71,
                  72,
                  13,
                  10};
    while (1)
    {
        HAL_UART_Transmit(&huart1, data, 40, 1000);
        printf("Some words to print, and a in ascii %d\n", data[0]);
    }
}
