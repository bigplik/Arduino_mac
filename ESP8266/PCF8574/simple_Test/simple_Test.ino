#include <Wire.h>
#include <ESP_PCF8574.h>

/*
 * espPCF.setBit(0,0) // first number is port #, second is 0-LOW, 1-HIGH
 * espPCF.setByte(1)  //send the 0-LOW, 1-HIGH to all OUTPUT GPIOS
 * espPCF.getByte() //get value of the all INPUT GPIOS
 * espPCF.getBit(0) //get value of port number (0-7) INPUT GPIO
 */

ESP_PCF8574 espPCF;

void setup() {
  // put your setup code here, to run once:
 espPCF.begin(0x20,0,2); //SDA, SCL

 espPCF.setBit(0,0);
 espPCF.setBit(1,0);
 espPCF.setBit(2,0);
// espPCF.pinMode(0,OUTPUT);
 //espPCF.pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
 espPCF.setBit(0,0);
 espPCF.setBit(1,0);
 espPCF.setBit(2,0);
 delay(1000);
  espPCF.setBit(0,1);
 delay(1000);
  espPCF.setBit(0,0);
  espPCF.setBit(1,1);
 delay(1000);
  espPCF.setBit(1,0);
  espPCF.setBit(2,1);
 delay(1000);
}
