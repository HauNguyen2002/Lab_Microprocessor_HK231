/*
 * Timer.h
 *
 *  Created on: Sep 18, 2023
 *      Author: ASUS
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

int timer_flag=0;
int timercounter=0;

void setTimer(int duration)
{
	timercounter=duration;
	timer_flag=0;
}

void timerRun()
{
	if(timercounter==0) timer_flag=1;
	if(timercounter>0) timercounter--;
}



#endif /* INC_TIMER_H_ */
