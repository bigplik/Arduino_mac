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

int LED = 13;

const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 6;
int ocena1 = 1;   // counter for the number of button presses
int ocena2 = 0;
int buttonState = 0;         // current state of the button
int buttonState2 = 0;
int buttonState3 = 0;
int lastButtonState = 0;
int lastButtonState2 = 0;
int alt_case = 0;

int wyswietlacz = 0;


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

#if (SSD1306_LCDHEIGHT != 32)
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


//******************VOID SETUP******************************
//**********************************************************
//**********************************************************
void setup()   {                
  Serial.begin(9600);

 pinMode(LED, OUTPUT);
 pinMode(buttonPin, INPUT);
 pinMode(buttonPin2, INPUT);

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


//*************************logo*****************8
display.setTextSize(3);
display.setTextColor(WHITE);
  display.setCursor(11,6);
  display.println("ORIGIN");
  display.display();
  delay(2500);
    display.clearDisplay();

    uint16_t a;
    for( a=0; a<128; a++) display.drawPixel(a, 19, 1);
    
    //for( a=0; a<128; a++) display.drawPixel(a, 50, 1);
    display.display();
    delay(800);
  display.setTextSize(2);
display.setTextColor(WHITE);
  display.setCursor(48,0);
  display.println("BDS");
  display.display();
  display.setTextSize(1);
display.setTextColor(WHITE);
  display.setCursor(20,24);
  display.println("Head Up Display");
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


SmV = (firstValue1/4.95); //dane przeliczone do miliVolt dla S1
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
  sensorGap();
  
  //************************************************
  //***********opis danych do sensorów w tabeli
  
  //************nagłówek tabeli
  //display.setTextSize(1);
 // display.setTextColor(WHITE);
  //display.setCursor(4,6);
  //display.println("#     mV     Status");
  
   //**********************numery sensorów
  /*
  display.setCursor(2,20);
  display.println("1");
  display.setCursor(2,36);
  display.println("2");
  display.setCursor(2,52);
  display.println("3");
  */
  
  //***************wartości sensorów w miliVoltach
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,8);     //pierwszy parametr szerokość, drugi wysokość
  display.print(SmV);
  display.setCursor(5,20);
  display.print("  mV");
  
  display.setCursor(49,8);
  display.println(S2mV);
  display.setCursor(49,20);
  display.print("  mV");
  
  display.setCursor(93,8);
  display.println(S3mV);
  display.setCursor(93,20);
  display.print("  mV");
  
  display.display();
  delay(2500);
  
  display.clearDisplay();

  
  //*********************sensor ok lub old lub Err
  sensorGap();
  display.setTextSize(2);

  if(SmV >= 9.00 && SmV <= 13.00){
    display.setCursor(10,8);
    display.println("OK");
    display.display();
  }
  else if(SmV <=8.99 && SmV >=8.00){
    display.setCursor(4,8);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(4,8);
    display.println("Err");
    display.display();
  }
  
  if(S2mV >= 9.00 && S2mV <= 13.00){   // 2 sensor
    display.setCursor(54,8);
    display.println("OK");
    display.display();
  }
  else if(S2mV <=8.99 && S2mV >=8.00){
    display.setCursor(48,8);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(48,8);
    display.println("Err");
    display.display();
  }
  
  if(S3mV >= 9.00 && S3mV <= 13.00){      // 3 sensor
    display.setCursor(97,8);
    display.println("OK");
    display.display();
  }
  else if(S3mV <=8.99 && S3mV >=8.00){
    display.setCursor(91,8);
    display.println("OLD");
    display.display();
  }else{
    display.setCursor(91,8);
    display.println("Err");
    display.display();
  }
  
  delay(5000);

  // Clear the buffer.
  display.clearDisplay();
  
  //***************battery voltage information
   
    battery_info();

 
 //*********************************koniec logo
  
  // text display tests
  display.setTextSize(1);
   display.setTextColor(WHITE);
  display.setCursor(0,2);
 // display.println("BDS PPO2 Display");
  

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


