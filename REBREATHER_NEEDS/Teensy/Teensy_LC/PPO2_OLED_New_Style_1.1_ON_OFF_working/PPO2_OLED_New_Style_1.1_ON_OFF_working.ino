#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1015.h>

#include <Snooze.h>

/*** Must be global ***/
SnoozeBlock config;

boolean state = true;

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

int16_t adc0, adc1, adc2;

double SmV, S2mV, S3mV, SmVact, SmVact2, SmVact3;

float PPO2, PPO22, PPO23;

Adafruit_ADS1115 ads;

unsigned int firstValue1 = 0;
unsigned int firstValue2 = 0;
unsigned int firstValue3 = 0;
unsigned int secondValue1 = 0;
unsigned int secondValue2 = 0;
unsigned int secondValue3 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.drawBitmap(0, 0, bds, 128, 64, WHITE);
  display.display();
  delay(1000);

//Version_Info
  delay(200);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(5,30); 
  display.print("V_OLED_NEW_STYLE_1.1");
  display.display();
  delay(5000);
  display.clearDisplay();
  display.display();
  
  ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  ads.begin();
  OxygenCalculations();

  delay(200);
    sensor_STATUS();
  //display.setRotation(2);

    //display.clearDisplay();
    //pinMode(15,OUTPUT);
    config.pinMode(9, INPUT_PULLUP, FALLING);
    //config.setTimer(5000);
    pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
//    display.drawRoundRect(20, 20, 20, 20, 5, WHITE); 
//    //x start position,y start position, szer, wys, zaokraglenie
//    display.display();
    switch(state){
      
      case false:
            Serial.println("Sleep");
            digitalWrite(15,HIGH);
            display.ssd1306_command(SSD1306_DISPLAYOFF); 
            //SSD1306_DISPLAYON 0xAF
            delay(200);
            Snooze.deepSleep( config );
            //Snooze.sleep( config );
            digitalWrite(15,LOW);
            display.ssd1306_command(SSD1306_DISPLAYON);
            state =! state;
            break;
      case true:
            OxygenLoop();
            loopDISPLAY();
//            int b = analogRead(A0);
//            int a = map(b,0,1023,0,123);
//                display.drawLine(0, 60, a,60, WHITE);
//                display.drawLine(0, 61, a,61, WHITE);
//                display.display();
//                Serial.println(b);
//                // start linii, wysokość startu, koniec linii, wysokość końca
//            delay(500);
//            display.drawLine(0, 60, 123,60, BLACK);
//            display.drawLine(0, 61, 123,61, BLACK);
            secondValue1 = 0;
            secondValue2 = 0;
            secondValue3 = 0;
            if(digitalRead(2) == LOW) state =! state;
            break;
    }
}
