/*
 * Segment.h
 *
 *  Created on: Sep 25, 2023
 *      Author: ASUS
 */

#ifndef INC_SEGMENT_H_
#define INC_SEGMENT_H_

#include "main.h"
static uint8_t seg1[11]={0xC0,0xF9,0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,0xFF};

void updateSEG1();
void displaySEG1();

#endif /* INC_SEGMENT_H_ */
