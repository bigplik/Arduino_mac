
byte mode = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(digitalRead(2) == LOW){
  mode++;
  delay(500);
  if(mode > 3) mode = 0;
 }

  switch (mode) {
    case 0:
      analogWrite(0,0);
      analogWrite(1,0);
      break;
    case 1:
      analogWrite(0,38);
      analogWrite(1,38);
      break;
    case 2:
      analogWrite(0,117);
      analogWrite(1,117);
      break;
    case 3:
      analogWrite(0,255);
      analogWrite(1,255);
      break;
  }
}
