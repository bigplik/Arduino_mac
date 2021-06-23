#include <avr/interrupt.h>

ISR(WDT_vect) {
   // Toggle Port B pin 4 output state
   PORTB ^= 1<<PB4;
}

int main(void) {
   // Set up Port B pin 4 mode to output
    DDRB = 1<<DDB4;

   // prescale timer to 0.5s
   WDTCR |= (1<<WDP2) | (1<<WDP0);

   // Enable watchdog timer interrupts
   WDTCR |= (1<<WDTIE);

   sei(); // Enable global interrupts 

   for (;;) {
      // Waiting for interrupt...
   }
}
