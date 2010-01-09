#include "WProgram.h"
#line 1 "DigitalReadSerial.pde"

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  int sensorValue = digitalRead(2);
  Serial.println(sensorValue, DEC);
}



#line 1 "/home/arduino/arduino-0017/hardware/cores/arduino/main.cxx"
int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

