/** 
 16 PWM outputs with the TLC5940
 Using the SMS protocol and the Tween library
 r [pin] [value] [duration] -> write PWM pin. (indices [0,n-1] | n = 16), time in ms
 @author Alexandre Quessy 
 @date 2008 May
 @uses https://whatever.metalab.at/user/wizard23/tlc5940/arduino/TLC5940/ 
 @see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1204292903/6
 @uses http://www.arduino.cc/playground/Code/SimpleMessageSystem
 */
// --------------------------
// >> Extract from TLC5940.cpp:
// Arduino pins (corresponds to the AVR pins below):
//   VPRG_PIN  = 12
//   SIN_PIN   = 13
//   SCLK_PIN  =  8
//   XLAT_PIN  =  9
//   BLANK_PIN = 10
// IREF  ---1k--- GND
// DCPROG ------- +5V 
//   GSCLK_PIN = 11
// sout -------- NC
// xerr ------- NC
// ------------------------
// remove if wiring
#include <SimpleMessageSystem.h> 
/*
  The TLC5940 library must be installed first:
  Copy (or symlink) the TLC5940 folder to <Arduino-dir>/hardware/libraries/
*/
#include <TLC5940.h>
// From LibInteract:
#include <Tween.h>
// --------------------- SETTINGS
#define BAUD_RATE   9600 // change!
#define NUM_TLC5940    1 // 1 chip
#define NUM_PWM       16 //  1 chip
#define MAX_VAL      255 // 8 bits,
#define BIT_DEPTH      8 // 8 bits

// ---------------------- ATTRIBUTES
typedef unsigned long time_t;

time_t ms_start[NUM_PWM];
//uint16_t pwm_vals[NUM_PWM];
Tween_t chase[NUM_PWM];

TLC5940 leds(NUM_TLC5940, BIT_DEPTH);

void setup()
{
  Serial.begin(BAUD_RATE);
  // FIXME: Pin allocation should be configures here
  leds.init();
  // SET ALL LED to 0
  leds.clear(); // Clear framebuffer
  int i;
  time_t now = millis();
  for (i = 0; i < NUM_PWM; i++)
  {
    // call constructor
    Tween_init(&chase[i]);
    Tween_setType(&chase[i], TWEEN_EASEINOUTCUBIC);
    ms_start[i] = now;
  }
  leds.display(); // Display framebuffer  
}
void loop()
{
  // SMS STUFF ----------------------
  // Checks to see if the message is complete and erases any previous messages
  if (messageBuild() > 0) 
  { 
    switch (messageGetChar()) 
    {
      case 'r': // ramp
        sms_ramp();
        break;
    }
  }
  // TLC5940 STUFF -------------------
  time_t now = millis();
  //leds.clear();
  for (byte i=0;i<NUM_PWM;i++) {
    //TLC5940::setLED(uint8_t lednr, uint16_t intensity)
    //leds.setLED(i, pwm_vals[i]);
    leds.setLED(i, (uint16_t)(Tween_tick(&chase[i], (now - ms_start[i]) )*MAX_VAL) );  
  }
  leds.display();
  
}
// set one PWM pin val
void sms_ramp() 
{
  int pin;
  int target;
  int duration;
  
  pin = messageGetInt(); // Gets the next word as an integer
  target = messageGetInt();
  duration = messageGetInt();
  //pwm_vals[(pin % NUM_PWM)] = (uint16_t) (val % MAX_VAL);
  
  Tween_line(&chase[pin], (float) target/255.0, (float) duration);
  ms_start[pin] = millis();
}

/*
TODO:
typedef struct 
{
  unsigned long ms_start;
  Tween_t *t;
} Line_t;

float Line_tick(Line_t *x, unsigned long ms_now);
void Line_tick(Line_t *x, unsigned long ms_now);
*/


