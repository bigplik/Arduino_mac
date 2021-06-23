/*
Rafal's garage door automation logic.

Cirucit made:
- on Arduino Uno 
- 2 relays for motor control
- 2 buttons (one NO[green], one NC[red])
- no beacon
- no remote
*/

// constants won't change. They're used here to set pin numbers:
const int redBTN = 2;       // close door    normal closed   NC btn
const int greenBTN =  3;    // open door     normal open     NO btn
const int openingStop = 11;     //open EndStop
const int closingStop = 9;      //close EndStop
const int motFet_open = 5;   //motor direction up
const int motFet_close = 6;  //motor direction down

// variables will change:
int R_S = 0; //red btn state
int G_S = 0; //green btn state
int O_S = 0; //opening state
int C_S = 0; //closing state


void setup() {
  // initialize the LED pin as an output:
  pinMode(greenBTN, INPUT_PULLUP);
  // initialize the pushbutton pin as an input:
  pinMode(redBTN, INPUT_PULLUP);
  pinMode(motFet_open,OUTPUT);
  pinMode(motFet_close,OUTPUT);
  pinMode(openingStop,INPUT_PULLUP);
  pinMode(closingStop,INPUT_PULLUP);
}

void loop() {
  // read the state of the pushbutton value:
  R_S = digitalRead(redBTN);
  G_S = digitalRead(greenBTN);
  
  // read the state of the endStops
  O_S = digitalRead(openingStop);
  C_S = digitalRead(closingStop);

  //DOOR CLOSING
  //when green btn is pressed and doors are open (opening endStop energized)
  //or green btn is pressed and doors are beetween open and close (both endStops are open-NOT energized)
  //DOOR CLOSING
  if (R_S==1 && G_S==1 && C_S==1 && O_S==0 || R_S==1 && G_S==1 && C_S==1 && O_S==1 ) {  //closing door
    // turn LED on:
    //delay(250);
    digitalWrite(motFet_open, 0);
    delay(500);
    digitalWrite(motFet_close, 1);
  } 

  //DOOR OPENING
  //when red btn is pressed and doors are closed (closing endStop energized)
  //or red btn is pressed and doors are beetween open and close (both endStops are open-NOT energized)
  //DOOR OPENING
  else if(G_S==0 && R_S==0 && O_S==1 && C_S==0 || G_S==0 && R_S==0 && O_S==1 && C_S==1){  //opening door
    //delay(250);
    digitalWrite(motFet_close, 0);
    delay(500);
    digitalWrite(motFet_open, 1);
  }
  
  //when two buttons (green[NO],red[NC])are pressed and
  //"openning" endStop is energized (conducts to GND), 
  //motor will STOP
  else if(R_S==0 && G_S==1 && C_S==0 && O_S==1){
    digitalWrite(motFet_open, 0);
    digitalWrite(motFet_close, 0);
    delay(500);
  }
  
  //when two buttons (green[NO],red[NC])are pressed and
  //"closing" endStop is energized (conducts to GND), 
  //motor will STOP
  else if(R_S==0 && G_S==1 && O_S==0 && C_S==1){
    digitalWrite(motFet_open, 0);
    digitalWrite(motFet_close, 0);
    delay(500);
  }

  //when two buttons (green[NO],red[NC])are NOT pressed
  //motor will STOP
  else if(R_S==1 && G_S==0){  //turn off
    //delay(250);
    // turn LED off:
    digitalWrite(motFet_open, 0);
    digitalWrite(motFet_close, 0);
    delay(500);
  }
}