//*******VOID LOOP *********************
//**************************************
//**************************************
void loop() {
 
lista();
  
}


//********************normal/basic info***********************
//************************************************************
void basic_loop_info(){

   //*********tabela - linie podstawowe************
  uint16_t i;
  for( i=0; i<128; i++) display.drawPixel(i, 16, 1);
  for( i=0; i<128; i++) display.drawPixel(i, 42, 1);

  for( i=0; i<64; i++) display.drawPixel( 60, i, 1);

  
//***********pomiar sensorów******************  
int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A2);
  
PPO2 = (sensorValue * (5.0 / 1023.0)*WK1); //wspólczynniki korekcji
PPO22 = (sensorValue2 * (5.0 / 1023.0)*WK2);
PPO23 = (sensorValue3 * (5.0 / 1023.0)*WK3);

if(SmV < 8.00 || SmV > 13.00){
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,2);
  display.print("Err");
}else{
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,2);
    display.print(PPO2);
    display.display();
    delay(500);
    }

//************ 2nd sensor ***************
    
if(S2mV < 8.00 || S2mV > 13.00){
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,22);
  display.print("Err");
}else{
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,22);
    display.print(PPO22);
    
    display.display();
    delay(500);
    }

// ************** 3rd sensor ***************

if(S3mV < 8.00 || S3mV > 13.00){
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(67,22);
  display.print("Err");
}else{
    display.setTextSize(1);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(67,22);
    display.print(PPO23);
    delay(500);
    display.display();
    }
    

// ************* warnning command **************
  warning();

//***************************************************

  battery_status(); 
    
//*********************    
//lista();
  
}


//*****************Menu *****************************
//***************************************************
void lista(){
  
    int lista = ocena1;
    int cena;
    int kal_level;
   
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
 
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
  if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      ocena1++;
      Serial.println("on");
      //Serial.print("number of button pushes:  ");
      Serial.println(ocena1);
    } 
    else {}
  }
 
  lastButtonState = buttonState;
  
  
  //***********SECOND BUTTON****************8
  
 if(lista == 2){
   if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
   if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      alt_case++;
      Serial.println("on");
      //Serial.print("number of button pushes:  ");
      Serial.println(alt_case);
    } 
    else {}
  }
 
  lastButtonState2 = buttonState3;
  
   if(alt_case > 2){
       
       alt_case = 0
       ;
    }
  
 }
 
 if(lista != 2){
 if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
   if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      ocena2++;
      Serial.println("on");
      //Serial.print("number of button pushes:  ");
      Serial.println(ocena2);
    } 
    else {}
  }
 
  lastButtonState2 = buttonState2;
  
 }
  
  //***************main menu count settings*****************
  /*
    int ocena = ocena1;
    int cena;
    int kal_level;
    */  
    if(ocena1 > 7){
        lista = 1;
        ocena1 =1;
    }
    
    
    
    if(ocena2 > 1){
       
       ocena2  = 0;
    }
    
    
    
    //****************  ta funkcja nie działa poprawnie, zmienia watości
    //pomiedzy A i B jednak kiedy zrobi to w "kalibracji" to potem zmienia
    //też w "solenoidzie"
   
  if(lista == 2 && alt_case == 0){
        kal_level = 'A';
    }
    else if(lista == 2 && alt_case == 1){
        kal_level = 'B';
    }
    else if(lista == 2 && alt_case == 2){
        kal_level = 'C';
    }
   
    //****************
    
    else if(lista == 3){
        cena = 'A';
    }else if(lista == 4){
        lista = 3;
        cena = 'B';
    }
    
    
    //***************select button counter*****************
   
   // stan;
   
   if(lista == 5){
     display.clearDisplay();
     battery_info();
     
   }
   else if(lista != 5){
     display.clearDisplay();
     basic_loop_info();
   }
   
   
   
   
   if(lista == 3 && cena == 'A' && ocena2 == 0){
       Serial.println("NORMAL DISPLAY");
       delay(200);
       digitalWrite(LED, LOW);
       display.ssd1306_command(0xAE);

   }
   else if(lista == 3 && cena == 'A' && ocena2 == 1){
       Serial.println("INVERT DISPLAY");
       delay(200);
       digitalWrite(LED, HIGH);
       display.ssd1306_command(0xAF);
   }
 

    switch(lista){
        case 1:
            Serial.println("SWITCH: Jedynka\n");
            break;
        case 2:
            switch(kal_level){
                case 'A':
                    Serial.println("Brightness 1");
                    display.ssd1306_command(SSD1306_SETCONTRAST);
                    display.ssd1306_command(85);
                    break;
                case 'B':
                    Serial.println("Brightness 2");
                    display.ssd1306_command(SSD1306_SETCONTRAST);
                    display.ssd1306_command(170);
                    break;
                case 'C':
                    Serial.println("Brightness 3");
                    display.ssd1306_command(SSD1306_SETCONTRAST);
                    display.ssd1306_command(255);
                    break;
                default:
                Serial.println("back");
            }
            break;
        case 3:
            switch(cena){
                case 'A':
                    Serial.println("SWITCH: A");
                    break;
                case 'B':
                    Serial.println("SWITCH: B");
                    break;
                default:
                Serial.println("SWITCH: Nieznana ocena\n");
            }
            break;
        case 5:
            Serial.println("SWITCH: Czwórka\n");
            break;
        case 6:
            Serial.println("SWITCH: Piątka\n");
            break;
        case 7:
            Serial.println("SWITCH: Szóstka\n");
            break;
        default:
            lista = 1;
    }
    
    delay(500);
  
}


