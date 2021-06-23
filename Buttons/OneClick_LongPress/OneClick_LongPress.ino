/*
 * One Button two button red button blue button
 *
 * learnelectronics
 * 23 Sept 2017
 *
 * www.youtube.com/c/learnelectronics
 * arduino0169@gmail.com
 *
 * Find the library here: http://www.mathertel.de/Arduino/OneButtonLibrary.aspx
 */
 
#include "OneButton.h"                              //we need the OneButton library
 
 
OneButton button(2, true);                         //attach a button on pin A1 to the library
int pwm = 0;
int led = 0;
 
 
void setup() {
 
  //pinMode(3, OUTPUT);                              // sets the digital pin as output
  //pinMode(2, OUTPUT);                              // sets the digital pin as output
  //pinMode(1, OUTPUT);                              // sets the digital pin as output
 
     
  //button.attachDoubleClick(doubleclick);            // link the function to be called on a doubleclick event.
  button.attachClick(singleclick);                  // link the function to be called on a singleclick event.
  button.attachLongPressStop(longclick);            // link the function to be called on a longpress event.
}
 
 
 
void loop() {
 
  button.tick();                                    // check the status of the button
  delay(10);
  
  switch (led) {
    case 0:
      analogWrite(9,0);
      analogWrite(10,pwm);
    break;
    case 1:
      analogWrite(10,0);
      analogWrite(9,pwm);
    break;
  }
  // a short wait between checking the button
} // loop
 
 
 
void doubleclick() {                                // what happens when button is double-clicked
 //digitalWrite(1,HIGH);                             // light the green LED
 //delay(1000);                                       // wait one second
 //digitalWrite(1,LOW);                              // turn off green LED
}
 
void singleclick(){                                 // what happens when the button is clicked
 //digitalWrite(2,HIGH);
 // light the red LED
 pwm = pwm +50;
 if(pwm > 250) pwm = 0;
 delay(200);                                       // wait one second
 //digitalWrite(2,LOW);                              // turn off the gren led
}
 
void longclick(){                                   // what happens when buton is long-pressed
 //digitalWrite(3,HIGH);
 // light the blue LED
 led=!led;
 delay(200);                                       // wait one second
 //digitalWrite(3,LOW);                              // turn off the blue LED
}
