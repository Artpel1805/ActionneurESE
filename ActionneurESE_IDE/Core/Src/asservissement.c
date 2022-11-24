/**
 *******************************************************************************
 * @file           : asservissement.c
 * @brief          : Asservissement du moteur via les PWM
 ******************************************************************************
 *
 */

#include "tim.h"
#include "asservissement.h"
#include "power_module.h"

/**
 * @brief Obtient la valeur du CCR
 *
 * @param[in] rapport_cyclique Le rapport cyclique donné
 *
 * @return La valeur du CCR
 */

int get_ccr_value(int rapport_cyclique){
	if(rapport_cyclique > 100){
		Error_Handler();
	}
	if(rapport_cyclique<0){
		Error_Handler();
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
	if( goalCCR1 > TIM1 -> CCR1){
		while(TIM1 -> CCR1 != goalCCR1){
			TIM1 -> CCR1 ++;
			TIM1 -> CCR2 --;
			HAL_Delay(50);
		}
	}
	if( goalCCR1 < TIM1 -> CCR1){
		while(TIM1 -> CCR1 != goalCCR1){
			TIM1 -> CCR1 --;
			TIM1 -> CCR2 ++;
			HAL_Delay(50);
		}
	}
}
