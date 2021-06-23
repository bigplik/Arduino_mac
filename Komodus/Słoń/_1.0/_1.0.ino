
boolean downBTN=5;         //down ride button
boolean upBTN=4;           //up ride button
boolean downRelay = 7;  //down open gate relay
boolean upRelay = 8;    //up open gate relay

int pwm = 3;

void setup() {
  // put your setup code here, to run once:
pinMode(downBTN,INPUT_PULLUP);
pinMode(upBTN,INPUT_PULLUP);
pinMode(downRelay,OUTPUT);
pinMode(upRelay,OUTPUT);
digitalWrite(downRealy,0);
digitalWrite(upRealy,0);
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(downBTN) == 0 & digitalRead(upBTN) == 0){
    downBTN = 0; upBTN = 0;
  }
//digitalWrite(upRelay,0);
//delay(5);
//digitalWrite(downRelay,1);
//analogWrite(3,125);
//delay(2000);
//analogWrite(3,0);
//delay(5000);
//digitalWrite(downRelay,0);
//delay(5);
//digitalWrite(upRelay,1);
//analogWrite(3,125);
//delay(2000);
//analogWrite(3,0);

}
