//Expander board settings below
#include <Wire.h>
#include <Expander.h>

/*
 * expander.setBit(0,0) // first number is port #, second is 0-LOW, 1-HIGH
 * expander.setByte(1)  //send the 0-LOW, 1-HIGH to all OUTPUT GPIOS
 * expander.getByte() //get value of the all INPUT GPIOS
 * expander.getBit(0) //get value of port number (0-7) INPUT GPIO
 */

Expander espander;

//Blynk settings
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "token";
//my example token 9cbad42a271b459d9a927057e2414090

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Kilimanjarro2";
char pass[] = "kasiapaweldaciamcv";
//char ssid[] = "network";
//char pass[] = "password";


void setup() {
  // put your setup code here, to run once:
  //Expander board
  ekspander.begin(0x20,0,2) //address, sda, scl

  //Blynk
  Blynk.begin(aut, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:

}
