/*
 * Timer.h
 *
 *  Created on: Sep 25, 2023
 *      Author: ASUS
 */

#include "main.h"
#include "Button.h"

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define INTERNAL_CLOCK	8000000



int counter_seg1=0;
int counter_light=0;
int counter_button_cooldown=0;
int counter_adjust_light=0;

static int flag_seg1=1;
static int flag_light=1;
static int flag_but_cooldown=1;
static int flag_adjust_light=1;


int getDuration(uint32_t duration,uint32_t prescaler, uint32_t period)
{
	return duration/((((prescaler*1.0+1)*(period+1))/INTERNAL_CLOCK)*1000);
}

void setSEG1Timer(int duration,uint32_t prescaler, uint32_t period){
	counter_seg1=getDuration(duration,prescaler,period);
	flag_seg1=0;

}

void timerseg1Run()
{
	if(counter_seg1==0) flag_seg1=1;
	if(counter_seg1>0) counter_seg1--;
}

void setLightTimer(int duration,uint32_t prescaler, uint32_t period){
	flag_light=0;
	counter_light=getDuration(duration,prescaler,period);
}

void timerLightRun()
{
	if(counter_light==0) flag_light=1;
	if(counter_light>0) counter_light--;
}

void setAdjustLightTimer(int duration,uint32_t prescaler, uint32_t period){
	flag_adjust_light=0;
	counter_adjust_light=getDuration(duration,prescaler,period);
}

void timerAdjustLightRun()
{
	if(counter_adjust_light==0) flag_adjust_light=1;
	if(counter_adjust_light>0) counter_adjust_light--;
}

void setButtonCooldownTimer(int duration,uint32_t prescaler, uint32_t period){
	flag_but_cooldown=0;
	counter_button_cooldown=getDuration(duration,prescaler,period);
}

void timerButtonCooldownRun()
{
	if(counter_button_cooldown==0) flag_but_cooldown=1;
	if(counter_button_cooldown>0) counter_button_cooldown--;
}

#endif /* INC_TIMER_H_ */
