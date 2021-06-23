/**
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS: Pin 10
* RST: Pin 9
*
* Script is based on the script of Miguel Balboa. 
* New cardnumber is printed when card has changed. Only a dot is printed
* if card is the same.
*
* @version 0.1
* @author Henri de Jong
* @since 06-01-2013
*/

#include <SPI.h>
#include <RFID.h>
#include <Servo.h> 

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 
int buzzPin = 3;
boolean range = true;

// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;

int caly;
void setup()
{ 
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  delay(2000);
  SPI.begin(); 
  rfid.init();
}

void loop()
{
    
    if (rfid.isCard()) {
        if (rfid.readCardSerial()) {
            if (rfid.serNum[0] != serNum0
                && rfid.serNum[1] != serNum1
                && rfid.serNum[2] != serNum2
                && rfid.serNum[3] != serNum3
                && rfid.serNum[4] != serNum4
            ) {
                /* With a new cardnumber, show it. */
//                Serial.println(" ");
//                Serial.println("Card found");
                serNum0 = rfid.serNum[0];
                serNum1 = rfid.serNum[1];
                serNum2 = rfid.serNum[2];
                serNum3 = rfid.serNum[3];
                serNum4 = rfid.serNum[4];
//               
//                //Serial.println(" ");
//                Serial.println("Cardnumber:");
//                Serial.print("Dec: ");
//		Serial.print(rfid.serNum[0],DEC);
//                Serial.print(", ");
//		Serial.print(rfid.serNum[1],DEC);
//                Serial.print(", ");
//		Serial.print(rfid.serNum[2],DEC);
//                Serial.print(", ");
//		Serial.print(rfid.serNum[3],DEC);
//                Serial.print(", ");
//		Serial.print(rfid.serNum[4],DEC);
//                Serial.println(" ");
//                        
//                Serial.print("Hex: ");
//		Serial.print(rfid.serNum[0],HEX);
//                Serial.print(", ");
//		Serial.print(rfid.serNum[1],HEX);
//                Serial.print(", ");
//		Serial.print(rfid.serNum[2],HEX);
//                Serial.print(", ");
//		Serial.print(rfid.serNum[3],HEX);
//                Serial.print(", ");
//		Serial.print(rfid.serNum[4],HEX);
//                Serial.println(" ");
                caly = serNum0 + serNum1 + serNum2 + serNum3 + serNum4   ;
//      Serial.print(caly);          
                //buzzer
//                  analogWrite(3,20);
//                  delay(500);
//                  analogWrite(3,0);
             }

             if (caly == 414 || caly== 650){
                switch (range) {
                    case true:    // your hand is on the sensor
                       digitalWrite(13, 0);
                       analogWrite(3,20);
                       digitalWrite(6,1);
                       //myservo.write(90);  
                       delay(200);
                       digitalWrite(6, 0);
                       analogWrite(3,0);
                       range != range;
                       //myservo.write(0);                      break;
                    case false:    // your hand is close to the sensor
                       digitalWrite(13, 0);
                       analogWrite(3,20);
                       digitalWrite(5,1);
                       //myservo.write(90);  
                       delay(200);
                       digitalWrite(5, 0);
                       analogWrite(3,0);
                       range != range;
                       //myservo.write(0);
                      break;
                  }

             }
          }
    }
    
    rfid.halt();
}



