

void setup() {
  // put your setup code here, to run once:
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
digitalWrite(13,0);
digitalWrite(12,0);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(2) == 0) digitalWrite(13,1);
else if(digitalRead(3) == 0) digitalWrite(12,1);
else{
  digitalWrite(12,0);
  digitalWrite(13,0);
}
delay(20);
}
