/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <PCF8574.h>
#include <Adafruit_ADS1015.h>
#include <StopWatch.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

#define greenLED 6
#define redLED 3

boolean buttonState = 0;
boolean buttonState2 = 0;

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
float bat1 = 0;

Adafruit_ADS1115 ads;
PCF8574 expander;
StopWatch sw_secs(StopWatch::SECONDS);


void setup()   {                
  Serial.begin(9600);
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(15);

  // Clear the buffer.
  display.clearDisplay();

time = sw_secs.value();
expander.begin(0x38);
expander.pinMode(0, INPUT);
expander.pinMode(1, INPUT);

buttonState = expander.digitalRead(0);
buttonState2 = expander.digitalRead(1);

//*************************logo*****************8
display.setTextSize(3);
display.setTextColor(WHITE);
  display.setCursor(10,22);
  display.println("Origin");
  display.display();
  delay(2500);
    uint16_t a;
    for( a=0; a<128; a++) display.drawPixel(a, 17, 1);
    
    for( a=0; a<128; a++) display.drawPixel(a, 50, 1);
    display.display();
    delay(800);
  display.setTextSize(2);
display.setTextColor(WHITE);
  display.setCursor(44,0);
  display.println("BDS");
  display.display();
  display.setTextSize(1);
display.setTextColor(WHITE);
  display.setCursor(29,56);
  display.println("PPO2 Display");
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setTextSize(1);
display.setTextColor(WHITE);
  display.setCursor(0,22);
  display.println("v.silmpe_I2C");
  display.setCursor(0,42);
  display.println("_no_bat_CASE");
  display.display();
  delay(1000);
  display.clearDisplay();
  
//******************************************  
//********************************kalibracja
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

firstValue1 /=10;                                                            //liczenie wartości średniej
firstValue2 /=10;                                                            //i zapamiętanie jej
firstValue3 /=10;

SmV = (firstValue1/5.0); //dane przeliczone do miliVolt dla S1
S2mV = (firstValue2/5.0);
S3mV = (firstValue3/5.0);

SmV1 = SmV*0.039906103;
S2mV2 = S2mV*0.039906103;
S3mV3 = S3mV*0.039906103;
  
  display.clearDisplay();
  delay(500);
  
  
  
  
  
  
  
  
  
  
  
  
     while(altitude >= 0 && altitude <=4){      //kalibracja wysokości
//      Serial.println("For Altitude Calibration Settings press In Button,");
//      Serial.println("else press Out Button");
//      Serial.println("time");
      display.clearDisplay();
      sw_secs.start();
      //Serial.println(sw_secs.value());
      
      buttonState = expander.digitalRead(0);
      buttonState2 = expander.digitalRead(1);

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(4, 10);
        display.print("To Set Altitude Level");
        display.setCursor(24, 20);
        display.print("press In Button");
        display.setCursor(40, 50);
        display.print("for skip");
        display.setCursor(2, 60);
        display.print("wait or press Out Button");
        display.display();
      
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
          
        display.clearDisplay();
        delay(5);
//          u8g.setFont(u8g_font_timB18r);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor( 38, 28);
        display.print("SKIP");  //1-szer, 2-wys,
        display.display();
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
     
     
     switch(altset2){
                 case 0:
//                     Serial.println("0m");
                     altFactor = 1;
                     display.clearDisplay();
                     delay(5);
                     display.setTextSize(1);
                     display.setTextColor(WHITE, BLACK);
                     display.setCursor(0,30);
                     display.print("0m");
                     display.setCursor(0, 0);
                     display.print("Sea Level");  //1-szer, 2-wys,;
                     display.display();
                     break;
                 case 1:
//                     Serial.println("300m");
                     altFactor = 0.964940;
                       display.clearDisplay();
                     delay(5);
                     display.setTextSize(1);
                     display.setTextColor(WHITE, BLACK);
                     display.setCursor(0,30);
                     display.print("300m");
                     display.setCursor(0, 0);
                     display.print("ALTITUDE");  //1-szer, 2-wys,;
                     display.display();
                     break;
                 case 2:
//                     Serial.println("600m");
                     altFactor = 0.9308828029;
                       display.clearDisplay();
                     delay(5);
                     display.setTextSize(1);
                     display.setTextColor(WHITE, BLACK);
                     display.setCursor(0,30);
                     display.print("600m");
                     display.setCursor(0, 0);
                     display.print("ALTITUDE");  //1-szer, 2-wys,;
                     display.display();
                     break;
                 case 3:
//                     Serial.println("900m");
                     altFactor = 0.8978050827;
                       display.clearDisplay();
                     delay(5);
                     display.setTextSize(1);
                     display.setTextColor(WHITE, BLACK);
                     display.setCursor(0,30);
                     display.print("900m");
                     display.setCursor(0, 0);
                     display.print("ALTITUDE");  //1-szer, 2-wys,;
                     display.display();
                     break;
                 case 4:
//                     Serial.println("1200m");
                     altFactor = 0.8656856649;
                       display.clearDisplay();
                     delay(5);
                     display.setTextSize(1);
                     display.setTextColor(WHITE, BLACK);
                     display.setCursor(0,30);
                     display.print("1200m");
                     display.setCursor(0, 0);
                     display.print("ALTITUDE");  //1-szer, 2-wys,;
                     display.display();
                     break;
                 case 5:
//                     Serial.println("1500m");
                     altFactor = 0.8345028374;
                       display.clearDisplay();
                     delay(5);
                     display.setTextSize(1);
                     display.setTextColor(WHITE, BLACK);
                     display.setCursor(0,30);
                     display.print("1500m");
                     display.setCursor(0, 0);
                     display.print("ALTITUDE");  //1-szer, 2-wys,;
                     display.display();
                     break;
         }
         
        if(altset2 > 5){
        altset2 = 0;
        }//    Serial.println(altset2);
    
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
          
          display.clearDisplay();
          delay(5);
          display.setTextSize(1);
          display.setTextColor(WHITE);
          display.setCursor(34, 28);
          display.print("SAVE");  //1-szer, 2-wys,
          display.display();

            delay(500);
        }
     
  
  
  
  
  while(counter >= 5){
//  Serial.println("Przeszło");
//  delay(2000);
  counter = 0;
  counter2 = 0;
  }
  
  

}
  
  
  
  
  display.clearDisplay();
  

  
  
  //*********************status sensorów
  uint16_t b;
    for( b=0; b<128; b++) display.drawPixel(b, 16, 1);
    
    for( b=0; b<128; b++) display.drawPixel(b, 32, 1);
    
    for( b=0; b<128; b++) display.drawPixel(b, 48, 1);
    
    for( b=17; b<64; b++) display.drawPixel(20, b, 1); // oś pionowa
    for( b=17; b<64; b++) display.drawPixel(75, b, 1);

  display.display();
  
  //************************************************
  //***********opis danych do sensorów w tabeli
  
  //************nagłówek tabeli
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4,6);
  display.println("#     mV     Status");
  
   //**********************numery sensorów
  display.setCursor(2,20);
  display.println("1");
  display.setCursor(2,36);
  display.println("2");
  display.setCursor(2,52);
  display.println("3");
  
  //***************wartości sensorów w miliVoltach
  display.setCursor(35,20);
  display.println(SmV*0.039906103);
  display.setCursor(35,36);
  display.println(S2mV*0.039906103);
  display.setCursor(35,52);
  display.println(S3mV*0.039906103);
  display.display();
  
  //*********************sensor ok lub old lub Err
  if(SmV1 >= 9.00 && SmV1 <= 13.00){
    display.setCursor(92,20);
    display.println("OK");
    display.display();
  }
  else if(SmV1 <=8.99 && SmV1 >=8.00){
    display.setCursor(92,20);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,20);
    display.println("Err");
    display.display();
  }
  
  if(S2mV2 >= 9.00 && S2mV2 <= 13.00){   // 2 sensor
    display.setCursor(92,36);
    display.println("OK");
    display.display();
  }
  else if(S2mV2 <=8.99 && S2mV2 >=8.00){
    display.setCursor(92,36);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,36);
    display.println("Err");
    display.display();
  }
  
  if(S3mV3 >= 9.00 && S3mV3 <= 13.00){      // 3 sensor
    display.setCursor(92,52);
    display.println("OK");
    display.display();
  }
  else if(S3mV3 <=8.99 && S3mV3 >=8.00){
    display.setCursor(92,52);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,52);
    display.println("Err");
    display.display();
  }
  
  delay(5000);


  // Clear the buffer.
  display.clearDisplay();
 
 //*********************************koniec logo
  
  // text display tests
  display.setTextSize(1);
   display.setTextColor(WHITE);
  display.setCursor(0,2);
  display.println("BDS PPO2 Display");
  
