/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <StopWatch.h>
#include <EEPROM.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS    10
#define TFT_RST    8  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     9

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


float startAltitude;
float meters = 0;
float checkmeters = 0;
float cisnienie = 0;
float rising = 0;

const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 101325;

float correct;
float wysokoscWzgledna;
float temp;

byte flightNo = 1;
byte flightTime = 0;
int Lot[2] = { flightNo, flightTime };
int start = 0;
int startSave = 0; // pos of addrr wher save is start
boolean stopTime = 0;

Adafruit_BMP085 bmp;
StopWatch sw_secs(StopWatch::SECONDS);
StopWatch sw_mils(StopWatch::MILLIS);

void setup(void) {
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);
    if (!bmp.begin()) {
     }
    else{ 
       tft.setCursor(0,0); tft.setTextColor(ST7735_WHITE); tft.setTextSize(2);
       tft.println("BMP........OK");
       delay(2000);
       }
       
  startAltitude = bmp.readAltitude(101325);
  cisnienie = bmp.readPressure();
  temp = bmp.readTemperature();
  delay(1);
    correct = (0 - startAltitude)*-1;
    wysokoscWzgledna = startAltitude - correct;      
       
  tft.setTextSize(2);
  //tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(0,25);
  tft.print(cisnienie/100,1);
  tft.println(" hPa");
  tft.setCursor(0,45);
  tft.print(startAltitude,1); tft.println(" Alt");
  tft.setCursor(0,75);
  //tft.setTextColor(ST7735_BLUE);
  tft.print(temp,1); tft.print("C");
  delay(5000);

  pinMode(5, OUTPUT);
  tft.fillScreen(ST7735_BLACK);
  
  //LOGBOOK CODE
  int b=0;
  int lastFlightNo;
  
  tft.setCursor(40,0);
  tft.setTextColor(ST7735_WHITE);
  tft.print("LOGBOOK");
  tft.setTextSize(1);
  
  while(b<5){
  
  static int i=17; 
  int begins = EEPROM.read(start);
  delay(50);
  int czas = EEPROM.read(start+1);
  delay(5);
      if(begins > 0){
          tft.setCursor(0,i);
          tft.print("LOT ");tft.print(begins);
          tft.print(" CZAS ");tft.println(czas);
          Serial.print("LOT Nr"); Serial.print(begins);
          Serial.print(" CZAS ");  Serial.println(czas);
          Serial.println("");
          delay(500);
          start = start +2;
          i=i+10;
      }
      else{
            //startSave = start;
            Serial.println("EEPROM EMPTY");
            Serial.println(start);
            delay(500); b=5;
      }
      startSave = start;
      delay(5);
      lastFlightNo = EEPROM.read(startSave-2);
      delay(5);
      Lot[0]= lastFlightNo + 1;
  }
  
  Serial.println(startSave);
  tft.fillScreen(ST7735_BLACK);
  //sw_secs.start();
  
  
  
}

