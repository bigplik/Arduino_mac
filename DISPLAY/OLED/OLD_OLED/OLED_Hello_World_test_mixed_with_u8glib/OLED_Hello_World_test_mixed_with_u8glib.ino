#include <Wire.h>
#include <OzOLED.h>
#include "U8glib.h"

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);




void setup(){

  OzOled.init();  //initialze Oscar OLED display
  OzOled.setCursorXY(10, 10);
  OzOled.printString("Hello World!"); //Print the String
  
  
    if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

u8g.firstPage();  
  do {
    uint8_t a;
  
  u8g.drawRFrame(88, 30,35,30, a+1);
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
  



}

void loop(){
  
}

