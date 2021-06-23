/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_MOSI   4
#define OLED_CLK   3
#define OLED_DC    6
#define OLED_CS    7
#define OLED_RESET 5
Adafruit_SH1106 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SH1106 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

const unsigned char PROGMEM bds [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0x0D, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xFF, 0xFF, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xC1, 0xFF, 0xFF, 0xFE, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFC, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x3F, 0xFF, 0xFC, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x1F, 0xFF, 0xF8, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xF8, 0x1F, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xE8, 0x07, 0xFF, 0xF0, 0x0F, 0x81, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x03, 0xFF, 0xF0, 0x06, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x80, 0x00, 0x00, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0xC0, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x60, 0x01, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x60, 0x00, 0x80, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xEC, 0x20, 0x6E, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x91, 0x13, 0x22, 0x00, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xED, 0x6C, 0x1F, 0x00, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0x00, 0x00, 0xED, 0x6C, 0x01, 0x00, 0xFF, 0xFC, 0x00, 0x7E, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x30, 0x92, 0x10, 0x60, 0xFF, 0xFE, 0x00, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x0F, 0x6D, 0xF0, 0xF0, 0xFF, 0xFE, 0x01, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x0F, 0x6D, 0x98, 0x80, 0xFF, 0xFE, 0x01, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC3, 0xC0, 0x10, 0x07, 0x92, 0x01, 0x00, 0xFF, 0xFE, 0x03, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC1, 0xC0, 0x18, 0x03, 0xEE, 0x0F, 0x40, 0x00, 0x16, 0x03, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC3, 0xC0, 0x1E, 0x02, 0x6C, 0x0C, 0xE0, 0x00, 0x00, 0x03, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x80, 0x1F, 0x01, 0xFA, 0x0B, 0x60, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x00, 0x1F, 0x19, 0xFA, 0x0B, 0x40, 0x01, 0x02, 0x03, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x80, 0x1E, 0x00, 0x70, 0x00, 0x40, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xC0, 0x1C, 0x0D, 0x7D, 0xED, 0xE0, 0x00, 0x6A, 0x03, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xE0, 0x1C, 0x01, 0x71, 0x89, 0x98, 0x00, 0x68, 0x01, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC1, 0xE0, 0x18, 0x11, 0x93, 0x63, 0x6C, 0x00, 0x98, 0x01, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC0, 0xE0, 0x18, 0x6D, 0xEF, 0x6F, 0x6F, 0x63, 0x78, 0x00, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC1, 0xE0, 0x10, 0x6C, 0x6C, 0x8C, 0x93, 0x13, 0x60, 0x00, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xE0, 0x10, 0xB9, 0xBB, 0x6B, 0x6D, 0x4D, 0xD0, 0x00, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xE0, 0x10, 0xB9, 0xBB, 0x6A, 0x2D, 0x4C, 0x40, 0x00, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0xC0, 0x18, 0x6C, 0x6C, 0x8C, 0x03, 0x10, 0x20, 0x01, 0xFE, 0x00, 0x00,
0x00, 0x00, 0x03, 0xC7, 0x80, 0x18, 0x0D, 0xEF, 0x6C, 0x00, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x01, 0x93, 0x60, 0x40, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x01, 0x6D, 0x80, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x01, 0x6D, 0xE0, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0x12, 0x00, 0x1D, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x09, 0x60, 0x3F, 0xF0, 0x00, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x09, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x04, 0x80, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x00, 0x01, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0x00, 0x03, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC0, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC0, 0x0F, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC2, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC3, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xC3, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

int greenLED = 3;    //blue wire
int redLED = 5;      //brown wire
int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;
int j;
int modelmV = 13;
float SmV;
float S2mV;
float S3mV;
float m1;
float m2;
float m3;
float M = 41.7;
float WK1;
float WK2;
float WK3;
float PPO2;
float PPO22;
float PPO23;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(15);

  // Clear the buffer.
  display.clearDisplay();

  display.drawBitmap(-5, 0, bds, 128, 64, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();

//*************************logo*****************8
display.setTextSize(3);
display.setTextColor(WHITE);
  display.setCursor(10,22);
  display.println("Origin");
  display.display();
  delay(2500);
    uint16_t a;
    for( a=0; a<128; a++) display.drawPixel(a, 17, 1);
    
    for( a=0; a<128; a++) display.drawPixel(a, 50, 1);
    display.display();
    delay(800);
  display.setTextSize(2);
display.setTextColor(WHITE);
  display.setCursor(44,0);
  display.println("BDS");
  display.display();
  display.setTextSize(1);
display.setTextColor(WHITE);
  display.setCursor(29,56);
  display.println("PPO2 Display");
  display.display();
  delay(3000);
  display.clearDisplay();
  
//******************************************  
//********************************kalibracja
  for(j = 0 ; j < 10 ; j++)

{

firstValue1 += analogRead(A0);                          //sumowanie kolejnych pomiarów
firstValue2 += analogRead(A1);
firstValue3 += analogRead(A2);
delay(100);                                               //opóźnienie

}

firstValue1 /=10;                                                            //liczenie wartości średniej
firstValue2 /=10;                                                            //i zapamiętanie jej
firstValue3 /=10;


SmV = (firstValue1/4.95)*1.062; //dane przeliczone do miliVolt dla S1
S2mV = (firstValue2/4.95); //dla S2
S3mV = (firstValue3/4.95); //dla S3
    //wartość M, współczynnik nachylenia dla prostej idealnej
                //dla sensora o 13mV
m1=(SmV/0.21);   //m dla sensora 1
m2=(S2mV/0.21);   //dla 2
m3=(S3mV/0.21);
WK1 = M/m1;
WK2 = M/m2;
WK3 = M/m3;
  
  //*********************status sensorów
  uint16_t b;
    for( b=0; b<128; b++) display.drawPixel(b, 16, 1);
    
    for( b=0; b<128; b++) display.drawPixel(b, 32, 1);
    
    for( b=0; b<128; b++) display.drawPixel(b, 48, 1);
    
    for( b=17; b<64; b++) display.drawPixel(20, b, 1); // oś pionowa
    for( b=17; b<64; b++) display.drawPixel(75, b, 1);

  display.display();
  
  //************************************************
  //***********opis danych do sensorów w tabeli
  
  //************nagłówek tabeli
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4,6);
  display.println("#     mV     Status");
  
   //**********************numery sensorów
  display.setCursor(2,20);
  display.println("1");
  display.setCursor(2,36);
  display.println("2");
  display.setCursor(2,52);
  display.println("3");
  
  //***************wartości sensorów w miliVoltach
  display.setCursor(35,20);
  display.println(SmV);
  display.setCursor(35,36);
  display.println(S2mV);
  display.setCursor(35,52);
  display.println(S3mV);
  display.display();
  
  //*********************sensor ok lub old lub Err
  if(SmV >= 9.00 && SmV <= 13.00){
    display.setCursor(92,20);
    display.println("OK");
    display.display();
  }
  else if(SmV <=8.99 && SmV >=8.00){
    display.setCursor(92,20);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,20);
    display.println("Err");
    display.display();
  }
  
  if(S2mV >= 9.00 && S2mV <= 13.00){   // 2 sensor
    display.setCursor(92,36);
    display.println("OK");
    display.display();
  }
  else if(S2mV <=8.99 && S2mV >=8.00){
    display.setCursor(92,36);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,36);
    display.println("Err");
    display.display();
  }
  
  if(S3mV >= 9.00 && S3mV <= 13.00){      // 3 sensor
    display.setCursor(92,52);
    display.println("OK");
    display.display();
  }
  else if(S3mV <=8.99 && S3mV >=8.00){
    display.setCursor(92,52);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(92,52);
    display.println("Err");
    display.display();
  }
  
  delay(5000);

  // Clear the buffer.
  display.clearDisplay();
 
 //*********************************koniec logo
  
  // text display tests
  display.setTextSize(1);
   display.setTextColor(WHITE);
  display.setCursor(0,2);
  display.println("BDS PPO2 Display");
  
