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

float bat;

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
  
 //if(screen == 0){
   //display.clearDisplay();
 //  delay(25);
  // display.setRotation(4);
   basic_info();
   
// }
 /*
 else if (screen == 1){
   display.clearDisplay();
   delay(25);
   display.setRotation(4);
   basic_info();
   
 }

 for(int i=0; i<1; i++){
   
   screen++;
   delay(2500);
   
   
 }
 
 if(screen > 1){
   screen = 0;
 }
*/

 Serial.println(bat);
 delay(500);

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
    //ostatnia wartość zapala -1 lub gasi -0 pixel
    for( b=0; b<128; b++) display.drawPixel(b, 16, 1);
    
    for( b=0; b<128; b++) display.drawPixel(b, 32, 1);
    
    for( b=0; b<128; b++) display.drawPixel(b, 48, 1);
    
    //for( b=17; b<63; b++) display.drawPixel(20, b, 1); // oś pionowa
    for( b=0; b<64; b++) display.drawPixel(63, b, 1);
    //obramówka settings
    for( b=1; b<62; b++) display.drawPixel(b, 1, 1);
    for( b=1; b<62; b++) display.drawPixel(b, 13, 1);
        for( b=8; b<56; b++) display.drawPixel(b, 3, 1);

    
    for( b=2; b<13; b++) display.drawPixel(1, b, 1);//oś pionowa
    for( b=2; b<13; b++) display.drawPixel(61, b, 1);
        for( b=3; b<12; b++) display.drawPixel(7, b, 1);
        for( b=3; b<12; b++) display.drawPixel(3, b, 1);//przed "settings"
        for( b=3; b<12; b++) display.drawPixel(4, b, 1);
        for( b=3; b<12; b++) display.drawPixel(5, b, 1);
        for( b=3; b<12; b++) display.drawPixel(6, b, 1);
        for( b=3; b<12; b++) display.drawPixel(56, b, 1);//po "settings"
        for( b=3; b<12; b++) display.drawPixel(57, b, 1);
        for( b=3; b<12; b++) display.drawPixel(58, b, 1);
        for( b=3; b<12; b++) display.drawPixel(59, b, 1);
        

  
  //display.display();
  
  //************************************************
  //***********opis danych do sensorów w tabeli
  
  //************nagłówek tabeli
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(8,4);
  display.println("SETTINGS");
  
   //**********************numery sensorów
  display.setTextColor(WHITE);
  display.setCursor(2,20);
  display.println("DISPL");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,36);
  display.println("CONTR");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,52);
  display.println("ROTAT");
  display.display();
  //***************wartości sensorów w miliVoltach
 
  display.setCursor(43,20);
  display.setTextColor(BLACK, WHITE);
  display.println("OFF");
  
  display.setCursor(37,36);
  display.setTextColor(BLACK, WHITE);
  display.println("HIGH");

  display.setTextColor(BLACK, WHITE);
  display.setCursor(43,52);
  display.println("180");
  display.display();
 
    display.setTextColor(WHITE);
    display.setCursor(66,4);
    display.println("RADIO");
    display.setCursor(66,20);
    display.println("CALIB");
    display.setCursor(66,36);
    display.println("UNITS");
    display.setCursor(66,52);
    display.println("LOGBK");
    
    display.setTextColor(BLACK, WHITE);
    display.setCursor(108,4);
    display.println("OFF");
    display.setCursor(102,20);
    display.setTextColor(BLACK, WHITE);
    display.println("AUTO");
    display.setCursor(108,36);
    display.setTextColor(BLACK, WHITE);
    display.println("MTR");
    display.setCursor(114,52);
    display.setTextColor(BLACK, WHITE);
    display.println(">>");
    
    display.display();
   
}



void basic_info(){
  
  display.ssd1306_command(SSD1306_NORMALDISPLAY);
  
  
   // text display tests
  display.setTextSize(1);
   display.setTextColor(WHITE);
  display.setCursor(0,3);
  display.println("BDS PPO2 Display");
  
  uint16_t i;
    for( i=0; i<128; i++) display.drawPixel(i, 16, 1);
    for( i=107; i<128; i++) display.drawPixel(i, 29, 1);
    for( i=0; i<128; i++) display.drawPixel(i, 42, 1);
    //oś pionowa
    for( i=42; i<63; i++) display.drawPixel( 20, i, 1);
    for( i=16; i<63; i++) display.drawPixel( 66, i, 1);
    for( i=16; i<63; i++) display.drawPixel( 106, i, 1);
    
    
  display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(1,45);
    display.println("INF");
    display.setCursor(3,54);
    display.println("<<");
    display.setCursor(109,45);
    display.println("SET");
    display.setCursor(111,54);
    display.println(">>");
    
    bateria();
    temp();
    depth();
    time();

  
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A2);
  
