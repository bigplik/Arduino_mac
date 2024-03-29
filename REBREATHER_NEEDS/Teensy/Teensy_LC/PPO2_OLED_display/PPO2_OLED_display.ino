

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


const unsigned char PROGMEM bds [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0x0D, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xC1, 0xFF, 0xFF, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFC, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x3F, 0xFF, 0xFC, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x1F, 0xFF, 0xF8, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF8, 0x1F, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xE8, 0x07, 0xFF, 0xF0, 0x0F, 0x81, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x03, 0xFF, 0xF0, 0x06, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x80, 0x00, 0x00, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0xC0, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x60, 0x01, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x60, 0x00, 0x80, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xEC, 0x20, 0x6E, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x91, 0x13, 0x22, 0x00, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xED, 0x6C, 0x1F, 0x00, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0x00, 0x00, 0xED, 0x6C, 0x01, 0x00, 0xFF, 0xFC, 0x00, 0x7E, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x30, 0x92, 0x10, 0x60, 0xFF, 0xFE, 0x00, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x0F, 0x6D, 0xF0, 0xF0, 0xFF, 0xFE, 0x01, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x0F, 0x6D, 0x98, 0x80, 0xFF, 0xFE, 0x01, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC3, 0xC0, 0x10, 0x07, 0x92, 0x01, 0x00, 0xFF, 0xFE, 0x03, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC1, 0xC0, 0x18, 0x03, 0xEE, 0x0F, 0x40, 0x00, 0x16, 0x03, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC3, 0xC0, 0x1E, 0x02, 0x6C, 0x0C, 0xE0, 0x00, 0x00, 0x03, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x80, 0x1F, 0x01, 0xFA, 0x0B, 0x60, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x00, 0x1F, 0x19, 0xFA, 0x0B, 0x40, 0x01, 0x02, 0x03, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x80, 0x1E, 0x00, 0x70, 0x00, 0x40, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xC0, 0x1C, 0x0D, 0x7D, 0xED, 0xE0, 0x00, 0x6A, 0x03, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xE0, 0x1C, 0x01, 0x71, 0x89, 0x98, 0x00, 0x68, 0x01, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC1, 0xE0, 0x18, 0x11, 0x93, 0x63, 0x6C, 0x00, 0x98, 0x01, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0xE0, 0x18, 0x6D, 0xEF, 0x6F, 0x6F, 0x63, 0x78, 0x00, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC1, 0xE0, 0x10, 0x6C, 0x6C, 0x8C, 0x93, 0x13, 0x60, 0x00, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xE0, 0x10, 0xB9, 0xBB, 0x6B, 0x6D, 0x4D, 0xD0, 0x00, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xE0, 0x10, 0xB9, 0xBB, 0x6A, 0x2D, 0x4C, 0x40, 0x00, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xC0, 0x18, 0x6C, 0x6C, 0x8C, 0x03, 0x10, 0x20, 0x01, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x80, 0x18, 0x0D, 0xEF, 0x6C, 0x00, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x01, 0x93, 0x60, 0x40, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x01, 0x6D, 0x80, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x01, 0x6D, 0xE0, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x12, 0x00, 0x1D, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x09, 0x60, 0x3F, 0xF0, 0x00, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x09, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x04, 0x80, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x00, 0x01, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0x00, 0x03, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC0, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC0, 0x0F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC2, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC3, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC3, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

int16_t adc0, adc1, adc2;

double SmV, S2mV, S3mV;

float PPO2, PPO22, PPO23;

Adafruit_ADS1115 ads;

int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;

void setup()   {                
  
  Serial.begin(9600);
     ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  //ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  //ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  ads.begin();
  OxygenCalculations();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.drawBitmap(0, 0, bds, 128, 64, WHITE);
  display.display();
    delay(1000);
  
  logo_ORIGIN();
  sensor_STATUS();  
  battery();
  
}

void loop() {
  
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  //adc3 = ads.readADC_SingleEnded(3);
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  //Serial.print("AIN3: "); Serial.println(adc3);
  Serial.println(" ");
  
  float sensorValue = adc0;
  float sensorValue2 = adc1;
  float sensorValue3 = adc2;
  float SmVact = adc0/5.0;
  float SmVact2 = adc1/5.0;
  float SmVact3 = adc2/5.0;
  PPO2 = (SmVact * (0.21/SmV));
  PPO22 = (SmVact2 * (0.21/S2mV));
  PPO23 = (SmVact3 * (0.21/S3mV));
  
  Serial.print("PPO2: ");         Serial.println(PPO2*0.9797);
  Serial.print("SmV: ");          Serial.println(SmV);
  Serial.print("SmV_adj: ");      Serial.println(SmV * 0.039906103);
  Serial.print("firstValue1: ");  Serial.println(firstValue1);
  
  Serial.print("PPO22: ");         Serial.println(PPO22*0.9797);
  Serial.print("S2mV: ");          Serial.println(S2mV);
  Serial.print("SmV_adj2: ");      Serial.println(S2mV * 0.039906103);
  Serial.print("firstValue2: ");  Serial.println(firstValue2);
  
  Serial.print("PPO23: ");         Serial.println(PPO23*0.9797);
  Serial.print("S3mV: ");          Serial.println(S3mV);
  Serial.print("SmV_adj3: ");      Serial.println(S3mV * 0.039906103);
  Serial.print("firstValue3: ");  Serial.println(firstValue3);
  Serial.println("");
  Serial.println("");
  
  if(SmV < 8.00 || SmV > 13.00){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,22);
    display.print("Err");
  }else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,22);
    display.print(PPO2);
    display.display();
    delay(500);
  }

//************ 2nd sensor ***************
    
  if(S2mV < 8.00 || S2mV > 13.00){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(67,22);
    display.print("Err");
  }else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(67,22);
    display.print(PPO22);
    display.display();
    delay(500);
  }

// ************** 3rd sensor ***************

  if(S3mV < 8.00 || S3mV > 13.00){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,47);
    display.print("Err");
  }else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,47);
    display.print(PPO23);
    display.display();
    delay(500);
  }
  
  delay(1000);
  warning();
  
}
