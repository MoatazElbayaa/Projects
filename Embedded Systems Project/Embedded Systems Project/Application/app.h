/*
 * app.h
 *
 * Created: 2022-09-05 3:04:53 AM
 *  Author: Moataz Elbayaa
 */ 
#ifndef APP_H_
#define APP_H_

#include "..\ECUAL\LEDs Driver\LEDs.h"
#include "..\ECUAL\Button Driver\button.h"
#include "..\MCAL\Interrupt Library\Interrupt.h"

//Value Defines
#define HALF_SECOND 1954 //NUMBER_OF_OVERFLOWS_0.5_SECOND
#define FIVE_SECONDS 19541 //NUMBER_OF_OVERFLOWS_5_SECONDS

//Value Defines
#define cars 0
#define pedestrians 1
#define cars_and_pedestrians 2

void App_init(void);
void App_start(void);
void delay(uint16_t NUMBER_OF_OVERFLOWS);
void normalMode(void);
void pedestrianMode(void);
void yellowLED_Blinking(uint8_t val);

#endif /* APP_H_ */