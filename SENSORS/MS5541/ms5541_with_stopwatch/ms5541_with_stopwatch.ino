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
float airPressure;
float waterPressure;



#include <StopWatch.h>

int minuty = 0;
int dive_time = 0;
//StopWatch sw_millis;    // MILLIS (default)
//StopWatch sw_micros(StopWatch::MICROS);
StopWatch sw_secs(StopWatch::SECONDS);



void setup() {
    Serial.begin(9600); 
    
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
  
  if(waterPressure > 0.0){
        
        
        sw_secs.start();
        dive_time = sw_secs.value();
    
     if(sw_secs.elapsed() == 60){
      
      minuty = minuty + 1;
      sw_secs.reset();
      
      
    }
    
    
    
    
    if(sw_secs.elapsed() <10){
    
    Serial.print(minuty);
    Serial.print(":0");
    Serial.println(sw_secs.elapsed());
    delay(250);
  
    }
    else{
    
    Serial.print(minuty);
    Serial.print(":");
    Serial.println(sw_secs.elapsed());
    delay(250);
      
    }
    
    
   Serial.println("CZAS NURKOWANIA: ");
   Serial.println(sw_secs.value());
   Serial.println(sw_secs.elapsed());
   Serial.println(dive_time);
   delay(2000);
    
    
  }
  
  else{
    
    sw_secs.stop();
    Serial.println(dive_time);
    Serial.println(sw_secs.value());
   Serial.println(sw_secs.elapsed());
    delay(2000);
    
  }
  
  
}
