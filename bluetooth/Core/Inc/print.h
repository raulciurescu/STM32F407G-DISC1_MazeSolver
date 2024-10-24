#ifndef PRINT_H
#define PRINT_H

#include "stm32f4xx_hal.h"  // Include header-ul HAL pentru STM32F4.

extern UART_HandleTypeDef huart3;  // Declară UART_HandleTypeDef pentru UART3 ca extern, definit în altă parte.

int _write(int file, char *data, int len);  // Prototipul funcției _write, care va fi folosită în print.c.

#endif /* PRINT_H */
