#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

#include <DataCoder.h>
#include <VirtualWire.h>

const int rx_pin = 11;
const int led_pin = 13;
const int baudRate = 1000;

float depth;

void setup()   {                
  //Serial.begin(9600);
  
  delay(1000);
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
  digitalWrite(led_pin,LOW);
  SetupRFDataRxnLink(rx_pin, baudRate);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  delay(500);
  pinMode(7, OUTPUT);
}


void loop() {  
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  union RFData inDataSeq;//To store incoming data
  
  float inArray[RF_DATA_ARRAY_SIZE];//To store decoded information
  //RF_DATA_ARRAY_SIZE can be changed if need be inside DataCoder.h
  
  
  if(RFLinkDataAvailable(buf, &buflen))
  {
        digitalWrite(led_pin, HIGH);
        
        for(int i =0; i< buflen; i++)
        {
          inDataSeq.s[i] = buf[i];
        }
        
        Serial.println();
        
        digitalWrite(led_pin, LOW);
      
        DecodeRFData(inArray, inDataSeq);
        
        //Do something with the information that have been received
       

  }
          //    depth = inArray[0];

        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0,5);
            //display.print(depth);
            display.print(inArray[0]);
            display.display();
        //    delay(500);
  display.clearDisplay();

}
