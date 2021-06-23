void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(11,INPUT_PULLUP);
pinMode(12,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean a = digitalRead(11);
  boolean b = digitalRead(12);
Serial.println(analogRead(A0));
Serial.println(a);
Serial.println(b);
delay(500);
}
