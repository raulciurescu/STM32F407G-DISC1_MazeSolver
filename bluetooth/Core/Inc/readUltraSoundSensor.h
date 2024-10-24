#ifndef READULTRASOUNDSENSOR_H   // Include guard pentru a preveni multiple includeri ale acestui fișier.
#define READULTRASOUNDSENSOR_H

#include "main.h"
#include "usb_host.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio.h"

extern TIM_HandleTypeDef htim1;
extern volatile unsigned int flag;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

void HCSR04_Read (unsigned int sensor);


#endif /* READULTRASOUNDSENSOR_H */
