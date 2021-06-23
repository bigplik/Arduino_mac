#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <StopWatch.h>
#include <PCF8574.h>
#include "U8glib.h"

//#define pin 2
//#define pin2 3
#define greenLED 6    //blue wire
#define redLED 3      //brown wire

float SmV, S2mV, S3mV;

int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;
byte time = 0;
//int bat = 0;

byte timer;

byte counter = 0;
byte counter2 = 0;
//int pin = 2; //default 2
//int pin2 = 3;//default 3
boolean buttonState = 0;
boolean buttonState2 = 0;
byte oxygen = 0;
byte altitude = 0;
byte altset = 0;
byte altset2 = 0;

float altFactor = 1;
float PPO2;
float PPO22;
float PPO23;
float O2factor  = 1;
float O2factor2 = 1;
float O2factor3 = 1;
float bat1 = 0;

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);
//U8GLIB_SH1106_128X64 u8g(13, 11, 10, 8);
PCF8574 expander;
StopWatch sw_secs(StopWatch::SECONDS);


void u8g_prepare(void) {
  //u8g.setFont(u8g_font_osb21);
  u8g.setFont(u8g_font_courR18);
  //u8g.setFont(u8g_font_profont17);//10-17
  //u8g.setFont(u8g_font_unifont);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
 
}

