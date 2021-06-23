/*
Rafal's garage door automation logic.

Cirucit made:
- on Arduino Uno 
- 2 relays for motor control
- 2 buttons (one NO[green], one NC[red])
*/

// constants won't change. They're used here to set pin numbers:
const int redBTN = 2;     // close door
const int greenBTN =  3;      // open door
const int openingStop = 12;      //open EndStop
const int closingStop = 9;      //close EndStop

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
  
  // read the state of the endStops
  openingState = digitalRead(openingStop);
  closingState = digitalRead(closingStop);

  // 
  if (redState == 1 && greenState == 1 && closingState == 1 && openingState == 0 || redState == 1 && greenState == 1 && closingState == 1 && openingState == 1 ) {  //closing door
    // turn LED on:
    //delay(250);
    digitalWrite(5, 0);
    delay(500);
    digitalWrite(6, 1);
  } 
  
  else if(greenState == 0 && redState == 0 && openingState == 1 && closingState == 0 || greenState == 0 && redState == 0 && openingState == 1 && closingState == 1){  //opening door
    //delay(250);
    digitalWrite(6, 0);
    delay(500);
    digitalWrite(5, 1);
  }
  
  //when two buttons (green[NO],red[NC])are pressed and
  //"openning" endStop is energized (conducts to GND), 
  //motor will STOP
  else if(redState == 0 && greenState == 1 && closingState == 0 && openingState == 1){
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    delay(500);
  }
  
  //when two buttons (green[NO],red[NC])are pressed and
  //"closing" endStop is energized (conducts to GND), 
  //motor will STOP
  else if(redState == 0 && greenState == 1 && openingState == 0 && closingState == 1){
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    delay(500);
  }

  //when two buttons (green[NO],red[NC])are NOT pressed
  //motor will STOP
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
