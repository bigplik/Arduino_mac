#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1015.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

int16_t adc0, adc1, adc2;

double SmV, S2mV, S3mV, SmVact, SmVact2, SmVact3;

float PPO2, PPO22, PPO23;

Adafruit_ADS1115 ads;

unsigned int firstValue1 = 0;
unsigned int firstValue2 = 0;
unsigned int firstValue3 = 0;
unsigned int secondValue1 = 0;
unsigned int secondValue2 = 0;
unsigned int secondValue3 = 0;

void setup() {
  // put your setup code here, to run once:
  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  ads.begin();
  OxygenCalculations();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,0); display.print(SmV);
    display.setCursor(0,25); display.print(S2mV);
    display.setCursor(0,45); display.print(S3mV);
    display.display();
    delay(2000);
    display.clearDisplay();
    adc0 = 0;
    adc1 = 0;
    adc2 = 0;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  OxygenLoop();
//  adc0 = ads.readADC_SingleEnded(0);
//  adc1 = ads.readADC_SingleEnded(1);
//  adc2 = ads.readADC_SingleEnded(2);
//
//  SmVact = (adc0*0.0078125); //dane przeliczone do miliVolt dla S1 zazwyczaj 5.0V
//  SmVact2 = (adc1*0.0078125);
//  SmVact3 = (adc2*0.0078125);

    //display.setTextSize(2);
    //display.setTextColor(WHITE, BLACK);
    display.setCursor(60,0); display.print(SmVact);
    display.setCursor(60,25); display.print(SmVact2);
    display.setCursor(60,45); display.print(SmVact3);
    display.display();
    delay(50);
    secondValue1 = 0;
    secondValue2 = 0;
    secondValue3 = 0;
    
}
