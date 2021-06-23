#include <idDHT11.h>
#include <StopWatch.h>

float bat;

int minuty = 0;
int dive_time = 0;
//StopWatch sw_millis;    // MILLIS (default)
//StopWatch sw_micros(StopWatch::MICROS);
StopWatch sw_secs(StopWatch::SECONDS);

int idDHT11pin = 3; //Digital pin for comunications
int idDHT11intNumber = 1; //interrupt number (must be the one that use the previus defined pin (see table above)

//declaration
void dht11_wrapper(); // must be declared before the lib initialization

// Lib instantiate
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

int humid;
int temp;

byte counter = 0;
byte counter2 = 0;
byte counter3 = 0;

float PPO2;
float PPO22;
float PPO23;
float mValue = 41.6;

#include <Wire.h>
#include <ADXL345.h>


int addr = 0;
int addr2 = 1;

byte value;
byte value2;

int firstValue1 = 0;
int firstValue2 = 0;
int firstValue3 = 0;

float SmV;
float S2mV;
float S3mV;

float SmVact;
float SmVact2;
float SmVact3;


ADXL345 accelerometer;


#include "U8glib.h"


U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 


void u8g_prepare(void) {
  //u8g.setFont(u8g_font_osb21);
  u8g.setFont(u8g_font_courR18r);
  //u8g.setFont(u8g_font_profont17);//10-17
  //u8g.setFont(u8g_font_unifont);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}
/*
void u8g_box_frame(uint8_t a) {
  u8g.drawStr( 0, 0, "drawBox");
  u8g.drawBox(5,10,20,10);
  u8g.drawBox(10+a,15,30,7);
  u8g.drawStr( 0, 30, "drawFrame");
  u8g.drawFrame(5,10+30,20,10);
  u8g.drawFrame(10+a,15+30,30,7);
}
*/
void u8g_disc_circle(uint8_t a) {
   
  u8g.drawStr(92,33, "R");//1-szer ,2-wysokosc
  u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
  u8g.print(minuty);
  u8g.setPrintPos( 70, 4); //2nd
  u8g.print(sw_secs.elapsed());
  u8g.setPrintPos( 2, 34); //3rd
  u8g.print(bat);
  
  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
  //u8g.drawRBox(50, 10,25,40, a+1);
}

void u8g_r_frame(uint8_t a) {
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
  
}

void u8g_string(uint8_t a) {
  u8g.drawStr(98,35, "i");//1-szer ,2-wysokosc
    u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
  u8g.setPrintPos( 1, 4); //1st - 1-szer, 2-wysokosc
  u8g.print("t.");
  u8g.print(temp);
  u8g.println("c");
  //u8g.setPrintPos( 70, 4); //2nd
  //u8g.print(PPO22);
    u8g.setPrintPos( 86, 4); //2nd
  u8g.print("10");
  u8g.setFont(u8g_font_courR14r);
  u8g.setPrintPos( 112, 18);
  u8g.println('"');
  u8g.setFont(u8g_font_courR18r);
  u8g.setPrintPos( 0, 50); //3rd
  u8g.print("h.");
  u8g.print(humid);
  u8g.setFont(u8g_font_courR14r);
  u8g.setPrintPos( 65, 50); //3rd
  u8g.println("%");
    
  u8g.drawRFrame(88, 30,35,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki

 
}

void u8g_line(uint8_t a) {
  u8g.sleepOn();
 
}

void u8g_triangle(uint8_t a) {
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
}
/*
void u8g_ascii_1() {
  char s[2] = " ";
  uint8_t x, y;
  u8g.drawStr( 0, 0, "ASCII page 1");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 32;
      u8g.drawStr(x*7, y*10+10, s);
    }
  }
}

void u8g_ascii_2() {
  char s[2] = " ";
  uint8_t x, y;
  u8g.drawStr( 0, 0, "ASCII page 2");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 160;
      u8g.drawStr(x*7, y*10+10, s);
    }
  }
}
*/



void u8g_extra_page(uint8_t a)
{
  if ( u8g.getMode() == U8G_MODE_HICOLOR || u8g.getMode() == U8G_MODE_R3G3B2) {
    /* draw background (area is 128x128) */
    u8g_uint_t r, g, b;
    b = a << 5;
    for( g = 0; g < 64; g++ )
    {
      for( r = 0; r < 64; r++ )
      {
	u8g.setRGB(r<<2, g<<2, b );
	u8g.drawPixel(g, r);
      }
    }
    u8g.setRGB(255,255,255);
    u8g.drawStr( 66, 0, "Color Page");
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT )
  {
    u8g.drawStr( 66, 0, "Gray Level");
    u8g.setColorIndex(1);
    u8g.drawBox(0, 4, 64, 32);    
    u8g.drawBox(70, 20, 4, 12);
    u8g.setColorIndex(2);
    u8g.drawBox(0+1*a, 4+1*a, 64-2*a, 32-2*a);
    u8g.drawBox(74, 20, 4, 12);
    u8g.setColorIndex(3);
    u8g.drawBox(0+2*a, 4+2*a, 64-4*a, 32-4*a);
    u8g.drawBox(78, 20, 4, 12);
  }
  else
  {
    u8g.drawStr( 0, 12, "setScale2x2");
    u8g.setScale2x2();
    u8g.drawStr( 0, 6+a, "setScale2x2");
    u8g.undoScale();
  }
}


uint8_t draw_state = 0; // AW - above water menu

void draw(void) {
  u8g_prepare();
  switch(draw_state >> 3) {
    //case 0: u8g_box_frame(draw_state&7); break;
    case 1: u8g_disc_circle(draw_state&7); break;
    case 2: u8g_r_frame(draw_state&7); break;
    case 3: u8g_string(draw_state&7); break;
    case 4: u8g_line(draw_state&7); break;
    case 5: u8g_triangle(draw_state&7); break;
    //case 6: u8g_ascii_1(); break;
    //case 7: u8g_ascii_2(); break;
    case 8: u8g_extra_page(draw_state&7); break;
   
  }
}


uint8_t draw_state2 = 5; // UW - underwater menu

  void draw2(void) {
  u8g_prepare();
  switch(draw_state2) {
    //case 0: u8g_box_frame(draw_state2&7); break;
    case 1: u8g_disc_circle(draw_state2&7); break; //set m value
    case 2: u8g_r_frame(draw_state2&7); break;     //m screen
    case 3: u8g_string(draw_state2&7); break;      //i screen
    case 4: u8g_line(draw_state2&7); break;        //r screen
    case 5: u8g_triangle(draw_state2&7); break;    //blank screen
  }
  }
uint8_t draw_state3 = 1; // UW - underwater menu

  
   void draw3(void) {
       u8g_prepare();
  u8g.drawStr( 6, 10, "Gray Level");
  delay(1000);
  
  
  }



void setup(void) {
  
 Serial.begin(9600);

  // Initialize ADXL345
  Serial.println("Initialize ADXL345");

  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }

  // Set tap detection on Z-Axis
  //accelerometer.setTapDetectionX(0);       // Don't check tap on X-Axis
  //accelerometer.setTapDetectionY(0);       // Don't check tap on Y-Axis
  accelerometer.setTapDetectionZ(1);       // Check tap on Z-Axis
  // or
  // accelerometer.setTapDetectionXYZ(1);  // Check tap on X,Y,Z-Axis

  accelerometer.setTapThreshold(2.5);      // Recommended 2.5 g
  accelerometer.setTapDuration(0.02);      // Recommended 0.02 s
  accelerometer.setDoubleTapLatency(0.10); // Recommended 0.10 s
  accelerometer.setDoubleTapWindow(0.30);  // Recommended 0.30 s

  // Select INT 1 for get activities
  accelerometer.useInterrupt(ADXL345_INT1);

  // Check settings
 // checkSetup();
  
  // flip screen, if required
  //u8g.setRot180();

  
  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);   
  

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


//////////////////////////////logo


  
}


