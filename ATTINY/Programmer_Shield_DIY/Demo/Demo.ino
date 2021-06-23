/* 

                 __________
       PB5 A0 RES _|        |_ VCC
       PB3  3 A3  _| ATTINY |_ SCL  SCK A1  2 PB2
       PB4  4 A4  _|   85   |_ MISO PWM     1 PB1
             GND  _|        |_ MOSI PWM SDA 0 PB0
                   |________|


            Programmer_Shield_DIY Pinout
                     __________
                RES _|        |_ VCC
        GREEN_LED 3 _| ATTINY |_ 2 A1 N/C
          RED_LED 4 _|   85   |_ 1 BLUE_LED PWM
                GND _|        |_ 0    N/C   PWM
                     |________|
    
*/

void setup() {
  // put your setup code here, to run once:
pinMode(0,INPUT);
pinMode(1,OUTPUT);
pinMode(2,INPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
/*  
int value = analogRead(A1);
int pwm = map(value,0,1023,0,255);
analogWrite(1,pwm);
*/
int voltage = analogRead(A1);
if(voltage > 2.8){
  digitalWrite(3,1);
  digitalWrite(4,0);
  digitalWrite(1,0);
}
else if(voltage < 2.81 && voltage > 2.09){
  digitalWrite(1,1);
  digitalWrite(3,0);
  digitalWrite(4,0); 
}
else{
  digitalWrite(4,1);
  digitalWrite(3,0);
  digitalWrite(1,0);
}
}

