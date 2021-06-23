//Blynk settings
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9cbad42a271b459d9a927057e2414090";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Kilimanjarro2";
char pass[] = "kasiapaweldaciamcv";

  BLYNK_WRITE(V0)
{
  boolean State = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  digitalWrite(0,State);
}

BLYNK_WRITE(V2)
{
  boolean State2 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  digitalWrite(2,State2);
}

void setup() {
  // put your setup code here, to run once:
  //Blynk
  Blynk.begin(auth, ssid, pass);

}

void loop() {
  Blynk.run();
}