//*********test linia  baterii************
uint16_t i;
for( i=0; i<128; i++) display.drawPixel(i, 16, 1);
for( i=0; i<128; i++) display.drawPixel(i, 42, 1);

for( i=17; i<64; i++) display.drawPixel( 60, i, 1);

  
//************bateria****************
 
  display.drawPixel(103, 3, WHITE);
  display.drawPixel(103, 4, WHITE);
  display.drawPixel(103, 5, WHITE);
  display.drawPixel(103, 6, WHITE);
  display.drawPixel(103, 7, WHITE);

  display.drawPixel(102, 3, WHITE);
  display.drawPixel(102, 4, WHITE);
  display.drawPixel(102, 5, WHITE);
  display.drawPixel(102, 6, WHITE);
  display.drawPixel(102, 7, WHITE);

  display.drawPixel(103, 3, WHITE);
  display.drawPixel(103, 4, WHITE);
  display.drawPixel(103, 5, WHITE);
  display.drawPixel(103, 6, WHITE);
  display.drawPixel(103, 7, WHITE);

  display.drawPixel(127, 1, WHITE);
  display.drawPixel(127, 2, WHITE);
  display.drawPixel(127, 3, WHITE);
  display.drawPixel(127, 4, WHITE);
  display.drawPixel(127, 5, WHITE);
  display.drawPixel(127, 6, WHITE);
  display.drawPixel(127, 7, WHITE);
  display.drawPixel(127, 8, WHITE);
  display.drawPixel(127, 9, WHITE);
  
   display.drawPixel(105, 1, WHITE);
  display.drawPixel(105, 2, WHITE);
  display.drawPixel(105, 3, WHITE);
  display.drawPixel(105, 4, WHITE);
  display.drawPixel(105, 5, WHITE);
  display.drawPixel(105, 6, WHITE);
  display.drawPixel(105, 7, WHITE);
  display.drawPixel(105, 8, WHITE);
  display.drawPixel(105, 9, WHITE);
  
  display.drawPixel(105, 0, WHITE);
  display.drawPixel(106, 0, WHITE);
  display.drawPixel(107, 0, WHITE);
  display.drawPixel(108, 0, WHITE);
  display.drawPixel(109, 0, WHITE);
  display.drawPixel(110, 0, WHITE);
  display.drawPixel(111, 0, WHITE);
  display.drawPixel(112, 0, WHITE);
  display.drawPixel(113, 0, WHITE);
  display.drawPixel(114, 0, WHITE);
  display.drawPixel(115, 0, WHITE);
  display.drawPixel(116, 0, WHITE);
  display.drawPixel(117, 0, WHITE);
  display.drawPixel(118, 0, WHITE);
  display.drawPixel(119, 0, WHITE);
  display.drawPixel(120, 0, WHITE);
  display.drawPixel(121, 0, WHITE);
  display.drawPixel(122, 0, WHITE);
  display.drawPixel(123, 0, WHITE);
  display.drawPixel(124, 0, WHITE);
  display.drawPixel(125, 0, WHITE);
  display.drawPixel(126, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(128, 0, WHITE);

  display.drawPixel(105, 10, WHITE);
  display.drawPixel(106, 10, WHITE);
  display.drawPixel(107, 10, WHITE);
  display.drawPixel(108, 10, WHITE);
  display.drawPixel(109, 10, WHITE);
  display.drawPixel(110, 10, WHITE);
  display.drawPixel(111, 10, WHITE);
  display.drawPixel(112, 10, WHITE);
  display.drawPixel(113, 10, WHITE);
  display.drawPixel(114, 10, WHITE);
  display.drawPixel(115, 10, WHITE);
  display.drawPixel(116, 10, WHITE);
  display.drawPixel(117, 10, WHITE);
  display.drawPixel(118, 10, WHITE);
  display.drawPixel(119, 10, WHITE);
  display.drawPixel(120, 10, WHITE);
  display.drawPixel(121, 10, WHITE);
  display.drawPixel(122, 10, WHITE);
  display.drawPixel(123, 10, WHITE);
  display.drawPixel(124, 10, WHITE);
  display.drawPixel(125, 10, WHITE);
  display.drawPixel(126, 10, WHITE);
  display.drawPixel(127, 10, WHITE);
  display.drawPixel(128, 10, WHITE);
  
   
//***********HUD DISPLAY*****************
pinMode(greenLED, OUTPUT);
pinMode(redLED, OUTPUT);

  
}

