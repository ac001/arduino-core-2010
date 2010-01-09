/*
 * Description:
 * Flash an LED using the DigitalToggle library.
 *
 * The digitalToggle() function toggles the state of the
 * specified digital output pin without needing to know the
 * current state of the pin. It does this by writing to the
 * PIN register instead of using digitalWrite() which uses
 * the PORT register.
 * 
 * The pin can be toggled by calling digitalWrite and
 * alternating the state of the pin. This produces an
 * output with a 7.4uS period, or ~135kHz and takes
 * 10 bytes per call (20 per toggle):
 *
 *    digitalWrite(ledPin,HIGH);  
 *    digitalWrite(ledPin,LOW);  
 *
 * The pin can be toggled by calling digitalToggle. This
 * produces an output with a 5.1uS period, or ~196kHz and
 * takes 8 bytes per toggle.
 * 
 *    digitalToggle(ledPin);
 *
 * The pin can be toggle by calling digitalToggleFast.
 * This produces an output with a 4.1uS period, or 244kHz
 * and takes 44 bytes per call.
 * 
 *    digitalToggleFast(ledPin);
 *
 */
#include <DigitalToggle.h>

#include "WProgram.h"
void setup();
void loop();
int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop(){
  delay(500);
  digitalToggle(ledPin);
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

