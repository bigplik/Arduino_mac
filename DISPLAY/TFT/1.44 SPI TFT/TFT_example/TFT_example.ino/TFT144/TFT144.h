#include <Adafruit_ST7735.h>

#ifndef TFT144_H
#define TFT144_H

// macros for applying the shift along the X/Y axes
#define ENABLE_SHIFT (nesting_level == 1 ? 0xFF : 0x00)
#define SHIFT_X (offset_x&ENABLE_SHIFT)
#define SHIFT_Y (offset_y&ENABLE_SHIFT)

// BGR color defs
#define TFT_BLACK   0x0000
#define TFT_BLUE    0xF800
#define TFT_RED     0x001F
#define TFT_GREEN   0x07E0
#define TFT_CYAN    0xFFE0
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW  0x07FF
#define TFT_WHITE   0xFFFF
#define TFT_GRAY    0x8410      // RGB888 = 128,128,128
#define TFT_LIGHTGRAY   0xCE59  // RGB888 = 200,200,200
#define TFT_DARKGRAY    0x528A  // RGB888 = 80,80,80 

class TFT144 : public Adafruit_ST7735 
{

  public:

    TFT144(int8_t CS, int8_t RS, int8_t RST = -1);

    void setRotation(uint8_t r);
    uint16_t correctColor(uint16_t color);
    void setCursor(int16_t x, int16_t y);
    void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
    void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
    void drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);

  protected:
  
    byte offset_x;          // shift value along the X axis to correct coords after a screen rotation
    byte offset_y;          // shift value along the Y axis to correct coords after a screen rotation
    byte nesting_level;     // nesting level of calls beetween graphic primitives (methods)
};

#endif
