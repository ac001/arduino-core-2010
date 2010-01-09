/*
  String getBytes() function demo
 
 Demonstrates the getBytes function of the String library. 
 
 To test it, send the microcontroller some characters. 
 
 by Tom Igoe
 created 8 Feb 2009
 */


#include <WString.h>                // include the String library


#include "WProgram.h"
void setup();
void loop ();
String colorString = String(3);       // allocate a new String

void setup() {
  // open the serial port:
  Serial.begin(9600);
  // Say hello:
  Serial.print("String Library version: ");
  Serial.println(colorString.version());
}

void loop () {
 int red = analogRead(0)/4;
 colorString.setCharAt(0, red);
 int green = analogRead(1)/4;
  colorString.setCharAt(1, green);
 int blue = analogRead(2)/4;
  colorString.setCharAt(2, blue);
 
 // print the string:
 Serial.println(colorString);
 
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