void dht11_wrapper() {
  DHT11.isrCallback();
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

 
  
  
 
   
   u8g.firstPage();  
  do {
    draw2();
  } while( u8g.nextPage() );
  
  // increase the state
  if ( draw_state2 > 5 )
   draw_state2 = 1;
 
  
  

    // Read values for activities
  delay(50);
  Vector norm = accelerometer.readNormalize();
  // Read activities
  Activites activ = accelerometer.readActivites();

  if (activ.isDoubleTap)
  {
    //Serial.println("Double Tap Detected");
    draw_state++;
    u8g.sleepOff();
    
  } else
  if (activ.isTap)
  {
    //Serial.println("Tap Detected");
    draw_state2++;
    
  } 
  
  if(draw_state2 == 3){     //Temp, Humidity screen
    if(activ.isDoubleTap){
      counter ++;
      sleepDisplay();
      delay(5);
  
    }else if(activ.isTap){
      idhc();
      delay(250);
    }
  }
  
  if(draw_state2 == 4){     //counter for Turn On or Off display
    if(activ.isDoubleTap){
      u8g.undoRotation();
      counter3 ++;
      sleepDisplay2();
      delay(5);
  
    }
  }
  
  
  
  if(draw_state2 == 2){     //counter for mValue screen
    if(activ.isDoubleTap){
      draw_state2 = 1;
      mValue = mValue - 0.1;
     // delay(5);
      
    } else
  if(draw_state2 == 1){
    if(activ.isTap){
      draw_state2 ++;
      // delay(5);
    }
  } 
}
  
   if(draw_state2 == 1){
    if(activ.isDoubleTap){
      mValue = mValue + 0.1;
    }
   }
   
   
   if(mValue > 42.00){
     mValue = 40.00;
   }
   
 //Serial.println(counter3);
 // Serial.println(counter);
 // Serial.println(counter2);
  delay(2);
  
    //idhc();
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


void sleepDisplay2(){
  
  if(counter3 == 0){
    u8g.undoRotation();   
  } else
  if(counter3 == 1){
    u8g.setRot180();
  } 
  
  if(counter3 > 1){
    counter3 = 0;  
  } 
  
  delay(2);
  
  
}


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
    
    
    
    else if(sw_secs.elapsed() <10){
    
   // Serial.print(minuty);
   // Serial.print(":0");
 //   Serial.println(sw_secs.elapsed());
    
  
    }
  delay(250);
}



