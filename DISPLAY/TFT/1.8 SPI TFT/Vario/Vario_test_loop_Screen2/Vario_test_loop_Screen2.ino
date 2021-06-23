

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

float temp = 26;

void setup() {
  // put your setup code here, to run once:
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(1);
  tft.fillScreen(ST7735_WHITE);
  


}

void loop() {
  // put your main code here, to run repeatedly:
  tft.setCursor(0,5);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
  //tft.fillScreen(ST7735_BLACK);
  tft.setTextWrap(true);
  tft.print("1100"); tft.println(" ");//real Alt
  tft.setCursor(2,22);
  tft.setTextSize(1);
  tft.print("Altitude");
  tft.setCursor(110,5);  //deniwelacja
  tft.setTextSize(2);
  tft.println("1200");
  tft.setCursor(110,22); tft.setTextSize(1); tft.print("Decrease");
  tft.setCursor(0,100); //maximum alt
  tft.setTextSize(2);
  tft.print("1024");
  tft.setCursor(2,117);
  tft.setTextSize(1);
  tft.print("Maximum");
  tft.setCursor(120,100);  //temp
  tft.setTextSize(2); tft.print(temp,0); tft.print("C");
  tft.setCursor(123,117);
  tft.setTextSize(1); tft.print("temp");
  
  tft.setTextSize(4);
  tft.setTextColor(ST7735_BLACK,ST7735_WHITE);
  tft.setCursor(20,50);
  tft.println(" 0.00");
  
  delay(2000);
  tft.invertDisplay(true);
  delay(2000);
  tft.invertDisplay(false);
}
