 /*
 Using Display: http://www.ebay.com/itm/301504841805
 Compiled Arduino GUI 1.7.0 on 2015-04-04 by M. Ray Burnette - PUBLIC DOMAIN excepting libs: see Licenses.h
    Sketch uses 28,456 bytes (26%) of program storage space. Maximum is 108,000 bytes.
    Global variables use 5,816 bytes of dynamic memory.
 */

#include <SPI.h>
#include <Wire.h>
#include <Streaming.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "BMP085.h" // #include "I2Cdev.h" is pulled in also

// These pin #'s are for Maple Mini
//     __Signal__Maple_//__OLED 128x64___
#define OLED_CS   14   //   ---   x Not Connected
#define OLED_DC   22   //   D/C   pin# 6
#define OLED_RST  21   //   RST   pin# 5
#define OLED_MOSI 20   //   SDA   pin# 4
#define OLED_CLK  19   //   SCL   pin# 3

Adafruit_SSD1306 OLED(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);  // OLED object
BMP085 barometer;                                                        // barometer object 

int hPa10, Fah10;                                    // used for Nokia LCD integer to character - faux decimal place
int localCorrect = 3400;                             //  +/- hPa*100 to correct for local altitude: 100X delta:  3400== Briscoe Field, Ga
float temperature;
float pressure;                                      // How many hPa in 1 mm Hg? The answer is 1.3332239
float inHg;
float mmhg_conversion= 3386.388140071641;            // convert hPa to inches Hg
float altitude;
int32_t lastMicros;
byte error, address        = 77;                     // I2C address specific to BMP180
unsigned long TimeMarker;
unsigned long PlotTime;                              // trigger point to store Barometric reading
const unsigned long GraphResponsemS = 540000 ;       // 9 minutes per array element,  9*80 = 720 minutes = 12 hours total

boolean Imperial = false;


void setup()   {
  pinMode (17, OUTPUT); digitalWrite(17, LOW);       // BMP180 "Gnd"
  pinMode (18, OUTPUT); digitalWrite(18, HIGH);      // BMP180 "Vcc"

  OLED.begin(SSD1306_SWITCHCAPVCC);                  // generate OLED HV on module!
  OLED.display();                                    // Splash screen == all blanks or Logo if present
  OLED.clearDisplay();                               // Clear the buffer, blank screen
  OLED.setTextColor(WHITE);                          // defaults to BLACK background
  // OLED.setCursor(0,16);                           // top-left of Blue Pixels (15 is blank-line separator)
  // OLED.setTextSize(1);                            // 21 char/line (fills 1st & 2nd lines in yellow) 8 lines Max
  // OLED.setTextSize(2);                            // 10 char/line (fills 1st line in yellow)        4 lines Max
  // OLED.setTextSize(3);                            //  7 char/line (overflows 1st yellow into Blue)
  OLED.setTextSize(2);
  OLED.setCursor(0, 0);
  OLED.print("Ver.150403");                          // .print writes into SRAM buffer
  OLED.display();                                    // .display() sends buffer to OLED
  
  Wire.begin(); 
  barometer.initialize();                            // I2C Stuff for barometer
  Wire.beginTransmission(address);                   // <       ditto       >
  error = Wire.endTransmission();

  if(barometer.testConnection())
  {
    OLED.println("I2C: OK");
  } else {
    OLED.println("IC2: Fail");
    for(;; ) {;}                                     // Error with infinite loop
  }
  OLED.setTextSize(1);
  OLED.println("");
  OLED.println(" by: Ray Burnette");
  OLED.print("  Barometric Pres. &   Temperature");
  OLED.display();
  delay(1000);
  // Y = 15 is the Blank Line between yellow / blue
}


void loop() {
  Imperial = !(Imperial);                            // toggle between British & SI
  barometer.setControl(BMP085_MODE_TEMPERATURE);     // request temperature
  lastMicros = micros();
  while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds()); // wait for conversion (4.5ms delay)
  if ( Imperial )  temperature = barometer.getTemperatureF();
  if (!(Imperial)) temperature = barometer.getTemperatureC();
  lastMicros = micros();
  barometer.setControl(BMP085_MODE_PRESSURE_3);      // request pressure (3x oversampling mode, high detail, 23.5ms delay)
  while (micros() - lastMicros < barometer.getMeasureDelayMicroseconds());

  pressure = barometer.getPressure();                // read calibrated pressure value in Pascals (Pa)
  pressure += localCorrect;
  inHg = float ( pressure / mmhg_conversion);

  OLED.clearDisplay();                               // Clear the buffer.
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);                          // only WHITE and BLACK available
  OLED.setCursor(0,0);
  OLED.println(  "Pressure Temperature");
  OLED.setCursor(0,16);                              // 15 is blank-line separator
  OLED.setTextSize(2);
  if (Imperial) {
    OLED.print(inHg);  OLED.println(" inHg     ");
    OLED.print(temperature); OLED.println(" F");
  } else {
    OLED.print(int(pressure/100L)); OLED.println("  hPa    ");
    OLED.print(temperature); OLED.print(" C");
  }
  OLED.display();
  OLED.startscrollleft(0x00, 0x01);
  delay(10000);
}

