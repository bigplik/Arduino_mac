byte pwm;

void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:
  byte change = 0;
  switch (change) {
    case 0:
            if(analogRead(A0) < 200){
              pwm=0;
              analogWrite(PB3,1);
              delay(5000);
              change = 1;
            }
            else{
            pwm = map(analogRead(A1),1023,0,0,255);
            }
            analogWrite(PB0,pwm);
            break;
    case 1:
            analogWrite(PB3,0);
            break;
  }
}
