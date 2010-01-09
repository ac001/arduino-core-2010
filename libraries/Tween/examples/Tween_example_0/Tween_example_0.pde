/** 
 * 3 PWM outputs with the arduino
 * Using the SMS protocol and the Tween library
 * Usage: L [pin] [value] [duration] -> write PWM pin. (indices [0,n-1] | n = 3), time in ms
 * The [value] should be within [0,MAX_VAL]
 * @author Alexandre Quessy 
 * @date 2008 May
 * @uses http://www.arduino.cc/playground/Code/SimpleMessageSystem
 */
// --------------------- INCLUDES
// remove if wiring
#include <SimpleMessageSystem.h> 
// From LibInteract:
#include <Tween.h>

// --------------------- SETTINGS
#define BAUD_RATE   9600 // change!
#define MAX_VAL     255 // 8 bits,
#define NUM_PWM 3
int led_pin[NUM_PWM] = {9,10,11};
// three PWM output pins. Indices are 0, 1 and 2, but real arduino pins are 9,10,11.

// ---------------------- ATTRIBUTES
typedef unsigned long time_t;
time_t ms_start[NUM_PWM];
Tween_t chase[NUM_PWM];

// functions
// setup()
void setup()
{
  int i;

  Serial.begin(BAUD_RATE);
  time_t now = millis();

  for (i = 0; i < NUM_PWM; i++)
  {
    // call constructor
    Tween_init(&chase[i]);
    Tween_setType(&chase[i], TWEEN_EASEINOUTCUBIC);
    // for now, the current and start time are managed from outside the class
    // we need to handle it manually here:
    ms_start[i] = now;

    // set PWM pin to output and blank them
    pinMode(led_pin[i],OUTPUT);
    analogWrite(led_pin[i], 0);
  }
}
// loop()
void loop()
{
  // SMS STUFF ----------------------
  // Checks to see if the message is complete and erases any previous messages
  if (messageBuild() > 0) 
  { 
    switch (messageGetChar()) 
    {
    case 'L': // line
      sms_ramp();
      break;
    }
  }
  // LED STUFF -------------------
  time_t now = millis();
  for (byte i=0;i<NUM_PWM;i++) 
  {
    // for now, the current and start time are managed from outside the class
    // we need to handle it manually here:	
    analogWrite(led_pin[i], (int) (Tween_tick(&chase[i], (now - ms_start[i]) )*MAX_VAL) );
  }
}
// set one PWM pin val
void sms_ramp() 
{
  int pin;
  int target;
  int duration;

  // Gets the next word as an integer
  pin = messageGetInt(); 
  target = messageGetInt();
  duration = messageGetInt();

  // the Tween class uses floats internally
  // so we convert the [0,255] to the range [0.0, 1.0]
  Tween_line(&chase[pin], (float) target/MAX_VAL, (float) duration);
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
