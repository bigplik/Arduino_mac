
/*
COMMON PIN SETTINGS:

Arduino Pro Mini    1.44" Red pcb TFT

pin 13 (SCK)        SCK
pin 11 (MOSI)       SDA
pin 10 (SS)         CS
pin 9               AO
pin 8               RESET
VCC                 VCC     
GND                 GND
VCC                 LED  

*/
 
#include <SPI.h>
#include "TFT144.h"

// PIN OUT used by gimpo:

#define TFT_CS                    10  // CS pin
#define TFT_RST                   8   // Reset pin - you can also connect this to the Arduino reset in which case, set this #define pin to 0!
#define TFT_DC                    9   // DC pin
#define TFT_BACKLIGHT             5   // DC pin
#define TFT_POWER                 4   // power pin to TFT

TFT144         tft = TFT144(TFT_CS,  TFT_DC, TFT_RST);

void setup() {   

    // turn on TFT
    pinMode(4,OUTPUT);
    digitalWrite(4, HIGH);

    // set TFT backlight to max value
    pinMode(5,OUTPUT);
    analogWrite(5, 255);

    // init stuff 
    tft.initR(INITR_18BLACKTAB);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  
    tft.setRotation(0); 
    tft.setCursor(0,0);
    tft.println("Hello world!");
    delay(1000);
}
void loop()
{   
    for(int i = 0;i <4; i++)
    {
        tft.setRotation(i);
        tft.fillScreen(TFT_BLACK);
        
        tft.fillTriangle(64, 0, 127, 127, 0, 127, TFT_GREEN);   // draw a triangle pointing upward
        tft.fillRoundRect(32, 64, 32, 64, 4, TFT_DARKGRAY);     // draw something else
        tft.fillCircle(32, 64, 10, TFT_RED);                    // draw something else
        tft.drawLine(127,0,0,127,TFT_BLUE);                     // draw something else
        
        // write the current rotation value
        tft.setCursor(0,0);
        tft.print("rot = ");
        tft.print(tft.getRotation());
        
        delay(4000);
    }
}
