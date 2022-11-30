/*
 * Task.c
 *
 *  Created on: Nov 30, 2022
 *      Author: ASUS
 */

#include "Task.h"
#include "stm32f103x6.h"
#include "main.h"



void TASK_A(void)
{
	HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
}


void TASK_B(void)
{
	HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
}

void TASK_C(void)
{
	HAL_GPIO_TogglePin(LED_3_GPIO_Port, LED_3_Pin);
}

void TASK_D(void)
{
	HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);
}


void TASK_E(void)
{
	HAL_GPIO_TogglePin(LED_5_GPIO_Port, LED_5_Pin);
}
