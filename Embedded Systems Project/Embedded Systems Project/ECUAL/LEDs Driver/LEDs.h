/*
 * LEDs.h
 *
 * Created: 2022-09-05 3:54:23 AM
 *  Author: Moataz Elbayaa
 */ 


#ifndef LEDS_H_
#define LEDS_H_

#include "..\..\MCAL\DIO Driver\DIO.h"

//LEDs for cars
#define carsGreen_LED_PORT PORT_A
#define carsGreen_LED_PIN PIN0

#define carsYellow_LED_PORT PORT_A
#define carsYellow_LED_PIN PIN1

#define carsRed_LED_PORT PORT_A
#define carsRed_LED_PIN PIN2

//LEDs for pedestrians
#define pedestriansGreen_LED_PORT PORT_B
#define pedestriansGreen_LED_PIN PIN0

#define pedestriansYellow_LED_PORT PORT_B
#define pedestriansYellow_LED_PIN PIN1

#define pedestriansRed_LED_PORT PORT_B
#define pedestriansRed_LED_PIN PIN2

//Value Defines
#define ON 1
#define OFF 0

void LED_init(uint8_t ledPort, uint8_t ledPin); //Initialize LED pin Direction
void LED_on(uint8_t ledPort, uint8_t ledPin);//Turn on the LED
void LED_off(uint8_t ledPort, uint8_t ledPin);//Turn off the LED
void LED_toggle(uint8_t ledPort, uint8_t ledPin);//Toggle the LED
uint8_t LED_status(uint8_t ledPort, uint8_t ledPin);//Toggle the LED



#endif /* LEDS_H_ */