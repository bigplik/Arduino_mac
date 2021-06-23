#include <MS5541.h>
#include <SPI.h>

/*********************************
* Please respect pin wiring:
* MOSI: pin 11 arduino or pin 7 on sensor
* MISO: pin 12 arduino or pin 8 on sensor
* SCK: pin 13 arduino or pin 1 on sensor
* MCLK: pin 9 arduino or pin 6 on sensor
*********************************/

//creating the sensor
MS5541 PressSensor;

void setup() {
    Serial.begin(9600); 
}

void loop() {
  //Before getting the values you need to update the sensor
  PressSensor.update();
  
  //get pressure
  Serial.print("Pressure (mbar): ");
  Serial.println(PressSensor.getPressureMBar());
  Serial.print("Pressure (bar): ");
  Serial.println(PressSensor.getPressureBar(),3);
  
  //get temperature
  Serial.print("Temperature (celsius): ");
  Serial.println(PressSensor.getTemperatureC());
  
  //get 2nd temperature --> see datasheet for details
  Serial.print("Temperatre 2nd (celsius): ");
  Serial.println(PressSensor.get2ndTemperatureC());

  //get temperature
  Serial.print("Temperature (fahrenheit): ");
  Serial.println(PressSensor.getTemperatureF());
  
  //get 2nd temperature --> see datasheet for details
  Serial.print("Temperatre 2nd (fahrenheit): ");
  Serial.println(PressSensor.get2ndTemperatureF());
  
  Serial.println();
  
  delay(2000);
}