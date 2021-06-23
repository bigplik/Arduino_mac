#include "MS55xx.h"
#include <SPI.h>
#include <Snooze.h>

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

int count = 0;

SnoozeBlock config;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT); 
    PressSensor.setPressureSensorType('MS5535');
    //start arduino before diving
    //otherwise a 1.0 bar is used as surface pressure
    PressSensor.update();
    airPressure = PressSensor.getPressureBar();
    if (airPressure > 1.2) {
      airPressure = 1.0;
    }
    config.pinMode(16, INPUT_PULLUP, RISING);//vibro sensor
}

void loop() {
  //Before getting the values you need to update the sensor
  PressSensor.update();

  //get pressure
  waterPressure = PressSensor.getPressureBar() - airPressure;
  float a = abs(waterPressure)*10.0;

  if(a >2000) waterPressure = 0;


  if((waterPressure) == 0.0){
    count++;
    delay(1000);
    Serial.println(count);
    if(count > 10){
        Snooze.deepSleep( config );
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        count = 0;
    }
  }
  else{
    count = 0;
    Serial.print("Deep (meters): ");
    Serial.println(abs(waterPressure)*10.0,1);
    
  //get 2nd temperature --> see datasheet for details
    Serial.print("Temperatre 2nd (celsius): ");
    Serial.println(PressSensor.get2ndTemperatureC());
  
  Serial.println();
  delay(2000);
  }
}
