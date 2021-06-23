/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:

#define battery A1
int led = PB1;
boolean ledState = 0;
float voltage;
int pwm;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(PB0, OUTPUT);
  pinMode(PB3, INPUT);
  pinMode(A1, INPUT);
  analogWrite(PB0, 0);

  voltage = analogRead(A1) * (5.0/1023.0);
  delay(500);
    if(voltage > 4.0){
       for(int a=0; a<3; a++){
        digitalWrite(led,HIGH);
        delay(250);
        digitalWrite(led,LOW);
        delay(250);
       }
    }else if
    (voltage < 4.1 && voltage > 3.6){
       for(int b=0; b<2; b++){
        digitalWrite(led,HIGH);
        delay(250);
        digitalWrite(led,LOW);
        delay(250);
       }
    }else if
    (voltage < 3.7 && voltage > 3.3){
        digitalWrite(led,HIGH);
        delay(250);
        digitalWrite(led,LOW);
        delay(250);
    }else{
      for(int d=0; d<20; d++){
        digitalWrite(led,HIGH);
        delay(100);
        digitalWrite(led,LOW);
        delay(100);
      }
    }
}

// the loop routine runs over and over again forever:
void loop() {
  
  voltage = analogRead(A1) * (5.0/1023.0);
  if(voltage > 3.3){
  pwm = map(analogRead(PB3),1023,0,0,255);
  analogWrite(PB0,pwm); // wait for a second
  //delay(50);
  }else{
  pwm = map(analogRead(PB3),1023,0,0,0);
  analogWrite(PB0,pwm); // wait for a second
  }
}
