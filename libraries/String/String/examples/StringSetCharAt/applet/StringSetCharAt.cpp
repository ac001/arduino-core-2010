/*
  String getBytes() function demo
 
 Demonstrates the getBytes function of the String library. 
 
 To test it, send the microcontroller some characters. 
 
 by Tom Igoe
 created 8 Feb 2009
 */


#include <WString.h>                // include the String library


#define maxLength 30

#include "WProgram.h"
void setup();
void loop ();
String nameString = String(maxLength);       // allocate a new String
int characterPosition = 4;                 // where the input characters will be added

void setup() {
  // open the serial port:
  Serial.begin(9600);
  // Say hello:
  Serial.print("String Library version: ");
  Serial.println(nameString.version());
  // give the string an initial value:
nameString = "***                        ***";
}

void loop () {
  if(Serial.available() > 0) {
    // read the incoming data as a char:
    char inChar = Serial.read();
     nameString.setCharAt(characterPosition, inChar);
   if (characterPosition < 25 ) {
     characterPosition++; 
   } else {
    characterPosition = 4; 
   }
     
    
  
    Serial.println(nameString);
  }

}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

