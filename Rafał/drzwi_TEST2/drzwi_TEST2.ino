/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

// constants won't change. They're used here to set pin numbers:
const int redBTN = 2;     // close door
const int greenBTN =  3;      // open door
const int openingStop = 9;      //open EndStop
const int closingStop = 12;      //close EndStop

// variables will change:
int redState = 0;         // variable for reading the pushbutton status
int greenState = 0;
int openingState = 0;
int closingState = 0;


void setup() {
  // initialize the LED pin as an output:
  pinMode(greenBTN, INPUT_PULLUP);
  // initialize the pushbutton pin as an input:
  pinMode(redBTN, INPUT_PULLUP);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(openingStop,INPUT_PULLUP);
  pinMode(closingStop,INPUT_PULLUP);
}

void loop() {
  // read the state of the pushbutton value:
  redState = digitalRead(redBTN);
  greenState = digitalRead(greenBTN);
  openingState = digitalRead(openingStop);
  closingState = digitalRead(closingStop);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (redState == 1 && greenState == 1 && closingState == 1) {  //closing door
    // turn LED on:
    //delay(250);
    digitalWrite(5, 0);
    delay(500);
    digitalWrite(6, 1);
  } 
  else if(greenState == 0 && redState == 0 && openingState == 1 ){  //opening door
    //delay(250);
    digitalWrite(6, 0);
    delay(500);
    digitalWrite(5, 1);
  }
  else if(redState == 0 && greenState == 1 && closingState == 0){
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    delay(500);
  }
  else if(redState == 0 && greenState == 1 && openingState == 0){
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    delay(500);
  }
  else if(redState == 1 && greenState == 0){  //turn off
    //delay(250);
    // turn LED off:
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    delay(500);
  }
//    else if(openingState == 0 && closingState == 0 ){  //turn off
//    //delay(250);
//    // turn LED off:
//    digitalWrite(5, 0);
//    digitalWrite(6, 0);
//    delay(500);
//  }
//  else{
//    digitalWrite(5,0);
//    digitalWrite(5,0);
//    delay(500);
//  }
}
