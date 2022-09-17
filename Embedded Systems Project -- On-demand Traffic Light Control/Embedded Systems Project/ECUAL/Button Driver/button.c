/*
 * button.c
 *
 * Created: 2022-09-05 3:39:08 AM
 *  Author: Moataz Elbayaa
 */ 
#include "button.h"

/************************************************************************/
/*                    Functions definitions                             */
/************************************************************************/

void BUTTON_init(uint8_t buttonPort, uint8_t buttonPin) //Button is an input device
{
	DIO_init(buttonPort,buttonPin,IN); //Button is an input device, so we will initialize it as input
}
void BUTTON_read(uint8_t buttonPort, uint8_t buttonPin, uint8_t *value)
{
	DIO_read(buttonPort,buttonPin, value);
}