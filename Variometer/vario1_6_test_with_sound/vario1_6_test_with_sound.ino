#include <Wire.h>
#include <StopWatch.h>
StopWatch sw_mils(StopWatch::MILLIS);
StopWatch sw_secs(StopWatch::SECONDS);
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
//#include <SimpleTimer.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

#define I2C_ADDRESS 0x77 

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

float meters = 0;
//SimpleTimer timer;
//
//void sendUptime()
//{
//  Serial.println(lastBeepAlt);
//}

void setup()
{  
  Serial.begin(19200); 
  Wire.begin();
  bmp085_get_cal_data();
  readSensorData(&temperature,&pressure);
  long altitude=44330000*((float) 1-pow(((float) (pressure)/101325), 1/5.255));
  lastBeepAlt=altitude;
  lastBeepTime=millis();
  lastPressure=pressure;
  smoothA=altitude;
  tone(8,500);
  delay(100);
  tone(8,2000);
  delay(100);
  tone(8,1000,50);
  
//  timer.setInterval(1000L, sendUptime);
}

void loop()
{
  sw_mils.start();
  sw_secs.start();
  readSensorData(&temperature,&pressure);
  long altitude=44330000*((float) 1-pow(((float) (pressure)/101325), 1/5.255)); // altitude in millimetres
  smoothA=smoothA+((altitude-smoothA)/altGain); // low pass filter
  
  if ((beep) && (smoothA>lastBeepAlt+beepDistance-silenceDistance)) {// stop beeping before reaching next beep threshold
    noTone(8);
    beep=false;
  } 
  else if (abs(smoothA-lastBeepAlt)>beepDistance) {
    roc=(smoothA-lastBeepAlt)*1000/((long) millis()-lastBeepTime);
    if (roc>cSquelch) {
      tone(8,500+(400*roc/(roc+4000)),maxBeepDuration);
      beep=true;
    } 
    else if (roc<dSquelch) {
      tone(8,250+(200*roc/(-roc+4000)),maxBeepDuration);
      beep=true;
    }
    lastBeepAlt=smoothA;
    lastBeepTime=millis();
  }
  while (millis()<lastLoop+loopTimer) {
  }
  lastLoop=millis();
  
  if(sw_mils.value() >= 1000){
  meters = (44330000*((float) 1-pow(((float) (pressure)/101325), 1/5.255)))/1000;
  Serial.println(meters);
  sw_mils.reset();
  }
  
  if(sw_secs.value() >=1){
  float change = 0;
  float checkmeters = (44330000*((float) 1-pow(((float) (pressure)/101325), 1/5.255)))/1000;
      if(checkmeters > meters){
      change = (checkmeters-meters);
      }
      else{
      change = (checkmeters-meters);
      }  
  Serial.print("m/s: ");
  Serial.println(change);
  sw_secs.reset();
  }
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




















