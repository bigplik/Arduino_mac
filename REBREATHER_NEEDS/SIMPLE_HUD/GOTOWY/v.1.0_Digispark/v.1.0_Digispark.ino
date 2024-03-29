#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <StopWatch.h>
#include <Flasher.h>

#define greenLED 5
#define redLED 6
#define blueLED 3

char sensorStatus = 'a';

boolean buttonState = 0;
boolean buttonState2 = 0;
//boolean sensorStatus = 0;
boolean sensorStatus1 = 0;
boolean sensorStatus2 = 0;
boolean sensorStatus3 = 0;

byte time = 0;
byte timer = 0;
byte counter = 0;
byte counter2 = 0;
byte oxygen = 0;
byte altitude = 0;
byte altset = 0;
byte altset2 = 0;

    //brown wire
int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;
int hud = 0;

float SmV, S2mV, S3mV, SmV1, S2mV2, S3mV3;
float PPO2, PPO22,PPO23;
float altFactor = 1;
float O2factor  = 1;
float O2factor2 = 1;
float O2factor3 = 1;
float battery;
float avrPPO2;

Adafruit_ADS1115 ads;
StopWatch sw_secs(StopWatch::SECONDS);
/*sw_secs.start(); sw_secs.stop(); sw_secs.elapsed();
sw_secs.value(); sw_reset();*/

    void setup() {
      
      // put your setup code here, to run once:
//      Serial.begin(9600);
//      Serial.println("SIPMLE_HUD v.1.0");
      ads.begin();
      sw_secs.start();
      
      pinMode(greenLED, OUTPUT);  pinMode(redLED, OUTPUT);  pinMode(blueLED, OUTPUT);
      
      digitalWrite(3,HIGH);
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  ads.begin();
  ads.setGain(GAIN_SIXTEEN);
  
  int16_t adc3, adc2, adc1;
  adc3 = ads.readADC_SingleEnded(3);
  adc2 = ads.readADC_SingleEnded(2);
  adc1 = ads.readADC_SingleEnded(1);

          for(int j = 0 ; j < 10 ; j++)
        {
        firstValue1 += adc3;                         //sumowanie kolejnych pomiarów
        firstValue2 += adc2;
        firstValue3 += adc1;
        delay(100);                                               //opóźnienie
        }
    
    firstValue1 /=10;                              //liczenie wartości średniej
    firstValue2 /=10;                              //i zapamiętanie jej
    firstValue3 /=10;
    
        SmV = (firstValue1/5.0); //dane przeliczone do miliVolt dla S1
        S2mV = (firstValue2/5.0);
        S3mV = (firstValue3/5.0);
        
        SmV1 = SmV*0.039906103;
        S2mV2 = S2mV*0.039906103;
        S3mV3 = S3mV*0.039906103;
        
  //**********FLASHER******************************
  ////////////////////////////////////////////////
  //Flasher(13,500); Flasher slowFlash(13,700); slowFlash.flash(20);
  Flasher slowG(5,500); Flasher slowR(6,500); Flasher slowB(3,500);
  Flasher fastG(5,200); Flasher fastR(6,200); Flasher fastB(3,200);
  
  //oznaczenie rozpoczęcia wskazań statusu sensorów przez LEDY
  digitalWrite(3,LOW);
  //***************wartości sensorów w miliVoltach
//   display.println(SmV*0.039906103);
//   display.println(S2mV*0.039906103);
//   display.println(S3mV*0.039906103);
   
  //*********************sensor ok lub old lub Err
  if(SmV1 >= 9.00 && SmV1 <= 13.00){        // 1 sensor - IF OK
    slowG.flash(3);
    sensorStatus1 = 1;
//    Serial.println("S1 - OK");
   }
  else if(SmV1 <=8.99 && SmV1 >=8.00){      // IF OLD
    slowB.flash(3);  slowR.flash(3);
    sensorStatus1 = 1;
//    Serial.println("S1 - OLD");
  }else{                                    // IF ERR
    fastR.flash(10);
    sensorStatus1 = 0;
//    Serial.println("S1 - Err");
  }
  delay(1000);
  
  
  if(S2mV2 >= 9.00 && S2mV2 <= 13.00){       // 2 sensor - IF OK
    slowG.flash(3);
    sensorStatus2 = 1;
//    Serial.println("S2 - OK");
  }
  else if(S2mV2 <=8.99 && S2mV2 >=8.00){    // IF OLD
    slowB.flash(3);  slowR.flash(3);
    sensorStatus2 = 1;
//    Serial.println("S2 - OLD");
  }else{                                    // IF ERR
    fastR.flash(10);
    sensorStatus2 = 0;
//    Serial.println("S2 - Err");
  }
  delay(1000);
  
  
  if(S3mV3 >= 9.00 && S3mV3 <= 13.00){      // 3 sensor - IF OK
    slowG.flash(3);
    sensorStatus3 = 1;
//    Serial.println("S3 - OK");
  }
  else if(S3mV3 <=8.99 && S3mV3 >=8.00){    // IF OLD
    slowB.flash(3);  slowR.flash(3);
    sensorStatus3 = 1;
//    Serial.println("S3 - OLD");
  }else{                                    // IF ERR
    fastR.flash(10);
    sensorStatus3 = 0;
//    Serial.println("S3 - Err");
  }
  delay(1000);  
  
//  Serial.println("SmV ----------");
//  Serial.println(SmV1); Serial.println(S2mV2); Serial.println(S3mV3);
//  Serial.println("Status 1-3 :");
//  Serial.println(sensorStatus1); Serial.println(sensorStatus2); Serial.println(sensorStatus3);
//average PPO2 calculations settings - take only working sensors

  if(sensorStatus1 == 1 && sensorStatus2 == 1 && sensorStatus3 == 1)  //TTT 111
  { sensorStatus = 'a';}
  if(sensorStatus1 == 1 && sensorStatus2 == 1 && sensorStatus3 == 0)  //TTF 110
  { sensorStatus = 'b';}
  if(sensorStatus1 == 1 && sensorStatus2 == 0 && sensorStatus3 == 0)  //TFF 100
  { sensorStatus = 'c';}
  if(sensorStatus1 == 0 && sensorStatus2 == 1 && sensorStatus3 == 1)  //FTT 11
  { sensorStatus ='d';} //011
  if(sensorStatus1 == 0 && sensorStatus2 == 1 && sensorStatus3 == 0)  //FTF 10
  { sensorStatus = 'e';} //010
  if(sensorStatus1 == 0 && sensorStatus2 == 0 && sensorStatus3 == 1)  //FFT 1
  { sensorStatus = 'f';} //001
  if(sensorStatus1 == 1 && sensorStatus2 == 0 && sensorStatus3 == 1)  //TFT 101
  { sensorStatus = 'g';}
  if(sensorStatus1 == 0 && sensorStatus2 == 0 && sensorStatus3 == 0)  //FFF 0
  { sensorStatus = 'h';} //000
  delay(50);
//  Serial.print("sensor status ");
//  Serial.println(sensorStatus);
//************bateria****************
 //make some combination of LED flash to show battery voltage 3 times
 for(byte a=0; a<3; a++){
  redOn();delay(500);allOff(); greenOn();delay(500);allOff(); blueOn();delay(500);allOff();
 }
//battery volts calculation
   battery = (analogRead(A3) * (5.0 / 1023.0)*1.83);                            //liczenie wartości średniej
                                                       //i zapamiętanie jej   
//   Serial.print("battery volts ");
//   Serial.println(battery);                            
//battery volts interpretation
   if(battery >= 3.45){ digitalWrite(5,HIGH); }
   else if(battery < 3.45 && battery >= 3.2){ digitalWrite(3,HIGH); }
   else if(battery < 3.2 && battery >= 2.95){ digitalWrite(5,HIGH); }
   else{ fastR.flash(10); }
   delay(4000);
   allOff();
}