//*********test linia  baterii************
uint16_t i;
for( i=0; i<128; i++) display.drawPixel(i, 16, 1);
for( i=0; i<128; i++) display.drawPixel(i, 42, 1);

for( i=17; i<64; i++) display.drawPixel( 60, i, 1);

  
//************bateria****************
 
  display.drawPixel(103, 3, WHITE);
  display.drawPixel(103, 4, WHITE);
  display.drawPixel(103, 5, WHITE);
  display.drawPixel(103, 6, WHITE);
  display.drawPixel(103, 7, WHITE);

  display.drawPixel(102, 3, WHITE);
  display.drawPixel(102, 4, WHITE);
  display.drawPixel(102, 5, WHITE);
  display.drawPixel(102, 6, WHITE);
  display.drawPixel(102, 7, WHITE);

  display.drawPixel(103, 3, WHITE);
  display.drawPixel(103, 4, WHITE);
  display.drawPixel(103, 5, WHITE);
  display.drawPixel(103, 6, WHITE);
  display.drawPixel(103, 7, WHITE);

  display.drawPixel(127, 1, WHITE);
  display.drawPixel(127, 2, WHITE);
  display.drawPixel(127, 3, WHITE);
  display.drawPixel(127, 4, WHITE);
  display.drawPixel(127, 5, WHITE);
  display.drawPixel(127, 6, WHITE);
  display.drawPixel(127, 7, WHITE);
  display.drawPixel(127, 8, WHITE);
  display.drawPixel(127, 9, WHITE);
  
   display.drawPixel(105, 1, WHITE);
  display.drawPixel(105, 2, WHITE);
  display.drawPixel(105, 3, WHITE);
  display.drawPixel(105, 4, WHITE);
  display.drawPixel(105, 5, WHITE);
  display.drawPixel(105, 6, WHITE);
  display.drawPixel(105, 7, WHITE);
  display.drawPixel(105, 8, WHITE);
  display.drawPixel(105, 9, WHITE);
  
  display.drawPixel(105, 0, WHITE);
  display.drawPixel(106, 0, WHITE);
  display.drawPixel(107, 0, WHITE);
  display.drawPixel(108, 0, WHITE);
  display.drawPixel(109, 0, WHITE);
  display.drawPixel(110, 0, WHITE);
  display.drawPixel(111, 0, WHITE);
  display.drawPixel(112, 0, WHITE);
  display.drawPixel(113, 0, WHITE);
  display.drawPixel(114, 0, WHITE);
  display.drawPixel(115, 0, WHITE);
  display.drawPixel(116, 0, WHITE);
  display.drawPixel(117, 0, WHITE);
  display.drawPixel(118, 0, WHITE);
  display.drawPixel(119, 0, WHITE);
  display.drawPixel(120, 0, WHITE);
  display.drawPixel(121, 0, WHITE);
  display.drawPixel(122, 0, WHITE);
  display.drawPixel(123, 0, WHITE);
  display.drawPixel(124, 0, WHITE);
  display.drawPixel(125, 0, WHITE);
  display.drawPixel(126, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(128, 0, WHITE);

  display.drawPixel(105, 10, WHITE);
  display.drawPixel(106, 10, WHITE);
  display.drawPixel(107, 10, WHITE);
  display.drawPixel(108, 10, WHITE);
  display.drawPixel(109, 10, WHITE);
  display.drawPixel(110, 10, WHITE);
  display.drawPixel(111, 10, WHITE);
  display.drawPixel(112, 10, WHITE);
  display.drawPixel(113, 10, WHITE);
  display.drawPixel(114, 10, WHITE);
  display.drawPixel(115, 10, WHITE);
  display.drawPixel(116, 10, WHITE);
  display.drawPixel(117, 10, WHITE);
  display.drawPixel(118, 10, WHITE);
  display.drawPixel(119, 10, WHITE);
  display.drawPixel(120, 10, WHITE);
  display.drawPixel(121, 10, WHITE);
  display.drawPixel(122, 10, WHITE);
  display.drawPixel(123, 10, WHITE);
  display.drawPixel(124, 10, WHITE);
  display.drawPixel(125, 10, WHITE);
  display.drawPixel(126, 10, WHITE);
  display.drawPixel(127, 10, WHITE);
  display.drawPixel(128, 10, WHITE);
  
   
//***********HUD DISPLAY*****************
pinMode(greenLED, OUTPUT);
pinMode(redLED, OUTPUT);
  
}

