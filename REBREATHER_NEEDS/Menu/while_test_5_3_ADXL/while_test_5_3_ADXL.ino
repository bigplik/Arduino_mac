#include <Wire.h>
#include <ADXL345.h>

int counter = 0;
int counter2 = 0;
int pin = 2;
int pin2 = 3;
int buttonState = 0;
int buttonState2 = 0;
int oxygen = 0;
int altitude = 0;
int altset = 0;
int altset2 = 0;

ADXL345 accelerometer;

void setup() {
  
  Serial.begin(9600);
  pinMode(pin, INPUT);
  pinMode(pin2, INPUT);
  
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






  // put your setup code here, to run once:
  
  while(counter >= 0 & counter <4){
    Serial.print("For Calibration Settings Double Tap, else Tap");
    Serial.println(counter);
  //  buttonState = digitalRead(pin);
    //  buttonState2 = digitalRead(pin2);
         delay(50);
  Vector norm = accelerometer.readNormalize();

  // Read activities
  Activites activ = accelerometer.readActivites(); 
        
           if(activ.isTap){
    Serial.println("Skip");
    delay(2000);

  oxygen = 5;
altitude = 5;
altset = 5;
     counter = counter +5;
    //oxygen calibration, this partion of the code
    //should 'calibrate' O2 sensors, by adjusting them to
    //eg. 0.99 PPO2 at 1.ATA at attitiude sea level (1025,0mbar)
    //by creating 'fudge factor' for multiplying raw PPO2
    //readings from the sensors by this factor
    //this value could be saved in EEPROM and by used for
    //air calibration for everytime device is started    
    }
        if(activ.isDoubleTap){
     Serial.println("Calibration Settings");
     delay(2000);
     counter = counter +5;
     oxygen = 2;
     }
     
    
    //this is the section for air calibration code,
    //which would be used everytime
    //'fudge factor' from EEPROM could be read evertime
    //device is started, except the first time when nothig
    //is stored in EEPROM - in this case static function
    //could be used and != function, which compare if 'fudge
    //factor' is different than 1, what could be as a static value
    //if 'fudge factor' read from EEPROM is different than 1
    //then should be used for PPO2 calculation instead of 1 static
    //value
    }
    
  delay(500);

  
    while(oxygen >= 0 && oxygen <=4){      //kalibracja tlenowa
      Serial.println("For Oxygen Calibration - Double Tap");
      Serial.println("to skip - Tap");
    
    delay(50);
    Vector norm = accelerometer.readNormalize();
  // Read activities
    Activites activ = accelerometer.readActivites(); 
      
      if(activ.isTap){
          Serial.println("Skipping");
          delay(2000);
          oxygen = 5;
      }
        
      if(activ.isDoubleTap){
          Serial.println("Oxygen Calibration Process");
          delay(2500);
          oxygen = 5;
          altitude = 0;  
      }
      
    }    
      
    while(altitude >= 0 && altitude <=4){      //kalibracja wysokości
      Serial.println("For Altitude Settings - Double Tap");
      Serial.println("to skip - Tap");
    
    delay(50);
    Vector norm = accelerometer.readNormalize();
  // Read activities
    Activites activ = accelerometer.readActivites(); 
      
      if(activ.isTap){
          Serial.println("Skipping");
          delay(2000);
          altitude = 5;
          altset = 5;
      }
        
      if(activ.isDoubleTap){
          Serial.println("Altitude Settings Process");
          delay(2500);

          oxygen = 5;   
          altset = 2;
      }
  
    }
    
    
  while(altset >=0 && altset <=4){   //przedziały wysokości
    delay(50);
    Vector norm = accelerometer.readNormalize();
  // Read activities
    Activites activ = accelerometer.readActivites();
    wysok();
    Serial.println(altset2);
    
    if(activ.isTap){
      altset2 = altset2 + 1;

    }
        
      if(activ.isDoubleTap){
          altset = 5;
        }
      }




  while(counter == 5){
  Serial.println("Przeszło");
  delay(2000);
  counter = 0;
  counter2 = 0;
  }
  
  pinMode(13, OUTPUT);
  
}

void wysok(){
  
           switch(altset2){
                 case 0:
                     Serial.println("0-100m");
                     break;
                 case 1:
                     Serial.println("100-200m");
                     break;
                 case 2:
                     Serial.println("200-300m");
                     break;
         }
         
        if(altset2 > 2){
        altset2 = 0;
        }
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



void loop() {
  
    // Read values for activities
  delay(50);
  Vector norm = accelerometer.readNormalize();

  // Read activities
  Activites activ = accelerometer.readActivites();

 
  
  //buttonState = digitalRead(pin);
    //buttonState2 = digitalRead(pin2);

    
static int counter = 0;
static int counter2 = 0;

    
    
   if(activ.isTap){
    counter2 = counter2 +1;
   //     delay(1);

    }
        if(activ.isDoubleTap){
     
    counter = counter + 1;
    counter2 = counter2 - 1;
    //delay(1);
    }
  
  /*
  if(millis()>3000){
  delay(2000);
  if(buttonState == HIGH){
    
    counter2 = counter2 +10;
    
  }
  

}
  */ 
  
  Serial.print("nie dupa");
  Serial.println(counter);
    Serial.println(counter2);

  delay(500);

  


}
