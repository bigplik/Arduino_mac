#include <Wire.h>
#include <ESP_PCF8574.h>
/*
 * espPCF.setBit(0,0) // first number is port #, second is 0-LOW, 1-HIGH
 * espPCF.setByte(1)  //send the 0-LOW, 1-HIGH to all OUTPUT GPIOS
 * espPCF.getByte() //get value of the all INPUT GPIOS
 * espPCF.getBit(0) //get value of port number (0-7) INPUT GPIO
 */

ESP_PCF8574 PCF;
ESP_PCF8574 PCF2;

void setup() {
  // put your setup code here, to run once:
 PCF.begin(0x20,0,2); //SDA, SCL
 PCF2.begin(0x27,0,2); //SDA, SCL

 PCF2.setBit(7,0);
// espPCF.pinMode(0,OUTPUT);
 //espPCF.pinMode(2,INPUT_PULLUP);
 delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

 if(PCF.getBit(7)==1){
   PCF2.setBit(7,1);
 }
 else{
   PCF2.setBit(7,0);
 }

}
