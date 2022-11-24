/*
 * asservissement.c
 *
 *  Created on: Nov 23, 2022
 *      Author: Cheng
 */
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "asservissement.h"
#include "power_module.h"

extern uint32_t ADC_Buffer[ADC_BUF_SIZE];

int get_ccr_value(int rapport_cyclique){
	if(rapport_cyclique > 100){
		return -1;
	}
	if(rapport_cyclique<0){
		return -1;
	}
	int arr = TIM1 -> ARR;
	return (rapport_cyclique * arr) / 100;
}


void change_ccr(int rapport_cyclique){
	int goalCCR1 = get_ccr_value(rapport_cyclique);
	if(goalCCR1 == -1){
		return;
	}
	if( goalCCR1 > TIM1 -> CCR1){
		while(TIM1 -> CCR1 != goalCCR1){
			TIM1 -> CCR1 ++;
			TIM1 -> CCR2 --;
			HAL_Delay(50);
		}
		return;
	}
	if( goalCCR1 < TIM1 -> CCR1){
		while(TIM1 -> CCR1 != goalCCR1){
			TIM1 -> CCR1 --;
			TIM1 -> CCR2 ++;
			HAL_Delay(50);
		}
		return;
	}
}

int get_mean_current(void){
	int current = 1;
	current = (int)ADC_Buffer[0];
	current = ((current * 3.3 / 4096) - 2.5 ) * 12;
	return current;
}
