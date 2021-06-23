/* Example of Wifi OFF on ESP8266
 *  from https://github.com/esp8266/Arduino/issues/644 
 */
 
#include <ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:
WiFi.mode(WIFI_OFF);
}

void loop() {
  // put your main code here, to run repeatedly:
//ESP.deepSleep(25000000, WAKE_RF_DEFAULT);//The time is in microseconds

//do something here, eg.sensor reading, and LED task

}
