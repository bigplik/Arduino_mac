/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMEP280 Breakout 
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required 
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

char auth[] = "58b735b834f34f2b862e39b8d22771a6";

SimpleTimer timer;

float bat, temp, pressure, altitude;

void sendUptime()
{
  
    temp = bmp.readTemperature();
    
    pressure = bmp.readPressure();

    altitude = bmp.readAltitude(1013.25); // this should be adjusted to your local forcase

  float bat = ESP.getVcc()*0.000952656;

  Blynk.virtualWrite(V5, temp);
  Blynk.virtualWrite(V6, pressure);
  Blynk.virtualWrite(V7, altitude);
  Blynk.virtualWrite(V8, bat);

}

void setup() {
  Serial.begin(115200);
  Serial.println(F("BMP280 test"));
  Blynk.begin(auth, "Kilimanjarro2", "kasiapaweldaciamcv");
  Wire.begin(D6,D5); //sda, scl
  
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  
  timer.setInterval(2000L, sendUptime);
  
}

void loop() {
    Blynk.run(); // Initiates Blynk
    timer.run(); // Initiates SimpleTimer
}
