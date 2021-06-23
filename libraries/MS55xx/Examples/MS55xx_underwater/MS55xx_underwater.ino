#include "MS55xx.h"
#include <SPI.h>

/*********************************
* Please respect pin wiring:
* MOSI: pin 11 arduino or pin 7 on sensor
* MISO: pin 12 arduino or pin 8 on sensor
* SCK: pin 13 arduino or pin 1 on sensor
* MCLK: pin 9 arduino or pin 6 on sensor
*********************************/

//creating the sensor
MS55xx PressSensor;
float airPressure;
float waterPressure;

void setup() {
    Serial.begin(9600); 
    PressSensor.setPressureSensorType('MS5535');
    //start arduino before diving
    //otherwise a 1.0 bar is used as surface pressure
    PressSensor.update();
    airPressure = PressSensor.getPressureBar();
    if (airPressure > 1.2) {
      airPressure = 1.0;
    }
}

void loop() {
  //Before getting the values you need to update the sensor
  PressSensor.update();
  
  //get pressure
  waterPressure = PressSensor.getPressureBar() - airPressure;
  Serial.print("Deep (meters): ");
  Serial.println(abs(waterPressure)*10.0,1);
   
  //get 2nd temperature --> see datasheet for details
  Serial.print("Temperatre 2nd (celsius): ");
  Serial.println(PressSensor.get2ndTemperatureC());
  
  Serial.println();
  
  delay(2000);
}
