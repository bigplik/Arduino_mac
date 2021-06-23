/*
Rafal's garage door automation logic.
difference from drzwi_TEST3.1.2 instead of digitalRead of openRMT and closeRMT
use analogRead

Cirucit made:
- on Arduino Uno 
- 2 relays for motor control
- 2 buttons (one NO[green], one NC[red])
- beacon
- remote
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
#define openEndPin 11
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
boolean OPENING = false;
//Closing
boolean CLOSING = false;

boolean closingREMOTE = false;
boolean openingREMOTE = false;

//remote
#define openRMT analogRead(A0)>1000
#define closeRMT analogRead(A5)>1000


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("drzwi_TEST3.1.2");
  pinMode(redBtnPin, INPUT_PULLUP);    //close BTN
  pinMode(greenBtnPin, INPUT_PULLUP);  //open  BTN
  pinMode(openEndPin, INPUT_PULLUP);   //open  endStop
  pinMode(closeEndPin, INPUT_PULLUP);  //close endStop
  pinMode(openMotPin, OUTPUT);         //open  door motor direction
  pinMode(closeMotPin, OUTPUT);        //close door motor direction
 
  //set motor pins LOW
  digitalWrite(openMotPin,0), digitalWrite(closeMotPin,0);

  //remote
  //pinMode(8,INPUT);       //openRMT  signal
  //pinMode(10,INPUT);       //closeRMT signal
}

void loop() {


  //DOOR CLOSING
  //when red btn is pressed and doors are open (opening endStop energized/pressed)
  //or red btn is pressed and doors are beetween open and close position 
  //(both endStops are open-NOT energized)
  //DOOR CLOSING
  if(RED && !GREEN && !CLOSE && OPEN || RED && !GREEN && !CLOSE && !OPEN){
    OPENING = false, CLOSING = true;
    openingREMOTE = false, closingREMOTE = false;
    digitalWrite(openMotPin,0);
    delay(500);
    digitalWrite(closeMotPin,1);
  }
  //REMOTE DOOR CLOSING
  //when there is no CLOSING or OPENING status and closeRMT btn is pressed and doors are open (opening endStop pressed)
  //or no CLOSING or OPENING status and closeRMT btn is pressed and both endStops are not pressed (door between open and close position)
  //REMOTE DOOR CLOSING
  else if(!RED && !GREEN && !CLOSE && OPEN && closeRMT || !RED && !GREEN && !CLOSE && !OPEN & closeRMT){
    closingREMOTE = true; openingREMOTE = false;
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
    CLOSING = false, OPENING = true;
    openingREMOTE = false, closingREMOTE = false;
    digitalWrite(closeMotPin,0);
    delay(500);
    digitalWrite(openMotPin,1);
  }
  //REMOTE DOOR OPENING
  //when there is no CLOSING or OPENING status and openRMT btn is pressed and doors are close (closing endStop pressed)
  //or no CLOSING or OPENING status and openRMT btn pressed and both endStops are not pressed (door between open and close position)
  //REMOTE DOOR OPENING
  else if(!RED && !GREEN && CLOSE && !OPEN && openRMT || !RED && !GREEN && !CLOSE && !OPEN & openRMT){
    openingREMOTE = true; closingREMOTE = false;
    digitalWrite(openMotPin,0);
    delay(500);
    digitalWrite(closeMotPin,1);
  }


  //when two buttons (green[NO],red[NC])are NOT pressed and
  //"openning" endStop is energized (conducts to GND), 
  //motor will STOP
  else if(!RED && !GREEN && !CLOSE && OPEN){
    OPENING = false, CLOSING = false;
    digitalWrite(openMotPin,0);
    digitalWrite(closeMotPin,0);
    delay(500);
  }
  
  //when two buttons (green[NO],red[NC])are NOT pressed and
  //"closing" endStop is energized (conducts to GND), 
  //motor will STOP
  else if(!RED && !GREEN && !OPEN && CLOSE){
    OPENING = false, CLOSING = false;
    digitalWrite(openMotPin,0);
    digitalWrite(closeMotPin,0);
    delay(500);
  }


  //when two buttons (green[NO],red[NC])are pressed
  //motor will STOP
  else if(RED && GREEN){
    OPENING = false, CLOSING = false;
    openingREMOTE = false, closingREMOTE = false;
    digitalWrite(openMotPin,0);
    digitalWrite(closeMotPin,0);
    delay(500);
  }
  //REMOTE STOP
  //when OPENING and !CLOSING or CLOSING and !OPENING status occur
  //and any of the remote btn are pressed
  //motor will STOP
  //and both OPENING and CLOSING status will change to false
//  //REMOTE STOP
    else if(openingREMOTE){
        if(openRMT){
          digitalWrite(openMotPin,0);
          digitalWrite(closeMotPin,0);
          delay(500);
        openingREMOTE = false, closingREMOTE = false; 
        OPENING = false, CLOSING = false;
        }         
    }
    else if(closingREMOTE){
        if(closeRMT){
          digitalWrite(openMotPin,0);
          digitalWrite(closeMotPin,0);
          delay(500);
        openingREMOTE = false, closingREMOTE = false; 
        OPENING = false, CLOSING = false;
        }
    }

//    else if(OPENING && openRMT || OPENING && closeRMT || CLOSING && openRMT || CLOSING && closeRMT){
//    digitalWrite(openMotPin,0);
//    digitalWrite(closeMotPin,0);
//    OPENING = false, CLOSING = false;
//    delay(500);
//  }
  Serial.println(openRMT);
  Serial.println(closeRMT);
}
