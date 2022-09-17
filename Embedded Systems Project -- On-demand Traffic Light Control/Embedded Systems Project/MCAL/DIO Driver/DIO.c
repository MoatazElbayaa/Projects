/*
 * DIO.c
 *
 * Created: 2022-09-05 3:28:19 AM
 *  Author: Moataz Elbayaa
 */ 

//include .h
#include "DIO.h"

/************************************************************************/
/*                    Functions definitions                             */
/************************************************************************/

void DIO_init(uint8_t portNumber, uint8_t pinNumber, uint8_t direction)
{
	switch(portNumber)
	{
		case PORT_A:
			if (direction==IN)
			{
				DDRA &=~(1<<pinNumber);//Input
			}
			else if(direction==OUT)
			{
				DDRA |=(1<<pinNumber);//Output
			}
			else
			{
				//Error handling Technique
			}
		break;
		
		case PORT_B:
		if (direction==IN)
		{
			DDRB &=~(1<<pinNumber);//Input
		}
		else if(direction==OUT)
		{
			DDRB |=(1<<pinNumber);//Output
		}
		else
		{
			//Error handling Technique
		}
		break;
		
		case PORT_C:
		if (direction==IN)
		{
			DDRC &=~(1<<pinNumber);//Input
		}
		else if(direction==OUT)
		{
			DDRC |=(1<<pinNumber);//Output
		}
		else
		{
			//Error handling Technique
		}
		break;
		
		case PORT_D:
		if (direction==IN)
		{
			DDRD &=~(1<<pinNumber);//Input
		}
		else if(direction==OUT)
		{
			DDRD |=(1<<pinNumber);//Output
		}
		else
		{
			//Error handling Technique
		}
		break;		
	}
}
void DIO_write(uint8_t portNumber, uint8_t pinNumber, uint8_t value)
{
	switch(portNumber)
	{
		case PORT_A:
		if (value==LOW)
		{
			PORTA &=~(1<<pinNumber);//Write 0
		}
		else if(value==HIGH)
		{
			PORTA |=(1<<pinNumber);//Write 1
		}
		else
		{
			//Error handling Technique
		}
		break;
		
		case PORT_B:
		if (value==LOW)
		{
			PORTB &=~(1<<pinNumber);//Write 0
		}
		else if(value==HIGH)
		{
			PORTB |=(1<<pinNumber);//Write 1
		}
		else
		{
			//Error handling Technique
		}
		break;
		
		case PORT_C:
		if (value==LOW)
		{
			PORTC &=~(1<<pinNumber);//Write 0
		}
		else if(value==HIGH)
		{
			PORTC |=(1<<pinNumber);//Write 1
		}
		else
		{
			//Error handling Technique
		}
		break;
		
		case PORT_D:
		if (value==LOW)
		{
			PORTD &=~(1<<pinNumber);//Write 0
		}
		else if(value==HIGH)
		{
			PORTD |=(1<<pinNumber);//Write 1
		}
		else
		{
			//Error handling Technique
		}
		break;
	}
}

void DIO_toggle(uint8_t portNumber, uint8_t pinNumber)
{
	uint8_t pinState;
	DIO_read(portNumber,pinNumber,&pinState);
	if(pinState == HIGH)
	{
		DIO_write(portNumber,pinNumber,LOW);
	}
	else if (pinState == LOW)
	{
		DIO_write(portNumber,pinNumber,HIGH);
	}
}

void DIO_read(uint8_t portNumber, uint8_t pinNumber, uint8_t *value)
{
	switch(portNumber)
	{
		case PORT_A:
		*value = (PINA & (1<<pinNumber))>>pinNumber; // get state -> read bit 0 or 1
		break;
		
		case PORT_B:
		*value = (PINB & (1<<pinNumber))>>pinNumber; // get state -> read bit 0 or 1
		break;
		
		case PORT_C:
		*value = (PINC & (1<<pinNumber))>>pinNumber; // get state -> read bit 0 or 1
		break;
		
		case PORT_D:
		*value = (PIND & (1<<pinNumber))>>pinNumber; // get state -> read bit 0 or 1
		break;
	}
}

