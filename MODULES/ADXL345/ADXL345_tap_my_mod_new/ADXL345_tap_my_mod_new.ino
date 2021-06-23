/*
    ADXL345 Triple Axis Accelerometer. Tap & Double Tap
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-akcelerometr-adxl345.html
    GIT: https://github.com/jarzebski/Arduino-ADXL345
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/


float m1;

float m;
int menu = 3;
int setdisplay;
int menu2;
int adj_m2;

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;
// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;
int addr2 = 1;
int val;
int adj_m;

#include <Wire.h>
#include <ADXL345.h>

ADXL345 accelerometer;

void setup(void) 
{
  Serial.begin(9600);
  
  pinMode(13,OUTPUT);

  // Initialize ADXL345
  Serial.println("Initialize ADXL345");

  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }

  // Set tap detection on Z-Axis
  accelerometer.setTapDetectionX(0);       // Don't check tap on X-Axis
  accelerometer.setTapDetectionY(0);       // Don't check tap on Y-Axis
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
  
  
  
  adj_m = EEPROM.read(addr);
  adj_m2 = EEPROM.read(addr2);
  delay(50);
  float m2 = adj_m2;
  float i = m2/100;
  m = adj_m + i;
  delay(50);
  m=m1;
  
  Serial.println(m2);
  Serial.println(i);
  Serial.println(adj_m);
  Serial.println(adj_m2);
  Serial.println(m);   
  delay(2000);
  
  
}

void checkSetup()
{
  Serial.print("Look tap on axis = "); 
  if (accelerometer.getTapDetectionX()) { Serial.print(" X "); }
  if (accelerometer.getTapDetectionY()) { Serial.print(" Y "); }
  if (accelerometer.getTapDetectionZ()) { Serial.print(" Z "); }
  Serial.println();

  Serial.print("Tap Threshold = "); Serial.println(accelerometer.getTapThreshold());
  Serial.print("Tap Duration = "); Serial.println(accelerometer.getTapDuration());
  Serial.print("Double Tap Latency = "); Serial.println(accelerometer.getDoubleTapLatency());
  Serial.print("Double Tap Window = "); Serial.println(accelerometer.getDoubleTapWindow());
}

void loop(void) 
{
  // Read values for activities
  delay(50);
  Vector norm = accelerometer.readNormalize();

  // Read activities
  Activites activ = accelerometer.readActivites();

  if (activ.isDoubleTap && menu == 1)  {
    Serial.println("Double Tap Detected");
    m1 = m + 0.1;
    
  }else  if (activ.isTap) {
    menu = menu + 1;
    
    Serial.println("Tap Detected");
    
  }



  if(menu > 3){  //zapętlaj menu przy pojedyńczym stuknięciu
    menu = 0;
    }
  
  
  if(menu == 0){      //wyłączanie wyświetlacza lub przejście dalej
    
    if(activ.isDoubleTap){
      
      Serial.println("Display OFF");
      //display off
      
    }
        
  }else if(menu == 1){
    
    if(activ.isDoubleTap){
      //m = m + 0.1;
      
    }
    
  }
 else if(menu == 2){
    
    if(activ.isDoubleTap){
      EEPROM.write(addr, adj_m);
      EEPROM.write(addr2, adj_m2);
      
    }

    
  }
  
  
  
  
  if(m > 42.0){   //zapętlanie wartości m w zakresie 40.0 - 42.0
    
    m = 40.0;
  }else{
    
    m = 41.7;
  }
  
  
 
  
  
  switch (menu) {
  case 0:    // turn off or leave on display
    Serial.println("display off");
    delay(500);
    break;
  case 1:
    //Serial.println("Set M_Value");
    Serial.println(m1);
    Serial.println("To set M_Value Double Tap else SingleTap");
    delay(500);
    break;        
  case 2:   
    Serial.println("To save new M_Value Double Tap else SingleTap");
    delay(500);
    break;
  case 3:   
    Serial.println("Basic Information");
    delay(500);
    break;
  } 
  delay(1);        // 
  
 // m_settings();
  
}



void m_settings(){
  
  if(m >= 40.00 && m < 41.00){
    
    adj_m = 40;
    
  }else if(m >= 41.00 && m < 42.00){
    
    adj_m = 41; 
    
  }else if(m > 41.90){
    
    adj_m = 42;
    
  }
  
   adj_m2 = (m - adj_m)*100;
   
}
  
  
  

