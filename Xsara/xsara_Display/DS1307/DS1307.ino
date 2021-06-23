/*
  DS1307: Real-Time Clock. Simple example
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-ds1307.html
  GIT: https://github.com/jarzebski/Arduino-DS1307
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <DS1307.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

DS1307 clock;
RTCDateTime dt;

void setup()
{
  Serial.begin(9600);
    lcd.init();


  // Initialize DS1307
  Serial.println("Initialize DS1307");;
  clock.begin();

  // If date not set
  if (!clock.isReady())
  {
    // Set sketch compiling time
    clock.setDateTime(__DATE__, __TIME__);
  }
  lcd.backlight();
}

void loop()
{
  dt = clock.getDateTime();

  // For leading zero look to DS1307_dateformat example

  lcd.setCursor(0,0); lcd.print(dt.year);
  lcd.setCursor(4,0); lcd.print("-");
  lcd.setCursor(5,0); lcd.print(dt.month);
  lcd.setCursor(7,0); lcd.print("-");
  lcd.setCursor(8,0); lcd.print(dt.day);
  lcd.setCursor(0,1); lcd.print(dt.hour);
  lcd.setCursor(2,1); lcd.print(":");
  lcd.setCursor(3,1); lcd.print(dt.minute);
  lcd.setCursor(5,1); lcd.print(":");
  lcd.setCursor(6,1); lcd.print(dt.second);

  /*
  Serial.print("Raw data: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  */
  delay(1000);
}
