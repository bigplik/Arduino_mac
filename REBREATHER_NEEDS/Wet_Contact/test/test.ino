int LED = 13;
boolean LEDState = true;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int a = analogRead(A0);
Serial.println(a);
Serial.println(LEDState);
delay(500);
if(a > 0) LEDState =! LEDState;
digitalWrite(LED,LEDState);
}
