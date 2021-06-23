#include "U8glib.h"
//#include <idDHT11.h>
//#include <StopWatch.h>
#include <Wire.h>
//#include <ADXL345.h>
#include <Adafruit_ADS1015.h>

//#define idDHT11pin 3
//#define idDHT11intNumber 1

#define greenLED 5    //blue wire
#define redLED 6      //brown wire

//zmienne
int minuty = 0;
int dive_time = 0;
int humid;
int temp;
int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;
int bat = 0;

double SmV, S2mV, S3mV;


byte counter = 0;
byte counter2 = 0;
byte counter3 = 0;
byte timer = 0;

float PPO2;
float PPO22;
float PPO23;
float SmVact;
float SmVact2;
float SmVact3;
float midPPO2;
//float bat = 0;
float bat1 = 0;
// initiation lines below

 Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */


//ADXL345 accelerometer;

//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); //display initiate
//U8GLIB_SH1106_128X64 u8g(13, 11, 10, 8);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0/DC = 9
//U8GLIB_SH1106_128X64 u8g(13, 11, 10, 8);
//StopWatch sw_secs(StopWatch::SECONDS);

//void dht11_wrapper();//initiation for line below
//idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

void u8g_prepare(void) {
  //u8g.setFont(u8g_font_osb21);
  u8g.setFont(u8g_font_courR18);
  //u8g.setFont(u8g_font_profont17);//10-17
  //u8g.setFont(u8g_font_unifont);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
 
}

void logo(void) {
  u8g_prepare();
  uint8_t a;
  // graphic commands to redraw the complete screen should be placed here  
  //u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_courR18r);
  u8g.setFont(u8g_font_timB18r);
  u8g.drawStr( 18, 42, "ORIGIN");  //1-szer, 2-wys,
  //uint8_t a;
  //u8g.drawRFrame(18,20,96,30, a+1);
}

void logo2(void) {
  u8g_prepare();
  uint8_t a;
  // graphic commands to redraw the complete screen should be placed here  
  //u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_courR18r);
  u8g.setFont(u8g_font_timB18r);
  u8g.drawStr( 18, 42, "ORIGIN");  //1-szer, 2-wys,
  
  u8g.drawRFrame(16,20,97,30, a+1);
}

void logo3(void) {
    u8g_prepare();
    uint8_t a;
    // graphic commands to redraw the complete screen should be placed here  
    //u8g.setFont(u8g_font_unifont);
    //u8g.setFont(u8g_font_courR18r);
    u8g.setFont(u8g_font_timB18r);
    u8g.drawStr( 18, 42, "ORIGIN");  //1-szer, 2-wys,
    u8g.setFont(u8g_font_profont10);
    u8g.drawStr( 25, 14, "BDS PPO2 Display");
    //u8g.setFont(u8g_font_courR10r);
    u8g.drawStr( 8, 60, "v.1.4.9 ADX & IDHT-less");
    u8g.drawRFrame(16,20,97,30, a+1);
}


void logo4() {
  
    u8g_prepare();
    uint8_t a;
    bat1 = (bat * (5.0/1023))*2;
            ////////////battery
          u8g.drawStr(94,35, "B");//1-szer ,2-wysokosc
          //u8g.setPrintPos( 2, 20); //1st - 1-szer, 2-wysokosc
          // u8g.setFont(u8g_font_unifont);
  

          //u8g.setFont(u8g_font_courR14r);
          u8g.setPrintPos( 2, 10); //3rd
          //delay(5);
          u8g.print(bat1);
          //delay(5);
          // ("Gratulacje, wybrałeś nitrox: %d\n", Nx);
          u8g.println("V");
          //delay(200);
          //u8g.setPrintPos( 20, 40); //3rd
          //u8g.print("OK");
          //u8g.drawStr( 0, 0, "drawRFrame/Box");
          u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawRBox(50, 10,25,40, a+1);
  //delay(500);
  
}

