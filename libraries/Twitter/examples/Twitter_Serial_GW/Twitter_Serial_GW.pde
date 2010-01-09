#include <Ethernet.h>
#include <Twitter.h>

// Sample : Serial port => Twitter gateway
//   Run this program on Arduino and connect via some Serial port terminal software.
//   Type a message and hit enter key, and it will be posted to Twitter.
//   Arduino IDE Serial Monitor is not usable because it doesn't seem able to send Enter key code.

// Ethernet Shield Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 10, 0, 0, 177 };
byte gateway[] = { 10, 0, 0, 1 };
byte subnet[] = { 255, 255, 0, 0 };

// Your Twitter ID:Password
Twitter twitter("YourID:Password");


char msg[141] = "";
int len = 0;


void setup()
{
  Ethernet.begin(mac, ip, gateway, subnet);
  Serial.begin(9600);
  
  delay(1000);
  Serial.print("> ");
}

void loop()
{
  if (Serial.available() > 0) {
    char recv = msg[len++] = Serial.read();
    if (recv == '\b' || recv == 127) { // Backspace
      if (len > 1) {
        len -= 2;
        Serial.print("\b \b");
      }
    }
    else if (recv == '\r' || recv == '\n') { // How to send CR/LF from IDE serial monitor ???
      Serial.print("\r\n");
      len--;
      msg[len] = 0;
      if (len > 0)
        post();
      len = 0;
      Serial.print("\r\n> ");
    }
    else if (len > 140)
      len = 140;
    else
      Serial.print(recv);
  }
}

void post()
{
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    int status = twitter.wait();
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
  delay(1000);
}
