/***************************************
 * deepSleep with pushbutton w/ pullup.
 * Expect IDD of  around 230uA for deepSleep
 * and 15uA for hibernate (Teensy 3.x) and
 * IDD of around 150uA for deepSleep and 4uA
 * (Teensy LC).
 ****************************************/
#include <Snooze.h>

int count = 0;

/*** Must be global ***/
SnoozeBlock config;

void setup() {

    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(9,OUTPUT);
    /********************************************************
     * Define digital pins for waking the teensy up. This
     * combines pinMode and attachInterrupt in one function.
     *
     * Teensy 3.x
     * Digtal pins: 2,4,6,7,9,10,11,13,16,21,22,26,30,33
     *
     * Teensy LC
     * Digtal pins: 2,6,7,9,10,11,16,21,22
     
     * Configure the pin like the normal pinMode and append
     * the interrupt type for the third parameter.
     ********************************************************/
    config.pinMode(16, INPUT_PULLUP, RISING);//vibro sensor
}


void loop() {
    /************************
     * feed the sleep function
     * its wakeup parameters.
     * Since USB is disabled
     * blink the led to indicate
     * a button was pushed and
     * woke up the mcu.
     *************************/
     if(analogRead(A0) < 512){
      digitalWrite(11,LOW);
      count++;
      delay(1000);
      Serial.println(count);
      digitalWrite(9, !digitalRead(9));
      if(count > 10){
        digitalWrite(11&9,LOW);
        Snooze.deepSleep( config );
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        count = 0;
      }
     }
     else{
     digitalWrite(9,LOW);
     digitalWrite(11, !digitalRead(11));
     delay(2000);
     }
}
