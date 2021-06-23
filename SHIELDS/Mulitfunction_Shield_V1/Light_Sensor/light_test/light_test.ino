void setup() {
  // put your setup code here, to run once:
pinMode(5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int a=analogRead(A1);
  if(a > 400) digitalWrite(5,1);
  else{ 
    digitalWrite(5,0);
  }
}
