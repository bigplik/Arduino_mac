#include "avr/interrupt.h"; 
 
volatile int value = 122;
volatile int lastEncoded = 0;
boolean button = false;
 
void setup()
{
  pinMode(6, OUTPUT);  // set LED pin to output
  //pinMode(1, OUTPUT);
  //pinMode(2, INPUT_PULLUP);
  // set pins 3 and 4 to input
  // and enable pullup resisters
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);




  GIMSK |= _BV(PCIE0);   // Enable Pin Change Interrupts
  //PCMSK0 |= _BV(PCINT0); // Use PA7 as interrupt pin
  //PCMSK0 |= _BV(PCINT1);
 
  //sei(); //Enable interrupts

//  GIMSK = 0b00100000;       // Enable pin change interrupts
  PCMSK0 = 0b00000011;       // Enable pin change interrupt for PB3 and PB4
  sei();                    // Turn on interrupts
}
 
void loop()
{
  analogWrite(6, value);
  //if(digitalRead(2) == LOW) button != button;
  
//  switch (button) {
//    case false:
//      analogWrite(0, value);
//      analogWrite(1,0);
//      if(digitalRead(2) == LOW) {
//        button = 1;
//        delay(500); //can deal with delay time to set optimal!!!!!!
//      }
//      break;
//    case true:
//      analogWrite(1, value);
//      analogWrite(0,0);
//      if(digitalRead(2) == LOW) {
//        button = 0;
//        delay(500);
//      }
//      break;
//  }
}
 
// This is the ISR that is called on each interrupt
// Taken from http://bildr.org/2012/08/rotary-encoder-arduino/
ISR(PCINT0_vect)
{
  int MSB = digitalRead(0); //MSB = most significant bit
  int LSB = digitalRead(1); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    value++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    value--;
 
  lastEncoded = encoded; //store this value for next time
   //if(digitalRead(2) == LOW) button != button;

  if (value <= 0)
    value = 0;
  if (value >= 1023)
    value = 1023;
}
