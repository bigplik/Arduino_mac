/*
VER 6
 Get pressure, altitude, and temperature from the BMP085.
 Serial.print it out at 19200 baud to serial monitor.
 */
 
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


float startAltitude;
float meters = 0;
float checkmeters = 0;
float cisnienie = 0;

const int sensorMin = 0;      // sensor minimum, discovered through experiment
const int sensorMax = 101325;

float correct;
float wysokoscWzgledna;
float temp;

float p = 3.14;

//#include <Wire.h>
#define BMP085_ADDRESS 0x77  // I2C address of BMP085

const unsigned char OSS = 0;  // Oversampling Setting

// Calibration values
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

long b5;

void setup(){
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  Serial.begin(19200);
  Serial.println("\n\rArduino BMP085 Variometer (Vario_002) By Chris Leaver");
  Wire.begin();

  bmp085Calibration();
  pinMode(5, OUTPUT);
}

void loop()
{
  tft.setRotation(1);
  float previous_altitude;
  float current_altitude = 0;
  float temperature;
  float pressure = 0;
  float current_pressure = 0;
  float mean;
  float change;
  float mean_change = 0;
  unsigned char counter = 0;
  unsigned char counter2 = 0;
 
  #define SAMPLES 100.00
  #define SAMPLES2  20
 
 // First Load initial mean of 100 points
 temperature = bmp085GetTemperature(bmp085ReadUT()); //MUST be called first
 
 for (unsigned int i=0;i< SAMPLES;i++) pressure += bmp085GetPressure(bmp085ReadUP());
 pressure = pressure / SAMPLES;    
 previous_altitude = calcAltitude(pressure);       

 Serial.print("ORIGINAL QNH = ");
 Serial.println(previous_altitude, 2); //display 2 decimal places
 
 while(1)
   {
     temperature = bmp085GetTemperature(bmp085ReadUT()); //MUST be called first for each loop
     current_pressure = bmp085GetPressure(bmp085ReadUP());
    
// Calculates moving average of 'n' SAMPLES    
     pressure = ((pressure * (SAMPLES-1)) + current_pressure)/SAMPLES;
 
// EVERY XXX INTERVALS do the following...
     counter ++;
     if (counter > 5) // 20 works OK
       {
         counter = 0; // Reset counter
        
         current_altitude = calcAltitude(pressure);
         change = current_altitude-previous_altitude;
         previous_altitude = current_altitude;
        
         mean_change = ((mean_change * (SAMPLES2-1)) + change)/SAMPLES2;
        
         generate_audio(mean_change);
         // total change over the period of the counter
       }  
     
// AND GENERATE PRINTED RESULTS AT A DIFFERENT RATE SAY EVERY 50 LOOPS 
     counter2 ++;
    if (counter2 > 50) // Print data every 50 samples
       {
         tft.setTextSize(4);
         tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
         tft.setCursor(10,10);
         counter2 = 0; // Reset counter
         Serial.print("QNH: ");
         Serial.print(current_altitude, 2); //display 2 decimal places
         tft.println(current_altitude,2);
         Serial.print("\tChange : ");
         Serial.println(mean_change);
         tft.setCursor(10,60);
         tft.println(mean_change);
       }
   }
}

// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void bmp085Calibration()
{
  ac1 = bmp085ReadInt(0xAA);
  ac2 = bmp085ReadInt(0xAC);
  ac3 = bmp085ReadInt(0xAE);
  ac4 = bmp085ReadInt(0xB0);
  ac5 = bmp085ReadInt(0xB2);
  ac6 = bmp085ReadInt(0xB4);
  b1 = bmp085ReadInt(0xB6);
  b2 = bmp085ReadInt(0xB8);
  mb = bmp085ReadInt(0xBA);
  mc = bmp085ReadInt(0xBC);
  md = bmp085ReadInt(0xBE);
}

// Calculate temperature in deg C
float bmp085GetTemperature(unsigned int ut){
  long x1, x2;

  x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
  x2 = ((long)mc << 11)/(x1 + md);
  b5 = x1 + x2;

  float temp = ((b5 + 8)>>4);
  temp = temp /10;

  return temp;
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long bmp085GetPressure(unsigned long up){
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;

  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;

  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;

  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;

  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;

  long temp = p;
  return temp;
}

// Read 1 byte from the BMP085 at 'address'
char bmp085Read(unsigned char address)
{
  unsigned char data;

  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(BMP085_ADDRESS, 1);
  while(!Wire.available());

  return Wire.read();
}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int bmp085ReadInt(unsigned char address)
{
  unsigned char msb, lsb;

  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(BMP085_ADDRESS, 2);
  while(Wire.available()<2)
    ;
  msb = Wire.read();
  lsb = Wire.read();

  return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value
unsigned int bmp085ReadUT(){
  unsigned int ut;

  // Write 0x2E into Register 0xF4
  // This requests a temperature reading
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(0xF4);
  Wire.write(0x2E);
  Wire.endTransmission();

  // Wait at least 4.5ms
  delay(5);

  // Read two bytes from registers 0xF6 and 0xF7
  ut = bmp085ReadInt(0xF6);
  return ut;
}

// Read the uncompensated pressure value
unsigned long bmp085ReadUP(){

  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;

  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(0xF4);
  Wire.write(0x34 + (OSS<<6));
  Wire.endTransmission();

  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));

  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  msb = bmp085Read(0xF6);
  lsb = bmp085Read(0xF7);
  xlsb = bmp085Read(0xF8);

  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);

  return up;
}

void writeRegister(int deviceAddress, byte address, byte val) {
  Wire.beginTransmission(deviceAddress); // start transmission to device
  Wire.write(address);       // send register address
  Wire.write(val);         // send value to write
  Wire.endTransmission();     // end transmission
}

int readRegister(int deviceAddress, byte address){

  int v;
  Wire.beginTransmission(deviceAddress);
  Wire.write(address); // register to read
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, 1); // read a byte

  while(!Wire.available()) {
    // waiting
  }

  v = Wire.read();
  return v;
}

float calcAltitude(float pressure){

  float A = pressure/101325;
  float B = 1/5.25588;
  float C = pow(A,B);
  C = 1 - C;
  C = C /0.0000225577;

  return C;
}

//=============== AUDIO BEEPS =============================

// Rate definitions for audio output
//#define alt_threshold  0.05 is about 2 standard deviations of noise on signal!
#define alt_threshold  0.04

void generate_audio(float change)
{
  // Dont bother if very small changes..
  // tone (pin, frequency, optional duration mS)
  // change is likely to be in the range -1.00 to +1.00
 
  if ((abs(change)) < alt_threshold)
    {
      noTone(5);
      return;
    }


// Ignore normal decents
 if ((change < 0) & (change > -0.08))
    {
      noTone(5);
      return;
    }
 
 
  // Double the OFF time if going DOWN
  if (change < 0)
      {
       noTone(5);
       delay(100);
      }
 
  // Given that the change is bigger than a minimal threshold
  // We need to constrain the values
  change = 1000*(constrain(change, -1, 1)); // to get +/-1000 as upper/lower limit
  change = map(change, -1000, 1000, 10, 2000);
 
 
  // Standard short pause for going up
  noTone(5);
  delay(100);               // wait for 1/10 second
  // Now generate correct tone...
  tone(5,change);
}