void setup() {
  
//  // assign default color value
//  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
//    u8g.setColorIndex(255);     // white
//  }
//  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
//    u8g.setColorIndex(3);         // max intensity
//  }
//  else if ( u8g.getMode() == U8G_MODE_BW ) {
//    u8g.setColorIndex(1);         // pixel on
//  }
//  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
//    u8g.setHiColorByRGB(255,255,255);
//  }
//  
//  
    u8g.firstPage();  
  do {
      u8g_prepare();
      uint8_t a;
        //u8g.setFont(u8g_font_timB18r);
        u8g.drawStr( 18, 22, "ORIGIN");  //1-szer, 2-wys,
        u8g.setFont(u8g_font_profont10);
//        u8g.drawStr( 25, 14, "BDS PPO2 Display");
        u8g.drawStr( 24, 60, "while_test_4_4_5");
//        u8g.drawRFrame(16,20,97,30, a+1);
      } while( u8g.nextPage() );
      delay(2000);
  
  time = sw_secs.value();
  
  Serial.begin(9600);
  expander.begin(0x38);
//  pinMode(pin, INPUT);
//  pinMode(pin2, INPUT);
//  expander.pinMode(7, OUTPUT);
//  expander.pinMode(6, OUTPUT);
  expander.pinMode(0, INPUT);
  expander.pinMode(1, INPUT);
//  pinMode(13, OUTPUT);
//  digitalWrite(13, HIGH);
  pinMode(2, OUTPUT);
  buttonState = expander.digitalRead(0);
      buttonState2 = expander.digitalRead(1);
  
  
//  Serial.println("Hello!");
//  Serial.println("Getting single-ended readings from AIN0..3");
//  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
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


//  while(counter >= 0 & counter <4){
////    Serial.println("For Calibration Settings press In Button,");
////    Serial.println("else press Out Button");
////    Serial.println(counter);
////    Serial.println("time");
////    Serial.println(sw_secs.value());
//  
//  u8g.firstPage();
//    do {    
//  u8g_prepare();
//      uint8_t a;
//        //u8g.setFont(u8g_font_timB18r);
//        u8g.drawStr( 2, 5, "SETTINGS");  //1-szer, 2-wys,
//        u8g.setFont(u8g_font_profont10);
//        //u8g.drawStr( 0, 10, "Settings ");
//        u8g.drawStr( 25, 35, "press In Button");
//        u8g.drawStr( 42, 55, "for skip");
//        u8g.drawStr( 2, 64, "wait or press Out Button");
//      } while( u8g.nextPage() );
//    
//      buttonState = expander.digitalRead(0);
//        buttonState2 = expander.digitalRead(1);
//      
//      //delay(1000);
//      sw_secs.start();
//
//      if(sw_secs.value() == 5){
//        oxygen = 5;
//        altitude = 5;
//        altset = 5;
//        counter = counter + 5;
//        sw_secs.reset();
//      }
//        
//        if(buttonState == HIGH){
//        //Serial.println("Skip");
//  
//        u8g.firstPage();  
//        do {
//            u8g_prepare();
//            uint8_t a;
//              u8g.setFont(u8g_font_timB18r);
//              u8g.drawStr( 38, 40, "SKIP");  //1-szer, 2-wys,
//            } while( u8g.nextPage() );
//    
//    //delay(2000);
//    
//    oxygen = 5;
//    altitude = 5;
//    altset = 5;
//    counter = counter +5;
//    //this is the section for air calibration code,
//    //which would be used everytime
//    //'fudge factor' from EEPROM could be read evertime
//    //device is started, except the first time when nothig
//    //is stored in EEPROM - in this case static function
//    //could be used and != function, which compare if 'fudge
//    //factor' is different than 1, what could be as a static value
//    //if 'fudge factor' read from EEPROM is different than 1
//    //then should be used for PPO2 calculation instead of 1 static
//    //value
//    }
//    
//    
//   if(buttonState2 == HIGH){
//    //Serial.println("Calibration Settings");
//    //delay(2000);
//    counter = counter +5;
//    oxygen = 2;
//    //oxygen calibration, this partion of the code
//    //should 'calibrate' O2 sensors, by adjusting them to
//    //eg. 0.99 PPO2 at 1.ATA at attitiude sea level (1025,0mbar)
//    //by creating 'fudge factor' for multiplying raw PPO2
//    //readings from the sensors by this factor
//    //this value could be saved in EEPROM and by used for
//    //air calibration for everytime device is started    
//    }
//  
//  }
//  
//  delay(500);
//  sw_secs.reset();

  
//  while(oxygen >= 0 && oxygen <=4){      //kalibracja tlenowa
////      Serial.println("For Oxygen Calibration Settings press In Button,");
////      Serial.println("else press Out Button");
////      Serial.println("time");
////      Serial.println(sw_secs.value());
//      
//      buttonState = expander.digitalRead(0);
//      buttonState2 = expander.digitalRead(1);
//      
//  u8g.firstPage();  
//  do {
//      u8g_prepare();
//      uint8_t a;
//        u8g.setFont(u8g_font_profont10);
//        u8g.drawStr( 4, 10, "For Oxygen Calibration");
//        u8g.drawStr( 24, 20, "press In Button");
//        u8g.drawStr( 40, 50, "for skip");
//        u8g.drawStr( 2, 60, "wait or press Out Button");
//      } while( u8g.nextPage() );
//      
//      //delay(1000);
//      sw_secs.start();
//
//
//      if(sw_secs.value() >= 20){
//        oxygen = 5;
//        altitude = 0;
//        //altset = 5;
//      }
//    
////    delay(50);
////    Vector norm = accelerometer.readNormalize();
////  // Read activities
////    Activites activ = accelerometer.readActivites(); 
//      
//      if(buttonState == HIGH){
//          //Serial.println("Skipping");
//          //delay(2000);
//          oxygen = 5;
//          altitude = 0;
//          
//      u8g.firstPage();  
//      do {
//        u8g_prepare();
//        uint8_t a;
//          u8g.setFont(u8g_font_timB18r);
//          u8g.drawStr( 38, 40, "SKIP");  //1-szer, 2-wys,
//        } while( u8g.nextPage() );
//        delay(500);
//      }
//        
//      if(buttonState2 == HIGH){
//          //Serial.println("Oxygen Calibration Process");
//          //delay(2500);
//          kalibracja_tlen();
//          oxygen = 5;
//          altitude = 0;
//      }
//      
//    }
//    
//    //delay(500);
//    sw_secs.reset();  
        
    while(altitude >= 0 && altitude <=4){      //kalibracja wysokości
//      Serial.println("For Altitude Calibration Settings press In Button,");
//      Serial.println("else press Out Button");
//      Serial.println("time");
      sw_secs.start();
      //Serial.println(sw_secs.value());
      
      buttonState = expander.digitalRead(0);
      buttonState2 = expander.digitalRead(1);
      
  u8g.firstPage();  
  do {
      u8g_prepare();
      uint8_t a;
        u8g.setFont(u8g_font_profont10);
        u8g.drawStr( 4, 10, "To Set Altitude Level");
        u8g.drawStr( 24, 20, "press In Button");
        u8g.drawStr( 40, 50, "for skip");
        u8g.drawStr( 2, 60, "wait or press Out Button");
      } while( u8g.nextPage() );
      
      //delay(1000);

      if(sw_secs.value() == 5){
        altitude = 5;
        altset = 5;
        sw_secs.reset();
      }
    
//    delay(50);
//    Vector norm = accelerometer.readNormalize();
//  // Read activities
//    Activites activ = accelerometer.readActivites(); 
      
      if(buttonState == HIGH){
          //Serial.println("Skipping");
          //delay(2000);
          altitude = 5;
          altset = 5;
          
      u8g.firstPage();  
      do {
        u8g_prepare();
        uint8_t a;
//          u8g.setFont(u8g_font_timB18r);
          u8g.drawStr( 38, 28, "SKIP");  //1-szer, 2-wys,
        } while( u8g.nextPage() );
        delay(500);         
      }
        
      if(buttonState2 == HIGH){
          //Serial.println("Altitude Settings Process");
          //delay(2500);
          altitude = 5;   
          altset = 0;
      }
    }
    
  //delay(500);
  sw_secs.reset();
  
  while(altset >=0 && altset <=4){   //przedziały wysokości
  
//    Serial.println("For Altitude level settings press Out Button");
//    Serial.println("else press In Button");
//    Serial.println("time");
//    Serial.println(sw_secs.value());
//    delay(50);
//    Vector norm = accelerometer.readNormalize();
//  // Read activities
//    Activites activ = accelerometer.readActivites();
     sw_secs.start();
     
     buttonState = expander.digitalRead(1);
     buttonState2 = expander.digitalRead(0);
    wysok();
//    Serial.println(altset2);
    
    //delay(1000);

      if(sw_secs.value() == 120){
        altset = 5;
        sw_secs.reset();
      }
    
    if(buttonState == HIGH){
      altset2 = altset2 + 1;

    }
        
      if(buttonState2 == HIGH){
          altset = 5;
          
          u8g.firstPage();  
          do {
            u8g_prepare();
            uint8_t a;
//              u8g.setFont(u8g_font_timB18r);
              u8g.drawStr( 34, 28, "SAVE");  //1-szer, 2-wys,
            } while( u8g.nextPage() );
            delay(500);
        }
      }
  
  
  
  
  while(counter >= 5){
//  Serial.println("Przeszło");
//  delay(2000);
  counter = 0;
  counter2 = 0;
  }
  
//  digitalWrite(13, LOW);
  
}


