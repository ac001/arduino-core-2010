#include <Ping.h>

Ping ping = Ping(13,74,29);

void setup(){
  Serial.begin(115200);
}

void loop(){
  ping.fire();
  Serial.print("Microseconds: ");
  Serial.print(ping.microseconds());
  Serial.print(" | Inches ");
  Serial.print(ping.inches());
  Serial.print(" | Centemeters: ");
  Serial.print(ping.centemeters());
  Serial.println();
}
