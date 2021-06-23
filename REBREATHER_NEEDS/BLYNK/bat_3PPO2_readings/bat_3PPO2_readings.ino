#include <Wire.h>
#include <Adafruit_ADS1015.h>
ADC_MODE(ADC_VCC);
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

float SmV, S2mV, S3mV, PPO2, PPO22, PPO23, SmVact, SmVact2, SmVact3;
int16_t adc0, adc1, adc2, adc3;

 Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */
int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;

void sendUptime()
{

  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  
  SmVact = adc3/5.0;
  SmVact2 = adc2/5.0;
   SmVact3 = adc1/5.0;
  PPO2 = (SmVact * (0.21/SmV));
  PPO22 = (SmVact2 * (0.21/S2mV));
  PPO23 = (SmVact3 * (0.21/S3mV));

  float bat = ESP.getVcc()*0.000952656;

  Blynk.virtualWrite(V5, PPO22);
  Blynk.virtualWrite(V6, PPO2);
  Blynk.virtualWrite(V7, PPO23);
  Blynk.virtualWrite(V8, bat);

}

void setup(void) 
{
  Serial.begin(115200);
  Blynk.begin(auth, "Kilimanjarro2", "kasiapaweldaciamcv");
  Wire.begin(4,5); //sda, scl

  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
   //ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
   ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();

  adc3 = ads.readADC_SingleEnded(3);
  adc2 = ads.readADC_SingleEnded(2);
  adc1 = ads.readADC_SingleEnded(1);

  //adc0 = ads.readADC_SingleEnded(0);
  //adc1 = ads.readADC_SingleEnded(1);
  //adc2 = ads.readADC_SingleEnded(2);
  
  
  for(int j = 0 ; j < 10 ; j++)

{
  


firstValue1 += adc3;                         //sumowanie kolejnych pomiarów
firstValue2 += adc2;
firstValue3 += adc1;
delay(100);                                               //opóźnienie

}

firstValue1 /=10;                                                            //liczenie wartości średniej
firstValue2 /=10;                                                            //i zapamiętanie jej
firstValue3 /=10;


SmV = (firstValue1/5.0); //dane przeliczone do miliVolt dla S1
S2mV = (firstValue2/5.0);
S3mV = (firstValue3/5.0);

delay(2000);
   timer.setInterval(2000L, sendUptime);
digitalWrite(13,LOW);
}

void loop(void) 



{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
