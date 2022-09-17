/*
 * DIO.h
 *
 * Created: 2022-09-05 3:23:41 AM
 *  Author: Moataz Elbayaa
 */ 


#ifndef DIO_H_
#define DIO_H_

//include registers.h
#include "..\..\Utilities\registers.h"

//All driver macros
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'

//Ports Pins
#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

//Direction Defines
#define IN 0
#define OUT 1

//Value Defines
#define LOW 0
#define HIGH 1

//All driver function prototypes
void DIO_init(uint8_t portNumber, uint8_t pinNumber, uint8_t direction); //Initialize DIO pin Direction
void DIO_write(uint8_t portNumber, uint8_t pinNumber, uint8_t value);//write data to DIO Pin
void DIO_toggle(uint8_t portNumber, uint8_t pinNumber);//toggle DIO pin
void DIO_read(uint8_t portNumber, uint8_t pinNumber, uint8_t *value);//Read DIO pin



#endif /* DIO_H_ */