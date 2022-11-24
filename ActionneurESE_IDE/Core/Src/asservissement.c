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
extern uint16_t vitesse;

/**
 * @brief Obtient la valeur du CCR
 *
 * @param[in] dutyCycle Le rapport cyclique donné
 *
 * @return La valeur du CCR
 */

int get_ccr_value(int dutyCycle){
	if(dutyCycle > 100){
		return -1;
	}
	if(dutyCycle<0){
		return -1;
	}
	int arr = TIM1 -> ARR;
	return (dutyCycle * arr) / 100;
}


/**
 * @brief Change la valeur du CCR
 *
 * @param[in] dutyCycle Le rapport cyclique donné
 *
 * @return
 */
void change_ccr(int dutyCycle){
	int goalCCR1 = get_ccr_value(dutyCycle);
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
/**
 * @brief Calcul le courant
 *
 * @return
 */

int get_mean_current(void){
	int current = 1;
	int i;
	for(i=0; i<ADC_BUF_SIZE; i++){
		current = current + (int)ADC_Buffer[i];
	}
	current = current / ADC_BUF_SIZE;
	current = ((current * 3.3 / 4096) - 2.5 ) * 12; // Convert ADC to Ampere value
	return current;
}

/**
 * @brief Recupere la valeur de la vitesse du moteur
 *
 * @return
 */

void fetch_speed(void){
	vitesse = htim2.Instance->CNT*10/1180;
	htim2.Instance->CNT=0;
}
