/*
 * app.c
 *
 * Created: 2022-09-05 3:04:31 AM
 *  Author: Moataz Elbayaa
 */ 

//include app.h
#include "app.h"

/************************************************************************/
/*                        Global Variables                              */
/************************************************************************/
uint8_t carsYellow_LED_status = OFF;
uint8_t ISR_Flag=0;
uint8_t i=1;
uint16_t overflowCounter = 0;

/*This flag will be used to prevent returning back to Cars Red LED On again ,
if the pedestrians Button has been clicked while the cars Yellow LED is on during switching from RED to Green*/
uint8_t carsYellow_backwords_flag=0;


/************************************************************************/
/*                    Functions definitions                             */
/************************************************************************/

/************************************************************************/
/* App_start function is starting and loops in the Normal Mode          */
/************************************************************************/
void App_start(void)
{
	while (1)
	{
		LED_off(carsYellow_LED_PORT,carsYellow_LED_PIN);
		LED_off(carsRed_LED_PORT,carsRed_LED_PIN);
		LED_on(carsGreen_LED_PORT, carsGreen_LED_PIN);
		LED_on(pedestriansRed_LED_PORT,pedestriansRed_LED_PIN);
		if(ISR_Flag==1)
		{
			ISR_Flag =0;
			continue;
		}
		delay(FIVE_SECONDS);
		
		if(ISR_Flag==1)
		{
			ISR_Flag =0;
			continue;
		}
		LED_off(carsGreen_LED_PORT, carsGreen_LED_PIN);
		
		carsYellow_backwords_flag=0;
		yellowLED_Blinking(cars);
		
		
		if(ISR_Flag==1)
		{
			ISR_Flag =0;
			continue;
		}
		LED_off(carsYellow_LED_PORT,carsYellow_LED_PIN);
		LED_on(carsRed_LED_PORT,carsRed_LED_PIN);
		if(ISR_Flag==1)
		{
			ISR_Flag =0;
			continue;
		}
		delay(FIVE_SECONDS);
		
		LED_off(carsRed_LED_PORT,carsRed_LED_PIN);
		
		carsYellow_backwords_flag=1;
		yellowLED_Blinking(cars);
	}
}