void logo5() { //MILI VOLTS
       

  u8g_prepare();
  uint8_t a;
            ///////////MiliVolts SCREEN
          u8g.drawStr(78,35, "mV");//1-szer ,2-wysokosc
          u8g.setFont(u8g_font_courR14r);
          if(SmV > 8.0 && SmV < 50.0){
          u8g.setPrintPos( 6, 20); //1st - 1-szer, 2-wysokosc
          u8g.print(SmV, 1);
          }else{
          u8g.setPrintPos( 6, 20);
          u8g.print("Err");
          }
          if(S2mV > 8.0 && S2mV < 50.0){
          u8g.setPrintPos( 70, 20); //2nd
          u8g.print(S2mV, 1);
          }else {
          u8g.setPrintPos( 70, 20);
          u8g.print("Err");
          }
          if(S3mV > 8.0 && S3mV < 50.0){
          u8g.setPrintPos( 6, 52); //3rd
          u8g.print(S3mV, 1);
          }else {
          u8g.setPrintPos( 6, 52);
          u8g.print("Err");
          }
          //u8g.drawStr( 20, 20, "drawRFrame/Box");
          u8g.drawRFrame(0, 0,62,30, a+1);
          u8g.drawRFrame(64, 0,62,30, a+1);
          u8g.drawRFrame(0, 32,62,30, a+1);
          //u8g.drawRFrame(82, 30,40,30, a+4);
          //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawBox(82, 30,40,30);
  
  
}



void logo6() { // TEMP WILG
  //u8g.setFont(u8g_font_timB10r);
  u8g_prepare();

    uint8_t a;
  
  /////////////////temp. humidity SCREEN 
          u8g.drawStr(10,35, "");//1-szer ,2-wysokosc
          //delay(500);
  
  
}

void logo7() {
  
  
  u8g_prepare();
  uint8_t a;
            ///////////MiliVolts SCREEN
          u8g.drawStr(78,35, "mV");//1-szer ,2-wysokosc
          u8g.setFont(u8g_font_courR14r);
          if(SmV > 8.0 && SmV <= 13.0){
          u8g.setPrintPos( 6, 20); //1st - 1-szer, 2-wysokosc
          u8g.print("OK");
          }else 
          if(SmV > 13.00){
          u8g.setPrintPos( 6, 20);
          u8g.print("WET?");
          }else {
          u8g.setPrintPos( 6, 20);
          u8g.print("Err");
          }
          if(S2mV > 8.0 && S2mV <= 13.0){
          u8g.setPrintPos( 70, 20); //2nd
          u8g.print("OK");
          }else 
          if(S2mV > 13.00){
          u8g.setPrintPos( 70, 20);
          u8g.print("WET?");
          }else {
          u8g.setPrintPos( 70, 20);
          u8g.print("Err");
          }
          if(S3mV > 8.0 && S3mV <= 13.0){
          u8g.setPrintPos( 6, 52); //3rd
          u8g.print("OK");
          }else 
          if(S3mV > 13.00){
          u8g.setPrintPos( 6, 52);
          u8g.print("WET?");
          }else {
          u8g.setPrintPos( 6, 52);
          u8g.print("Err");
          }
          //u8g.drawStr( 20, 20, "drawRFrame/Box");
          u8g.drawRFrame(0, 0,62,30, a+1);
          u8g.drawRFrame(64, 0,62,30, a+1);
          u8g.drawRFrame(0, 32,62,30, a+1);
          //u8g.drawRFrame(82, 30,40,30, a+4);
          //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawBox(82, 30,40,30);
  
  
}




/*

void one(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Hello World!");
}

void two(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Hello World!");
}

void three(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Hello World!");
}

void four(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Hello World!");
}

*/

//void dht11_wrapper() {
//  DHT11.isrCallback();
//}



