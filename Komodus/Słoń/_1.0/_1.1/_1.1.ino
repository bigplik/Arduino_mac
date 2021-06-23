void setup() {
  // put your setup code here, to run once:
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(4) == LOW & digitalRead(5) == LOW){
  
}
else if(digitalRead(4) == LOW){
digitalWrite(8,0);
digitalWrite(7,1);
digitalWrite(13,1);
analogWrite(3,255);
}
else if
(digitalRead(5) == LOW){
digitalWrite(7,0);
digitalWrite(8,1);
digitalWrite(13,0);
analogWrite(3,255);
}
else{
  digitalWrite(13,0);
  digitalWrite(7,0); digitalWrite(8,0);
  analogWrite(3,0);
}
}
