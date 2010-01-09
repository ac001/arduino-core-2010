/*
  String getBytes() function demo
 
 Demonstrates the getBytes function of the String library. 
 
 To test it, send the microcontroller some characters. 
 
 by Tom Igoe
 created 8 Feb 2009
 */


#include <WString.h>                // include the String library


String nameString = String(40);     // allocate a new String

void setup() {
  // open the serial port:
  Serial.begin(9600);
  // Say hello:
  Serial.print("String Library version: ");
  Serial.println(nameString.version());
  // give the string an initial value:

}

void loop () {
  if(Serial.available() > 0) {
    // read the incoming data as a char:
    char inChar = Serial.read();
    if (inChar != 'Z') {
      nameString.setCharAt(nameString.length(), inChar);
    } 
    else {
      // empty the string by setting it equal to initial string:
      nameString = "Hello!  My name is: ";
    }
    Serial.println(nameString);
  }

}
