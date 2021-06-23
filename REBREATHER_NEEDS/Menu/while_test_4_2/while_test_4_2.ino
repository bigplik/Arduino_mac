#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <StopWatch.h>

double SmV, S2mV, S3mV;

 Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */
int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;

int counter = 0;
int counter2 = 0;
int pin = 2; //default 2
int pin2 = 3;//default 3
int buttonState = 0;
int buttonState2 = 0;
int oxygen = 0;
int altitude = 0;
int altset = 0;
int altset2 = 0;
int time = 0;

float altFactor = 1;
float PPO2;
float PPO22;
float PPO23;
float O2factor  = 1;
float O2factor2 = 1;
float O2factor3 = 1;

StopWatch sw_secs(StopWatch::SECONDS);

void setup() {
  
  time = sw_secs.value();
  
  Serial.begin(9600);
  pinMode(pin, INPUT);
  pinMode(pin2, INPUT);
  buttonState = digitalRead(pin);
      buttonState2 = digitalRead(pin2);
  
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


  // put your setup code here, to run once:
  
  while(counter >= 0 & counter <4){
    Serial.println("For Calibration Settings press In Button,");
    Serial.println("else press Out Button");
    Serial.println(counter);
    Serial.println("time");
    Serial.println(sw_secs.value());
    
    buttonState = digitalRead(pin);
      buttonState2 = digitalRead(pin2);
      
      delay(1000);
      sw_secs.start();

      if(sw_secs.value() == 5){
        oxygen = 5;
        altitude = 5;
        altset = 5;
        counter = counter + 5;
        sw_secs.reset();
      }
        
        if(buttonState == HIGH){
     Serial.println("Skip");
     delay(2000);
    oxygen = 5;
    altitude = 5;
    altset = 5;
    counter = counter +5;
    //this is the section for air calibration code,
    //which would be used everytime
    //'fudge factor' from EEPROM could be read evertime
    //device is started, except the first time when nothig
    //is stored in EEPROM - in this case static function
    //could be used and != function, which compare if 'fudge
    //factor' is different than 1, what could be as a static value
    //if 'fudge factor' read from EEPROM is different than 1
    //then should be used for PPO2 calculation instead of 1 static
    //value
    }
    
    
   if(buttonState2 == HIGH){
    Serial.println("Calibration Settings");
    delay(2000);
    counter = counter +5;
    oxygen = 2;
    //oxygen calibration, this partion of the code
    //should 'calibrate' O2 sensors, by adjusting them to
    //eg. 0.99 PPO2 at 1.ATA at attitiude sea level (1025,0mbar)
    //by creating 'fudge factor' for multiplying raw PPO2
    //readings from the sensors by this factor
    //this value could be saved in EEPROM and by used for
    //air calibration for everytime device is started    
    }
  
  }
  
  delay(500);
  
  while(oxygen >= 0 && oxygen <=4){      //kalibracja tlenowa
      Serial.println("For Oxygen Calibration Settings press In Button,");
      Serial.println("else press Out Button");
      
      buttonState = digitalRead(pin);
      buttonState2 = digitalRead(pin2);
      
      delay(1000);
    
//    delay(50);
//    Vector norm = accelerometer.readNormalize();
//  // Read activities
//    Activites activ = accelerometer.readActivites(); 
      
      if(buttonState == HIGH){
          Serial.println("Skipping");
          delay(2000);
          oxygen = 5;
          altitude = 0;
      }
        
      if(buttonState2 == HIGH){
          Serial.println("Oxygen Calibration Process");
          delay(2500);
          kalibracja_tlen();
          oxygen = 5;
          altitude = 0;  
      }
      
    }
  
        
    while(altitude >= 0 && altitude <=4){      //kalibracja wysokości
      Serial.println("For Altitude Calibration Settings press In Button,");
      Serial.println("else press Out Button");
      
      buttonState = digitalRead(pin);
      buttonState2 = digitalRead(pin2);
      
      delay(1000);
    
//    delay(50);
//    Vector norm = accelerometer.readNormalize();
//  // Read activities
//    Activites activ = accelerometer.readActivites(); 
      
      if(buttonState == HIGH){
          Serial.println("Skipping");
          delay(2000);
          altitude = 5;
          altset = 5;
      }
        
      if(buttonState2 == HIGH){
          Serial.println("Altitude Settings Process");
          delay(2500);

          altitude = 5;   
          altset = 0;
      }
  
    }
    
    
  while(altset >=0 && altset <=4){   //przedziały wysokości
  
  Serial.println("For Altitude level settings press Out Button");
  Serial.println("else press In Button");
//    delay(50);
//    Vector norm = accelerometer.readNormalize();
//  // Read activities
//    Activites activ = accelerometer.readActivites();

     buttonState = digitalRead(pin);
     buttonState2 = digitalRead(pin2);
    wysok();
    Serial.println(altset2);
    
    delay(1000);
    
    if(buttonState == HIGH){
      altset2 = altset2 + 1;

    }
        
      if(buttonState2 == HIGH){
          altset = 5;
        }
      }
  
  
  
  
  while(counter == 5){
  Serial.println("Przeszło");
  delay(2000);
  counter = 0;
  counter2 = 0;
  }
  
  pinMode(13, OUTPUT);
  
}


