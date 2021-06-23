


boolean counter = 0;
boolean counter2 = 0;
boolean counter3 = 0;

float PPO2;
float mValue = 41.6;

#include <Wire.h>
#include <ADXL345.h>


ADXL345 accelerometer;


#include "U8glib.h"


U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

void u8g_prepare(void) {
  //u8g.setFont(u8g_font_osb21);
  //u8g.setFont(u8g_font_fub20);
  u8g.setFont(u8g_font_profont17);//10-17
  //u8g.setFont(u8g_font_unifont);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}
/*
void u8g_box_frame(uint8_t a) {
    u8g.drawStr(12,23, "S-");//1-szer ,2-wysokosc
  //u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos( 51, 23); //1st - 1-szer, 2-wysokosc
  u8g.print(mValue);
  //u8g.setPrintPos( 70, 4); //2nd
  //u8g.print(PPO2);
  //u8g.setPrintPos( 2, 34); //3rd
  //u8g.print(PPO2);
  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  u8g.drawRFrame(7, 16,120,40, a+1); //1-szer, 2wys, 3szer, 4-wysokosc famki
  //u8g.drawRBox(50, 10,25,40, a+1);
}
*/
void u8g_disc_circle(uint8_t a) {
  u8g.drawStr(12,23, "M-");//1-szer ,2-wysokosc
  //u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos( 51, 23); //1st - 1-szer, 2-wysokosc
  u8g.print(mValue);
  //u8g.setPrintPos( 70, 4); //2nd
  //u8g.print(PPO2);
  //u8g.setPrintPos( 2, 34); //3rd
  //u8g.print(PPO2);
  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  u8g.drawRFrame(7, 16,120,40, a+1); //1-szer, 2wys, 3szer, 4-wysokosc famki
  //u8g.drawRBox(50, 10,25,40, a+1);
}

void u8g_r_frame(uint8_t a) {
  u8g.drawStr(90,33, "M");//1-szer ,2-wysokosc
  u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
  u8g.print(PPO2);
  u8g.setPrintPos( 70, 4); //2nd
  u8g.print(PPO2);
  u8g.setPrintPos( 2, 34); //3rd
  u8g.print(PPO2);
  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
  //u8g.drawRBox(50, 10,25,40, a+1);
}

void u8g_string(uint8_t a) {
 u8g.drawStr(92,33, "D");//1-szer ,2-wysokosc
  u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
  u8g.print(PPO2);
  u8g.setPrintPos( 70, 4); //2nd
  u8g.print(PPO2);
  u8g.setPrintPos( 2, 34); //3rd
  u8g.print(PPO2);
  
  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
  //u8g.drawRBox(50, 10,25,40, a+1);
}

void u8g_line(uint8_t a) {
  u8g.drawStr(92,33, "R");//1-szer ,2-wysokosc
  u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
  u8g.print(PPO2);
  u8g.setPrintPos( 70, 4); //2nd
  u8g.print(PPO2);
  u8g.setPrintPos( 2, 34); //3rd
  u8g.print(PPO2);
  
  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
  //u8g.drawRBox(50, 10,25,40, a+1);
}

void u8g_triangle(uint8_t a) {
   u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
  u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
  u8g.print(PPO2);
  u8g.setPrintPos( 70, 4); //2nd
  u8g.print(PPO2);
  u8g.setPrintPos( 2, 34); //3rd
  u8g.print(PPO2);
  
  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
  //u8g.drawRBox(50, 10,25,40, a+1);
}
/*
void u8g_ascii_1() {
   u8g.drawStr(92,33, " ");//1-szer ,2-wysokosc
  u8g.setPrintPos( 2, 4); //1st - 1-szer, 2-wysokosc
  u8g.print(PPO2);
  u8g.setPrintPos( 70, 4); //2nd
  u8g.print(PPO2);
  u8g.setPrintPos( 2, 34); //3rd
  u8g.print(PPO2);
  
  //u8g.drawStr( 0, 0, "drawRFrame/Box");
  u8g.drawRFrame(82, 30,40,30, a+1); //1-ys, 2-, 3szer, 4-wysokosc famki
  //u8g.drawRBox(50, 10,25,40, a+1);
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
    // draw background (area is 128x128) 
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
  

}


uint8_t draw_state = 0;

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


uint8_t draw_state2 = 5;

  void draw2(void) {
  u8g_prepare();
  switch(draw_state2) {
    //case 0: u8g_box_frame(draw_state2&7); break;
    case 1: u8g_disc_circle(draw_state2&7); break; //set m value
    case 2: u8g_r_frame(draw_state2&7); break;     //m screen
    case 3: u8g_string(draw_state2&7); break;      //d screen
    case 4: u8g_line(draw_state2&7); break;        //r screen
    case 5: u8g_triangle(draw_state2&7); break;    //blank screen
  }
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
  checkSetup();
  
  // flip screen, if required
  //u8g.setRot180();

  
  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);   
}

void loop(void) {
  
    int sensorValue = analogRead(A0);
  PPO2 = sensorValue * (5.0/1023.0);
 
  
  
  
  if(PPO2 > 0.25){
  // picture loop  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // increase the state
  if ( draw_state >= 8 )
   draw_state = 0;

 } else
 if (PPO2 <= 0.25){
   
   u8g.firstPage();  
  do {
    draw2();
  } while( u8g.nextPage() );
  
  // increase the state
  if ( draw_state2 > 5 )
   draw_state2 = 2;
 }
  
  

    // Read values for activities
  delay(50);
  Vector norm = accelerometer.readNormalize();
  // Read activities
  Activites activ = accelerometer.readActivites();

  if (activ.isDoubleTap)
  {
    Serial.println("Double Tap Detected");
    draw_state++;
    u8g.sleepOff();
    
  } else
  if (activ.isTap)
  {
    Serial.println("Tap Detected");
    draw_state2++;
    
  } 
  
  if(draw_state2 == 3){     //counter for Turn On or Off display
    if(activ.isDoubleTap){
      counter ++;
      sleepDisplay();
      delay(5);
  
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
   
 Serial.println(counter3);
 // Serial.println(counter);
 // Serial.println(counter2);
  delay(2);

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
  //Serial.print("Double Tap Latency = "); Serial.println(accelerometer.getDoubleTapLatency());
  //Serial.print("Double Tap Window = "); Serial.println(accelerometer.getDoubleTapWindow());
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





