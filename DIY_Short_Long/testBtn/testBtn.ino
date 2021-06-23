
boolean range=0;
int count;

void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
pinMode(10,OUTPUT);
pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean button = digitalRead(2);

  //pressed
  if(button==LOW){ 
    digitalWrite(10,1);
    digitalWrite(12,0);  
    delay(20);
    count++;
    if(count>5){
    digitalWrite(13,1);
    count=100;
    }
    else if(count<6){
      digitalWrite(13,0);
      delay(200);
      range =! range;
    }
  }
  //not pressed
  else if(button==HIGH){
      count=0;
//      digitalWrite(10,0);
//      digitalWrite(12,1);
      digitalWrite(13,0);
  }




switch(range){
  case 0:
    digitalWrite(12,1);
    digitalWrite(10,0);
    break;
  case 1:
    digitalWrite(12,0);
    digitalWrite(10,1);
    break;
}
}
