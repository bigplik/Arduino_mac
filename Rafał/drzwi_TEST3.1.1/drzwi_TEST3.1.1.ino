/*
Rafal's garage door automation logic.

Cirucit made:
- on Arduino Uno 
- 2 relays for motor control
- 2 buttons (one NO[green], one NC[red])
*/
//buttons
#define redBtnPin 2
#define greenBtnPin 3
//circuit wired to GND through NC Red btn
//Red btn (pulledUp, conducts to Vcc when pressed)
//when btn NOT pressed, conducts to GND
#define RED digitalRead(redBtnPin)==HIGH
//circuit wired to GND through NO Green btn
//Green btn (pulledUp, conducts to GND when pressed)
//when btn NOT pressed, conducts to Vcc
#define GREEN digitalRead(greenBtnPin)==LOW

//endStops
#define openEndPin 12
#define closeEndPin 9
//circuit wired to GND through endStop
//opening endStop (pulledUp, conducts to GND when pressed)
//status Open when endStop LOW
#define OPEN digitalRead(openEndPin)==LOW
//circuit wired to GND through endStop
//closing endStop (pulledUp, conducts to GND when pressed)
//status Open when endStop LOW
#define CLOSE digitalRead(closeEndPin)==LOW


//motor
#define openMotPin 5
#define closeMotPin 6
//motor direction
//set FET control for opening or closing
//Opening
#define OPENING digitalWrite(openMotPin)==HIGH
//Closing
#define CLOSING digitalWrite(closeMotPin)==HIGH



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("drzwi_TEST3.1.1");
  pinMode(redBtnPin, INPUT_PULLUP);
  pinMode(greenBtnPin, INPUT_PULLUP);
  pinMode(openEndPin, INPUT_PULLUP);
  pinMode(closeEndPin, INPUT_PULLUP);
  pinMode(openMotPin, OUTPUT);
  pinMode(closeMotPin, OUTPUT);
 
  //set motor pins LOW
  digitalWrite(openMotPin,0), digitalWrite(closeMotPin,0);
}

void loop() {

  //DOOR CLOSING
  //when red btn is pressed and doors are open (opening endStop energized/pressed)
  //or red btn is pressed and doors are beetween open and close position 
  //(both endStops are open-NOT energized)
  //DOOR CLOSING
  if(RED && !GREEN && !CLOSE && OPEN || RED && !GREEN && !CLOSE && !OPEN){
    digitalWrite(openMotPin,0);
    delay(500);
    digitalWrite(closeMotPin,1);
  } 

  //DOOR OPENING
  //when green btn is pressed and doors are closed (closing endStop energized/pressed)
  //or green btn is pressed and doors are beetween open and close position 
  //(both endStops are open-NOT energized)
  //DOOR OPENING
  else if(GREEN && !RED && !OPEN && CLOSE || GREEN && !RED && !OPEN && !CLOSE){
    digitalWrite(closeMotPin,0);
    delay(500);
    digitalWrite(openMotPin,1);
  }

  //when two buttons (green[NO],red[NC])are NOT pressed and
  //"openning" endStop is energized (conducts to GND), 
  //motor will STOP
  else if(!RED && !GREEN && !CLOSE && OPEN){
    digitalWrite(openMotPin,0);
    digitalWrite(closeMotPin,0);
    delay(500);
  }
  
  //when two buttons (green[NO],red[NC])are NOT pressed and
  //"closing" endStop is energized (conducts to GND), 
  //motor will STOP
  else if(!RED && !GREEN && !OPEN && CLOSE){
    digitalWrite(openMotPin,0);
    digitalWrite(closeMotPin,0);
    delay(500);
  }

  //when two buttons (green[NO],red[NC])are pressed
  //motor will STOP
  else if(RED && GREEN){
    digitalWrite(openMotPin,0);
    digitalWrite(closeMotPin,0);
    delay(500);
  }

}
