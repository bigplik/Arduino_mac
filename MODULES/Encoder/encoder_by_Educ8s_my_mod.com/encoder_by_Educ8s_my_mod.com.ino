#include <ClickEncoder.h>
#include <TimerOne.h>
//#include <LCD5110_Graph.h>

/*
LCD5110 lcd(8,9,10,12,11);
extern unsigned char SmallFont[];
extern unsigned char TinyFont[];
*/

ClickEncoder *encoder;
int16_t last, value;

void timerIsr() {
  encoder->service();
}



void pwm(){
  
  if(value > 254 || value < -254){
    
    value = 0; 
    
  }
   
}

void setup() {
  
  Serial.begin(9600);
  //lcd.InitLCD();
  //lcd.setFont(TinyFont);
  Serial.print("Rotary Endcoder");
  Serial.println("DEMO");
  //lcd.update();
  delay(2000);
  //lcd.setFont(SmallFont);
  encoder = new ClickEncoder(A1, A0, A2);
  encoder->setAccelerationEnabled(false);
  encoder->setDoubleClickEnabled(true);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  last = -1;
  


}

void loop() {  
  
  pwm();
  int encoderValue;
  int encoderPosition;
  //lcd.setFont(SmallFont);
  char encoderValueArray[3]; 
  char encoderPositionArray[3];
  
  value += encoder->getValue();
  
  if (value/4 != last) {
    encoderValue = value/4;
    encoderPosition = encoderValue%20;
      
    last = encoderValue;
    
    //lcd.clrScr();
    Serial.print("Value: ");
    dtostrf(encoderValue, 3, 0, encoderValueArray);
    Serial.println(encoderValueArray);
    
    dtostrf(encoderPosition, 3, 0, encoderPositionArray);
    Serial.print("Position:");
    
    if(encoderPosition <0)
      encoderPosition = -encoderPosition;
    Serial.println(encoderPositionArray);
    Serial.println(value);

    //Serial.print("\n");
    //lcd.update();
  }
  
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    #define VERBOSECASE(label) case label:Serial.print("case");Serial.println(#label); break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed);
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
      VERBOSECASE(ClickEncoder::Clicked)
      case ClickEncoder::DoubleClicked:
          encoder->setDoubleClickEnabled(!encoder->getDoubleClickEnabled());
         // encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
        break;
    }
    
    if(b == ClickEncoder::Clicked){
    value = value+50;
    }
  } 

    //pwm();
    analogWrite(3, value);
    analogWrite(5, value);
    analogWrite(6, value);
    //analogWrite(9, value);
    //analogWrite(10, value);
    //analogWrite(12, value);
  
    //Serial.println(value);
    

  
}


