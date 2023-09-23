/*
 * Timer.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ASUS
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

int TIMER_CYCLE=10;

int timer_counter=0;
int timer_flag=0;

int scan_timer_counter=0;
int scan_timer_flag=0;

int matrix_timer_counter=0;
int matrix_timer_flag=0;

int shift_timer_counter=0;
int shift_timer_flag=0;

void scansetTimer(int duration)
{
	scan_timer_counter=duration/TIMER_CYCLE;
	scan_timer_flag=0;
}

void scantimerRun()
{
	if(scan_timer_counter==0) scan_timer_flag=1;
	if(scan_timer_counter>0) scan_timer_counter--;
}

void setTimer(int duration)
{
	timer_counter=duration/TIMER_CYCLE;
	timer_flag=0;
}

void timerRun()
{
	if(timer_counter==0) timer_flag=1;
	if(timer_counter>0) timer_counter--;
}

void matrixsetTimer(int duration)
{
	matrix_timer_counter=duration/TIMER_CYCLE;
	matrix_timer_flag=0;
}

void matrixtimerRun()
{
	if(matrix_timer_counter==0) matrix_timer_flag=1;
	if(matrix_timer_counter>0) matrix_timer_counter--;
}

void shiftsetTimer(int duration)
{
	shift_timer_counter=duration/TIMER_CYCLE;
	shift_timer_flag=0;
}

void shifttimerRun()
{
	if(shift_timer_counter==0) shift_timer_flag=1;
	if(shift_timer_counter>0) shift_timer_counter--;
}



#endif /* INC_TIMER_H_ */