void loop() {

  static int minimum = 0;
  static int maximum = 0;
  int deniwelacja = maximum - minimum;
  static int newDeniwelacja = 0;
  static boolean startStatus = 0;
  
    cisnienie = bmp.readPressure();
    temp = bmp.readTemperature();
  //float range = map(cisnienie, sensorMin, sensorMax, 1500, 3000);
  
  float realAlt = bmp.readAltitude(101325);
  float realAltcorrect = realAlt - correct;
  float lastrealAltcorrect;
  static float countAlt = 0;
  rising = realAlt-countAlt;
  int barRising = rising*100;
  float b = map(barRising,-200,200,120,1);
  if(countAlt == 0) {countAlt = realAlt;}
  else{ countAlt = (countAlt + realAlt)/2;}
  
  if(realAltcorrect > maximum) { maximum = realAltcorrect; }
  else if(realAltcorrect < minimum) { minimum = realAltcorrect; }
  
  if(maximum > 2 || deniwelacja > 2 || deniwelacja < -2 && rising > 1.1 || rising < -1.1){
      sw_secs.start();
      startStatus = 1;
      tft.setCursor(112,100);  //
      tft.setTextSize(2); tft.print(sw_secs.value()); //tft.print("C");
      tft.setCursor(117,117);
      tft.setTextSize(1); tft.print(" REC ");
      if(deniwelacja == newDeniwelacja){
        sw_mils.start();
        if(sw_mils.value() == 10000){
          sw_secs.stop();
          sw_mils.stop();
        }
      }else{
        sw_mils.stop();
        sw_mils.reset();
      }
  }
  /*else if(deniwelacja == newDeniwelacja && startStatus == 1){
      tft.setCursor(112,100);  //
      tft.setTextSize(2); tft.print(sw_secs.value()); //tft.print("C");
      tft.setCursor(117,117);
      tft.setTextSize(1); tft.print(" REC ");
        static int counter = 0;
        tft.setCursor(60,100);
        tft.print(counter);
        counter++;
        if(counter >=50){
          sw_secs.stop();
          tft.setCursor(112,100);  //
          tft.setTextSize(2); tft.print(sw_secs.value()); //tft.print("C");
          tft.setCursor(117,117);
          tft.setTextSize(1); tft.print("STOP ");
        }
  }
  */
  else{
      sw_secs.stop();
      tft.setCursor(112,100);  //
      tft.setTextSize(2); tft.print(sw_secs.value()); //tft.print("C");
      tft.setCursor(117,117);
      tft.setTextSize(1); tft.print("START");
  }
  
  //tone(pin, frequency)
  //tone(pin, frequency, duration)
  /* Board	Min frequency (Hz)	Max frequency (Hz)
      Uno        	31               	65535
  pin: the pin on which to generate the tone
     frequency: the frequency of the tone in hertz - unsigned int
     duration: the duration of the tone in milliseconds (optional) - unsigned long
  noTone(pin) - Stops the generation of a square wave triggered by tone(). 
                Has no effect if no tone is being generated. If you 
                want to play different pitches on multiple pins, 
                you need to call noTone() on one pin before calling 
                tone() on the next pin.  
  */ 
  if(realAlt < (countAlt-0.3)){
    tft.setTextSize(4); 
    tft.setTextColor(ST7735_RED,ST7735_BLACK);
    tft.setCursor(10,50);
    tft.println(rising);
    tft.fillRect(150,b,10,120-b,ST7735_GREEN);
    tft.fillRect(150,0,10,b,ST7735_RED);
    if(rising < -1.2) tone(5,1500); //fq1500
  }
  else if(realAlt > (countAlt+0.3)){
    tft.setTextSize(4);
    tft.setTextColor(ST7735_GREEN,ST7735_BLACK);
    tft.setCursor(10,50); tft.print("+");
    tft.println(rising);
    tft.fillRect(150,b,10,120,ST7735_GREEN);
    tft.fillRect(150,0,10,b,ST7735_RED);
    tone(5,3000,100); //fq3000
  }
  else{
  tft.setTextSize(4);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  tft.setCursor(10,50);
  tft.print(" 0.00");
  //b=60;
  tft.fillRect(150,b,10,120,ST7735_GREEN);
  tft.fillRect(150,0,10,b,ST7735_RED);
  noTone(5);
  }
  
  tft.setCursor(0,5);
  tft.setTextSize(3);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  //tft.fillScreen(ST7735_BLACK);
  tft.setTextWrap(true);
  tft.print(realAlt-correct,0); tft.println(" ");//real Alt
  tft.setCursor(2,30);
  tft.setTextSize(1);
  tft.print("Altitude");
  tft.setCursor(95,5);  //deniwelacja
  tft.setTextSize(2);
  tft.println(deniwelacja);
  tft.setCursor(95,22); tft.setTextSize(1); tft.print("Decrease");
  tft.setCursor(0,100); //maximum alt
  tft.setTextSize(2);
  tft.print(maximum);
  tft.setCursor(2,117);
  tft.setTextSize(1);
  tft.print("Max Alt");
  newDeniwelacja = deniwelacja;
  
  delay(200);
  
}

//COLORS - WHITE, BLACK, RED, YELLOW, GREEN, BLUE, MAGENTA

