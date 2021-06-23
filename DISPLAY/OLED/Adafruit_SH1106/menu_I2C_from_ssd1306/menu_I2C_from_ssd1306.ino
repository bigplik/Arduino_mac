/*********************************************************************
This is an example for our Monochrome OLEDs based on SH1106 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using SPI to communicate
4 or 5 pins are required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// If using I2C
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

int screen;


void setup()   {                
  Serial.begin(9600);
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(20);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
}


void loop() {

sensory();

}




void logo(){
  
  
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
  
  
}


void sensory(){
  
  //display.invertDisplay(0xA7);
  
    //*********************status sensorów
  uint16_t b;
    for( b=0; b<127; b++) display.drawPixel(b, 16, 1);
    
    for( b=0; b<127; b++) display.drawPixel(b, 32, 1);
    
    for( b=0; b<127; b++) display.drawPixel(b, 48, 1);
    
    //for( b=17; b<63; b++) display.drawPixel(20, b, 1); // oś pionowa
    for( b=17; b<63; b++) display.drawPixel(63, b, 1);

  
  //display.display();
  
  //************************************************
  //***********opis danych do sensorów w tabeli
  
  //************nagłówek tabeli
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(16,6);
  display.println("Set your Origin");
  
   //**********************numery sensorów
  display.setCursor(2,20);
  display.setTextColor(WHITE);
  display.println("ALTITUDE");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,36);
  display.println("SCREEN");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,52);
  display.println("02 CAL");
  display.display();
  //***************wartości sensorów w miliVoltach
 
  display.setCursor(45,20);
  display.setTextColor(BLACK, WHITE);
  display.println("");
  
  display.setCursor(42,36);
  display.setTextColor(WHITE);
  display.println("");

  display.setCursor(35,52);
  display.println("");
  display.display();
 
      display.setCursor(92,20);
    display.println("0m");
    display.setCursor(82,36);
    display.println("NORMAL");
    display.setTextColor(BLACK, WHITE);
    display.setCursor(72,52);
    display.println("NEXT -->>");
    
    display.display();
   
}