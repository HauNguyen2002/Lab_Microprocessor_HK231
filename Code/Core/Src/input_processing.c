/*
 * input_processing.c
 *
 *  Created on: Sep 25, 2023
 *      Author: ASUS
 */

#include "main.h"
#include "input_processing.h"
#include "Timer.h"

enum ButtonState{BUTTON_HOLD,BUTTON_RELEASED, BUTTON_PRESSED,
	BUTTON_PRESSED_MORE_THAN_1_SECOND};


enum ButtonState increasebuttonState= BUTTON_HOLD;
enum ButtonState modebuttonState= BUTTON_RELEASED;
enum ButtonState setbuttonState= BUTTON_HOLD;

enum LightState{RED_GREEN, RED_YELLOW, GREEN_RED, YELLOW_RED,HOLD, RESETALL};
enum LightState lightstate= RED_GREEN;

enum AdjustState{ADJUST_HOLD, ADJUST_RESET, RED,YELLOW,GREEN};
enum AdjustState adjuststate=ADJUST_HOLD;

int led_scan_flag=0;
int numSEG[2][2]={{0,0},{0,0}};
int led_ini_flag=0;


int incRoad1SEG=0;
int modeRoad2SEG=0;

int trafficduration[2][3]={{6,4,3},{4,3,6}};
int reddur=6;
int yellowdur=3;
int greendur=4;
int ini_traffic_flag=0;

void checkAdjustMode(int mode)
{
	switch(mode){
	case 2:
		incRoad1SEG=reddur-1;
		break;
	case 3:
		incRoad1SEG=yellowdur-1;
		adjuststate= YELLOW;
		break;
	case 4:
		incRoad1SEG=greendur-1;
		adjuststate= GREEN;
		break;
	}
}

void applyDuration();
void setDuration(int duration,int mode)
{
	switch(mode){
	case 2:
		reddur=duration+1;
		break;
	case 3:
		yellowdur=duration+1;
		break;
	case 4:
		greendur=duration+1;
		break;
	}
	applyDuration();
}

void applyDuration()
{
	trafficduration[0][0]=reddur;
	trafficduration[1][2]=reddur;
	trafficduration[0][2]=yellowdur;
	trafficduration[1][1]=yellowdur;
	trafficduration[0][1]=greendur;
	trafficduration[1][0]=greendur;
}

