/*
 * LEDs.c
 *
 * Created: 2022-09-05 3:54:39 AM
 *  Author: Moataz Elbayaa
 */ 
#include "LEDs.h"


/************************************************************************/
/*                    Functions definitions                             */
/************************************************************************/

void LED_init(uint8_t ledPort, uint8_t ledPin) //LED is an output device
{
	DIO_init(ledPort, ledPin, OUT); //LED is an output device, so we will initialize it as output
}
void LED_on(uint8_t ledPort, uint8_t ledPin)
{
	DIO_write(ledPort, ledPin, HIGH);
}
void LED_off(uint8_t ledPort, uint8_t ledPin)
{
	DIO_write(ledPort, ledPin, LOW);
}
void LED_toggle(uint8_t ledPort, uint8_t ledPin)
{
	DIO_toggle(ledPort, ledPin);
}
uint8_t LED_status(uint8_t ledPort, uint8_t ledPin)
{
	uint8_t ledStatus;
	DIO_read(ledPort, ledPin, &ledStatus);
	return ledStatus;
}

