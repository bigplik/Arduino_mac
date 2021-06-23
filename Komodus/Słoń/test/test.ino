void setup() {
  // put your setup code here, to run once:
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
digitalWrite(7,0);
digitalWrite(8,0);
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(8,0);
delay(5);
digitalWrite(7,1);
analogWrite(3,125);
delay(2000);
analogWrite(3,0);
delay(5000);
digitalWrite(7,0);
delay(5);
digitalWrite(8,1);
analogWrite(3,125);
delay(2000);
analogWrite(3,0);

}
