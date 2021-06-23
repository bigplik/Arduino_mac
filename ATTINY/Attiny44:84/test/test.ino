//#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define ENCODER_PIN 0 // D3
#define LED_PIN  7 // D2

static int interrupted;

ISR(PCINT0_vect) { interrupted = true; }

void handleInterrupt() {
  //Turn on LED for 2 seconds when an interrupt is caught
  digitalWrite(LED_PIN, HIGH);
 
  delay(2000);
 
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  interrupted = false;
 
  pinMode(ENCODER_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
 
  GIMSK |= _BV(PCIE0);   // Enable Pin Change Interrupts
  PCMSK0 |= _BV(PCINT0); // Use PA7 as interrupt pin
 
  sei(); //Enable interrupts
}

void loop() {
  if(interrupted) {
    handleInterrupt();

    interrupted = false;
  }
}
