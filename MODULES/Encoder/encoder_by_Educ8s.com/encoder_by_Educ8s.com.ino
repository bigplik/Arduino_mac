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

void setup() {
  
  Serial.begin(9600);
  //lcd.InitLCD();
  //lcd.setFont(TinyFont);
  Serial.print("Rotary Endcoder");
  Serial.print("DEMO");
  //lcd.update();
  delay(2000);
  //lcd.setFont(SmallFont);
  encoder = new ClickEncoder(A1, A0, A2);
  encoder->setAccelerationEnabled(false);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  last = -1;
}

void loop() {  
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
    Serial.print(encoderValueArray);
    
    dtostrf(encoderPosition, 3, 0, encoderPositionArray);
    Serial.print("Position:");
    
    if(encoderPosition <0)
      encoderPosition = -encoderPosition;
    Serial.print(encoderPositionArray);

    //Serial.print("\n");
    //lcd.update();
  }
  
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
    #define VERBOSECASE(label) case label:Serial.print("case");Serial.print(#label); break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed);
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
      VERBOSECASE(ClickEncoder::Clicked)
      case ClickEncoder::DoubleClicked:
          encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
        break;
    }
  }    
}


