//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int minutes = 0;
int seconds = 0;

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Hello Pawel");
  lcd.setCursor(0,1);
  lcd.print("I am your Xsara");
  delay(2000);
  lcd.setCursor(2,0);
  lcd.print(" Today is    ");
  lcd.setCursor(0,1);
  lcd.print("  01 Jan 2001    ");
  delay(2000);
  lcd.setCursor(2,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Have a nice day ;)");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("                  ");
  //lcd.backlight();
}


void loop()
{
  seconds++;
    //lcd.setCursor(3,0);
//lcd.print("Hello, world!");
  lcd.setCursor(0,0); lcd.print("01-01-2001");
  
  if(seconds<10){
    lcd.setCursor(3,1); lcd.print("0");
    lcd.setCursor(4,1); lcd.print(seconds);
  }
  else{
    lcd.setCursor(3,1); lcd.print(seconds);
  }

  if(seconds >= 59){
    seconds = 0;
    minutes++;
    //lcd.setCursor(11,0); lcd.print("       ");
  }

  if(minutes<10){
  lcd.setCursor(0,1); lcd.print("0");
  lcd.setCursor(1,1); lcd.print(minutes);
  lcd.setCursor(2,1); lcd.print(":");
  }
  else{
    lcd.setCursor(0,1); lcd.print(minutes);
    lcd.setCursor(2,1); lcd.print(":");
  }
  delay(1000);
}
