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
#define rxPin 3
#define txPin 4

SoftwareSerial mySerial(rxPin, txPin);

int sensorPin = 7; //ACTUALLY PIN LABELED AS "2" on the HLT tutorial
int sensorVal = -1;

boolean switchFans = 0;


// the setup routine runs once when you press reset:
void setup() {                
  pinMode(sensorPin, INPUT);
  mySerial.begin(9600);
}

// the loop routine runs over and over asensorpingain forever:
void loop() {

  sensorVal = analogRead(sensorPin); 
  mySerial.print("Input Val: ");
  mySerial.print(sensorVal);

  mySerial.println();
}
