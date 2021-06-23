int counter = 0;
int counter2 = 0;
int pin = 2;
int pin2 = 3;
int buttonState = 0;
int buttonState2 = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(pin, INPUT);
  pinMode(pin2, INPUT);
  
    


  // put your setup code here, to run once:
  
  while(counter >= 0 & counter <4){
    Serial.print("dupa");
    Serial.println(counter);
    buttonState = digitalRead(pin);
      buttonState2 = digitalRead(pin2);
        
        if(buttonState == HIGH){
     Serial.println("Air Calibration Only - Skip");
     delay(2000);
    counter = counter +5;
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
    
    
   if(buttonState2 == HIGH){
    Serial.println("Oxygen Calibration");
    delay(2000);
    counter = counter +5;
    //oxygen calibration, this partion of the code
    //should 'calibrate' O2 sensors, by adjusting them to
    //eg. 0.99 PPO2 at 1.ATA at attitiude sea level (1025,0mbar)
    //by creating 'fudge factor' for multiplying raw PPO2
    //readings from the sensors by this factor
    //this value could be saved in EEPROM and by used for
    //air calibration for everytime device is started    
    }
  delay(500);
  }
  
  while(counter == 5){
  Serial.println("Przeszło");
  delay(2000);
  counter = 0;
  }
  
  pinMode(13, OUTPUT);
  
}

void loop() {
  
  buttonState = digitalRead(pin);
    buttonState2 = digitalRead(pin2);

    

    if(buttonState == HIGH){
    counter = counter +1;
    //delay(1);
    }
    
    
   if(buttonState2 == HIGH){
    counter2 = counter2 +1;
   //     delay(1);

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
