/*
 * Blumenbewaesserung.cpp
 *
 * Created: 04.11.2018 16:27:17
 * Author : Bastian Reul
 * This Code should automatically "bewässern" th Plant in my bureau.
 * By the way, it should teach me, how to use github
 */ 

#include <avr/io.h>
#include "Pin_ATMEGA328_V0_1.h"

#ifndef F_CPU
#define F_CPU 16000000UL				// CPU Takt
#endif


int main(void)
{
	Pin BuildInLed('B', 6, true);
	
    /* Replace with your application code */
	BuildInLed.setze_Status(true);
    while (1) 
    {
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
