/*
  MS5611 Barometric Pressure & Temperature Sensor. Simple Example
  Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/czujnik-cisnienia-i-temperatury-ms5611.html
  GIT: https://github.com/jarzebski/Arduino-MS5611
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MS5611.h>

MS5611 ms5611;

double referencePressure;
float maximum;
float minimum;

void setup() 
{
  Serial.begin(9600);

  // Initialize MS5611 sensor
  Serial.println("Initialize MS5611 Sensor");

  while(!ms5611.begin())
  {
    Serial.println("Could not find a valid MS5611 sensor, check wiring!");
    delay(500);
  }

  // Get reference pressure for relative altitude
  referencePressure = ms5611.readPressure();

  // Check settings
  checkSettings();
}

void checkSettings()
{
  Serial.print("Oversampling: ");
  Serial.println(ms5611.getOversampling());
}

void loop()
{

  uint32_t rawPressure = ms5611.readRawPressure();

  // Read true temperature & Pressure
  long realPressure = ms5611.readPressure();

  // Calculate altitude
  float absoluteAltitude = ms5611.getAltitude(realPressure);
  float realAlt = ms5611.getAltitude(realPressure, referencePressure);
  static float countAlt = 0;
  static float rising = realAlt - countAlt;
  static float deniwelacja = maximum - minimum;
  
  if(countAlt == 0) {countAlt = realAlt;}
  else{ countAlt = (countAlt + realAlt)/2;}
  
  if(realAlt > maximum) { maximum = realAlt; }
  else if(realAlt < minimum) { minimum = realAlt; }
  
//  if(maximum >= 2 || deniwelacja >= 2 || deniwelacja <= -2 && rising > 1.1 || rising < -1.1){
//    change = 1;
//  }

  Serial.println("--");


  Serial.println(rising);
  Serial.println(realAlt);    
  Serial.println(deniwelacja);
  Serial.println(maximum);

  delay(500);
}


