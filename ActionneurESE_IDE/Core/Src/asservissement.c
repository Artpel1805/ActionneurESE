/**
 *******************************************************************************
 * @file           : asservissement.c
 * @brief          : Asservissement du moteur via les PWM
 ******************************************************************************
 *
 */
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "asservissement.h"
#include "power_module.h"

extern uint32_t ADC_Buffer[ADC_BUF_SIZE];

/**
 * @brief Obtient la valeur du CCR
 *
 * @param[in] rapport_cyclique Le rapport cyclique donné
 *
 * @return La valeur du CCR
 */

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


/**
 * @brief Change la valeur du CCR
 *
 * @param[in] rapport_cyclique Le rapport cyclique donné
 *
 * @return
 */
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
