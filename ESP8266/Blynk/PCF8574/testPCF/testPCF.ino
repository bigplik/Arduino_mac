//PCF settings below
#include <Wire.h>
#include <ESP_PCF8574.h>

/*
 * espPCF.setBit(0,0) // first number is port #, second is 0-LOW, 1-HIGH
 * espPCF.setByte(1)  //send the 0-LOW, 1-HIGH to all OUTPUT GPIOS
 * espPCF.getByte() //get value of the all INPUT GPIOS
 * espPCF.getBit(0) //get value of port number (0-7) INPUT GPIO
 */
ESP_PCF8574 espPCF;

//Blynk settings
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Kilmanjarro2";
char pass[] = "kasiapaweldaciamcv";


  BLYNK_WRITE(V1)
{
  int pcfState = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  espPCF.setBit(0,pcfState);
}

BLYNK_WRITE(V2)
{
  int pcfState2 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  espPCF.setBit(1,pcfState2);
}

BLYNK_WRITE(V3)
{
  int pcfState3 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  espPCF.setBit(2,pcfState3);
}

BLYNK_WRITE(V4)
{
  int pcfState4= param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  espPCF.setBit(3,pcfState4);
}

BLYNK_WRITE(V5)
{
  int pcfState5 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  espPCF.setBit(4,pcfState5);
}

BLYNK_WRITE(V6)
{
  int pcfState6 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  espPCF.setBit(5,pcfState6);
}

BLYNK_WRITE(V7)
{
  int pcfState7 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  espPCF.setBit(6,pcfState7);
}

BLYNK_WRITE(V8)
{
  int pcfState8 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
  espPCF.setBit(7,pcfState8);
}


void setup() {
   //PCF
      espPCF.begin(0x20,4,5); //address, sda, scl

      espPCF.setByte(0);

   //Blynk
     Blynk.begin(auth, ssid, pass);

}

void loop() {
  Blynk.run();
}
