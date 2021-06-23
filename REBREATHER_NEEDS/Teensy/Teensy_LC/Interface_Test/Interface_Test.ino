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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
      display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,0); display.print("0.21");
    display.setCursor(0,20); display.print("0.21");
    display.setCursor(0,40); display.print("0.21");

    display.fillRoundRect(51, 0, 39, 57, 5, WHITE);
    display.setTextSize(1);
    display.setTextColor(BLACK,WHITE);
    display.setCursor(53,5); display.print("40.8mV");
        display.setCursor(53,24); display.print("40.8mV");
            display.setCursor(53,43); display.print("40.8mV");

    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(98,2); display.print("99");
    display.setCursor(98,40); display.print("70");
    display.setTextSize(1);
    display.setCursor(121,2); display.print("%");
    display.setCursor(121,40); display.print("C");
    display.setCursor(99,25); display.print("3.7V");

    display.drawRoundRect(94, 0, 34, 19, 5, WHITE);
        display.drawRoundRect(94, 38, 34, 19, 5, WHITE); 
    //x start position,y start position, szer, wys, zaokraglenie
                
    display.display();
    //display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
//    display.drawRoundRect(20, 20, 20, 20, 5, WHITE); 
//    //x start position,y start position, szer, wys, zaokraglenie
//    display.display();
int b = analogRead(A0);
int a = map(b,0,1023,0,123);
    display.drawLine(0, 60, a,60, WHITE);
    display.drawLine(0, 61, a,61, WHITE);
    display.display();
    Serial.println(b);
    // start linii, wysokość startu, koniec linii, wysokość końca
delay(500);
    display.drawLine(0, 60, 123,60, BLACK);
    display.drawLine(0, 61, 123,61, BLACK);
}
