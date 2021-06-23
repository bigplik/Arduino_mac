void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12, INPUT_PULLUP);
pinMode(17, INPUT_PULLUP );
pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int buton = digitalRead(12);
int buton2 = digitalRead(17);

if(buton != HIGH || buton2 != HIGH) { digitalWrite(6,HIGH); }
else { digitalWrite(6,LOW); }

Serial.println(buton);
Serial.println(buton2);
delay(500);
}
