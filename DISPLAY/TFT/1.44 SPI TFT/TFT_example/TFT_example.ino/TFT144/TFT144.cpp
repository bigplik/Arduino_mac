/*
 * VERSION 1.0 - April 2016
 * 
 * This class implements the correct coordinate translation for 1.44" 128x128 TFTs
 * when a rotation of the screen is applied.
 * 
 * This class is a wrapper of the original Adafruit_ST7735.cpp implementation and
 * can be used in place of that.
 * If don't need to rotate the screen then the original Adafruit_ST7735 should be
 * used for performance reasons since the (minimal) overhead introduced by this code.
 * 
 * CONTRIBUTORS:
 * 
 * gimpo    (Giulio Buccini)
 * dcpyatt  (David C. Pyatt)
 * 
 * REFERENCE:
 * 
 * arduino forum: http://forum.arduino.cc/index.php?topic=260605.75
 * GitHub: https://github.com/sumotoy/TFT_ILI9163C/issues/26
 */

#include "TFT144.h"
#include <Adafruit_ST7735.h>

// Constructor when using software SPI.  All output pins are configurable.

TFT144::TFT144(int8_t cs, int8_t rs, int8_t rst) : Adafruit_ST7735(cs, rs, rst) { }

/*
 * Set the correct offset/shift that must be applied
 * after the screen is rotated.
 */
void  TFT144::setRotation(uint8_t r)
{
  Adafruit_ST7735::setRotation(r);
  switch(rotation)
  {
      case 0:  offset_y = 32;  offset_x = 0;  break; 
      case 1:  offset_y = 0;   offset_x = 32; break;
      case 2:  offset_y = 0;   offset_x = 0;  break;
      case 3:  offset_y = 0;   offset_x = 0;  break;
  }
}

/*
 * RGB565 to BGR565 converter (thanks to David C. Pyatt)
 */
uint16_t TFT144::correctColor(uint16_t color)
{
    return (color & 0xF800) >> 11 | color & 0x07E0 | (color & 0x001F) << 11;
}


void TFT144::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawLine(x0+SHIFT_X, y0+SHIFT_Y,  x1+SHIFT_X,  y1+SHIFT_Y,  color);
    nesting_level--;
}
void TFT144::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawTriangle(x0+SHIFT_X, y0+SHIFT_Y,  x1+SHIFT_X,  y1+SHIFT_Y,  x2+SHIFT_X,  y2+SHIFT_Y,  color);
    nesting_level--;
}
void TFT144::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::fillRoundRect(x0+SHIFT_X, y0+SHIFT_Y, w, h, radius, color);
    nesting_level--;
}
void TFT144::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::fillRect(x+SHIFT_X, y+SHIFT_Y,  w, h, color);
    nesting_level--;
}

void  TFT144::setCursor(int16_t x, int16_t y) {
    nesting_level++;
    Adafruit_ST7735::setCursor(x+SHIFT_X,y+SHIFT_Y);
    nesting_level--;
}

void TFT144::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::fillTriangle(x0+SHIFT_X, y0+SHIFT_Y, x1+SHIFT_X, y1+SHIFT_Y,x2+SHIFT_X, y2+SHIFT_Y, color);
    nesting_level--;
}


void TFT144::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawFastVLine(x+SHIFT_X,  y+SHIFT_Y,   h,  color);
    nesting_level--;
}
void TFT144::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawFastHLine(x+SHIFT_X,  y+SHIFT_Y,   w,  color);
    nesting_level--;
}
void TFT144::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawRect(x+SHIFT_X, y+SHIFT_Y,  w, h, color);
    nesting_level--;
}

void TFT144::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawCircle(x0+SHIFT_X, y0+SHIFT_Y,  r, color);
    nesting_level--;
}
void TFT144::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::fillCircle(x0+SHIFT_X, y0+SHIFT_Y,  r, color);
    nesting_level--;
}

void TFT144::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawRoundRect(x0+SHIFT_X, y0+SHIFT_Y,  w, h, radius, color);
    nesting_level--;
}
void TFT144::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
    nesting_level++;
    Adafruit_ST7735::drawChar(x+SHIFT_X,  y+SHIFT_Y,  c, color, bg, size);
    nesting_level--;
}

void TFT144::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawBitmap(x+SHIFT_X, y+SHIFT_Y,  bitmap, w, h, color);
    nesting_level--;
}
void TFT144::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    nesting_level++;
    Adafruit_ST7735::drawBitmap(x+SHIFT_X, y+SHIFT_Y,  bitmap, w, h, color, bg);
    nesting_level--;
}
void TFT144::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawBitmap(x+SHIFT_X,  y+SHIFT_Y,  bitmap, w, h, color);
    nesting_level--;
}
void TFT144::drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) {
    nesting_level++;
    Adafruit_ST7735::drawBitmap(x+SHIFT_X,  y+SHIFT_Y,  bitmap, w, h, color, bg);
    nesting_level--;
}
void TFT144::drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    nesting_level++;
    Adafruit_ST7735::drawXBitmap(x+SHIFT_X,  y+SHIFT_Y,  bitmap, w, h, color);
    nesting_level--;
}


