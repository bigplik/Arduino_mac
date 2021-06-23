// Mruga wbudowaną diodą świecącą przy pomocy biblioteki Timers
// Autor: Łukasz Tretyn - http://nettigo.pl

#include <Timers.h>



Timer ledBlinkTimer;

byte led;

void setup() {
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  ledBlinkTimer.time(SECS(2));
}

void loop() {
  
  if (ledBlinkTimer.available())
  {
    led +=50;
    if(led>250) led = 0;
    ledBlinkTimer.restart();
  }

  analogWrite(1,led);
}
