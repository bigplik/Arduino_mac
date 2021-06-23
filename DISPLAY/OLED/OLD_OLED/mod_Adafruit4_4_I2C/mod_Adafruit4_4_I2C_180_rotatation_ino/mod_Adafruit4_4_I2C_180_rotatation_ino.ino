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
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
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

int screen;

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(15);

  // Clear the buffer.
  display.clearDisplay();

}





void loop() {
  
 if(screen == 0){
   display.clearDisplay();
   delay(25);
   display.setRotation(4);
   sensory();
   
 }else if (screen == 1){
   display.clearDisplay();
   delay(25);
   display.setRotation(2);
   sensory();
 }

 for(int i=0; i<1; i++){
   
   screen++;
   delay(2500);
   
   
 }
 
 if(screen > 1){
   screen = 0;
 }

 Serial.print(screen);

}




void logo(){
  
  
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
  
  
}


void sensory(){
  
  display.ssd1306_command(SSD1306_INVERTDISPLAY);
  
    //*********************status sensorów
  uint16_t b;
    for( b=0; b<127; b++) display.drawPixel(b, 16, 1);
    
    for( b=0; b<127; b++) display.drawPixel(b, 32, 1);
    
    for( b=0; b<127; b++) display.drawPixel(b, 48, 1);
    
    //for( b=17; b<63; b++) display.drawPixel(20, b, 1); // oś pionowa
    for( b=17; b<63; b++) display.drawPixel(63, b, 1);

  
  //display.display();
  
  //************************************************
  //***********opis danych do sensorów w tabeli
  
  //************nagłówek tabeli
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(16,6);
  display.println("Set your Origin");
  
   //**********************numery sensorów
  display.setCursor(2,20);
  display.println("Depth");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,36);
  display.println("2");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,52);
  display.println("3");
  display.display();
  //***************wartości sensorów w miliVoltach
 
  display.setCursor(45,20);
  display.setTextColor(BLACK, WHITE);
  display.println(" M");
  
  display.setCursor(35,36);
  display.setTextColor(WHITE);
  display.println("set");

  display.setCursor(35,52);
  display.println("set");
  display.display();
 
      display.setCursor(92,20);
    display.println("OK");
    display.setCursor(92,36);
    display.println("OK");
    display.setCursor(92,52);
    display.println("OK");
    
    display.display();
   
}

