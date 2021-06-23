#include <StopWatch.h>

#include <Flasher.h>

#define brakeSignal digitalRead(3)==1
byte mode = 0;

StopWatch sw_secs(StopWatch::SECONDS);
/*sw_secs.start(); sw_secs.stop(); sw_secs.elapsed();
sw_secs.value(); sw_reset();*/

void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Flasher slowG(5,500);
  //slowR.flash(1);
  Flasher brakeLight(7,300);
  switch (mode) {
    case 0:
        sw_secs.reset();
        //sw_secs.stop();
        if(brakeSignal) {brakeLight.flash(2),
            mode = 1;}
    break;
    case 1:      
        if(brakeSignal) digitalWrite(7,1);
            sw_secs.stop();
        if(!brakeSignal){
            sw_secs.start();
            if(sw_secs.value() >= 5) mode = 0;
            digitalWrite(7,0);
            }
    break;
  }
  delay(1);
}
