/*
 * WERSJA GRZEGORZ KUŚPIEL - WGK
 * 
 * progam ATTINY85 at 1MHz! (important with this chip)
 * otherwise it would be to fast or too slow
      *          __________
     PB5 A0 RES _|        |_ VCC
         D3 A3  _| ATTINY |_ A1  D2 SCL SCK
         D4 A2  _|   85   |_ PWM D1 MISO
            GND _|        |_ PWM D0 SDA MOSI
                 |________|
                      __________
      PB5        RES _|        |_ VCC
      PB3        CTR _| ATTINY |_ BatLEVEL        PB2
      PB4        N/C _|   85   |_ powerLED   PWM  PB1
                 GND _|        |_ LED             PB0
                      |________|
 */

//#define battery A1
const byte led = 0;         //A3 PB4
const byte powerLED = 1;   //D0
const byte BatLEVEL = A1;           //A2 PB3
byte CTR = PB3;
byte ADC2 = PB4;
float batCheck = 0;
byte pwm;
int change = 0;

//LOW BAT 450
//HIGH BAT 550

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(powerLED, OUTPUT);
  pinMode(BatLEVEL, INPUT);
  pinMode(CTR, INPUT_PULLUP);
  pinMode(ADC2, INPUT_PULLUP);

  analogWrite(powerLED, 0); //off driver

  
  for(int j=0; j<10 ; j++){
  batCheck += analogRead(BatLEVEL)*(4.98/1023.0);
  delay(10);
  }
  batCheck /=10;
     
    if(batCheck > 2.5){
       for(int a=0; a<3; a++){
        analogWrite(powerLED,50);
        delay(250);
        analogWrite(powerLED,0);
        delay(250);
       }
    }else if(batCheck < 2.51  && batCheck > 2.3){
       for(int b=0; b<2; b++){
        analogWrite(powerLED,50);
        delay(250);
        analogWrite(powerLED,0);
        delay(250);
       }
    }else if(batCheck < 2.31  && batCheck > 2.1){
       for(int c=0; c<1; c++){
        analogWrite(powerLED,50);
        delay(250);
        analogWrite(powerLED,0);
        delay(250);
       }
    }else{
        change = 4;
    }
    delay(1000);
}

void loop() {

float battery = analogRead(A1)*(4.98/1023.0);
if(battery < 2.00) change = 4;

switch (change) {
    case 0:
            if(digitalRead(CTR) == LOW){
                delay(200);
                change=1;
              }
            analogWrite(powerLED,0);
            break;
    case 1:
            if(digitalRead(CTR) == LOW){
                delay(200);
                change=2;
              }
            analogWrite(powerLED,85);
            break;
    case 2:
            if(digitalRead(CTR) == LOW){
                delay(200);
                change=3;
              }
            analogWrite(powerLED,160);
            break;
    case 3:
            if(digitalRead(CTR) == LOW){
                delay(200);
                change=0;
              }
            analogWrite(powerLED,255);
            break;
    case 4:
            for(int i=0;i<20;i++){
              digitalWrite(powerLED, !digitalRead(powerLED));
              delay(100);
            }
            analogWrite(powerLED,0);
            change = 4;
            break;
    case 5:
            //just stop
            break;
  }



}
