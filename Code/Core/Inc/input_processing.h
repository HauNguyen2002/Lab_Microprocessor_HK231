/*
 * input_reading.h
 *
 *  Created on: Sep 25, 2023
 *      Author: ASUS
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

void button_reading(void);
void fsm_for_increasing_button(uint32_t prescaler, uint32_t period);
void fsm_for_mode_button(uint32_t prescaler, uint32_t period);
void fsm_for_set_button(uint32_t prescaler, uint32_t period);
void fsm_for_traffic_light(uint32_t prescaler, uint32_t period);
void fsm_for_adjusting_light(uint32_t prescaler, uint32_t period);
static uint8_t seg1[11]={0xC0,0xF9,0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,0xFF};
static uint8_t seg2[11]={0xC0,0xF9,0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,0xFF};

void updateSEG(uint32_t prescaler, uint32_t period);
void updatenumSEG();
void displaySEG1();
void displaySEG2();
void changeAutoTrafficLights(int state);
void changeBlinkTrafficLights(int state);

#endif /* INC_INPUT_PROCESSING_H_ */
