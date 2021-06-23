#include <SoftwareServo.h> 
int potentiometer=A0;
int potval;
int curval;
int button1 = 13;
int button2 = 12;

SoftwareServo ESC;

void setup() {

  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(potentiometer, INPUT);
  ESC.attach(9);    
  Serial.begin(9600);  
  curval=0;
  ESC.setMinimumPulse(800);
  ESC.setMaximumPulse(2000);
}

void loop() {

//if(digitalRead(button2) == LOW){ 
  //curval = 0;
//}
//else if ( digitalRead(button1) == LOW){

  potval=analogRead(potentiometer);
  potval=map(potval,1023,741,0,180);
  
  while(curval<potval){
    potval=analogRead(potentiometer);
    potval=map(potval,1023,741,0,180);
    curval=curval+1;
    ESC.write(curval);
    SoftwareServo::refresh();
    Serial.println(curval);
    delay(30);}

  while(curval>potval){
    potval=analogRead(potentiometer);
    potval=map(potval,1023,741,0,180);
    curval=curval-1;
    ESC.write(curval);
    SoftwareServo::refresh();
    Serial.println(curval);
    delay(30);}


//}
    Serial.println(curval);
    ESC.write(curval);
    SoftwareServo::refresh();
}

