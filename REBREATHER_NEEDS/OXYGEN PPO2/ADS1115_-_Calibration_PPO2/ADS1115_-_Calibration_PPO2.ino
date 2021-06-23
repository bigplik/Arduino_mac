#include <Wire.h>
#include <Adafruit_ADS1015.h>

double SmV, S2mV, S3mV;

 Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */
int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
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
  
  int16_t adc3, adc2, adc1;
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
 
  
}

void loop(void) 



{
  int16_t adc0, adc1, adc2, adc3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.println(" ");
  
  float sensorValue = adc3;
  float sensorValue2 = adc2;
  float sensorValue3 = adc1;
  float SmVact = adc3/5.0;
  float SmVact2 = adc2/5.0;
  float SmVact3 = adc1/5.0;
  float PPO2 = (SmVact * (0.21/SmV));
  float PPO22 = (SmVact2 * (0.21/S2mV));
  float PPO23 = (SmVact3 * (0.21/S3mV));
  
  Serial.print("PPO2: ");         Serial.println(PPO2*0.9797);
  Serial.print("SmV: ");          Serial.println(SmV);
  Serial.print("SmV_adj: ");      Serial.println(SmV * 0.039906103);
  Serial.print("firstValue1: ");  Serial.println(firstValue1);
  
  Serial.print("PPO22: ");         Serial.println(PPO22*0.9797);
  Serial.print("S2mV: ");          Serial.println(S2mV);
  Serial.print("SmV_adj2: ");      Serial.println(S2mV * 0.039906103);
  Serial.print("firstValue2: ");  Serial.println(firstValue2);
  
  Serial.print("PPO23: ");         Serial.println(PPO23*0.9797);
  Serial.print("S3mV: ");          Serial.println(S3mV);
  Serial.print("SmV_adj3: ");      Serial.println(S3mV * 0.039906103);
  Serial.print("firstValue3: ");  Serial.println(firstValue3);

  
  delay(1000);
}
