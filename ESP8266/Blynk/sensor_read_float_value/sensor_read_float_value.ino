/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example shows how value can be pushed from Arduino to
 * the Blynk App.
 *
 * WARNING :
 * For this example you'll need SimpleTimer library:
 *   https://github.com/jfturcot/SimpleTimer
 * Visit this page for more information:
 *   http://playground.arduino.cc/Code/SimpleTimer
 *
 * App project setup:
 *   Value Display widget attached to V5
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <Ethernet.h>
//#include <BlynkSimpleEthernet.h>
#include <SimpleTimer.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e2e5a06027dd402294ea9806d58d5418";

SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendUptime()
{
  int sensorValue = analogRead(A0);
  float volt = (sensorValue/1024.0) * 3.3;

  int tempC = ((volt + 0.05) * 20);
  volt = (tempC / 20.0);
  String nowy = "zero";
  //Blynk.virtualWrite(0, tempC);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  float volt2 = analogRead(A0) * (3.3/1023.0);
  volt = volt - 0.05;
  Blynk.virtualWrite(V5, volt);
  Blynk.virtualWrite(V6, nowy);
  Blynk.virtualWrite(V7, "%2.f", volt);

}

//  BLYNK_READ(V0)
//{
//float vbat = (float)analogRead(A0)/75;
//Blynk.virtualWrite(0, vbat);
//}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, "HTC_one", "12345678");

  // Setup a function to be called every second
  timer.setInterval(1000L, sendUptime);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}


