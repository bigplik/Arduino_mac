#define POT A0

void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT); pinMode(10,OUTPUT); pinMode(11,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(POT)>768) {
    analogWrite(9,100);
    analogWrite(10,0); analogWrite(11,0);
  }
  else if(analogRead(POT)>512 && analogRead(POT)<769) {
    analogWrite(11,100);
    analogWrite(9,0); analogWrite(10,0); 
  }
  else if(analogRead(POT) >256 && analogRead(POT) <513){
    analogWrite(10,100);
    analogWrite(9,0); analogWrite(11,0);
  }
  else{
    analogWrite(9,0); analogWrite(10,0); analogWrite(11,0);
  }
}
