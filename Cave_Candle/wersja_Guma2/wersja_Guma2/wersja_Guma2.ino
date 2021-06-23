 /*
                  __________
      PB5 A0 RES _|        |_ VCC
          LED A3 _| ATTINY |_ A1 POT          PB2
    BAT LEVEL A2 _|   85   |_ N/C
             GND _|        |_ PWM LED DRIVER  PB0
                  |________|
 */

 //uploaded on 23-07-2019

//#define battery A1
int led = A3;
int led_Driver = PB0;
int BatLEVEL = A2;
int POT = A1;
int capacity;
unsigned int batCount;
float voltage, batCheck;
int pwm;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(led_Driver, OUTPUT);
  pinMode(BatLEVEL, INPUT);
  pinMode(POT, INPUT);
  pinMode(PB0, OUTPUT); // N/C

  digitalWrite(led_Driver, 0);
  digitalWrite(PB0, 0);

  for(int j=0; j<10 ; j++){
  batCheck += analogRead(BatLEVEL) * (3.3/1023.0);
  delay(10);
  }
  batCheck /=10;
  voltage = batCheck;
   
    if(voltage > 2.65){
       for(int a=0; a<3; a++){
        digitalWrite(led,HIGH);
        delay(250);
        digitalWrite(led,LOW);
        delay(250);
       }
    }else if
    (voltage < 2.66 && voltage > 2.45){
       for(int b=0; b<2; b++){
        digitalWrite(led,HIGH);
        delay(250);
        digitalWrite(led,LOW);
        delay(250);
       }
    }else if
    (voltage < 2.46 && voltage > 2.20){
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
  batCount++;
  if(batCount>65000)calibration();
  
  if(capacity > 620){
  POT = analogRead(A1);
  pwm = map(POT,900,0,255,0);
  analogWrite(led_Driver,pwm); // wait for a second
  //delay(50);
  }else{
  //pwm = map(analogRead(A3),1023,0,0,0);
  analogWrite(led_Driver,0); // wait for a second
  }
}
