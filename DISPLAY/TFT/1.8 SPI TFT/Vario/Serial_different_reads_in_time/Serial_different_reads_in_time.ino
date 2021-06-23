#include <StopWatch.h>

int sensor;
int change = 0;

StopWatch sw_secs(StopWatch::SECONDS);
StopWatch sw_mils(StopWatch::MILLIS);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
sensor = analogRead(A0);

if(sensor > 1000){ change = 1; }

    switch(change){
      case 0:
        Serial.println("START");
        Serial.println(sensor);
        
        break;
      case 1:
        Serial.println("RECORD");
        sw_secs.start();
        Serial.println(sw_secs.value());
        if(sw_secs.value() >= 10){
          checkSensor();
        }
        
        break;
      case 2:
        sw_secs.stop();
        Serial.println("STOP");
        Serial.println(sw_secs.value());
        break; 
    }
delay(500);
}

int checkSensor(){
  //sw_secs.stop();
  int sensor2 = analogRead(A0);
  if(sensor == sensor2){
    sw_mils.start();
   Serial.print("mils "); Serial.println(sw_mils.value()); 
   Serial.println("SAME READS - SENSOR STOP");
   Serial.println(sensor); Serial.println(sensor2);
   Serial.print("secs "); Serial.println(sw_secs.value());
   if(sw_mils.value()>=10000){ change=2; }
  }
  else{
    sw_mils.stop(); delay(5); sw_mils.reset();
    Serial.print("mils "); Serial.println(sw_mils.value());
    Serial.println("DIFFERENT READS - SENSOR WOKING");
    Serial.println(sensor);
    Serial.println(sensor2);
    Serial.print("secs "); Serial.println(sw_secs.value());
  }
  //sw_secs.reset();
}
