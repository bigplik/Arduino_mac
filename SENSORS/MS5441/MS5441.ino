/*
 MS5541 Pressure Sensor Display

Circuit:
MS5541 sensor attached to pins 10 - 13:
MOSI: pin 11
MISO: pin 12
SCK: pin 13

*/

// library:
#include <SPI.h>

//Sensor memory register addresses:
const int PRESSURE = 0x0F;      //MSB pressure
const int PRESSURE_LSB = 0x40;  //LSB of pressure
const int TEMPERATURE = 0x0F;   //MSB temperature
const int TEMPERATURE_LSB = 0x20;  //LSB temperature
const int W1M = 0x1D; // MSB Calibration word 1
const int W1L = 0x50; // LSB Calibration word 1
const int W2M = 0x1D; // MSB Calibration word 2
const int W2L = 0x60; // LSB Calibration word 2
const int W3M = 0x1D; // MSB Calibration word 3
const int W3L = 0x90; // LSB Calibration word 3
const int W4M = 0x1D; // MSB Calibration word 4
const int W4L = 0xA0; // LSB Calibration word 4
const byte RST1 = 0x15; //Reset sequence word 1
const byte RST2 = 0x55; //Reset sequence word 2
const byte RST3 = 0x40; //Reset sequence word 3


// CS just in case
const int chipSelectPin = 10;

void setup() {
 Serial.begin(9600);
 SPI.begin();
 pinMode(chipSelectPin, OUTPUT);
 delay(100);
}

void loop() {
 //RESET
 SPI.setDataMode(1);
 SPI.transfer(0x15);
 SPI.transfer(0x55);
 SPI.transfer(0x40);
 delay(100);
 
 //Calibration word 1
 unsigned int result1 = 0;
 unsigned int inbyte1 = 0;
 digitalWrite (chipSelectPin, LOW);  
 SPI.transfer(0x1D);
 SPI.transfer(0x50);
 SPI.setDataMode(0);
 result1 = SPI.transfer(0x00);
 result1 = result1 <<8;
 inbyte1 = SPI.transfer(0x00);
 result1 = result1 | inbyte1;
 digitalWrite(chipSelectPin, HIGH);
 Serial.print("Calibration word 1 =");
 Serial.println(result1);
 
 //Calibration word 2
 unsigned int result2 = 0;
 byte inbyte2 = 0;
 digitalWrite (chipSelectPin, LOW);  
 SPI.setDataMode(1);
 SPI.transfer(0x1D);
 SPI.transfer(0x60);
 SPI.setDataMode(0);
 result2 = SPI.transfer(0x00);
 result2 = result2 <<8;
 inbyte2 = SPI.transfer(0x00);
 result2 = result2 | inbyte2;
 digitalWrite(chipSelectPin, HIGH);
 Serial.print("Calibration word 2 =");
 Serial.println(result2);  
 
 //Calibration word 3
 unsigned int result3 = 0;
 byte inbyte3 = 0;
 digitalWrite (chipSelectPin, LOW);  
 SPI.setDataMode(1);
 SPI.transfer(0x1D);
 SPI.transfer(0x90);
 SPI.setDataMode(0);
 result3 = SPI.transfer(0x00);
 result3 = result3 <<8;
 inbyte3 = SPI.transfer(0x00);
 result3 = result3 | inbyte3;
 digitalWrite(chipSelectPin, HIGH);
 Serial.print("Calibration word 3 =");
 Serial.println(result3);  
 
 //Calibration word 4
 unsigned int result4 = 0;
 byte inbyte4 = 0;
 digitalWrite (chipSelectPin, LOW);  
 SPI.setDataMode(1);
 SPI.transfer(0x1D);
 SPI.transfer(0xA0);
 SPI.setDataMode(0);
 result4 = SPI.transfer(0x00);
 result4 = result4 <<8;
 inbyte4 = SPI.transfer(0x00);
 result4 = result4 | inbyte4;
 digitalWrite(chipSelectPin, HIGH);
 Serial.print("Calibration word 4 =");
 Serial.println(result4);
 
 //Temperature:
 unsigned int tempMSB = 0;
 byte tempLSB =0;
 digitalWrite (chipSelectPin, LOW);  
 SPI.setDataMode(1);
 SPI.transfer(0x0F);
 SPI.transfer(0x20);
 delay(30);
 SPI.setDataMode(0);
 tempMSB = SPI.transfer(0x00);
 tempMSB = tempMSB <<8;
 tempLSB = SPI.transfer(0x00);
 tempMSB = tempMSB | tempLSB;
 digitalWrite(chipSelectPin, HIGH);
 Serial.print("Temperature raw =");
 Serial.println(tempMSB);
 
 
 //Pressure:
 unsigned int presMSB = 0;
 byte presLSB =0;
 digitalWrite (chipSelectPin, LOW);  
 SPI.setDataMode(1);
 SPI.transfer(0x0F);
 SPI.transfer(0x40);
 delay(30);
 SPI.setDataMode(0);
 presMSB = SPI.transfer(0x00);
 presMSB = presMSB <<8;
 presLSB = SPI.transfer(0x00);
 presMSB = presMSB | presLSB;
 digitalWrite(chipSelectPin, HIGH);
 Serial.print("Pressure raw =");
 Serial.println(presMSB);
 
 
 delay(10000);
}
