/*
 * Timer.c
 *
 *  Created on: Sep 25, 2023
 *      Author: ASUS
 */


#include "main.h"
#include "Button.h"

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim ){
	timerseg1Run();
	timerLightRun();
	timerAdjustLightRun();
	timerButtonCooldownRun();
	if (htim->Instance == TIM2){
		button_reading();
	}
}
