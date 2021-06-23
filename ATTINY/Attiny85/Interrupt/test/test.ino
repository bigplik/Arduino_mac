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


const byte LED = 0;          // pin 5 (D0)
const byte SW = 2;           // pin 7 (D2)
byte tryb = 0;
 
ISR (INT0_vect)
{
  //GIMSK &= ~bit(INT0);     // disable INT0
  tryb++;
}

void setup ()
  {
  pinMode (LED, OUTPUT);
  pinMode (0, INPUT_PULLUP);
  //digitalWrite (0, HIGH);  // input pull-up
  GIFR  = bit (INTF0);   // clear interrupt flag
  GIMSK = bit (INT0);    // enable INT0
  MCUCR &= ~(bit(ISC01) | bit(ISC00));    // INT0 on low level
  }  // end of setup

void loop ()
  {
  if(tryb >1) tryb = 0;
  
      switch(tryb){
        case 0:
          analogWrite(1,50);
          analogWrite(3,0);
          break;
        case 1:
          analogWrite(1,0);
          analogWrite(3,50);
          break;
          
      }

  }  // end of loop 
