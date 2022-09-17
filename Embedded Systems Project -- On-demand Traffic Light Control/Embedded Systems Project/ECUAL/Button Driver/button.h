/*
 * button.h
 *
 * Created: 2022-09-05 3:39:25 AM
 *  Author: Moataz Elbayaa
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "..\..\MCAL\DIO Driver\DIO.h"

//Pedestrians Button
#define PEDESTRIANS_BUTTON_PORT PORT_D
#define PEDESTRIANS_BUTTON_PIN PIN2

//Button States
#define LOW 0
#define HIGH 1

//initializing the button
void BUTTON_init(uint8_t buttonPort, uint8_t buttonPin);

//read the button
void BUTTON_read(uint8_t buttonPort, uint8_t buttonPin, uint8_t *value);



#endif /* BUTTON_H_ */