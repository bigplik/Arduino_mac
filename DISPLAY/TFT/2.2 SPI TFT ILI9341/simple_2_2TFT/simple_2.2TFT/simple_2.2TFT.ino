/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 2
#define TFT_CS 7
#define TFT_MOSI 3
#define TFT_CLK 5
#define TFT_RST 10
#define TFT_MISO 4

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
 
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
 
  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(500);
/*
  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(3000);

  Serial.print(F("Lines                    "));
  //Serial.println(testLines(ILI9341_CYAN));
  delay(500);

  Serial.print(F("Horiz/Vert Lines         "));
 // Serial.println(testFastLines(ILI9341_RED, ILI9341_BLUE));
  delay(500);

  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(ILI9341_GREEN));
  delay(500);

  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(ILI9341_YELLOW, ILI9341_MAGENTA));
  delay(500);

  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, ILI9341_MAGENTA));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, ILI9341_WHITE));
  delay(500);

  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(500);

  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(500);

  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(500);

  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(500);

  Serial.println(F("Done!"));
*/
}


void loop(void) {
  //for(uint8_t rotation=0; rotation<4; rotation++) {
   // tft.setRotation(rotation);
   tft.setRotation(3);
    testText();
   delay(5000);
    testText2();
   delay(5000);
 // }
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_YELLOW);
  tft.fillScreen(ILI9341_RED);
  tft.fillScreen(ILI9341_PINK);
  tft.fillScreen(ILI9341_GREEN);
  tft.fillScreen(ILI9341_LIGHTGREY);
  tft.fillScreen(ILI9341_BLUE);
  tft.fillScreen(ILI9341_BLACK);
  return micros() - start;
}

unsigned long testText() {
  //tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(4);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_LIGHTGREY);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_DARKGREY);
  tft.println("my foonting turlingdromes.");
  tft.setTextColor(ILI9341_NAVY);
  tft.println("And hooptiously drangle me");
  tft.setTextColor(ILI9341_DARKGREEN);
  tft.println("with crinkly bindlewurdles,");
  tft.setTextColor(ILI9341_DARKCYAN);
  tft.println("Or I will rend thee");
  tft.setTextColor(ILI9341_MAROON);
  tft.println("in the gobberwarts");
  tft.setTextColor(ILI9341_PURPLE);
  tft.println("with my blurglecruncheon,");
  tft.setTextColor(ILI9341_OLIVE);
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long testText2() {
  //tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLUE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_CYAN); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_MAGENTA);    tft.setTextSize(4);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_ORANGE);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_GREENYELLOW);
  tft.println("my foonting turlingdromes.");
  tft.setTextColor(ILI9341_PINK);
  tft.println("And hooptiously drangle me");
  tft.setTextColor(ILI9341_DARKGREEN);
  tft.println("with crinkly bindlewurdles,");
  tft.setTextColor(ILI9341_DARKCYAN);
  tft.println("Or I will rend thee");
  tft.setTextColor(ILI9341_MAROON);
  tft.println("in the gobberwarts");
  tft.setTextColor(ILI9341_PURPLE);
  tft.println("with my blurglecruncheon,");
  tft.setTextColor(ILI9341_OLIVE);
  tft.println("see if I don't!");
  return micros() - start;
}