//*************************************************
//****************warning commands**************
void warning(){            
  if ( PPO2 <= 0.40 || PPO22 <0.40 || PPO23 <0.40){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(68,47);
    display.print("LOW!");
    display.display();
    digitalWrite(redLED, HIGH);         //turn on the Red LED
    digitalWrite(greenLED, LOW);        //turn off the Green LED
    
  }else if ( PPO2 >= 1.40 || PPO22 >= 1.40 || PPO23 >= 1.40){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(67,47);
    display.print("HIGH!");
    display.display();
    delay(500);
    display.setCursor(67,47);
    display.print("     ");
    display.display();
    delay(50);
    digitalWrite(redLED, HIGH);        //turn on the Red LED
    digitalWrite(greenLED, LOW);       //turn off the Green LED
  }else{
     display.setTextSize(2.9);
     display.setTextColor(WHITE, BLACK);
     display.setCursor(65,47);
     display.print("     ");
     display.display();
     digitalWrite(redLED, LOW);        //turn off the Red LED
     digitalWrite(greenLED, HIGH);     //turn on the Green LED
     
     
  }
}



void loop(){
  
  int16_t adc0, adc1, adc2, adc3;

  //adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  
  float SmVact = adc3/5.0;
  float SmVact2 = adc2/5.0;
  float SmVact3 = adc1/5.0;
  float PPO2 = (SmVact * (0.21/SmV)) * O2factor * altFactor;
  float PPO22 = (SmVact2 * (0.21/S2mV)) * O2factor2 * altFactor;
  float PPO23 = (SmVact3 * (0.21/S3mV)) * O2factor3 * altFactor;

if(SmV1 < 8.00 || SmV1 > 13.00){
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,22);
  display.print("Err");
}else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,22);
    display.print(PPO2);
    display.display();
    //delay(500);
    }

