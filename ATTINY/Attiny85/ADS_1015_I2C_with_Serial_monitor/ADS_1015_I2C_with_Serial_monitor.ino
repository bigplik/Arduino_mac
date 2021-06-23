/* This code use modified Adafruit_ADS1015.h library, named now
   Adafruit_ADS1015_1.h 
   To work this library need to contain following files:
   USI_TWI_Master.h , USI_TWI_Master.cpp , TinyWireM.h
   TinyWireM.cpp , Adafruit_ADS1015_1.h and Adafruit_ADS1015.cpp
   
   It use I2C modified library (TinyWireM.h) which let
   to send data to Attiny from I2C devices.
   SDA >>>>>>>>>>> PB0
   SCL >>>>>>>>>>> PB2
   
   SoftwareSerial.h is used here for serial communication between 
   Attiny85 and Arduino Uno by Rx Tx pins.
*/

#include <Adafruit_ADS1015_1.h>
#include <SoftwareSerial.h>

// Definitions
#define rxPin 3
#define txPin 4

SoftwareSerial mySerial(rxPin, txPin);

Adafruit_ADS1115 ads;

void setup() {
  // put your setup code here, to run once:
  
    mySerial.begin(9600);

  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
   ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  mySerial.println("------------------------------------------------------------");
  mySerial.print("GAIN_EIGHT 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV");
  
  ads.begin();
  
  int16_t adc3, adc2, adc1, adc0;
  adc3 = ads.readADC_SingleEnded(3);
  adc2 = ads.readADC_SingleEnded(2);
  adc1 = ads.readADC_SingleEnded(1);
  adc0 = ads.readADC_SingleEnded(0);
  
  delay(2000);
}


void loop() {
  // put your main code here, to run repeatedly:
    int16_t adc0, adc1, adc2, adc3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  mySerial.println(adc0);
  mySerial.println(adc1);
  mySerial.println(adc2);
  mySerial.println(adc3);
  mySerial.println("             ");
  delay(500);
  
}
