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
	
    while (1) 
    {
		//_delay_ms(1000);
		//WateringPump.toggle_Pin();
		if (stunde % 4 == 0)
		{
			if (minute == 0)
			{
				PoweringHumidMeter.setze_Status(true);
				_delay_ms(2000);
			}

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

/*

*/
/*
// Hardwire Set-Up
const int pumpPin =  1;// Number of the Pin where the Relay fot the pump is attached
const int CheckUpLed = 2; //Number of the Check-UP Led. The moisture measurement is not constant. Measuring two times a day will do the Job. When doing a measurement, switch this LED on

bool CheckUpLedState = false;
bool pumpState = false;
bool moistureToDry = false;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000*60;           // for testing purpose measuring moisture every 60 seconds

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}
*/
