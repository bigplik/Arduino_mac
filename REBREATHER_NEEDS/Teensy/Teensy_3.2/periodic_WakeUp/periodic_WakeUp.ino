/***************************************
 * sleep with pushbutton w/ pullup.
 * expect IDD of around 900uA (Teensy 3.x).
 * and IDD of around 1.2mA (Teensy LC).
 ****************************************/
#include <Snooze.h>

/*** Must be global ***/
SnoozeBlock config;

void setup() {
    pinMode(13, OUTPUT);
    /***************************************
     * define the configuration parameters 
     * for waking the teensy up. Any digital 
     * pin can be used.
     *
     * This will configure the pin like the 
     * normal pinMode will.
     *
     * Not all pins are interrupt capibale 
     * with the Teensy LC, see pinout sheet.
     ****************************************/
    //config.pinMode(3, INPUT_PULLUP, RISING);
    config.setTimer(5000);
}


void loop() {
    /***************************************
     * feed the sleep function its wakeup 
     * parameters. Since USB is disabled blink 
     * the led to indicate a button was pushed 
     * and woke up the mcu.
     ****************************************/
    Snooze.sleep( config );
    for(int i=0; i<10; i++){
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    }
}
