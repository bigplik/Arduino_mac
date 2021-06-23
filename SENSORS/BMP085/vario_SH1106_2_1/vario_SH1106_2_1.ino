

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_BMP085.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SH1106 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SH1106 display(OLED_DC, OLED_RESET, OLED_CS);
*/

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
int cisnienie = 0;

const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 102523;

Adafruit_BMP085 bmp;

void setup()   {                
  Serial.begin(9600);
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC);
  // init done
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  
  startAltitude = bmp.readAltitude(104400);
  cisnienie = bmp.readPressure();
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(200);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  
  pinMode(7, OUTPUT);
}


void loop() {


  
    cisnienie = bmp.readPressure();
  float range = map(cisnienie, sensorMin, sensorMax, 0, 500);
  
  float realAlt = bmp.readAltitude(104400);
  static float countAlt = 0;
  if(countAlt == 0) {countAlt = realAlt;}
  else{ countAlt = (countAlt + realAlt)/2;}
  
  if(realAlt < (countAlt-0.3)){ 
  display.setCursor(20,40);
  display.println(realAlt-countAlt);
  display.display();
  tone(7,1500,1000);
  }
  else if(realAlt > (countAlt+0.3)){ 
  display.setCursor(20,40);display.print("+");
  display.println(realAlt-countAlt);
  display.display();
  tone(7,3000,200);
  }
  
display.setTextSize(3);
display.setTextColor(WHITE);
  display.setCursor(10,5);
  display.println(realAlt);
  display.display();
  delay(500);
  display.clearDisplay();
  //display.display();
  //digitalWrite(7,LOW);
  
}