void screens() {
  u8g_prepare();
  uint8_t a;
    //u8g.setFont(u8g_font_profont17);//10-17


          u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
          
          if(SmV > 8.0 && SmV < 65.0){
          u8g.setPrintPos( 0, 4); //1st - 1-szer, 2-wysokosc
          u8g.print(PPO2);
          }else {
          u8g.setPrintPos( 0, 4); //1st - 1-szer, 2-wysokosc
          u8g.print("Err");
          }
          if(S2mV > 8.0 && S2mV < 65.0){
          u8g.setPrintPos( 70, 4); //2nd
          u8g.print(PPO22);
          }else {
          u8g.setPrintPos( 70, 4); //2nd
          u8g.print("Err");
          }
          if(S3mV > 8.0 && S3mV < 65.0){
          u8g.setPrintPos( 0, 34); //3rd
          u8g.print(PPO23);
          }else {
          u8g.setPrintPos( 0, 34); //3rd
          u8g.print("Err");
          }

          //delay(500);
          //u8g.drawStr( 0, 0, "drawRFrame/Box");
          u8g.drawRFrame(65, 32,63 ,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawRFrame(94, 30,30,30, a+1);
          //u8g.drawRBox(50, 10,25,40, a+1);
          warning();
          //LEDblink();
}



//****************************************************************
  



void setup(void) {
  
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  
  digitalWrite(7, HIGH);
  
     ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  int16_t adc3, adc2, adc1;
  adc3 = ads.readADC_SingleEnded(3);
  adc2 = ads.readADC_SingleEnded(2);
  adc1 = ads.readADC_SingleEnded(1);

  // flip screen, if required
  // u8g.setRot180();
  
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  
  
////////////////LOGO
u8g.firstPage();  
  do {
    logo();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
  
  u8g.firstPage();  
  do {
    logo2();
  } while( u8g.nextPage() );
  
  delay(500);
  
  
  u8g.firstPage();  
  do {
    logo3();
  } while( u8g.nextPage() );
  
  delay(2000);
  
 
    for(int i = 0 ; i < 10 ; i++)

{

bat += analogRead(A3);                          //sumowanie kolejnych pomiarów
delay(100);                                               //opóźnienie

}

bat /=10;
  
    u8g.firstPage();        //battery
  do {
    logo6();
  } while( u8g.nextPage() );
  
  delay(20);
  
      for(int j = 0 ; j < 10 ; j++)

{
  


firstValue1 += adc3;                         //sumowanie kolejnych pomiarów
firstValue2 += adc2;
firstValue3 += adc1;
delay(100);                                               //opóźnienie

}

firstValue1 /=10;                                                            //liczenie wartości średniej
firstValue2 /=10;                                                            //i zapamiętanie jej
firstValue3 /=10;


SmV = (firstValue1/5.0); //dane przeliczone do miliVolt dla S1
S2mV = (firstValue2/5.0);
S3mV = (firstValue3/5.0);

  
      u8g.firstPage();     //mili volts
  do {
  
    logo5();
    //u8g_prepare();
/*
      uint8_t a;
            ///////////MiliVolts SCREEN
          u8g.drawStr(88,33, "mV");//1-szer ,2-wysokosc
          if(SmV > 8.0 && SmV < 50.0){
          u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
          u8g.println(SmV);
          }else{
          u8g.setPrintPos( 2, 4);
          u8g.print("Err");
          }
          if(S2mV > 8.0 && S2mV < 50.0){
          u8g.println(S2mV);
          u8g.setPrintPos( 70, 4); //2nd
          }else {
          u8g.setPrintPos( 70, 4);
          u8g.print("Err");
          }
          if(S3mV > 8.0 && S3mV < 50.0){
          u8g.println(S3mV);
          u8g.setPrintPos( 2, 34); //3rd
          }else {
          u8g.setPrintPos( 2, 34);
          u8g.print("Err");
          }
          //u8g.drawStr( 0, 0, "drawRFrame/Box");
          u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawRBox(50, 10,25,40, a+1);
          //LEDblink();
    */
    
  } while( u8g.nextPage() );
  
  delay(2000);
  
  
          u8g.firstPage();   //sensor status - OK vs ERR 
  do {
    logo7();
  } while( u8g.nextPage() );
  
  delay(2000);
  
 
        u8g.firstPage();   //temp wilg
  do {
    logo4();
  } while( u8g.nextPage() );
  
  delay(3000);
  
 // idht();
 
 digitalWrite(7, LOW);
 
}

void loop(void) {
  
    // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
    int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A2);
  int sensorValue4 = analogRead(A3);
  int sensorValue5 = analogRead(A4);
  int sensorValue6 = analogRead(A5);
    int sensorValue7 = analogRead(A6);
  int sensorValue8 = analogRead(A7);


  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
 // PPO2 = sensorValue * (5.0 / 1023.0);
 //   PPO22 = sensorValue2 * (5.0 / 1023.0);
 //PPO23 = sensorValue3 * (5.0 / 1023.0);
  //float voltage4 = sensorValue4 * (5.0 / 1023.0);
  //float voltage5 = sensorValue5 * (5.0 / 1023.0);
  //float voltage6 = sensorValue6 * (5.0 / 1023.0);
  //float voltage7 = sensorValue7 * (5.0 / 1023.0);
  //float voltage8 = sensorValue8 * (5.0 / 1023.0);

  // print out the value you read:
 //Serial.println(voltage);//*************
  //Serial.println(voltage2);//***************
  //Serial.println(voltage3);//************
  
    SmVact = (analogRead(A0)/5.0)*1.186046512;
    SmVact2 = (analogRead(A1)/5.0)*1.186046512;
      SmVact3 = (analogRead(A2)/5.0)*1.186046512;
           
  
   // int sensorValue = analogRead(A0);
  PPO2 = (SmVact * (0.21/SmV));
    PPO22 = (SmVact2 * (0.21/S2mV));

    PPO23 = (SmVact3 * (0.21/S3mV));
    
    Serial.println(SmV);
    Serial.println(SmVact);
    Serial.println("------------");
    Serial.println(S2mV);
    Serial.println(SmVact2);
    Serial.println("------------");
    Serial.println(S3mV);
    Serial.println(SmVact3);
    Serial.println("------------");
    Serial.println("------------");
    Serial.println(timer);

    delay(500);
    

  //delay(2000);
  

for (int z = 0 ; z < 5; z ++){
    u8g.firstPage();  
    do {
       screens();
       
       //LEDblink();
    } while( u8g.nextPage() );
    // rebuild the picture after some delay
    delay(500);
    timer = timer + 1;
    //idht();
}

//timer do dopracowania
/*
  if((PPO2 && PPO22 || PPO2 && PPO23
  || PPO22 && PPO23 < 0.25) && (PPO2 && PPO23
  && PPO22 > 0.19)){
    if(timer > 20){
        u8g.sleepOn();
    }
  }else{
    u8g.sleepOff();
  }
  
  */
 /* 
  if(PPO2 && PPO22 || PPO2 && PPO23
  || PPO22 && PPO23 > 0.25){
  timer = 0;
  }
  */





//Serial.println(timer);
//delay(200);

//warning();
  
}




/*
void sleepDisplay(){
  
  if(counter == 0){
    u8g.sleepOff();   
  } else
  if(counter == 1){
    u8g.sleepOn();
  } 
  
  if(counter > 1){
    counter = 0;  
  } 
  

  
}
*/
/*
void idht(){
  
  DHT11.acquire();
  while (DHT11.acquiring())
    ;
  int result = DHT11.getStatus();
 
  //Serial.print("Humidity (%): ");
  humid = DHT11.getHumidity();

  //Serial.print("Temperature (oC): ");
  temp = DHT11.getCelsius();

  delay(500);
  
}
*/

//*************************************************
//****************warning commands**************
void warning(){
  u8g_prepare();  
  if ( PPO2 <= 0.40 || PPO22 <0.40 || PPO23 <0.40){
    
//red LED on
    u8g.drawStr(70, 34, "LOW");
    digitalWrite(redLED, HIGH);         //turn on the Red LED
    digitalWrite(greenLED, LOW);        //turn off the Green LED
    //LEDblink();
 
  }else if ( PPO2 >= 1.40 || PPO22 >= 1.40 || PPO23 >= 1.40){

//red LED on   
    u8g.setFont(u8g_font_courR14r);
    u8g.drawStr(66,49, "HIGH!");
    digitalWrite(redLED, HIGH);        //turn on the Red LED
    digitalWrite(greenLED, LOW);       //turn off the Green LED
    
  }else if ( PPO2 > 0.40 && PPO2 < 0.70 || PPO22 > 0.40 && PPO22 < 0.70 || PPO23 > 0.40 && PPO23 < 0.70){

//orange LED on  

    u8g.setFont(u8g_font_courR14r);
    //if (timer >= 0 & timer < 20){
    //u8g.setPrintPos( 92, 53);
    //u8g.print(temp);
    u8g.drawStr(113, 53, "^^^");
    //}else if (timer >= 20 & timer < 400){
    //u8g.setPrintPos( 92, 53);
    //u8g.print(humid);
    //u8g.drawStr(113, 53, "%");
    //}

    //ORANGE LIGHT
  
   analogWrite(redLED, 230);
   analogWrite(greenLED, 250);
   
  }else{

//green LED on

     u8g.setFont(u8g_font_courR14r);
    //if (timer >= 0 & timer < 20){
    //u8g.setPrintPos( 92, 53);
    //u8g.print(temp);
    u8g.drawStr(113, 53, "~OK~");
    //}else if (timer >= 20){
    //u8g.setPrintPos( 92, 53);
    //u8g.print(humid);
    //u8g.drawStr(113, 53, "%");
    //}

     digitalWrite(redLED, LOW);        //turn off the Red LED
     digitalWrite(greenLED, HIGH);     //turn on the Green LED
  }
  


    
}


