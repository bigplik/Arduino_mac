/* Example of spleep mode of ESP8266
 *  from http://www.esp8266.com/viewtopic.php?f=32&t=2305
 *  You need to connect the RESET and GPIO 16 (or other) pins 
 *  together for this to work... They are not exposed in all 
 *  of the ESP boards. 
 */
#include <ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
ESP.deepSleep(25000000, WAKE_RF_DEFAULT);//The time is in microseconds

//do something here, eg.sensor reading, and LED task

}
