/*
 * registers.h
 *
 * Created: 2022-09-05 3:17:22 AM
 *  Author: Moataz Elbayaa
 */ 
#ifndef REGISTERS_H_
#define REGISTERS_H_

//include types.h
#include "types.h"

/************************************************************************/
/*               DIO Registers                                          */
/************************************************************************/

//PORTA registers
#define PORTA *((volatile uint8_t*)0x3B)
#define DDRA *((volatile uint8_t*)0x3A)
#define PINA *((volatile uint8_t*)0x39)

//PORTB registers
#define PORTB *((volatile uint8_t*)0x38)
#define DDRB *((volatile uint8_t*)0x37)
#define PINB *((volatile uint8_t*)0x36)

//PORTC registers
#define PORTC *((volatile uint8_t*)0x35)
#define DDRC *((volatile uint8_t*)0x34)
#define PINC *((volatile uint8_t*)0x33)

//PORTC registers
#define PORTD *((volatile uint8_t*)0x32)
#define DDRD *((volatile uint8_t*)0x31)
#define PIND *((volatile uint8_t*)0x30)

/************************************************************************/
/* Timer0 Registers                                                     */
/************************************************************************/

#define TCNT0 *((volatile uint8_t*)0x52) // Timer/Counter 0 ->8bits
#define TCCR0 *((volatile uint8_t*)0x53)
#define TIFR *((volatile uint8_t*)0x58)

/************************************************************************/
/* Interrupt Registers and bits                                         */
/************************************************************************/

#define MCUCR *((volatile uint8_t*)0x55)
#define MCUCSR *((volatile uint8_t*)0x54)
#define GICR *((volatile uint8_t*)0x5B)
#define GIFR *((volatile uint8_t*)0x5A)

/* Bit numbers */

/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5
#define IVSEL   1
#define IVCE    0

/* GIFR */
#define INTF1   7
#define INTF0   6
#define INTF2   5

/* MCUCR */
#define SE      7
#define SM2     6
#define SM1     5
#define SM0     4
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

/* MCUCSR */
#define JTD     7
#define ISC2    6
/* bit 5 reserved */
#define JTRF    4
#define WDRF    3
#define BORF    2
#define EXTRF   1
#define PORF    0

#endif /* REGISTERS_H_ */