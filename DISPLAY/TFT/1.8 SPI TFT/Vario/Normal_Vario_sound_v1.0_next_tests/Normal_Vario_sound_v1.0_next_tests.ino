#include <Wire.h>

#define I2C_ADDRESS 0x77 


/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <StopWatch.h>
#include <EEPROM.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS    10
#define TFT_RST    8  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     9

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


const unsigned char oversampling_setting = 3; 
const unsigned char pressure_waittime[4] = {5, 8, 14, 26};
const int cSquelch=0;      // beep when climbin at more than xxx mm/s
const int dSquelch=-2200;  // buzz when descending at more than xxx mm/s
const int loopTimer=40; // ms per loop
const unsigned int altGain=18; // more means slower response / less noise
const int beepDistance=250;  // beep every xxx mm
const int silenceDistance=100; // silence xxx mm before next beep
const int maxBeepDuration=300; // beep no longer than xxx ms

//BMP180 calibration data
int ac1;
int ac2; 
int ac3; 
unsigned int ac4;
unsigned int ac5;
unsigned int ac6;
int b1; 
int b2;
int mb;
int mc;
int md;
long roc=0;
unsigned long lastLoop=0;
long smoothA=0;
long lastBeepAlt=0; 
long lastBeepTime=0;
boolean beep=false;
int  temperature;
long pressure;
long lastPressure;

float rising;
float hPa;
float freshAlt;
float lastAlt;
float startAlt;
float loopAlt;
float secondAlt;

StopWatch sw_mils(StopWatch::MILLIS);
StopWatch sw_micros(StopWatch::MICROS);

void setup()
{  
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0,0); tft.setTextColor(ST7735_WHITE); tft.setTextSize(2);
       tft.println("START");
       delay(2000);
  // Serial.begin(14400); 
  Wire.begin();
  bmp085_get_cal_data();
  readSensorData(&temperature,&pressure);
  long altitude=44330000*((float) 1-pow(((float) (pressure)/101325), 1/5.255));
  lastBeepAlt=altitude;
  lastBeepTime=millis();
  lastPressure=pressure;
  smoothA=altitude;
  tone(5,500);
  delay(100);
  tone(5,2000);
  delay(100);
  tone(5,1000,50);
  hPa = pressure*0.01;
  startAlt = 44330.0 * (1.0 - pow(hPa / 1013.25, 0.1903));
}

void loop()
{
  sw_mils.start();
  readSensorData(&temperature,&pressure);
  long altitude=44330000*((float) 1-pow(((float) (pressure)/101325), 1/5.255)); // altitude in millimetres
  smoothA=smoothA+((altitude-smoothA)/altGain); // low pass filter
  
  if ((beep) && (smoothA>lastBeepAlt+beepDistance-silenceDistance)) {// stop beeping before reaching next beep threshold
    noTone(5);
    beep=false;
  } 
  else if (abs(smoothA-lastBeepAlt)>beepDistance) {
    roc=(smoothA-lastBeepAlt)*1000/((long) millis()-lastBeepTime);
    if (roc>cSquelch) {
      tone(5,500+(400*roc/(roc+4000)),maxBeepDuration);
      beep=true;
    } 
    else if (roc<dSquelch) {
      tone(5,250+(200*roc/(-roc+4000)),maxBeepDuration);
      beep=true;
    }
    lastBeepAlt=smoothA;
    lastBeepTime=millis();
  }
  while (millis()<lastLoop+loopTimer) {
  }
  lastLoop=millis();
  
  

  if(sw_mils.value() >= 1000){
  readAlt();
  }
//  tft.println("temp");
//  tft.setCursor(0,55);
//  tft.print(hPa,2); tft.println("press");
//  tft.setCursor(0,75);
//  tft.print(hPa*8.43,1); tft.println("alt");
  
}

void readSensorData(int* temperature, long* pressure) {
  int  ut= bmp085_read_ut();
  long up = bmp085_read_up();
  long x1, x2, x3, b3, b5, b6, p;
  unsigned long b4, b7;

  //calculate the temperature
  x1 = ((long)ut - ac6) * ac5 >> 15;
  x2 = ((long) mc << 11) / (x1 + md);
  b5 = x1 + x2;
  *temperature = (b5 + 8) >> 4;

  //calculate the pressure
  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11; 
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
  b3 = (((int32_t) ac1 * 4 + x3 +2)<<oversampling_setting) >> 2;
  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (uint32_t) (x3 + 32768)) >> 15;
  b7 = ((uint32_t) up - b3) * (50000 >> oversampling_setting);
  p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;

  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  *pressure = p + ((x1 + x2 + 3791) >> 4);

}


unsigned int bmp085_read_ut() {
  write_register(0xf4,0x2e);
  delay(5); //longer than 4.5 ms
  return read_int_register(0xf6);
}

void  bmp085_get_cal_data() {
  ac1 = read_int_register(0xAA);
  ac2 = read_int_register(0xAC);
  ac3 = read_int_register(0xAE);
  ac4 = read_int_register(0xB0);
  ac5 = read_int_register(0xB2);
  ac6 = read_int_register(0xB4);
  b1 = read_int_register(0xB6);
  b2 = read_int_register(0xB8);
  mb = read_int_register(0xBA);
  mc = read_int_register(0xBC);
  md = read_int_register(0xBE);
}


long bmp085_read_up() {
  write_register(0xf4,0x34+(oversampling_setting<<6));
  delay(pressure_waittime[oversampling_setting]);

  unsigned char msb, lsb, xlsb;
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(0xf6);  // register to read
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDRESS, 3); // read a byte
  while(!Wire.available()) {
    // waiting
  }
  msb = Wire.read();
  while(!Wire.available()) {
    // waiting
  }
  lsb |= Wire.read();
  while(!Wire.available()) {
    // waiting
  }
  xlsb |= Wire.read();
  return (((long)msb<<16) | ((long)lsb<<8) | ((long)xlsb)) >>(8-oversampling_setting);
}

void write_register(unsigned char r, unsigned char v)
{
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(r);
  Wire.write(v);
  Wire.endTransmission();
}

char read_register(unsigned char r)
{
  unsigned char v;
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(r);  // register to read
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDRESS, 1); // read a byte
  while(!Wire.available()) {
    // waiting
  }
  v = Wire.read();
  return v;
}

int read_int_register(unsigned char r)
{
  unsigned char msb, lsb;
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(r);  // register to read
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDRESS, 2); // read a byte
  while(!Wire.available()) {
    // waiting
  }
  msb = Wire.read();
  while(!Wire.available()) {
    // waiting
  }
  lsb = Wire.read();
  return (((int)msb<<8) | ((int)lsb));
}

void readAlt(){
  sw_mils.stop();
  hPa = pressure*0.01;
  freshAlt = (44330.0 * (1.0 - pow(hPa / 1013.25, 0.1903)))-startAlt;
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
  tft.setCursor(0,35);
  if(freshAlt != lastAlt) {
    lastAlt = (lastAlt + freshAlt)/2;
    tft.print(freshAlt-lastAlt);
  }
  else{ tft.print("0.0"); }
  
  sw_mils.reset(); 
}


















