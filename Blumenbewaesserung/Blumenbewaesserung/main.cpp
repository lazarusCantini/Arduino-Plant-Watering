/*
 * Blumenbewaesserung.cpp
 *
 * Created: 04.11.2018 16:27:17
 * Author : Bastian Reul
 * This Code should automatically "bewässern" th Plant in my bureau.
 * By the way, it should teach me, how to use github
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL				// CPU Takt
#endif

#include <avr/io.h>
#include "Pin_ATMEGA328.h"
#include <util/delay.h>

#include <avr/interrupt.h>

//Variablen für die Zeit
volatile unsigned int millisekunden = 0;
volatile unsigned int sekunde = 0;
volatile unsigned int minute = 0;
volatile unsigned int stunde = 0;


//Sensor is High wenn Dry

__attribute__((optimize(0)))
int main(void)
{
	TCCR0A |= (1 << COM0A1);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	 // ((1000000/8)/1000) = 125
	 OCR0A = 125-1;
	 
	   // Compare Interrupt erlauben
	   TIMSK0 |= (1<<OCIE0A);
	   
	  // Global Interrupts aktivieren
	  sei();
	   
	Pin WateringPump('C', 5, false);
	Pin PoweringHumidMeter ('C', 4, false);
	Pin PlantToDry('C', 3, true);
	
    //Init all	WateringPump.setze_Status(false);
	PoweringHumidMeter.setze_Status(false);
	WateringPump.setze_Status(true);
	
    while (1) 
    {
		//_delay_ms(1000);
		//WateringPump.toggle_Pin();
		if (stunde % 4 == 0)
		{
			if ((minute == 0) && (sekunde < 2))
			{
				PoweringHumidMeter.setze_Status(true);
				//_delay_ms(2000);
			}
			else
			{
				if ((minute < 1) && (PlantToDry.lese_status()))
				{
					WateringPump.setze_Status(false);
				}
				else
				{
					WateringPump.setze_Status(true);
					PoweringHumidMeter.setze_Status(false);
				}
			}

		}
    }
}



/*
Der Compare Interrupt Handler
wird aufgerufen, wenn
TCNT0 = OCR0A = 125-1
ist (125 Schritte), d.h. genau alle 1 ms
*/
ISR (TIMER0_COMPA_vect)
{
	millisekunden++;
	if(millisekunden == 1000)
	{
		sekunde++;
		millisekunden = 0;
		if(sekunde == 60)
		{
			minute++;
			sekunde = 0;
		}
		if(minute == 60)
		{
			stunde++;
			minute = 0;
		}
		if(stunde == 24)
		{
			stunde = 0;
		}
	}
}
