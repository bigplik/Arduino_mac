/*
  MS5541 Pressure Sensor Display

Circuit:
MS5541 sensor attached to pins 10 - 13:
MOSI: pin 11  //data input
MISO: pin 12  //data output
SCK: pin 13
MCLK: pin 9

Voltage divider converts 5V to 3.3V on all lines except MISO

created 4 August 2011
by SMStrauch
*/

// library:
#include <SPI.h>

// MCKL signal pin
const int clock = 9;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV32); //divide 16 MHz to communicate on 500 kHz
  pinMode(clock, OUTPUT);
  delay(100);
}

void loop() {
  TCCR1B = (TCCR1B & 0xF8) | 1 ; //generates the MCKL signal
  analogWrite (clock, 128) ;
 
  //RESET
  SPI.setDataMode(SPI_MODE0);
  SPI.transfer(0x15);
  SPI.transfer(0x55);
  SPI.transfer(0x40);
  delay(100);

  //Calibration word 1
  unsigned int result1 = 0;
  unsigned int inbyte1 = 0;
  SPI.transfer(0x1D);
  SPI.transfer(0x50);
  SPI.setDataMode(SPI_MODE1);
  result1 = SPI.transfer(0x00);
  result1 = result1 << 8;
  inbyte1 = SPI.transfer(0x00);
  result1 = result1 | inbyte1;
  Serial.print("Calibration word 1 =");
  Serial.println(result1);
 
  //RESET
  SPI.setDataMode(SPI_MODE0);
  SPI.transfer(0x15);
  SPI.transfer(0x55);
  SPI.transfer(0x40);
 
  //Calibration word 2
  unsigned int result2 = 0;
  byte inbyte2 = 0;
  SPI.transfer(0x1D);
  SPI.transfer(0x60);
  SPI.setDataMode(SPI_MODE1);
  result2 = SPI.transfer(0x00);
  result2 = result2 <<8;
  inbyte2 = SPI.transfer(0x00);
  result2 = result2 | inbyte2;
  Serial.print("Calibration word 2 =");
  Serial.println(result2); 
 
  //RESET
  SPI.setDataMode(SPI_MODE0);
  SPI.transfer(0x15);
  SPI.transfer(0x55);
  SPI.transfer(0x40);
 
  //Calibration word 3
  unsigned int result3 = 0;
  byte inbyte3 = 0;
  SPI.transfer(0x1D);
  SPI.transfer(0x90);
  SPI.setDataMode(SPI_MODE1);
  result3 = SPI.transfer(0x00);
  result3 = result3 <<8;
  inbyte3 = SPI.transfer(0x00);
  result3 = result3 | inbyte3;
  Serial.print("Calibration word 3 =");
  Serial.println(result3); 

  //RESET
  SPI.setDataMode(SPI_MODE0);
  SPI.transfer(0x15);
  SPI.transfer(0x55);
  SPI.transfer(0x40);
   
  //Calibration word 4
  unsigned int result4 = 0;
  byte inbyte4 = 0;
  SPI.transfer(0x1D);
  SPI.transfer(0xA0);
  SPI.setDataMode(SPI_MODE1);
  result4 = SPI.transfer(0x00);
  result4 = result4 <<8;
  inbyte4 = SPI.transfer(0x00);
  result4 = result4 | inbyte4;
  Serial.print("Calibration word 4 =");
  Serial.println(result4);
 
  unsigned int c1 = 0;
  unsigned int c2 = 0;
  unsigned int c3 = 0;
  unsigned int c4 = 0;
  unsigned int c5 = 0;
  unsigned int c6 = 0;

  c1 = result1 >> 3 & 0x1FFF;
  c2 = ((result1 & 0x7) << 10) | ((result2 >> 6) & 0x3FF);
  c3 = (result3 >> 6) & 0x3FF;
  c5 = ((result2 & 0x3F) << 6) | (result3 & 0x3F);
  c4 = (result4 >> 7) & 0x7FF;
  c6 = result4 & 0x7F;

  Serial.println(c1);
  Serial.println(c2);
  Serial.println(c3);
  Serial.println(c4);
  Serial.println(c5);
  Serial.println(c6);

  //RESET
  SPI.setDataMode(SPI_MODE0);
  SPI.transfer(0x15);
  SPI.transfer(0x55);
  SPI.transfer(0x40);
 
  //Temperature:
  unsigned int tempMSB = 0;
  unsigned int tempLSB = 0;
  SPI.transfer(0x0F);
  SPI.transfer(0x20);
  /*int ready = digitalRead (12);
  while (ready = 0)
  {
  delay (10);
  }*/
  delay(50);
  SPI.setDataMode(SPI_MODE1);
  tempMSB = SPI.transfer(0x00);
  tempMSB = tempMSB << 8;
  tempLSB = SPI.transfer(0x00);
  tempMSB = tempMSB | tempLSB;
  Serial.print("Temperature raw =");
  Serial.println(tempMSB);
 
  //RESET
  SPI.setDataMode(SPI_MODE0);
  SPI.transfer(0x15);
  SPI.transfer(0x55);
  SPI.transfer(0x40);
 
  //Pressure:
  unsigned int presMSB = 0;
  unsigned int presLSB =0;
  SPI.transfer(0x0F);
  SPI.transfer(0x40);
  delay(50);
  SPI.setDataMode(SPI_MODE1);
  presMSB = SPI.transfer(0x00);
  presMSB = presMSB << 8;
  presLSB = SPI.transfer(0x00);
  presMSB = presMSB | presLSB;
  Serial.print("Pressure raw =");
  Serial.println(presMSB);
 
 
  delay(10000);
}