//********************battery info********************
//****************************************************
void battery_info(){
  
  int sensorValue4 = analogRead(A6);
    float bat = sensorValue4 * (5.0 / 1023.0);
    
    display.setTextSize(1);
    display.setCursor(6,6);
    display.println("Battery");
    display.setCursor(6,16);
    display.println("Voltage");
    display.setTextSize(2);
    display.setCursor(63,8);
    display.print(bat);
    display.print("V");
    
        uint16_t b;
    for( b=58; b<127; b++) display.drawPixel(b, 1, 1);
    for( b=2; b<32; b++) display.drawPixel(58, b, 1); // oś pionowa
    for( b=58; b<127; b++) display.drawPixel(b, 31, 1);
    for( b=2; b<32; b++) display.drawPixel(127, b, 1); // oś pionowa
    display.display();
    delay(2000);
    
    display.clearDisplay();
  
}


//**************************battery status************************
//****************************************************************
void battery_status(){
   
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

//***********gaps for sensors reading in void setup************
//*************************************************************
void sensorGap(){
  uint16_t b;
    for( b=0; b<40; b++) display.drawPixel(b, 1, 1);
    for( b=2; b<32; b++) display.drawPixel(0, b, 1); // oś pionowa
    for( b=0; b<40; b++) display.drawPixel(b, 31, 1);
    for( b=2; b<32; b++) display.drawPixel(40, b, 1); // oś pionowa
    
    for( b=44; b<84; b++) display.drawPixel(b, 1, 1);
    for( b=2; b<32; b++) display.drawPixel(44, b, 1); // oś pionowa
    for( b=44; b<84; b++) display.drawPixel(b, 31, 1);
    for( b=2; b<32; b++) display.drawPixel(84, b, 1); // oś pionowa
    
    for( b=88; b<127; b++) display.drawPixel(b, 1, 1);
    for( b=2; b<32; b++) display.drawPixel(88, b, 1); // oś pionowa
    for( b=88; b<127; b++) display.drawPixel(b, 31, 1);
    for( b=2; b<32; b++) display.drawPixel(127, b, 1); // oś pionowa

    
  display.display();
}
