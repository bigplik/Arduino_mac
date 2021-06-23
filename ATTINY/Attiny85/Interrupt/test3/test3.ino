#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

boolean state = true;
byte tryb = 0;

ISR(PCINT0_vect)
{
    state = false;
}

void setup() {
  // put your setup code here, to run once:
    pinMode(3, OUTPUT);
    pinMode(2,INPUT_PULLUP);
    pinMode(1,OUTPUT);

    //SREG =  0b10000010;
    GIMSK = 0b00100000;  
    PCMSK = 0b00000001;   
    //MCUCR = 0b00000000;   
    sei(); 
}

void loop() {
  // put your main code here, to run repeatedly:
    while(state == false){
      tryb++;
      if(tryb>1) tryb = 0;
      state = true;
    }

    switch(tryb){
      case 0:
        digitalWrite(1,1);
        digitalWrite(3,0);
        break;
      case 1:
        digitalWrite(1,0);
        digitalWrite(3,1);
        break;
    }

}
