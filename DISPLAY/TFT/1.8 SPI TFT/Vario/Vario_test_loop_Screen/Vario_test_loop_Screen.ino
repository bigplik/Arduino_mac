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
int deniwelacja = 1200;

const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 101325;

float correct;
float wysokoscWzgledna;
float temp = 27;

Adafruit_BMP085 bmp;

void setup(void) {
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);
  
  tft.setCursor(0,5);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  //tft.fillScreen(ST7735_BLACK);
  tft.setTextWrap(true);
  tft.println("1024");
  tft.setCursor(2,22);
  tft.setTextSize(1);
  tft.print("RealAlt");
  tft.setCursor(110,5);
  tft.setTextSize(2);
  tft.println(deniwelacja);
  tft.setCursor(110,22); tft.setTextSize(1); tft.print("Decrease"); 
  
  tft.setCursor(0,100);
  tft.setTextSize(2);
  tft.println("1100");
  tft.setCursor(2,117);
  tft.setTextSize(1);
  tft.print("Maximum");
  
  tft.setCursor(120,100);
  tft.setTextSize(2); tft.print(temp,0); tft.print("C");
  tft.setCursor(123,117);
  tft.setTextSize(1); tft.print("temp");
  
  tft.setTextSize(4);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  tft.setCursor(20,50);
  tft.println("+5.25");
  
}

void loop() {

}
