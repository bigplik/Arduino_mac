#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN 3

LiquidCrystal_I2C	lcd(0x27,2,1,0,4,5,6,7);

void setup()
{
  lcd.begin (16,2);
 lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
 lcd.setBacklight(HIGH);

lcd.home ();
//lcd.print("Elektro Maras");  
}

void loop()
{
  
 float s1 = analogRead(A0)*(5.0/1023);
 float s2 = analogRead(A1)*(5.0/1023);
 float s3 = analogRead(A2)*(5.0/1023);
 float s4 = analogRead(A4)*(5.0/1023);
 
 lcd.setCursor(0, 0);
 lcd.print("S1 ");
 lcd.print(s1,2);
 lcd.setCursor(9, 0);
 lcd.print("S2 ");
 lcd.print(s2,2);
 lcd.setCursor(0, 1);
 lcd.print("S3 ");
 lcd.print(s3,2);
 lcd.setCursor(9, 1);
 lcd.print("S4 ");
 lcd.print(s4,2);
delay(1000);
 }
