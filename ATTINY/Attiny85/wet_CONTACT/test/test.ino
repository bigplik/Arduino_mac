void setup() {
  // put your setup code here, to run once:
pinMode(1,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
digitalWrite(4,HIGH);
//delay(2000);
_delay_ms(2000);
digitalWrite(4,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
int a = analogRead(A0);
if(a < 912) digitalWrite(1,HIGH);
else{ digitalWrite(1,LOW); }
}
