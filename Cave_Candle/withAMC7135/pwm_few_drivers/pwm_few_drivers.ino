/*
 * for AMC7135 LED driver
 * by PJW
 * 
 * testing pwm drving of two (or more)
 * connected AMC7135
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int range = map(analogRead(A0), 0, 1023, 0, 250);
if(range < 45) range = 0;
analogWrite(6,range);
Serial.println(range);
}
