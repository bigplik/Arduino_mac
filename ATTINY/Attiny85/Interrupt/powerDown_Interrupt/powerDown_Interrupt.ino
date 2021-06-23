// ATMEL ATTINY 25/45/85 / ARDUINO
// Pin 1 is /RESET
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1 
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+

/*

  Pin 7  <-- switch to Gnd

  Pin 5 (PB0) <---- LED ---> 330 R <-----> Gnd
  
*/


#include <avr/sleep.h>    // Sleep Modes
#include <avr/power.h>    // Power management

const byte LED = 0;          // pin 5 (D0)
const byte SW = 2;           // pin 7 (D2)
 
ISR (INT0_vect)
{
  GIMSK &= ~bit(INT0);     // disable INT0 
}

void setup ()
  {
  pinMode (LED, OUTPUT);
  pinMode (SW, INPUT);
  digitalWrite (SW, HIGH);  // input pull-up
  ADCSRA = 0;            // turn off ADC
  MCUCR &= ~(bit(ISC01) | bit(ISC00));    // INT0 on low level
  }  // end of setup

void loop ()
  {

  power_timer0_enable ();
  delay (100);  // let timer reach a known point
  digitalWrite (LED, HIGH);
  delay (20); 
  digitalWrite (LED, LOW);
  power_timer0_disable ();

  while (digitalRead (SW) == LOW)
    { }  // wait for switch to be released

  noInterrupts ();
  GIFR  = bit (INTF0);   // clear interrupt flag
  GIMSK = bit (INT0);    // enable INT0 
    
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  sleep_enable ();       // ready to sleep
  interrupts ();
  sleep_cpu ();          // sleep                
  sleep_disable ();      // precaution

  }  // end of loop 
