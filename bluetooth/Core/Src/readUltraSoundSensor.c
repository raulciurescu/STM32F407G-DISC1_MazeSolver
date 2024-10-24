#include "main.h"
#include "usb_host.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio.h"



uint32_t IC_Val11 = 0;
uint32_t IC_Val21 = 0;
uint32_t Difference1 = 0;
uint8_t Is_First_Captured1 = 0;  // is the first value captured ?
uint8_t Distance1  = 0;

uint32_t IC_Val12 = 0;
uint32_t IC_Val22 = 0;
uint32_t Difference2 = 0;
uint8_t Is_First_Captured2 = 0;  // is the first value captured ?
uint8_t Distance2  = 0;


uint32_t IC_Val13 = 0;
uint32_t IC_Val23 = 0;
uint32_t Difference3 = 0;
uint8_t Is_First_Captured3 = 0;  // is the first value captured ?
uint8_t Distance3  = 0;

#define TRIG_PIN1 GPIO_PIN_10
#define TRIG_PORT1 GPIOE

#define TRIG_PIN2 GPIO_PIN_12
#define TRIG_PORT2 GPIOE

#define TRIG_PIN3 GPIO_PIN_14
#define TRIG_PORT3 GPIOE


extern TIM_HandleTypeDef htim1;  // If it's declared elsewhere

 volatile unsigned int flag ;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
	{
		if (Is_First_Captured1==0) // if the first value is not captured
		{
			IC_Val11 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
			Is_First_Captured1 = 1;  // set the first captured as true
			// Now change the polarity to falling edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}

		else if (Is_First_Captured1==1)   // if the first is already captured
		{
			IC_Val21 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // read second value
			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

			if (IC_Val21 > IC_Val11)
			{
				Difference1 = IC_Val21-IC_Val11;
			}

			else if (IC_Val11 > IC_Val21)
			{
				Difference1 = (0xffff - IC_Val11) + IC_Val21;
			}

			Distance1 = Difference1 * .034/2;
			Is_First_Captured1 = 0; // set it back to false

			// set polarity to rising edge
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
		}
	}

	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)  // if the interrupt source is channel1
		{
			if (Is_First_Captured2==0) // if the first value is not captured
			{
				IC_Val12 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2); // read the first value
				Is_First_Captured2 = 1;  // set the first captured as true
				// Now change the polarity to falling edge
				__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
			}

			else if (Is_First_Captured2==1)   // if the first is already captured
			{
				IC_Val22 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);  // read second value
				__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

				if (IC_Val22 > IC_Val12)
				{
					Difference2 = IC_Val22-IC_Val12;
				}

				else if (IC_Val12 > IC_Val22)
				{
					Difference2 = (0xffff - IC_Val12) + IC_Val22;
				}

				Distance2 = Difference2 * .034/2;
				Is_First_Captured2 = 0; // set it back to false

				// set polarity to rising edge
				__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
				__HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
			}
		}

	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)  // if the interrupt source is channel1
		{
			if (Is_First_Captured3==0) // if the first value is not captured
			{
				IC_Val13 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3); // read the first value
				Is_First_Captured3 = 1;  // set the first captured as true
				// Now change the polarity to falling edge
				__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING);
			}

			else if (Is_First_Captured3==1)   // if the first is already captured
			{
				IC_Val23 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);  // read second value
				__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

				if (IC_Val23 > IC_Val13)
				{
					Difference3 = IC_Val23-IC_Val13;
				}

				else if (IC_Val13 > IC_Val23)
				{
					Difference3 = (0xffff - IC_Val13) + IC_Val23;
				}

				Distance3 = Difference3 * .034/2;
				Is_First_Captured3 = 0; // set it back to false

				// set polarity to rising edge
				__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
				__HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3);
			}
		}

	flag = 1;
}

void HCSR04_Read (unsigned int sensor)
{
	flag = 0;
	if(sensor == 1)
	{
		HAL_GPIO_WritePin(TRIG_PORT1, TRIG_PIN1, GPIO_PIN_SET);  // pull the TRIG pin HIGH
		HAL_Delay(10);  // wait for 10 us
		HAL_GPIO_WritePin(TRIG_PORT1, TRIG_PIN1, GPIO_PIN_RESET);  // pull the TRIG pin low
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
	}else if(sensor == 2)
	{
		HAL_GPIO_WritePin(TRIG_PORT2, TRIG_PIN2, GPIO_PIN_SET);  // pull the TRIG pin HIGH
		HAL_Delay(10);  // wait for 10 us
		HAL_GPIO_WritePin(TRIG_PORT2, TRIG_PIN2, GPIO_PIN_RESET);  // pull the TRIG pin low
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC2);
	}else if(sensor == 3)
	{
		HAL_GPIO_WritePin(TRIG_PORT3, TRIG_PIN3, GPIO_PIN_SET);  // pull the TRIG pin HIGH
		HAL_Delay(10);  // wait for 10 us
		HAL_GPIO_WritePin(TRIG_PORT3, TRIG_PIN3, GPIO_PIN_RESET);  // pull the TRIG pin low
		__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC3);
	}

//	HAL_GPIO_WritePin(TRIG_PORT1, TRIG_PIN1, GPIO_PIN_SET);  // pull the TRIG pin HIGH
//	HAL_Delay(10);  // wait for 10 us
//	HAL_GPIO_WritePin(TRIG_PORT1, TRIG_PIN1, GPIO_PIN_RESET);  // pull the TRIG pin low
//	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);


	while(flag == 0);
}