void loop() {
  
    int16_t adc0, adc1, adc2, adc3;
  
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  delay(50);
  float SmVact = adc3/5.0;
  float SmVact2 = adc2/5.0;
  float SmVact3 = adc1/5.0;
  float PPO2 = (SmVact * (0.21/SmV));
  float PPO22 = (SmVact2 * (0.21/S2mV));
  float PPO23 = (SmVact3 * (0.21/S3mV));
  delay(50);
  
  if(sensorStatus == 'a')    //TTT
  { avrPPO2 = (PPO2 + PPO22 + PPO23)/3;}
  if(sensorStatus == 'b')       //TTF
  { avrPPO2 = (PPO2 + PPO22)/2;}
  if(sensorStatus == 'c')       //TFF 100
  { avrPPO2 = PPO2;}
  if(sensorStatus == 'd')      //FTT
  { avrPPO2 = (PPO22 + PPO23)/2;}
  if(sensorStatus == 'e')      //FTF 010
  { avrPPO2 = PPO22;}
  if(sensorStatus == 'f')      //FFT
  { avrPPO2 = PPO23;}
  if(sensorStatus == 'g')      //TFT
  { avrPPO2 = (PPO2 + PPO23)/2;}
  if(sensorStatus == 'h')      //FFF
  { avrPPO2 = 0.01; }
  
//  
//  Serial.print("loop - sensor status: ");
//  Serial.println(sensorStatus);
//  delay(500);
  
  Flasher slowG(5,500); Flasher slowR(6,500); Flasher slowB(3,500);
  Flasher fastG(5,200); Flasher fastR(6,150); Flasher fastB(3,200);
//  
//  Serial.println("loop");
//  Serial.print("avrPPO2: ");
//  Serial.println(avrPPO2);
//  Serial.println(PPO2);
//  Serial.println(PPO22);
//  Serial.print(PPO23);
  // put your main code here, to run repeatedly:

  
  //avrPPO2 = analogRead(A1) * (5.0/1023.0);
  if(avrPPO2 < 0.06){ sos(); }
  else if(avrPPO2 < 0.20 && avrPPO2 > 0.05){ 
  redOn(); greenOff();
  delay(200);
  redOff(); greenOn();
  delay(150);
  }
  else if(avrPPO2 > 0.19 && avrPPO2 < 0.4){ slowR.flash(1); greenOff(); blueOff(); }
  else if(avrPPO2 > 0.39 && avrPPO2 < 0.7){ blueOn(); redOff(); greenOff(); }
  else if(avrPPO2 > 0.69 && avrPPO2 < 1.21){ greenOn(); redOff(); blueOff();}
  else if(avrPPO2 > 1.20 && avrPPO2 < 1.4){ slowB.flash(1); redOff(); greenOff(); }
  else{ fastR.flash(1); blueOff(); greenOff(); }
}

void redOn(){ digitalWrite(redLED,HIGH);}
void greenOn(){ digitalWrite(greenLED,HIGH);}
void blueOn(){ digitalWrite(blueLED,HIGH);}
void orangeOn(){ analogWrite(redLED,200); analogWrite(greenLED,50); }
void allOff(){ digitalWrite(redLED,LOW);digitalWrite(greenLED,LOW);digitalWrite(blueLED,LOW);}
void redOff(){ digitalWrite(redLED,LOW); }
void greenOff(){ digitalWrite(greenLED,LOW); }
void blueOff(){ digitalWrite(blueLED,LOW); }
void sos() { 
Flasher fastRed(6,400); Flasher slowRed(6,800);
fastRed.flash(3);delay(200);slowRed.flash(3);delay(200);fastRed.flash(3);delay(2000); 
}
