#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <toneAC.h>

/*************************************************** 
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

float startAltitude;
float meters = 0;
float checkmeters = 0;
int cisnienie = 0;

const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 102523;

Adafruit_BMP085 bmp;
  
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  
  startAltitude = bmp.readAltitude(101500);
  cisnienie = bmp.readPressure();
  
}
  
void loop() {
  cisnienie = bmp.readPressure();
  float range = map(cisnienie, sensorMin, sensorMax, 0, 500);
  
  
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    
    Serial.print("start Alitude = ");
    Serial.print(bmp.readAltitude(101500)-startAltitude);
    Serial.println(" meters");
    
    Serial.println();
    Serial.println(((bmp.readPressure())-99600)*10);
    delay(50);
    
    toneAC(((bmp.readPressure())-99600)*10);
    delay(50);
    
    toneAC();
    
}
