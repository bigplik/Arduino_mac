#include <SoftwareServo.h> 
int potentiometer=A6;
int potval;
int curval;
int button1 = 6;
int button2 = 7;

SoftwareServo ESC;

void setup() {
  //pinMode(13,OUTPUT);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(potentiometer, INPUT);
  //pinMode(1,OUTPUT);
  ESC.attach(9);    
  //Serial.begin(9600);  
  curval=0;
  ESC.setMinimumPulse(800);
  ESC.setMaximumPulse(2000);
}

void loop() {

if(digitalRead(button2) == LOW){ 
  curval = 0;
}
else if ( digitalRead(button1) == LOW){

  potval=analogRead(potentiometer);
  potval=map(potval,504,1023,0,180);
  
  while(curval<potval){
    potval=analogRead(potentiometer);
    potval=map(potval,504,1023,0,180);
    curval=curval+1;
    ESC.write(curval);
    SoftwareServo::refresh();
    //Serial.println(curval);
    delay(30);}

  while(curval>potval){
    potval=analogRead(potentiometer);
    potval=map(potval,504,1023,0,180);
    curval=curval-1;
    ESC.write(curval);
    SoftwareServo::refresh();
    //Serial.println(curval);
    delay(30);}


  }
    //Serial.println(curval);
    ESC.write(curval);
    SoftwareServo::refresh();
    //digitalWrite(13,HIGH);
}

