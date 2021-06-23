/*
      *          __________
     PB5 A0 RES _|        |_ VCC
         D3 A3  _| ATTINY |_ A1  D2 SCL SCK
         D4 A2  _|   85   |_ PWM D1 MISO
            GND _|        |_ PWM D0 SDA MOSI
                 |________|
                      __________
    PB5          RES _|        |_ VCC
    PB4 A3       POT _| ATTINY |_ LED    A1       PB2
    PB3 A2 BAT LEVEL _|   85   |_ N/C
                 GND _|        |_ PWM LED DRIVER  PB0
                      |________|
 */

//#define battery A1
int led = A1;         //A3 PB4
int led_Driver = 0;   //D0 PB0  
int BatLEVEL = A2;    //A2 PB3
int POT = A3;         //A1 PB2
float voltage, batCheck;
int pwm;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(led_Driver, OUTPUT);
  pinMode(BatLEVEL, INPUT);
  pinMode(POT, INPUT);

  analogWrite(led_Driver, 0); //off driver

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
    //delay(5000);
}

void loop() {
  POT = analogRead(A3);
  
  pwm = map(POT,1023,0,0,255);
  analogWrite(led_Driver,pwm);
}
