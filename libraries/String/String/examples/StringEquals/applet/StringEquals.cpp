/*
  String endsWith() function demo
 
 Demonstrates the endsWith function of the String library.
 
 To test it, send the microcontroller some characters ending with "end". 
 
 by Tom Igoe
 created 8 Feb 2009
 */


#include <WString.h>                // include the String library


#define maxLength 30

#include "WProgram.h"
void setup();
void loop ();
void askQuestion();
void getIncomingChars();
String inString = String(maxLength);       // allocate a new String
boolean answerComplete = false;

void setup() {
  // open the serial port:
  Serial.begin(9600);
  // Say hello:
  Serial.print("String Library version: ");
  Serial.println(inString.version());
  askQuestion();
}

void loop () {
  if(Serial.available() > 0) {
    getIncomingChars();
  }

  if (answerComplete == true) {
    if (inString.equals("monkey")) {
      Serial.println();
      Serial.println("That's right, and don't you say otherwise.");
      Serial.println();
      answerComplete = true;
    } 
    else {
      Serial.println("Wrong. Loser."); 
    }
    inString = "";
    askQuestion(); 
  }

}

void askQuestion() {
  Serial.print("What's the coolest animal?"); 
  answerComplete = false;
}

void getIncomingChars() {
  // read the incoming data as a char:
  char inChar = Serial.read();
  // if it's a newline or return, print the string:
  if ((inChar == '\n') || (inChar == '\r')) {
    Serial.println(inString); 
    answerComplete = true;
  } 
  else {
    // if you're not at the end of the string, append
    // the incoming character:
    if (inString.length() < maxLength) {
      inString.append(inChar);
    }
    else {
      // empty the string by setting it equal to the inoming char:
      inString = inChar;
    }
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