PPO2 = (sensorValue * (5.0 / 1023.0)*WK1);
PPO22 = (sensorValue2 * (5.0 / 1023.0)*WK2);
PPO23 = (sensorValue3 * (5.0 / 1023.0)*WK3);

if(SmV < 8.00 || SmV > 13.00){
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(2,24);
  display.print("Err");
}else{
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(2,24);
    display.print(PPO2);
    display.display();
    delay(500);
    }

//************ 2nd sensor ***************
    
if(S2mV < 8.00 || S2mV > 13.00){
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(24,24);
  display.print("Err");
}else{
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(24,24);
    display.print(PPO22);
    
    display.display();
    delay(500);
    }

// ************** 3rd sensor ***************

if(S3mV < 8.00 || S3mV > 13.00){
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(46,24);
  display.print("Err");
}else{
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(46,24);
    display.print(PPO23);
    delay(500);
    display.display();
    }
    

// ************* warnning command **************
  warning();



//***************************************************
//*********************battery status****************
   
   int sensorValue4 = analogRead(A5);
   bat = sensorValue4 * (5.0 / 1023.0);

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
  for( i=107; i<112; i++) display.drawPixel(i, 9, 1);
  for( i=107; i<112; i++) display.drawPixel(i, 10, 1);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 1); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 9, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 10, 1);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 1);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 9, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 10, 1);
     
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
  for( i=107; i<112; i++) display.drawPixel(i, 9, 0);
  for( i=107; i<112; i++) display.drawPixel(i, 10, 0);
  
  for( i=114; i<119; i++) display.drawPixel(i, 8, 1); //half battery
  for( i=114; i<119; i++) display.drawPixel(i, 7, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 6, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 5, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 4, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 9, 1);
  for( i=114; i<119; i++) display.drawPixel(i, 10, 1);
  
  for( i=121; i<126; i++) display.drawPixel(i, 8, 1);//low battery
  for( i=121; i<126; i++) display.drawPixel(i, 7, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 6, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 5, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 4, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 9, 1);
  for( i=121; i<126; i++) display.drawPixel(i, 10, 1);
     
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
  
}







//****************warning commands**************
void warning(){            
  if ( PPO2 <= 0.40 || PPO22 <0.40 || PPO23 <0.40){
    
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(109,19);
    display.println("LOW");
    display.display();
    digitalWrite(redLED, HIGH);         //turn on the Red LED
    digitalWrite(greenLED, LOW);        //turn off the Green LED

  }else if ( PPO2 >= 1.40 || PPO22 >= 1.40 || PPO23 >= 1.40){
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(109,19);
    display.print("HI!");
    display.display();
    delay(500);
    display.setCursor(109,19);
    display.print("   ");
    display.display();
    delay(50);
    digitalWrite(redLED, HIGH);        //turn on the Red LED
    digitalWrite(greenLED, LOW);       //turn off the Green LED
  }else{
     display.setTextSize(1);
     display.setTextColor(WHITE, BLACK);
     display.setCursor(109,19);
     display.print("   ");
     display.display();
     digitalWrite(redLED, LOW);        //turn off the Red LED
     digitalWrite(greenLED, HIGH);     //turn on the Green LED
  }
  
  delay(60000);
  
}





void bateria(){
  
  
  uint16_t x;
  for( x=105; x<128; x++) display.drawPixel(x, 2, 1);// oś pozioma
  for( x=105; x<128; x++) display.drawPixel(x, 12, 1);
  
    for( x=2; x<12; x++) display.drawPixel(105, x, 1);
    for( x=2; x<12; x++) display.drawPixel(127, x, 1);
    
     for( x=5; x<10; x++) display.drawPixel(102, x, 1);//czubek baterii
     for( x=5; x<10; x++) display.drawPixel(103, x, 1);

  
  display.display();
  
}

void temp(){
  
  display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(109,32);
    display.println("36C");
    display.display();
  
}

void depth(){
  
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(69,22);
  display.print("130");
  display.display();

}  

void time(){
  
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(78,46);
  display.println("250");
  display.setCursor(78,54);
  display.println("min");
  display.display();

}
