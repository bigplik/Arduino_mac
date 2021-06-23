/* to listening serial monitor
you need to open it on Uno (or other different board)
and load there blanc sketch before

Connection Wiring
___________________________________________________________

    Attiny                  |          Uno
(any 25 or bigger)          |       (or other)
___________________________________________________________

     PIN 3                            RX PIN(0)
     PIN 4                            TX PIN(1)
*/


#include <SoftwareSerial.h>
// Definitions
#define rxPin 10
#define txPin 9

SoftwareSerial mySerial(rxPin, txPin);

int sensorPin = 1; //ACTUALLY PIN LABELED AS "2" on the HLT tutorial
int sensorVal = 0;

float a,b;
//
//boolean switchFans = 0;


// the setup routine runs once when you press reset:
void setup() {                
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(6,OUTPUT);
  mySerial.begin(9600);
}

// the loop routine runs over and over asensorpingain forever:
void loop() {
  if(digitalRead(1)==0){
      digitalWrite(6,1);
      for(int i=0;i<10;i++){
          a += analogRead(A0); 
          b += analogRead(A2);
          delay(20);
      }
      a /= 10;
      b /= 10;

      
      mySerial.write(a);
      delay(500);
      mySerial.write(b);
      delay(500);
      none();
  }
  else{
    digitalWrite(6,0);
  }

}

void none(){
  
}

