#include "U8glib.h"
#include <idDHT11.h>
#include <StopWatch.h>
#include <Wire.h>
#include <ADXL345.h>

#define idDHT11pin 3
#define idDHT11intNumber 1

//zmienne
int minuty = 0;
int dive_time = 0;
int humid;
int temp;
int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;

byte counter = 0;
byte counter2 = 0;
byte counter3 = 0;

float PPO2;
float PPO22;
float PPO23;
float SmV;
float S2mV;
float S3mV;
float SmVact;
float SmVact2;
float SmVact3;
float bat;
float midPPO2;

// initiation lines below

ADXL345 accelerometer;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); //display initiate
StopWatch sw_secs(StopWatch::SECONDS);

void dht11_wrapper();//initiation for line below
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

void u8g_prepare(void) {
  //u8g.setFont(u8g_font_osb21);
  u8g.setFont(u8g_font_courR18r);
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
  
  u8g.drawRFrame(16,20,96,30, a+1);
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
    u8g.drawStr( 47, 60, "v.1.4.4");
    u8g.drawRFrame(16,20,96,30, a+1);
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

void dht11_wrapper() {
  DHT11.isrCallback();
}

uint8_t menu = 1;   //above water menu

void screens() {
  u8g_prepare();
  uint8_t a;
  switch(menu) {
    case 1:
            ///////////MAIN PPO2 SCREEN
          u8g.sleepOff();
          u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
          
          if(SmV > 8.0 && SmV < 50.0){
          u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
          u8g.print(PPO2);
          }else {
          u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
          u8g.print("Err");
          }
          if(S2mV > 8.0 && S2mV < 50.0){
          u8g.setPrintPos( 70, 4); //2nd
          u8g.print(PPO22);
          }else {
          u8g.setPrintPos( 70, 4); //2nd
          u8g.print("Err");
          }
          if(S3mV > 8.0 && S3mV < 50.0){
          u8g.setPrintPos( 2, 34); //3rd
          u8g.print(PPO23);
          }else {
          u8g.setPrintPos( 2, 34); //3rd
          u8g.print("Err");
          }

          //delay(500);
          //u8g.drawStr( 0, 0, "drawRFrame/Box");
          u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawRBox(50, 10,25,40, a+1);
    break; //
    case 2:
          ///////////MiliVolts SCREEN
          u8g.drawStr(88,33, "mV");//1-szer ,2-wysokosc
          if(SmV > 8.0 && SmV < 50.0){
          u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
          u8g.print(SmV);
          }else{
          u8g.print("Err");
          u8g.setPrintPos( 2, 4);
          }
          if(S2mV > 8.0 && S2mV < 50.0){
          u8g.print(S2mV);
          u8g.setPrintPos( 70, 4); //2nd
          }else {
          u8g.print("Err");
          u8g.setPrintPos( 70, 4);
          }
          if(S3mV > 8.0 && S3mV < 50.0){
          u8g.print(S3mV);
          u8g.setPrintPos( 2, 34); //3rd
          }else {
          u8g.print("Err");
          u8g.setPrintPos( 2, 34);
          }
          //u8g.drawStr( 0, 0, "drawRFrame/Box");
          u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawRBox(50, 10,25,40, a+1);
    break;     //
    case 3:
          /////////////////temp. humidity SCREEN 
          u8g.drawStr(98,35, "i");//1-szer ,2-wysokosc
          u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
          u8g.setPrintPos( 0, 4); //1st - 1-szer, 2-wysokosc
          u8g.print("t.");
          u8g.print(temp);
          u8g.println("c");
          //u8g.setPrintPos( 70, 4); //2nd
          //u8g.print(PPO22);
          //u8g.setPrintPos( 86, 4); //2nd
          //u8g.print(minuty);
          //u8g.setFont(u8g_font_courR14r);
          //u8g.println('"');
          //u8g.setFont(u8g_font_courR18r);
          u8g.setPrintPos( 0, 40); //3rd
          u8g.print("h.");
          u8g.print(humid);
          //u8g.setFont(u8g_font_courR14r);
          u8g.setPrintPos( 60, 40); //3rd
          u8g.println("%");
          u8g.drawRFrame(88, 30,35,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
    break;      //
    case 4: 
          ////////////battery
          u8g.drawStr(94,35, "B");//1-szer ,2-wysokosc
          //u8g.setPrintPos( 2, 20); //1st - 1-szer, 2-wysokosc
          // u8g.setFont(u8g_font_unifont);
          u8g.setPrintPos( 2, 10); //3rd
          u8g.print(bat);
          // ("Gratulacje, wybrałeś nitrox: %d\n", Nx);
          u8g.println("V");
          //u8g.setPrintPos( 20, 40); //3rd
          //u8g.print("OK");
          //u8g.drawStr( 0, 0, "drawRFrame/Box");
          u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawRBox(50, 10,25,40, a+1);
    break;        //
    case 5:
          /////////sleepOn SCREEN
          u8g.sleepOn();
    break; 
  }
  }
  
  
  uint8_t menu2 = 1;   //under water menu

void screens2() {
  u8g_prepare();
  uint8_t a;
  switch(menu2) {
    case 1:
          ///////////MAIN PPO2 SCREEN
          u8g.sleepOff();
          u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
          u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
          u8g.print(PPO2);
          u8g.setPrintPos( 70, 4); //2nd
          u8g.print(PPO22);
          u8g.setPrintPos( 2, 34); //3rd
          u8g.print(PPO23);
          //delay(500);
          //u8g.drawStr( 0, 0, "drawRFrame/Box");
          u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawRBox(50, 10,25,40, a+1);
    break; //
    case 2:
          ///////////MiliVolts SCREEN
          u8g.drawStr(88,33, "mV");//1-szer ,2-wysokosc
          if(SmV > 8.0 && SmV < 50.0){
          u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
          u8g.print(SmV);
          }else{
          u8g.print("Err");
          u8g.setPrintPos( 2, 4);
          }
          if(S2mV > 8.0 && S2mV < 50.0){
          u8g.print(S2mV);
          u8g.setPrintPos( 70, 4); //2nd
          }else {
          u8g.print("Err");
          u8g.setPrintPos( 70, 4);
          }
          if(S3mV > 8.0 && S3mV < 50.0){
          u8g.print(S3mV);
          u8g.setPrintPos( 2, 34); //3rd
          }else {
          u8g.print("Err");
          u8g.setPrintPos( 2, 34);
          }
          //u8g.drawStr( 0, 0, "drawRFrame/Box");
          u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
          //u8g.drawRBox(50, 10,25,40, a+1);
    break;     //
    case 3:
          /////////////////temp. humidity SCREEN 
          u8g.drawStr(98,35, "i");//1-szer ,2-wysokosc
          u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
          u8g.setPrintPos( 0, 4); //1st - 1-szer, 2-wysokosc
          u8g.print("t.");
          u8g.print(temp);
          u8g.println("c");
          //u8g.setPrintPos( 70, 4); //2nd
          //u8g.print(PPO22);
          u8g.setPrintPos( 86, 4); //2nd
          u8g.print(minuty);
          //u8g.setFont(u8g_font_courR14r);
          u8g.println('"');
          //u8g.setFont(u8g_font_courR18r);
          u8g.setPrintPos( 0, 40); //3rd
          u8g.print("h.");
          u8g.print(humid);
          //u8g.setFont(u8g_font_courR14r);
          u8g.setPrintPos( 60, 40); //3rd
          u8g.println("%");
          u8g.drawRFrame(88, 30,35,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
    break;      //
  }
  }


void setup(void) {
  
  Serial.begin(9600);
  
  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }
    accelerometer.setTapDetectionZ(1);       // Check tap on Z-Axis
    
  accelerometer.setTapThreshold(2.5);      // Recommended 2.5 g
  accelerometer.setTapDuration(0.02);      // Recommended 0.02 s
  accelerometer.setDoubleTapLatency(0.10); // Recommended 0.10 s
  accelerometer.setDoubleTapWindow(0.30);  // Recommended 0.30 s
  
    // Select INT 1 for get activities
  accelerometer.useInterrupt(ADXL345_INT1);
  
  for(int j = 0 ; j < 10 ; j++)

{

firstValue1 += analogRead(A0);                          //sumowanie kolejnych pomiarów
firstValue2 += analogRead(A6);
firstValue3 += analogRead(A7);
delay(100);                                               //opóźnienie

}

firstValue1 /=10;                                                            //liczenie wartości średniej
firstValue2 /=10;                                                            //i zapamiętanie jej
firstValue3 /=10;


SmV = (firstValue1/4.9); //dane przeliczone do miliVolt dla S1
S2mV = (firstValue2/4.9); //dla S2
S3mV = (firstValue3/4.9); //dla S3


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
  
}

void loop(void) {
  
    SmVact = (analogRead(A0)/4.9);
    SmVact2 = (analogRead(A6)/4.9);
      SmVact3 = (analogRead(A7)/4.9);
            bat = (analogRead(A3)/4.9);

  
   // int sensorValue = analogRead(A0);
  PPO2 = (SmVact * (0.21/SmV));
    PPO22 = (SmVact2 * (0.21/S2mV));

    PPO23 = (SmVact3 * (0.21/S3mV));
  
  

  
     // Read values for activities
  delay(50);
  Vector norm = accelerometer.readNormalize();
  // Read activities
  Activites activ = accelerometer.readActivites();
  
  
  //when above water menu is active
  if (PPO2 < 0.26 || PPO22 < 0.26 || PPO23 < 0.26){
    // picture loop
    u8g.firstPage();  
    do {
       screens();
    } while( u8g.nextPage() );
    // rebuild the picture after some delay
    delay(50);
    
    if (activ.isTap){  //menu lap
      menu ++;
      delay(5);
    }
 
   //when underwater menu is active
  }else {
    
    u8g.firstPage();  
    do {
       screens2();
    } while( u8g.nextPage() );
    // rebuild the picture after some delay
    delay(50);
    
     //when underwater menu is active
    if (activ.isTap){
      menu2 ++;
      delay(5);
    }
  }
  
  //loops for menu and menu2
  if (menu > 5){
      menu = 1;
  }else
  if (menu2 > 3){
      menu2 = 1;
  }
  
    idhc();
    stopper();
  
}



void checkSetup()
{
  Serial.print("Look tap on axis = "); 
  if (accelerometer.getTapDetectionX()) { Serial.print(" X "); }
  if (accelerometer.getTapDetectionY()) { Serial.print(" Y "); }
  if (accelerometer.getTapDetectionZ()) { Serial.print(" Z "); }
  Serial.println();

  //Serial.print("Tap Threshold = "); Serial.println(accelerometer.getTapThreshold());
  //Serial.print("Tap Duration = "); Serial.println(accelerometer.getTapDuration());
 // Serial.print("Double Tap Latency = "); Serial.println(accelerometer.getDoubleTapLatency());
 // Serial.print("Double Tap Window = "); Serial.println(accelerometer.getDoubleTapWindow());
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

void idhc(){
  
  DHT11.acquire();
  while (DHT11.acquiring())
    ;
  int result = DHT11.getStatus();
 
  //Serial.print("Humidity (%): ");
  humid = DHT11.getHumidity();

  //Serial.print("Temperature (oC): ");
  temp = DHT11.getCelsius();

  //delay(500);
  
}


void stopper(){
    
   sw_secs.start();
   dive_time = sw_secs.value();
    
     if(sw_secs.elapsed() == 60){
        minuty = minuty + 1;
        sw_secs.reset();
     }
   
   delay(250);
   
}

