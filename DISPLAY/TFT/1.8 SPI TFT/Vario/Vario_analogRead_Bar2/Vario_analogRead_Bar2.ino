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


float p = 3.14;
int a;

void setup(void) {
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  //testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST7735_WHITE);
  //delay(1000);


  //fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
  //           uint16_t color)
             
  //fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
  //uint16_t color)
  
  //fillRect(width_Start, height_Start,  _width, _height, color);
  
  // tft print function!
  //tftPrintTest();
  //delay(4000);

  // a single pixel
  //tft.drawPixel(tft.width()/2, tft.height()/2, ST7735_GREEN);
  //delay(500);

  // line draw test
  //testlines(ST7735_YELLOW);
  //delay(500);

  // optimized lines
  //testfastlines(ST7735_RED, ST7735_BLUE);
  //delay(500);

  //testdrawrects(ST7735_GREEN);
  //delay(500);

  //testfillrects(ST7735_YELLOW, ST7735_MAGENTA);
  //delay(500);

  //tft.fillScreen(ST7735_BLACK);
  //testfillcircles(10, ST7735_BLUE);
  //testdrawcircles(10, ST7735_WHITE);
  //delay(500);

  //testroundrects();
  //delay(500);

  //testtriangles();
  //delay(500);
  
  //mediabuttons();
  //delay(500);

  //Serial.println("done");
  //delay(1000);
  pinMode(A0,INPUT);
}

void loop() {
  
  static int change = 0;
  
  switch(change){
    case 0:
      a = analogRead(A0);
      break;
    case 1:
      a = analogRead(A1);
      break;
  }

  
  int b = map(a,0,1024,1,60);
  int c = 60-b;
  //fillRect(width_Start, height_Start,  _width, _height, color);
  tft.fillRect(135,b,20,c,ST7735_WHITE);
  tft.fillRect(135,0,20,b,ST7735_BLACK);
  
  //tft.fillRect(105,0,20,b,ST7735_WHITE);
  //tft.fillRect(105,b,20,120,ST7735_BLACK);
  delay(200);
  change =! change;

  //tft.fillScreen(ST7735_BLACK);
  //tft.fillRect(135,0,20,120,ST7735_BLACK);

  //delay(200);

  /*
  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
  */

}

