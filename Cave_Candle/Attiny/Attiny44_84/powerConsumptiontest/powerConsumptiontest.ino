void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(5,1);   //1.1A - 9.25W
//delay(2000);
digitalWrite(6,1); //0.4A - 3.35W
//delay(2000);
digitalWrite(7,1); //0.38A - 3.25W
//delay(2000);
digitalWrite(8,1); //0.76A - 6.35W
//delay(2000);
//digitalWrite(5,0);
//digitalWrite(6,0);
//digitalWrite(7,0);
//digitalWrite(8,0);
//delay(10000);
}
