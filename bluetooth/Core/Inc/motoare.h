#ifndef MOTOARE_H   // Include guard pentru a preveni multiple includeri ale acestui fișier.
#define MOTOARE_H

#include "main.h"
#include "usb_host.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio.h"

extern TIM_HandleTypeDef htim4;

void stopMotoare (void);
void mersInainte (uint8_t putere);
void mersInapoi (uint8_t putere);
void curbaStanga (uint8_t putere);
void curbaDreapta (uint8_t putere);

#endif /* MOTOARE_H */