//************ 2nd sensor ***************
    
if(S2mV2 < 8.00 || S2mV2 > 13.00){
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(67,22);
  display.print("Err");
}else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(67,22);
    display.print(PPO22);
    
    display.display();
    //delay(500);
    }

// ************** 3rd sensor ***************

if(S3mV3 < 8.00 || S3mV3 > 13.00){
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,47);
  display.print("Err");
}else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,47);
    display.print(PPO23);
    //delay(500);
    display.display();
    }
    

// ************* warnning command **************
  warning();

//***************************************************
//*********************battery status****************
   
//   int sensorValue4 = analogRead(A6);
//   float bat = sensorValue4 * (5.0 / 1023.0);
  float bat = 3.60;
//*************************************************************
  if(bat >= 3.90){                  //full battery section
  
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(122,7);
  
  uint16_t i;
  
  for( i=107; i<112; i++) display.drawPixel(i, 8, 1); //full battery icon
  for( i=107; i<112; i++) display.drawPixel(i, 7, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 6, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 5, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 4, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 3, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 2, 1);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 1); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 3, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 2, 1);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 1);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 3, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 2, 1);
     
  //delay(500);
  display.display();
  
//********************************************************************  
}else if(bat <=3.89 && bat >=3.60){ //mid battery section
  
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(122,7);
  
   uint16_t i;
   
  for( i=107; i<112; i++) display.drawPixel(i, 8, 0); //full battery icon
  for( i=107; i<112; i++) display.drawPixel(i, 7, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 6, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 5, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 4, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 3, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 2, 0);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 1); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 3, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 2, 1);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 1);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 3, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 2, 1);
     
  //delay(500);
  display.display();
  
  //******************************************************************
  }else if (bat <=3.59 && bat >=3.30){  //low battery section
  
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(122,7);
  
   uint16_t i;
  
  for( i=107; i<112; i++) display.drawPixel(i, 8, 0); //full battery icon
  for( i=107; i<112; i++) display.drawPixel(i, 7, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 6, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 5, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 4, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 3, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 2, 0);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 0); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 3, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 2, 0);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 1);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 3, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 2, 1);
     
  //delay(500);
  display.display();
  
 //**********************************************************
  }else if (bat <=3.29){             //flat battery icon
 
 
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(122,7);
  
   uint16_t i;
  
  for( i=107; i<112; i++) display.drawPixel(i, 8, 0); //full battery icon
  for( i=107; i<112; i++) display.drawPixel(i, 7, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 6, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 5, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 4, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 3, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 2, 0);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 0); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 3, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 2, 0);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 0);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 3, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 2, 0);
     
  //delay(500);
  display.display();
  
  }
  
  //display.ssd1306_command(SSD1306_DISPLAYOFF);
  //display.drawPixel(a, 17, 1);
 // display.begin(0xAE);
  
  
  //SSD1306_DISPLAYALLON_RESUME;
  //display.display();
//  delay(6000);
//  display.SH1106_command(SH1106_DISPLAYON);
//  display.display();
//  delay(6000);
  delay(500);
}
