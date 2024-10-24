#include "main.h"
#include "usb_host.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio.h"

extern TIM_HandleTypeDef htim4;


void stopMotoare (){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);   // PB3 (IN1) -> HIGH
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); // PB5 (IN2) -> LOW



					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);   // PB3 (IN3) -> HIGH
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); // PB5 (IN4) -> LOW

}

void mersInainte (uint8_t putere){

	//pornireMotoareFata();

	htim4.Instance->CCR3 = (htim4.Init.Period / 100) * putere ;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);   // PB3 (IN1) -> HIGH
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); // PB5 (IN2) -> LOW
	htim4.Instance->CCR4 = (htim4.Init.Period / 100) * putere ;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);   // PB3 (IN3) -> HIGH
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); // PB5 (IN4) -> LOW
}

void mersInapoi (uint8_t putere){

	//pornireMotoareSpate();

	htim4.Instance->CCR3 = htim4.Init.Period / 100 * putere ;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);   // PB3 (IN1) -> HIGH
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET); // PB5 (IN2) -> LOW
	htim4.Instance->CCR4 = htim4.Init.Period / 100 * putere ;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);   // PB3 (IN3) -> HIGH
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); // PB5 (IN4) -> LOW

}

void curbaStanga (uint8_t putere){

	//pornireMotoareCurbaStanga();

	htim4.Instance->CCR3 = htim4.Init.Period / 100 * putere ;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);   // PB3 (IN1) -> HIGH
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET); // PB5 (IN2) -> LOW
	htim4.Instance->CCR4 = htim4.Init.Period / 100 * putere ;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);   // PB3 (IN3) -> HIGH
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); // PB5 (IN4) -> LOW

}

void curbaDreapta (uint8_t putere){

	//pornireMotoareCurbaDreapta();

	htim4.Instance->CCR3 = htim4.Init.Period / 100 * putere ;
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);   // PB3 (IN1) -> HIGH
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET); // PB5 (IN2) -> LOW
	htim4.Instance->CCR4 = htim4.Init.Period / 100 * putere ;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);   // PB3 (IN3) -> HIGH
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET); // PB5 (IN4) -> LOW

}

