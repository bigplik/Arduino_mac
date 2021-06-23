

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_BMP085.h>

/*
// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SH1106 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
*/

// Uncomment this block to use hardware SPI
#define OLED_DC     9
#define OLED_CS     8
#define OLED_RESET  10
Adafruit_SH1106 display(OLED_DC, OLED_RESET, OLED_CS);


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


float startAltitude;
float meters = 0;
float checkmeters = 0;
float cisnienie = 0;

const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 101325;

float correct;
float wysokoscWzgledna;

Adafruit_BMP085 bmp;

void setup()   {                
  //Serial.begin(9600);
  pinMode(13,OUTPUT);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC);
  display.clearDisplay();
  display.display();
  // init done
  if (!bmp.begin()) {
     for(int a=0; a<10; a++){
       digitalWrite(13,digitalRead(13)^1);
       delay(500);
     }
  }
  else{ 
     }

  startAltitude = bmp.readAltitude(101325);
  cisnienie = bmp.readPressure();
  delay(1);
    correct = 0 - startAltitude;
    wysokoscWzgledna = startAltitude + correct; 
  
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,5);
    display.print(cisnienie/100,1);
    display.println(" hPa");
    display.setCursor(10,30);
    display.println(startAltitude);
    display.setCursor(10,50);
    display.println(wysokoscWzgledna);
    display.display();
    delay(5000);
  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // draw a single pixel
  
  pinMode(7, OUTPUT);
}


void loop() {


  
  //cisnienie = bmp.readPressure();
  //float range = map(cisnienie, sensorMin, sensorMax, 0, 500);
  
  float realAlt = bmp.readAltitude(101325);
  float realAltcorrect = realAlt + correct;
  static float countAlt = 0;
  if(countAlt == 0) {countAlt = realAlt;}
  else{ countAlt = (countAlt + realAlt)/2;}
  
  static int minimum = 0;
  static int maximum = 0;
  if(realAltcorrect < minimum){
    minimum = realAltcorrect;
  }
  if(realAltcorrect > maximum){
    maximum = realAltcorrect;
  }
  int deniwelacja = maximum - minimum;
  
      if(realAlt > (countAlt+0.7)){ 
      display.setCursor(20,40);display.print("+");
      display.println((realAlt-countAlt)*2);
      display.display();
      tone(7,3000,200);
      }
      else if(realAlt < (countAlt-0.7)){ 
      display.setCursor(20,40);
      display.println((realAlt-countAlt)*2);
      display.display();
      tone(7,1500,1000);
      }
  
display.setTextSize(3);
display.setTextColor(WHITE);
  display.setCursor(10,5);
  display.println(realAltcorrect,0);
  display.setTextSize(2);
  display.setCursor(0,40);
  display.print(minimum);
  display.setCursor(32,40);
  display.print(maximum);
  display.display();
  delay(500);
  display.clearDisplay();
  //display.display();
  //digitalWrite(7,LOW);
  
}
