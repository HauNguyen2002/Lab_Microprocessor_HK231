/*
 * Timer.h
 *
 *  Created on: Sep 10, 2023
 *      Author: ASUS
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

int timerflag=0;
int counter;



void setTimer(int num)
{
	timerflag=0;
	counter=num;
}

void timerRun()
{
	if(counter==0) timerflag=1;
	counter--;
}



#endif /* INC_TIMER_H_ */
