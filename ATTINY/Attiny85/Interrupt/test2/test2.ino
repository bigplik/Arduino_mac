#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const int led = 1;

int main(void)
{
    //delay(50);


    setup();

    while(1) {}

    return 0;
}

void setup()
{
    pinMode(led, OUTPUT);
    pinMode(2,INPUT_PULLUP);
    
    GIMSK = 0b01000000;  
    PCMSK = 0b00000010;   
    MCUCR = 0b00000000;   
    sei();            
}

ISR(INT0_vect)
{
digitalWrite(led, !digitalRead(led)); 
}