/************************************************************************/
/* App_init function is sets the system to its initial state            */
/************************************************************************/
void App_init(void)
{
	//Set pedestrians button direction to be input
	BUTTON_init(PEDESTRIANS_BUTTON_PORT,PEDESTRIANS_BUTTON_PIN);
	
	//Set All LEDs to be output
	LED_init(carsGreen_LED_PORT,carsGreen_LED_PIN);
	LED_init(carsYellow_LED_PORT,carsYellow_LED_PIN);
	LED_init(carsRed_LED_PORT,carsRed_LED_PIN);
	LED_init(pedestriansGreen_LED_PORT,pedestriansGreen_LED_PIN);
	LED_init(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
	LED_init(pedestriansRed_LED_PORT,pedestriansRed_LED_PIN);
	
	/************************************************************************/
	/* Initialization of Interrupt                                          */
	/************************************************************************/
	//Enable global interrupts - by setting bit 7 in the status register to 1
	sei();
	
	//Choose the external interrupt sense - sense on rising edge
	MCUCR |= (1<<ISC00)|(1<<ISC01);
	
	//Enable External interrupt 0 - INT0
	GICR |= (1<<INT0);
	
	/************************************************************************/
	/* Initialization of Timer0                                             */
	/************************************************************************/
	//Choose Timer mode
	TCCR0 = 0x00; //Normal Mode
	//Set Timer initial value
	TCNT0 = 0x00;
	// Timer start -> setting the clock source
	TCCR0 |= (1<<0); //No Prescaler
	
	
	//Turn All LEDs off
	LED_off(carsGreen_LED_PORT,carsGreen_LED_PIN);
	LED_off(carsYellow_LED_PORT,carsYellow_LED_PIN);
	LED_off(carsRed_LED_PORT,carsRed_LED_PIN);
	LED_off(pedestriansGreen_LED_PORT,pedestriansGreen_LED_PIN);
	LED_off(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
	LED_off(pedestriansRed_LED_PORT,pedestriansRed_LED_PIN);
}

/************************************************************************/
/* yellowLED_Blinking function is used for                              */
/* controlling Blinking of Yellow Lights        */
/************************************************************************/
void yellowLED_Blinking(uint8_t val)
{
	switch(val)
	{
		case cars:
		{
			carsYellow_LED_status=ON;
			
			for(; i<=5; ++i)
			{
				LED_on(carsYellow_LED_PORT,carsYellow_LED_PIN);
				if(ISR_Flag==1) //After executing the ISR and return back, if the Normal mode was in yellow Blinking, then we will break from it
				{
					break;
				}
				delay(HALF_SECOND);
				
				LED_off(carsYellow_LED_PORT,carsYellow_LED_PIN);
				if(ISR_Flag==1)
				{
					break;
				}
				delay(HALF_SECOND);
			}
			i=1;
			carsYellow_LED_status=OFF;
			break;
		}
		
		case pedestrians:
		{
			for(; i<=5; ++i)
			{
				LED_on(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
				if(ISR_Flag==1)
				{
					break;
				}
				delay(HALF_SECOND);
				
				LED_off(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
				if(ISR_Flag==1)
				{
					break;
				}
				delay(HALF_SECOND);
			}
			i=1;
			break;
		}
		
		case cars_and_pedestrians:
		{
			for(; i<=5; ++i)
			{
				LED_on(carsYellow_LED_PORT,carsYellow_LED_PIN);
				LED_on(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
				if(ISR_Flag==1)
				{
					break;
				}
				delay(HALF_SECOND);
				
				LED_off(carsYellow_LED_PORT,carsYellow_LED_PIN);
				LED_off(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
				if(ISR_Flag==1)
				{
					break;
				}
				delay(HALF_SECOND);
			}
			i=1;
			carsYellow_LED_status=OFF;
			break;
		}
		
		default:
			break;
	}
}

/************************************************************************/
/* ISR ( Interrupt Serves Routine), it will call the pedestrianMode     */
/************************************************************************/
ISR(EXT_INT_0)
{
	pedestrianMode();
	//setting the ISR_Flag to 1, to indicate that the ISR has been executed and to not complete the delay from the normal mode after the  ISR
	ISR_Flag=1;
}

/************************************************************************/
/* pedestrianMode function is the function of how the system will act   */
/* after clicking the pedestrians crosswalk button                      */
/************************************************************************/
void pedestrianMode(void)
{
	/************************************************************************************/
	/* Change from normal mode to pedestrian mode when the pedestrian button is pressed */
	/************************************************************************************/
	
	//If pressed when the cars' Red LED is on
	if( LED_status(carsRed_LED_PORT,carsRed_LED_PIN) == ON )
	{
		//the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds
		//cars' Red LED is already ON
		LED_off(pedestriansRed_LED_PORT,pedestriansRed_LED_PIN);
		LED_on(pedestriansGreen_LED_PORT,pedestriansGreen_LED_PIN);
		
		delay(FIVE_SECONDS);
	}
	/*If pressed when the cars' Green LED is on or the cars' Yellow LED is blinking,the pedestrian Red LED will be on 
	then both Yellow LEDs start to blink for five seconds, 
	then the cars' Red LED and pedestrian Green LEDs are on for five seconds, 
	this means that pedestrian must wait until the Green LED is on.*/
	else if(LED_status(carsGreen_LED_PORT,carsGreen_LED_PIN)==ON || carsYellow_LED_status==ON)
	{
		if(LED_status(carsGreen_LED_PORT,carsGreen_LED_PIN)==ON)
		{
			//The pedestrian Red LED will be on
			LED_on(pedestriansRed_LED_PORT,pedestriansRed_LED_PIN);
		
			//then both Yellow LEDs start to blink for five seconds
			yellowLED_Blinking(cars_and_pedestrians);
			LED_off(carsGreen_LED_PORT,carsGreen_LED_PIN);
		}
		
		else if(carsYellow_LED_status==ON && carsYellow_backwords_flag == 0)
		{
			//The pedestrian Red LED will be on
			LED_on(pedestriansRed_LED_PORT,pedestriansRed_LED_PIN);
			
			//if the ISR has been called while the main function was within a delay,
			//then we will complete the previous delay till it becomes complete (5 seconds as the cars' Green LED was On)
			yellowLED_Blinking(cars_and_pedestrians);
			
		}
		
		else if(carsYellow_LED_status==ON && carsYellow_backwords_flag == 1)
		{
			//complete the previous delay1st
			yellowLED_Blinking(cars_and_pedestrians);
			
			
			LED_on(carsGreen_LED_PORT, carsGreen_LED_PIN);
			yellowLED_Blinking(pedestrians);
			//delay(FIVE_SECONDS);

			LED_off(carsGreen_LED_PORT, carsGreen_LED_PIN);
			yellowLED_Blinking(cars_and_pedestrians);
			carsYellow_backwords_flag = 0;
		}
		
		
		//After 5 Seconds delay of Yellow LEDs On
		LED_off(carsYellow_LED_PORT,carsYellow_LED_PIN);
		
		//then the cars' Red LED and pedestrian Green LEDs are on for five seconds,
		LED_on(carsRed_LED_PORT,carsRed_LED_PIN);
		
		//
		delay(HALF_SECOND);
		
		LED_off(pedestriansRed_LED_PORT,pedestriansRed_LED_PIN);
		LED_on(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
		
		delay(HALF_SECOND);
		
		LED_off(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
		LED_on(pedestriansGreen_LED_PORT,pedestriansGreen_LED_PIN);
		
		delay(FIVE_SECONDS);
	}
	
	LED_off(carsRed_LED_PORT,carsRed_LED_PIN);
	//both Yellow LEDs start blinking for 5 seconds and the pedestrian's Green LED is still on
	yellowLED_Blinking(cars_and_pedestrians);
	
	// the pedestrian Green LED will be off and both the pedestrian Red LED and the cars' Green LED will be on.
	LED_off(pedestriansGreen_LED_PORT,pedestriansGreen_LED_PIN);
	LED_off(pedestriansYellow_LED_PORT,pedestriansYellow_LED_PIN);
	LED_on(pedestriansRed_LED_PORT,pedestriansRed_LED_PIN);	
}



/************************************************************************/
/* Delay function using Timer0, and it is controlling the delay in      */
/* the (Normal Mode) and continue the delays from Normal Mode when it   */
/* is switching to the ISR: (Pedestrian Mode)                           */
/************************************************************************/

void delay(uint16_t NUMBER_OF_OVERFLOWS)
{
	//checking  ISR_Flag:
	//if ISR_Flag is 1,then this means that we was in ISR and we will change it to 0 
	//and overcome or break from the delay
	if(ISR_Flag==1)
	{
		ISR_Flag=0;
	}
	else
	{
		//Set Timer initial value
		TCNT0 = 0x00;
		
		while(overflowCounter<=NUMBER_OF_OVERFLOWS)
		{
			//Stop after one overflow -> 256 ms
			//Wait until the overflow flag to be set
			while ((TIFR & (1<<0)) == 0); //it will loop until the flag becomes 1
			
			//Clear the overflow flag
			TIFR |= (1<<0);
			
			//checking  ISR_Flag:
			//if ISR_Flag is 1,then this means that we was in ISR and we will change it to 0
			//and overcome or break from the delay
			if(ISR_Flag==1)
			{
				break;
			}
			
			overflowCounter++;
			
		}
		
		//Clear overflowCounter
		overflowCounter=0;
		
		//Timer stop
		TCCR0 = 0x00;
		// Timer start -> setting the clock source
		TCCR0 |= (1<<0); //No Prescaler
	}
	
}