//*************************************************
//****************warning commands**************
void warning(){            
  if ( PPO2 <= 0.40 || PPO22 <0.40 || PPO23 <0.40){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(68,47);
    display.print("LOW!");
    display.display();
    digitalWrite(redLED, HIGH);         //turn on the Red LED
    digitalWrite(greenLED, LOW);        //turn off the Green LED
    
  }else if ( PPO2 >= 1.40 || PPO22 >= 1.40 || PPO23 >= 1.40){
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(67,47);
    display.print("HIGH!");
    display.display();
    delay(500);
    display.setCursor(67,47);
    display.print("     ");
    display.display();
    delay(50);
    digitalWrite(redLED, HIGH);        //turn on the Red LED
    digitalWrite(greenLED, LOW);       //turn off the Green LED
  }else{
     display.setTextSize(2.9);
     display.setTextColor(WHITE, BLACK);
     display.setCursor(65,47);
     display.print("     ");
     display.display();
     digitalWrite(redLED, LOW);        //turn off the Red LED
     digitalWrite(greenLED, HIGH);     //turn on the Green LED
     
     
  }
}

void loop() {
  
int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A2);
  
PPO2 = (sensorValue * (5.0 / 1023.0)*WK1);
PPO22 = (sensorValue2 * (5.0 / 1023.0)*WK2);
PPO23 = (sensorValue3 * (5.0 / 1023.0)*WK3);

