/***************************************
 * deepSleep with pushbutton w/ pullup.
 * Expect IDD of  around 230uA for deepSleep
 * and 15uA for hibernate (Teensy 3.x) and
 * IDD of around 150uA for deepSleep and 4uA
 * (Teensy LC).
 ****************************************/
#include <Snooze.h>

/*** Must be global ***/
SnoozeBlock config;

boolean state = true;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
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
    config.pinMode(10, INPUT_PULLUP, RISING);
    pinMode(9,INPUT_PULLUP);
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
    switch(state){
      
      case false:
            Serial.println("Sleep");
            delay(200);
            Snooze.deepSleep( config );
            state =! state;
            break;
      case true:
            Serial.println("Wake_Up");
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            digitalWrite(LED_BUILTIN, LOW);
            if(digitalRead(9) == LOW) state =! state;
            break;
    }
    Serial.println(state);
    //delay(200);
}
