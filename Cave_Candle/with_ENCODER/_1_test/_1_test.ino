//location - Cave_Lamp > with_ENCODER

int count=0;
byte range=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  pinMode(4,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), button, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), zlicz, FALLING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(range){
    case 0:
      //Serial.println("0");
      analogWrite(10,count);
      digitalWrite(13,0);
      break;
    case 1:
      //Serial.println("1");
      analogWrite(10,0);
      digitalWrite(13,1);
      break;
    case 2:
      //Serial.println("2");
      digitalWrite(13,0);
      analogWrite(10,0);
      break;
  }
  delay(1);
}

void zlicz() {
  if(digitalRead(4))
  count=count+10;
  else count=count-10;
  if(count<0) count = 0;
  else if(count>255) count = 255;
  Serial.println(count);
}

void button() {
  range++;
  if(range>2) range = 0;
}