void wysok(){

           switch(altset2){
                 case 0:
//                     Serial.println("0m");
                     altFactor = 1;
                     u8g.firstPage();
                        do {    
                        u8g_prepare();
                          uint8_t a;
                            u8g.drawStr( 52, 44, "0m");
                            u8g.setFont(u8g_font_profont10);
                            u8g.drawStr( 45, 10, "Sea Level");  //1-szer, 2-wys,;
//                            u8g.setFont(u8g_font_timB18r);
                          } while( u8g.nextPage() );
                     break;
                 case 1:
//                     Serial.println("300m");
                     altFactor = 0.964940;
                     u8g.firstPage();
                        do {    
                        u8g_prepare();
                          uint8_t a;
                            u8g.drawStr( 37, 44, "300m");
                            u8g.setFont(u8g_font_profont10);
                            u8g.drawStr( 45, 10, "ALTITUDE");
//                            u8g.setFont(u8g_font_timB18r);
                            
                          } while( u8g.nextPage() );
                     break;
                 case 2:
//                     Serial.println("600m");
                     altFactor = 0.9308828029;
                        u8g.firstPage();
                        do {    
                        u8g_prepare();
                          uint8_t a;
                            u8g.drawStr( 37, 44, "600m");
                            u8g.setFont(u8g_font_profont10);
                            u8g.drawStr( 45, 10, "ALTITUDE");
//                            u8g.setFont(u8g_font_timB18r);
                          } while( u8g.nextPage() );
                     break;
                 case 3:
//                     Serial.println("900m");
                     altFactor = 0.8978050827;
                     u8g.firstPage();
                        do {    
                        u8g_prepare();
                          uint8_t a;
                            u8g.drawStr( 37, 44, "900m");
                            u8g.setFont(u8g_font_profont10);
                            u8g.drawStr( 45, 10, "ALTITUDE");
//                            u8g.setFont(u8g_font_timB18r);
                          } while( u8g.nextPage() );
                     break;
                 case 4:
//                     Serial.println("1200m");
                     altFactor = 0.8656856649;
                     u8g.firstPage();
                        do {    
                        u8g_prepare();
                          uint8_t a;
                            u8g.drawStr( 32, 44, "1200m");
                            u8g.setFont(u8g_font_profont10);
                            u8g.drawStr( 45, 10, "ALTITUDE");
//                            u8g.setFont(u8g_font_timB18r);
                          } while( u8g.nextPage() );
                     break;
                 case 5:
//                     Serial.println("1500m");
                     altFactor = 0.8345028374;
                     u8g.firstPage();
                        do {    
                        u8g_prepare();
                          uint8_t a;
                            u8g.drawStr( 32, 44, "1500m");
                            u8g.setFont(u8g_font_profont10);
                            u8g.drawStr( 45, 10, "ALTITUDE");
//                            u8g.setFont(u8g_font_timB18r);
                          } while( u8g.nextPage() );
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


//void kalibracja_tlen(){
//  
////    int16_t adc3, adc2, adc1;
////  adc3 = ads.readADC_SingleEnded(3);
////  adc2 = ads.readADC_SingleEnded(2);
////  adc1 = ads.readADC_SingleEnded(1);
//////          PPO2 = 0.96;  this only for tests
//////          PPO22 = 0.98; when ads is off
//////          PPO23 = 0.99;
////       for(int a=0 ; a < 10; a++)
////{       
////  SmVact = adc3/5.0;
////  SmVact2 = adc2/5.0;
////  SmVact3 = adc1/5.0;
////  delay(100);
////}
////
////SmVact /=10;                                                            //liczenie wartości średniej
////SmVact2 /=10;                                                            //i zapamiętanie jej
////SmVact3 /=10;
////
////  PPO2 = (SmV * (0.21/SmV));
////  PPO22 = (S2mV * (0.21/S2mV));
////  PPO23 = (S3mV * (0.21/S3mV));
//
////          Serial.println("Oxygen Calibration");
//          delay(5000);
//          
//          if(PPO2 != 0.98){
//            O2factor = 0.98/PPO2;
//          }
//          if(PPO22 != 0.98){
//            O2factor2 = 0.98/PPO22;
//          }
//          if(PPO23 != 0.98){
//            O2factor3 = 0.98/PPO23;
//          }
//          else{
//            O2factor  = 1;
//            O2factor2 = 1;
//            O2factor3 = 1;
//          }
////        Serial.println(O2factor);
////        Serial.println(O2factor2);
////        Serial.println(O2factor3);
//        delay(1000);
//}


void loop() {
  
//  buttonState = expander.digitalRead(0);
//    buttonState2 = expander.digitalRead(1);

    

//    if(buttonState == HIGH){
//    counter2 = counter2 +1;
//    //delay(1);
//    }
//    
//    
//   if(buttonState2 == HIGH){
//     counter = counter + 1;
//   //counter2 = counter2 +1;
//   //counter2 = counter2 - 1;
//   //     delay(1);
//
//    }
    
    int16_t adc0, adc1, adc2, adc3;

  //adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
//  Serial.print("AIN0: "); Serial.println(adc0);
//  Serial.print("AIN1: "); Serial.println(adc1);
//  Serial.print("AIN2: "); Serial.println(adc2);
//  Serial.print("AIN3: "); Serial.println(adc3);
//  Serial.println(" ");
  
//  float sensorValue = adc3;
//  float sensorValue2 = adc2;
//  float sensorValue3 = adc1;
  float SmVact = adc3/5.0;
  float SmVact2 = adc2/5.0;
  float SmVact3 = adc1/5.0;
  float PPO2 = (SmVact * (0.21/SmV)) * O2factor * altFactor;
  float PPO22 = (SmVact2 * (0.21/S2mV)) * O2factor2 * altFactor;
  float PPO23 = (SmVact3 * (0.21/S3mV)) * O2factor3 * altFactor;
  delay(500);
//  Serial.print("PPO2: ");         Serial.println(PPO2);
//  Serial.print("SmV: ");          Serial.println(SmV);
//  Serial.print("SmV_adj: ");      Serial.println(SmV * 0.039906103);
//  Serial.print("firstValue1: ");  Serial.println(firstValue1);
//  
//  Serial.print("PPO22: ");         Serial.println(PPO22);
//  Serial.print("S2mV: ");          Serial.println(S2mV);
//  Serial.print("SmV_adj2: ");      Serial.println(S2mV * 0.039906103);
//  Serial.print("firstValue2: ");  Serial.println(firstValue2);
//  
//  Serial.print("PPO23: ");         Serial.println(PPO23);
//  Serial.print("S3mV: ");          Serial.println(S3mV);
//  Serial.print("SmV_adj3: ");      Serial.println(S3mV * 0.039906103);
//  Serial.print("firstValue3: ");  Serial.println(firstValue3);
//
//  Serial.print("nie dupa");
//  Serial.println(counter);
//  Serial.println(counter2);
//  Serial.println("factor PPO2 ");
//  Serial.println(altFactor, 2);
//  Serial.println("-----------------");
//  Serial.println(sw_secs.value());
//  delay(1000);
  
  /*
  if(millis()>3000){
  delay(2000);
  if(buttonState == HIGH){
    
    counter2 = counter2 +10;
    
  }
  

}
  */ 
  


    u8g.firstPage();  
    do {
    u8g_prepare();
  uint8_t a;
    //u8g.setFont(u8g_font_profont17);//10-17


          u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
          
          u8g.setPrintPos( 0, 4); //1st - 1-szer, 2-wysokosc
          u8g.print(PPO2);
   
          u8g.setPrintPos( 70, 4); //2nd
          u8g.print(PPO22);

          u8g.setPrintPos( 0, 34); //3rd
          u8g.print(PPO23);
          
          u8g.drawRFrame(65, 32,63 ,30, a+1);
          
/////////////////////////////////////////////////////////////////
///WARNING COMMANDS -- HUD LED LIGHTS////////////////////////////
/////////////////////////////////////////////////////////////////
  if ( PPO2 <= 0.40 || PPO22 <=0.40 || PPO23 <=0.40 ){  
//red LED on
      u8g.drawStr(73, 36, "LOW");
//      analogWrite(redLED, 255);
//      analogWrite(greenLED, 0);

  }
  else if ((PPO2 > 0.40 && PPO2 < 0.70) && (PPO22 > 0.40 && PPO22 < 0.70) && (PPO23 > 0.40 && PPO23 < 0.70)){
//orange LED on  
    u8g.setFont(u8g_font_courR14r);
    u8g.drawStr(69, 57, "^^^^^");
    orange();
  }
  else if ( PPO2 >= 1.40 || PPO22 >= 1.40 || PPO23 >= 1.40){
//red LED on   
    u8g.setFont(u8g_font_courR14r);
    u8g.drawStr(66,36, "HIGH");
  }else{
//green LED on
    u8g.setFont(u8g_font_courR14r);
    u8g.drawStr(75, 53, "~OK~");
    analogWrite(greenLED, 255);
    analogWrite(redLED, 0);
  }
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
              
       //LEDblink();
    } while( u8g.nextPage() );
    delay(500);
    // rebuild the picture after some delay

//timer do dopracowania
/*
  if((PPO2 && PPO22 || PPO2 && PPO23
  || PPO22 && PPO23 < 0.25) && (PPO2 && PPO23
  && PPO22 > 0.19)){
    if(timer > 20){
        u8g.sleepOn();
    }
  }else{
    u8g.sleepOff();
  }
  
  */
 /* 
  if(PPO2 && PPO22 || PPO2 && PPO23
  || PPO22 && PPO23 > 0.25){
  timer = 0;
  }
  */

//while(PPO2 <= 0.40 || PPO22 <0.40 || PPO23 <0.40){
//        analogWrite(redLED, 255);
//      analogWrite(greenLED, 0);
//      delay(100);
//      analogWrite(redLED, 0);
//      analogWrite(greenLED, 0);
//      delay(100);
//}



//Serial.println(timer);
//delay(200);
     if ( PPO2 <= 0.40 && PPO2 >=0.20 || PPO22 <=0.40 && PPO2 >= 0.20 || PPO23 <=0.40 && PPO23 >= 0.20 ){  
//red LED on
      analogWrite(redLED, 255);
      analogWrite(greenLED, 0);
      }
      else if ( PPO2 >= 1.40 || PPO22 >= 1.40 || PPO23 >= 1.40){
//red LED on   
      analogWrite(redLED, 255);
      analogWrite(greenLED, 0);
   
      }
//      else if ((PPO2 > 0.40 && PPO2 < 0.70) && (PPO22 > 0.40 && PPO22 < 0.70) && (PPO23 > 0.40 && PPO23 < 0.70)){
////orange LED on  
//       analogWrite(redLED, 230);
//       analogWrite(greenLED, 250);
//      }

      
      
//warning();

      if ( PPO2 < 0.20 || PPO22 <0.20 || PPO23 <0.20){ 
        sw_secs.start(); 
        if(sw_secs.value() >=3){
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);
        delay(1500);
        for(int q=0; q<5; q++){
        analogWrite(greenLED, 255);
        analogWrite(redLED, 0);
        delay(200);
        analogWrite(greenLED, 0);
        analogWrite(redLED, 255);
        delay(200);
        }
        }
      }else{
        digitalWrite(2, LOW);
        sw_secs.stop();
        sw_secs.reset();
      }
  
   
}




/*
void sleepDisplay(){
  
  if(counter == 0){
    u8g.sleepOff();   
  } else
  if(counter == 1){
    u8g.sleepOn();
  } 
  
  if(counter > 1){
    counter = 0;  
  } 
  

  
}
*/
/*
void idht(){
  
  DHT11.acquire();
  while (DHT11.acquiring())
    ;
  int result = DHT11.getStatus();
 
  //Serial.print("Humidity (%): ");
  humid = DHT11.getHumidity();

  //Serial.print("Temperature (oC): ");
  temp = DHT11.getCelsius();

  delay(500);
  
}
*/

////*************************************************
////****************warning commands**************
//void warning(){
//  u8g_prepare(); 
//
////else if ( PPO2 > 1.40 || PPO22 > 1.40 || PPO23 > 1.40){
////
//////red LED on   
//////    u8g.setFont(u8g_font_courR14r);
////    u8g.drawStr(70,34, "HIGH!");
////      analogWrite(redLED, 255);
////      analogWrite(greenLED, 0);
//////    digitalWrite(redLED, HIGH);        //turn on the Red LED
//////    digitalWrite(greenLED, LOW);       //turn off the Green LED
////    
////  }
//}
void orange(){
      analogWrite(redLED, 230);
      analogWrite(greenLED, 250);
}