void wysok(){
  
           switch(altset2){
                 case 0:
                     Serial.println("0m");
                     altFactor = 1;
                     break;
                 case 1:
                     Serial.println("300m");
                     altFactor = 0.964940;
                     break;
                 case 2:
                     Serial.println("600m");
                     altFactor = 0.9308828029;
                     break;
                 case 3:
                     Serial.println("900m");
                     altFactor = 0.8978050827;
                     break;
                 case 4:
                     Serial.println("1200m");
                     altFactor = 0.8656856649;
                     break;
                 case 5:
                     Serial.println("1500m");
                     altFactor = 0.8345028374;
                     break;
         }
         
        if(altset2 > 5){
        altset2 = 0;
        }

//           switch(altset2){
//                 case 0:
//                     Serial.println("0-100m");
//                     //factorPPO2 = 1;
//                     break;
//                 case 1:
//                     Serial.println("100-200m");
//                     //factorPPO2 = 0.96;
//                     break;
//                 case 2:
//                     Serial.println("200-300m");
//                     //factorPPO2 = 0.94;
//                     break;
//         }
//         
//        if(altset2 > 2){
//        altset2 = 0;
//        }

}


void kalibracja_tlen(){
  
//          PPO2 = 0.96;  this only for tests
//          PPO22 = 0.98; when ads is off
//          PPO23 = 0.99;
     
          Serial.println("Oxygen Calibration");
          delay(5000);
          
          if(PPO2 != 0.98){
            O2factor = 0.98/PPO2;
          }
          if(PPO22 != 0.98){
            O2factor2 = 0.98/PPO22;
          }
          if(PPO23 != 0.98){
            O2factor3 = 0.98/PPO23;
          }
          else{
            O2factor  = 1;
            O2factor2 = 1;
            O2factor3 = 1;
          }
        Serial.println(O2factor);
        Serial.println(O2factor2);
        Serial.println(O2factor3);
        delay(1000);
}


void loop() {
  
  buttonState = digitalRead(pin);
    buttonState2 = digitalRead(pin2);

    

    if(buttonState == HIGH){
    counter2 = counter2 +1;
    //delay(1);
    }
    
    
   if(buttonState2 == HIGH){
     counter = counter + 1;
   //counter2 = counter2 +1;
   //counter2 = counter2 - 1;
   //     delay(1);

    }
    
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
  float PPO2 = (SmVact * (0.21/SmV)) * O2factor * altFactor;
  float PPO22 = (SmVact2 * (0.21/S2mV)) * O2factor2 * altFactor;
  float PPO23 = (SmVact3 * (0.21/S3mV)) * O2factor3 * altFactor;
  
  Serial.print("PPO2: ");         Serial.println(PPO2);
  Serial.print("SmV: ");          Serial.println(SmV);
  Serial.print("SmV_adj: ");      Serial.println(SmV * 0.039906103);
  Serial.print("firstValue1: ");  Serial.println(firstValue1);
  
  Serial.print("PPO22: ");         Serial.println(PPO22);
  Serial.print("S2mV: ");          Serial.println(S2mV);
  Serial.print("SmV_adj2: ");      Serial.println(S2mV * 0.039906103);
  Serial.print("firstValue2: ");  Serial.println(firstValue2);
  
  Serial.print("PPO23: ");         Serial.println(PPO23);
  Serial.print("S3mV: ");          Serial.println(S3mV);
  Serial.print("SmV_adj3: ");      Serial.println(S3mV * 0.039906103);
  Serial.print("firstValue3: ");  Serial.println(firstValue3);

  Serial.print("nie dupa");
  Serial.println(counter);
  Serial.println(counter2);
  Serial.println("factor PPO2 ");
  Serial.println(altFactor, 2);
  Serial.println("-----------------");
  
  delay(1000);
  /*
  if(millis()>3000){
  delay(2000);
  if(buttonState == HIGH){
    
    counter2 = counter2 +10;
    
  }
  

}
  */ 
  


  


}
