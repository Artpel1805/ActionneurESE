/*
 * power_module.c
 *
 *  Created on: Nov 23, 2022
 *      Author: arthurpellegrin
 */


#include "power_module.h"
#include "main.h"

void start_module(){
	HAL_GPIO_WritePin(ISO_RESET_GPIO_Port, ISO_RESET_Pin, SET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(ISO_RESET_GPIO_Port, ISO_RESET_Pin, RESET);
}
