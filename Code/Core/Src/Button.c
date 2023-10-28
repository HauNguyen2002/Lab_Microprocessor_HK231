/*
 * Button.c
 *
 *  Created on: Sep 24, 2023
 *      Author: ASUS
 */

#include "main.h"


#define NO_OF_BUTTONS		3
#define DURATION_FOR_AUTO_INCREASING	100
#define BUTTON_IS_PRESSED				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED				GPIO_PIN_SET

int Buttons[NO_OF_BUTTONS]={But1_Pin,But2_Pin,But3_Pin};
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1 [ NO_OF_BUTTONS ];
static GPIO_PinState debounceButtonBuffer2 [ NO_OF_BUTTONS ];

static uint8_t flagForButtonPress1s [ NO_OF_BUTTONS ];

static uint16_t counterForButtonPress1s [ NO_OF_BUTTONS ];


void button_reading(void){
	for(char i=0;i< NO_OF_BUTTONS;i++){
		debounceButtonBuffer2[i]=debounceButtonBuffer1[i];
		debounceButtonBuffer1[i]= HAL_GPIO_ReadPin(GPIOA, Buttons[i]);
		if(debounceButtonBuffer1[i]==debounceButtonBuffer2[i]) buttonBuffer[i]= debounceButtonBuffer1[i];

		if(buttonBuffer[i]==BUTTON_IS_PRESSED){
			if(counterForButtonPress1s[i]<DURATION_FOR_AUTO_INCREASING){
				counterForButtonPress1s[i]++;
				}
			else{
					flagForButtonPress1s[i]=1;
				}
		}
		else{
			counterForButtonPress1s[i]=0;
			flagForButtonPress1s[i]=0;
		}
	}
}

unsigned char is_button_pressed(uint8_t index){
	if(index>=NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index){
	if(index>= NO_OF_BUTTONS) return 0xff;
	return (flagForButtonPress1s[index] == 1);
}
