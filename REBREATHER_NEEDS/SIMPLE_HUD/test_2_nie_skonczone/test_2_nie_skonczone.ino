#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <StopWatch.h>
#include <Flasher.h>

#define greenLED 8
#define redLED 10
#define blueLED 9

boolean buttonState = 0;
boolean buttonState2 = 0;
boolean statusS1 = 0;
boolean statusS2 = 0;
boolean statusS3 = 0;

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
      Serial.begin(9600);
      ads.begin();
      sw_secs.start();
      
      pinMode(greenLED, OUTPUT);  pinMode(redLED, OUTPUT);  pinMode(blueLED, OUTPUT);
      
      digitalWrite(9,HIGH);
  
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
  Flasher slowG(8,500); Flasher slowR(10,500); Flasher slowB(9,500);
  Flasher fastG(8,200); Flasher fastR(10,200); Flasher fastB(9,200);
  
  //oznaczenie rozpoczęcia wskazań statusu sensorów przez LEDY
  digitalWrite(9,LOW);
  //***************wartości sensorów w miliVoltach
//   display.println(SmV*0.039906103);
//   display.println(S2mV*0.039906103);
//   display.println(S3mV*0.039906103);
   
  //*********************sensor ok lub old lub Err
  if(SmV1 >= 9.00 && SmV1 <= 13.00){        // 1 sensor - IF OK
    slowG.flash(3);
    statusS1 = 1;
   }
  else if(SmV1 <=8.99 && SmV1 >=8.00){      // IF OLD
    slowB.flash(3);  slowR.flash(3);
    statusS1 = 1;
  }else{                                    // IF ERR
    fastR.flash(10);
    statusS1 = 0;
  }
  delay(1000);
  
  
  if(S2mV2 >= 9.00 && S2mV2 <= 13.00){       // 2 sensor - IF OK
    slowG.flash(3);
    statusS2 = 1;
  }
  else if(S2mV2 <=8.99 && S2mV2 >=8.00){    // IF OLD
    slowB.flash(3);  slowR.flash(3);
    statusS2 = 1;
  }else{                                    // IF ERR
    fastR.flash(10);
    statusS2 = 0;
  }
  delay(1000);
  
  
  if(S3mV3 >= 9.00 && S3mV3 <= 13.00){      // 3 sensor - IF OK
    slowG.flash(3);
    statusS3 = 1;
  }
  else if(S3mV3 <=8.99 && S3mV3 >=8.00){    // IF OLD
    slowB.flash(3);  slowR.flash(3);
    statusS3 = 1;
  }else{                                    // IF ERR
    fastR.flash(10);
    statusS3 = 0;
  }
  delay(1000);  
  
  Serial.print("sensor status ");
  Serial.print(statusS1); Serial.print(statusS2); Serial.println(statusS3);
  Serial.println("SmV ----------");
  Serial.println(SmV1); Serial.println(S2mV2); Serial.println(S3mV3);
//average PPO2 calculations settings - take only working sensors

//  if(statusS1 == 1 && statusS2 == 1 && statusS3 == 1)        //TTT
//  { avrPPO2 = (PPO2 + PPO22 + PPO23)/3;}
//  if(statusS1 == 1 && statusS2 == 1 && statusS3 == 0)  //TTF
//  { avrPPO2 = (PPO2 + PPO22)/2;}
//  if(statusS1 == 1 && statusS2 == 0 && statusS3 == 0)  //TFF
//  { avrPPO2 = PPO2;}
//  if(statusS1 == 0 && statusS2 == 1 && statusS3 == 0)  //FTT
//  { avrPPO2 = (PPO22 + PPO23)/2;}
//  if(statusS1 == 0 && statusS2 == 1 && statusS3 == 0)  //FTF
//  { avrPPO2 = PPO22;}
//  if(statusS1 == 0 && statusS2 == 0 && statusS3 == 1)  //FFT
//  { avrPPO2 = PPO23;}
//  if(statusS1 == 1 && statusS2 == 0 && statusS3 == 1)  //TFT
//  { avrPPO2 = (PPO2 + PPO23)/2;}
//  if(statusS1 == 0 && statusS2 == 0 && statusS3 == 0)
//  { avrPPO2 = 1.1111 ;}
//  delay(50);

//************bateria****************
 //make some combination of LED flash to show battery voltage 3 times
 for(byte a=0; a<3; a++){
  redOn();delay(500);allOff(); greenOn();delay(500);allOff(); blueOn();delay(500);allOff();
 }
//battery volts calculation
   battery = analogRead(A1) * (5.0 / 1023.0);                            //liczenie wartości średniej
                                                       //i zapamiętanie jej   
   Serial.print("battery volts ");
   Serial.print(battery);                            
//battery volts interpretation
   if(battery >= 3.45){ digitalWrite(8,HIGH); }
   else if(battery < 3.45 && battery >= 3.2){ digitalWrite(9,HIGH); }
   else if(battery < 3.2 && battery >= 2.95){ digitalWrite(10,HIGH); }
   else{ fastR.flash(10); }
   delay(4000);
   allOff();
}



void loop() {
  
  int wynik = 1;
  
  switch (wynik){
    case 1:
      avrPPO2 = (PPO2 + PPO22 + PPO23)/3;
      break;
    case 2:
      avrPPO2 = (PPO2 + PPO22)/2;
      break;
    case 3:
      avrPPO2 = PPO2;
      break;
    case 4:
      avrPPO2 = (PPO22 + PPO23)/2;
      break;
    case 5:
      avrPPO2 = PPO22;
      break;
    case 6:
      avrPPO2 = PPO23;
      break;
    case 7:
      avrPPO2 = (PPO2 + PPO23)/2;
      break;
    case 8:
      avrPPO2 = 1.1111 ;
      break;    
  }
  
  Flasher slowG(8,500); Flasher slowR(10,500); Flasher slowB(9,500);
  Flasher fastG(8,200); Flasher fastR(10,150); Flasher fastB(9,200);
  
  Serial.println("loop");
  Serial.print("avrPPO2: ");
  Serial.println(avrPPO2);
  Serial.println(PPO2);
  Serial.println(PPO22);
  Serial.print(PPO23);
  // put your main code here, to run repeatedly:
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
  
  //avrPPO2 = analogRead(A1) * (5.0/1023.0);
  
  if(avrPPO2 < 0.20){ redOn();delay(200);redOff(); greenOn();delay(200);greenOff(); }
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
