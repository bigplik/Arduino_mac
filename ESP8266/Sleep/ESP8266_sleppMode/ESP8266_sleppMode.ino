/* Example of spleep mode of ESP8266
 *  from http://www.esp8266.com/viewtopic.php?f=32&t=2305
 *  You need to connect the RESET and GPIO 16 pins together 
 *  for this to work... They are not exposed in all of the 
 *  ESP boards. 
 */
#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}


void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
//system_deep_sleep_set_option(0);
  for(int i=0; i<10; i++){
    digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
    delay(500);
  }

    //WiFi.mode(WIFI_OFF);
    //WiFi.disconnect(); // DO NOT DISCONNECT WIFI IF YOU WANT TO LOWER YOUR POWER !
    wifi_set_sleep_type(LIGHT_SLEEP_T);
    delay(5000); // 20s

//system_deep_sleep(6000000);//The time is in microseconds


//do something here, eg.sensor reading, and LED task

//other things
//ESP.deepSleep(25000000, WAKE_RF_DEFAULT); 

}
