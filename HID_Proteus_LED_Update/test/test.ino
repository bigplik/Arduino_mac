float voltage;

void setup() {
  // put your setup code here, to run once:
//  pinMode(PB0,OUTPUT);
//  pinMode(PB1,OUTPUT);
//  pinMode(PB2,OUTPUT);
//  pinMode(PB3, INPUT);
  pinMode(PB4,OUTPUT);
//  digitalWrite(PB0,0);
//  digitalWrite(PB1,0);
//  digitalWrite(PB2,0);
//  delay(5);
//  while(analogRead(A3)*(5.0/1023.0)>1.4){
//    digitalWrite(PB4,0);
//  }
}

void loop() {
  //voltage = analogRead(PB3) * (4.98/1023.0);
  // put your main code here, to run repeatedly:
  if(analogRead(PB3) > 595){  //600 works from 6.3V up to 7.5V
  digitalWrite(PB4,0);
  //analogWrite(PB4,0);
  }
  else{
    digitalWrite(PB4,1);
    //analogWrite(PB4,200);
  }
}
