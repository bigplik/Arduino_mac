#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

byte tryb = 0;

ISR(INT0_vect)
{
  tryb++;
}

void setup() {
  // put your setup code here, to run once:
    pinMode(0,INPUT_PULLUP);
    pinMode(1,OUTPUT);
    pinMode(3,OUTPUT);

    MCUCR = 0b00000000;
    GIMSK = 0b01000000;    // turns on pin change interrupts
    //GIMSK = 0b01000000;
    //GIFR =  0b01000000;
    PCMSK = 0b00000100;    // turn on interrupts on pins PB0, PB1, &amp;amp; PB4
    sei();                 // enables interrupts
                //MCUCR &= ~(bit(ISC01) | bit(ISC00));    // INT0 on low level
    //SREG =  0b10000000;

}

void loop() {
  // put your main code here, to run repeatedly:
  if(tryb > 1) tryb = 0;
  
  switch(tryb){
    case 0:
      digitalWrite(1,1);//blue
      digitalWrite(3,0);
      break;
    case 1:
      digitalWrite(1,0);
      digitalWrite(3,1);//green
      break;
  }

  
}