if(SmV < 8.00 || SmV > 13.00){
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,22);
  display.print("Err");
}else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,22);
    display.print(PPO2);
    display.display();
    delay(500);
    }

//************ 2nd sensor ***************
    
if(S2mV < 8.00 || S2mV > 13.00){
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(67,22);
  display.print("Err");
}else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(67,22);
    display.print(PPO22);
    
    display.display();
    delay(500);
    }

// ************** 3rd sensor ***************

if(S3mV < 8.00 || S3mV > 13.00){
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,47);
  display.print("Err");
}else{
    display.setTextSize(2.9);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,47);
    display.print(PPO23);
    delay(500);
    display.display();
    }
    

// ************* warnning command **************
  warning();

//***************************************************
//*********************battery status****************
   
   int sensorValue4 = analogRead(A6);
   float bat = sensorValue4 * (5.0 / 1023.0);

//*************************************************************
  if(bat >= 3.90){                  //full battery section
  
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(122,7);
  
  uint16_t i;
  
  for( i=107; i<112; i++) display.drawPixel(i, 8, 1); //full battery icon
  for( i=107; i<112; i++) display.drawPixel(i, 7, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 6, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 5, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 4, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 3, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 2, 1);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 1); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 3, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 2, 1);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 1);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 3, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 2, 1);
     
  delay(500);
  display.display();
  
//********************************************************************  
}else if(bat <=3.89 && bat >=3.60){ //mid battery section
  
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(122,7);
  
   uint16_t i;
   
  for( i=107; i<112; i++) display.drawPixel(i, 8, 0); //full battery icon
  for( i=107; i<112; i++) display.drawPixel(i, 7, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 6, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 5, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 4, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 3, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 2, 0);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 1); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 3, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 2, 1);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 1);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 3, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 2, 1);
     
  delay(500);
  display.display();
  
  //******************************************************************
  }else if (bat <=3.59 && bat >=3.30){  //low battery section
  
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(122,7);
  
   uint16_t i;
  
  for( i=107; i<112; i++) display.drawPixel(i, 8, 0); //full battery icon
  for( i=107; i<112; i++) display.drawPixel(i, 7, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 6, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 5, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 4, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 3, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 2, 0);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 0); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 3, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 2, 0);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 1);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 3, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 2, 1);
     
  delay(500);
  display.display();
  
 //**********************************************************
  }else if (bat <=3.29){             //flat battery icon
 
 
  display.setTextSize(2.9);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(122,7);
  
   uint16_t i;
  
  for( i=107; i<112; i++) display.drawPixel(i, 8, 0); //full battery icon
  for( i=107; i<112; i++) display.drawPixel(i, 7, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 6, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 5, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 4, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 3, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 2, 0);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 0); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 3, 0);
  for( i=114; i<119; i++) display.drawPixel(i, 2, 0);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 0);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 3, 0);
  for( i=121; i<126; i++) display.drawPixel(i, 2, 0);
     
  delay(500);
  display.display();
  
  }
  
  //display.ssd1306_command(SSD1306_DISPLAYOFF);
  //display.drawPixel(a, 17, 1);
 // display.begin(0xAE);
  
  
  //SSD1306_DISPLAYALLON_RESUME;
  //display.display();
  delay(6000);
  display.SH1106_command(SH1106_DISPLAYON);
  display.display();
  delay(6000);

}