void fsm_for_mode_button(uint32_t prescaler, uint32_t period)
{
	if(flag_but_cooldown==1)
	{
		switch(modebuttonState){
		case BUTTON_HOLD:
			modebuttonState=BUTTON_RELEASED;
			break;
		case BUTTON_RELEASED:
			if(is_button_pressed(0)){
				modebuttonState= BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(0)){
				modeRoad2SEG++;
				modebuttonState= BUTTON_RELEASED;
				if(modeRoad2SEG>4){
					modeRoad2SEG=1;
					lightstate=RESETALL;
				}
				if(modeRoad2SEG==1){
					increasebuttonState=BUTTON_HOLD;
					setbuttonState= BUTTON_HOLD;
					adjuststate=ADJUST_HOLD;
					led_ini_flag=0;
				}
				else{
					increasebuttonState=BUTTON_RELEASED;
					setbuttonState= BUTTON_RELEASED;
					adjuststate= ADJUST_RESET;
					lightstate=HOLD;
					checkAdjustMode(modeRoad2SEG);
					updatenumSEG(modeRoad2SEG,0);
					updatenumSEG(incRoad1SEG, 1);
				}
				setButtonCooldownTimer(200,prescaler, period);
			}
			else{
				if(is_button_pressed_1s(0)){
					modebuttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if(!is_button_pressed(0)){
				modebuttonState = BUTTON_RELEASED;
			}
			break;
		}
	}
}

void fsm_for_increasing_button(uint32_t prescaler, uint32_t period)
{
	if(flag_but_cooldown==1)
	{
		switch(increasebuttonState){
		case BUTTON_HOLD:
			break;
		case BUTTON_RELEASED:
			if(is_button_pressed(1)){
				increasebuttonState= BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(1)){
				increasebuttonState= BUTTON_RELEASED;
				incRoad1SEG++;
				if(incRoad1SEG>99) incRoad1SEG=1;
				updatenumSEG(incRoad1SEG,1);
				setButtonCooldownTimer(200,prescaler, period);
			}
			else{
				if(is_button_pressed_1s(1)){
					increasebuttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if(!is_button_pressed(1)){
				increasebuttonState = BUTTON_RELEASED;
			}
			else{
				if(incRoad1SEG>99) incRoad1SEG=0;
				updatenumSEG(incRoad1SEG++,1);
				setButtonCooldownTimer(1000,prescaler, period);
			}
			break;
		}
	}
}

void fsm_for_set_button(uint32_t prescaler, uint32_t period)
{
	if(flag_but_cooldown==1)
		{
			switch(setbuttonState){
			case BUTTON_HOLD:
				break;
			case BUTTON_RELEASED:
				if(is_button_pressed(2)){
					setbuttonState= BUTTON_PRESSED;
				}
				break;
			case BUTTON_PRESSED:
				if(!is_button_pressed(2)){
					setbuttonState= BUTTON_RELEASED;
					HAL_GPIO_TogglePin(GPIOB, TEST_Pin);
					setDuration(incRoad1SEG,modeRoad2SEG);
					setButtonCooldownTimer(200,prescaler, period);
				}
				else{
					if(is_button_pressed_1s(2)){
						setbuttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
					}
				}
				break;
			case BUTTON_PRESSED_MORE_THAN_1_SECOND:
				if(!is_button_pressed(2)){
					setbuttonState = BUTTON_RELEASED;
				}
				break;
			}
		}
}

void fsm_for_traffic_light(uint32_t prescaler, uint32_t period)
{
	if(flag_light==1)
	{
		switch (lightstate){
		case HOLD:
			break;
		case RESETALL:
			HAL_GPIO_WritePin(GPIOA, 0x1000,0);
			HAL_GPIO_WritePin(GPIOB, 0x8000,0);
			ini_traffic_flag=0;
			applyDuration();
			lightstate=RED_GREEN;
			break;
		case RED_GREEN:
				HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin,0);
				HAL_GPIO_WritePin(GPIOB, RED2_Pin,0);
				HAL_GPIO_WritePin(GPIOA, RED1_Pin,1);
				HAL_GPIO_WritePin(GPIOB, GREEN2_Pin,1);
				ini_traffic_flag=1;
				if(trafficduration[1][0]==1){
					trafficduration[1][0]=trafficduration[0][1];
					lightstate=RED_YELLOW;
					ini_traffic_flag=0;
					break;
				}
					trafficduration[0][0]--;
					trafficduration[1][0]--;
			updatenumSEG(trafficduration[1][0], 0);
			updatenumSEG(trafficduration[0][0], 1);
			break;
		case RED_YELLOW:
				HAL_GPIO_WritePin(GPIOB, YELLOW2_Pin,1);
				HAL_GPIO_WritePin(GPIOB, GREEN2_Pin,0);
				if(trafficduration[0][0]==1 && trafficduration[1][1]==1){
					trafficduration[0][0]=trafficduration[1][2];
					trafficduration[1][1]=trafficduration[0][2];
					lightstate=GREEN_RED;
					ini_traffic_flag=0;
					break;
				}
					trafficduration[0][0]--;
					trafficduration[1][1]--;
			updatenumSEG(trafficduration[1][1], 0);
			updatenumSEG(trafficduration[0][0], 1);
			break;
		case GREEN_RED:
				HAL_GPIO_WritePin(GPIOA, GREEN1_Pin,1);
				HAL_GPIO_WritePin(GPIOB, RED2_Pin,1);
				HAL_GPIO_WritePin(GPIOA, RED1_Pin,0);
				HAL_GPIO_WritePin(GPIOB, YELLOW2_Pin,0);
				if(trafficduration[0][1]==1){
					lightstate=YELLOW_RED;
					trafficduration[0][1]=trafficduration[1][0];
					ini_traffic_flag=0;
					break;
				}
					trafficduration[0][1]--;
					trafficduration[1][2]--;
			updatenumSEG(trafficduration[1][2], 0);
			updatenumSEG(trafficduration[0][1], 1);
			break;
		case YELLOW_RED:
				HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin,1);
				HAL_GPIO_WritePin(GPIOA, GREEN1_Pin,0);
				if(trafficduration[0][2]==1 && trafficduration[1][2]==1){
					trafficduration[0][2]=trafficduration[1][1];
					trafficduration[1][2]=trafficduration[0][0];
					lightstate=RED_GREEN;
					ini_traffic_flag=0;
					break;
				}
					trafficduration[0][2]--;
					trafficduration[1][2]--;
			updatenumSEG(trafficduration[1][2], 0);
			updatenumSEG(trafficduration[0][2], 1);
			break;
		}
		setLightTimer(1000,prescaler, period);
	}
}

void fsm_for_adjusting_light(uint32_t prescaler, uint32_t period)
{
	switch (adjuststate){
	case ADJUST_HOLD:
		break;
	case ADJUST_RESET:
		HAL_GPIO_WritePin(GPIOB, 0xE000,0);
		HAL_GPIO_WritePin(GPIOA, 0x1C00,0);

		adjuststate=RED;
		break;
	case RED:
		if(flag_adjust_light==1)
		{
			HAL_GPIO_TogglePin(GPIOA, RED1_Pin);
			HAL_GPIO_TogglePin(GPIOB, RED2_Pin);
			setAdjustLightTimer(250,prescaler, period);
		}
		break;
	case YELLOW:
		if(flag_adjust_light==1)
		{
			HAL_GPIO_WritePin(GPIOA, RED1_Pin,0);
			HAL_GPIO_WritePin(GPIOB, RED2_Pin,0);
			HAL_GPIO_TogglePin(GPIOA, YELLOW1_Pin);
			HAL_GPIO_TogglePin(GPIOB, YELLOW2_Pin);
			setAdjustLightTimer(250,prescaler, period);
		}
		break;
	case GREEN:
		if(flag_adjust_light==1)
		{
			HAL_GPIO_WritePin(GPIOA, YELLOW1_Pin,0);
			HAL_GPIO_WritePin(GPIOB, YELLOW2_Pin,0);
			HAL_GPIO_TogglePin(GPIOA, GREEN1_Pin);
			HAL_GPIO_TogglePin(GPIOB, GREEN2_Pin);
			setAdjustLightTimer(250,prescaler, period);
		}
		break;
	}
}

void updatenumSEG(int num,int seg)
{
	if(num<10){
		numSEG[seg][0]=0;
		numSEG[seg][1]=num;
	}
	if(num>=10){
		numSEG[seg][0]=num/10;
		numSEG[seg][1]=num-((num/10)*10);
	}
}


void updateSEG(uint32_t prescaler, uint32_t period)
{
	if(flag_seg1==1&&led_ini_flag==1)
	{
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, EN11_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, EN12_Pin, 0);
		switch(led_scan_flag){
		case 0:
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, 1);
			HAL_GPIO_WritePin(GPIOB, EN11_Pin, 1);
			led_scan_flag=1;
			displaySEG1(numSEG[0][1]);
			displaySEG2(numSEG[1][1]);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, 1);
			HAL_GPIO_WritePin(GPIOB, EN12_Pin, 1);
			displaySEG1(numSEG[0][0]);
			displaySEG2(numSEG[1][0]);
			led_scan_flag=0;
			break;
		}
		setSEG1Timer(100, prescaler, period);
	}
	else{
		led_ini_flag=1;
	}
}


void displaySEG2(int num)
{
	HAL_GPIO_WritePin(GPIOA, seg2[10],0);
	HAL_GPIO_TogglePin(GPIOA, seg2[num]);
}

void displaySEG1(int num)
{
	HAL_GPIO_WritePin(GPIOB, seg1[10],0);
	HAL_GPIO_TogglePin(GPIOB, seg1[num]);
}






