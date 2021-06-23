#include <StopWatch.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "U8glib.h"
#include <toneAC.h>


float meters = 0;
float checkmeters = 0;
float startAltitude;


StopWatch sw_secs(StopWatch::SECONDS);
Adafruit_BMP085 bmp;
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.setPrintPos( 60, 20);
  u8g.print(meters);
  u8g.setPrintPos( 0, 20);
  u8g.print(checkmeters);
}

void setup() {
   Serial.begin(9600);
   pinMode(5, OUTPUT);
  // put your setup code here, to run once:
    if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  
    if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  startAltitude = bmp.readAltitude(101500);

}

void loop() {
  
  meters = bmp.readAltitude(101500);
  int cisnienie = bmp.readPressure();

  // put your main code here, to run repeatedly:
  delay(500);
  checkmeters = bmp.readAltitude(101500);
  delay(500);
  measure();
//    Serial.print("Temperature = ");
//    Serial.print(bmp.readTemperature());
//    Serial.println(" *C");
//    
//    Serial.print("Pressure = ");
//    Serial.print(bmp.readPressure());
//    Serial.println(" Pa");
//    
//    // Calculate altitude assuming 'standard' barometric
//    // pressure of 1013.25 millibar = 101325 Pascal
//    Serial.print("Altitude = ");
//    Serial.print(bmp.readAltitude());
//    Serial.println(" meters");
//
//  // you can get a more precise measurement of altitude
//  // if you know the current sea level pressure which will
//  // vary with weather and such. If it is 1015 millibars
//  // that is equal to 101500 Pascals.
//    Serial.print("Real altitude = ");
//    Serial.print(bmp.readAltitude(101500));
//    Serial.println(" meters");
      Serial.println(checkmeters);
      Serial.println(meters);
      Serial.println(cisnienie);
      
        u8g.firstPage();  
  do {
    draw();
    measure();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
 
 
  
 toneAC(cisnienie/2);
 delay(5);

}

void measure(){
  
    if(checkmeters > (meters+1.0) && checkmeters < (meters+2.0)){
    Serial.println("HIGH");
    u8g.drawStr(0,35, "+ 1m/s");
  }
    if(checkmeters > (meters+1.99) && checkmeters < (meters+3.0)){
    u8g.drawStr(0,35, "+2m/s");
  }
  if(checkmeters < (meters-1.0) && checkmeters > (meters-2.0)){
    Serial.println("LOW");
    u8g.drawStr(0,35, "- 1m/s");
  }
  if(checkmeters < (meters-1.99) && checkmeters > (meters-3.0)){
    u8g.drawStr(0,35, "-2m/s");
  }
  

  
}

void tones(){
  
    for  (int x=0; x<100; x++) {
digitalWrite(5, HIGH);
delay (bmp.readPressure());
digitalWrite(5,LOW);
delay(bmp.readPressure());
}
  
}
