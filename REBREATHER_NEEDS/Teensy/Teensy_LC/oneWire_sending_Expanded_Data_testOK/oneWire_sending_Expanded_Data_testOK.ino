#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1015.h>
#include <DataCoder.h>
#include <VirtualWire.h>

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

const int rx_pin = 4;
const int led_pin = 13;
const int baudRate = 1000;

float mVsens1 = 0;

float temp = 0;
float hum = 0;
float bat = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.display();
  SetupRFDataRxnLink(rx_pin, baudRate);
  delay(200);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(5,30); 
  display.print("version_OneWire_1.0");
  display.display();
  delay(5000);
  display.clearDisplay();
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
//    display.drawRoundRect(20, 20, 20, 20, 5, WHITE); 
//    //x start position,y start position, szer, wys, zaokraglenie
//    display.display();

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  union RFData inDataSeq;//To store incoming data
  
  float inArray[RF_DATA_ARRAY_SIZE];//To store decoded information
  //RF_DATA_ARRAY_SIZE can be changed if need be inside DataCoder.h

    if(RFLinkDataAvailable(buf, &buflen))
  {
        display.clearDisplay();
        display.display();        
        for(int i =0; i< buflen; i++)
        {
          inDataSeq.s[i] = buf[i];
        }
        DecodeRFData(inArray, inDataSeq);
        
        mVsens1 = inArray[0];
        temp = inArray[1];
        hum = inArray[2];
        bat = inArray[3];
        
  }else{

    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,0); display.print("0.21");
    display.setCursor(0,20); display.print("0.21");
    display.setCursor(0,40); display.print("0.21");

    display.fillRoundRect(51, 0, 39, 57, 5, WHITE);
    display.setTextSize(1);
    display.setTextColor(BLACK,WHITE);
    display.setCursor(53,5); display.print("40.8mV");
        display.setCursor(53,24); display.print(mVsens1);
            display.setCursor(53,43); display.print("40.8mV");

    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(98,2); display.print(hum,0);
    display.setCursor(98,40); display.print(temp,0);
    display.setTextSize(1);
    display.setCursor(121,2); display.print("%");
    display.setCursor(121,40); display.print("C");
    display.setCursor(99,25); display.print(bat);

    display.drawRoundRect(94, 0, 34, 19, 5, WHITE);
        display.drawRoundRect(94, 38, 34, 19, 5, WHITE); 
    //x start position,y start position, szer, wys, zaokraglenie
                
    display.display();
    //display.clearDisplay();
  }
}
