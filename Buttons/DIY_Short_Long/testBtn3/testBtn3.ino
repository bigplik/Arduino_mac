
byte range=0;
int count0;
int _count0;
int count;
int _count;

void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
pinMode(11,OUTPUT);
pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean button = digitalRead(2);

switch(range){
  case 0:
    if(!button){
      delay(20);
      count0++;
      if(count0>0)_count0 = count0;
    }
    else{
      _count = 0;
      count = 0;
      digitalWrite(12,0);
      digitalWrite(11,0);
      digitalWrite(13,0);
      if(_count0>0){
        delay(200);
        range = 1;
      }
    }
    break;
  case 1:
    if(!button){
      delay(200);
      range = 2;
    }
    else{
      _count = 0;
      count = 0;
      digitalWrite(12,1);
      digitalWrite(11,0);
      digitalWrite(13,0);
    }
    break;
  case 2:
    if(!button){
      digitalWrite(12,0);
      delay(20);
      count++;
      if(count>20){
        digitalWrite(11,0);
        digitalWrite(13,1);
        _count=0;
      }
      else{ _count = count;}
    }
    else if(button){
      count = 0;
      _count0 = 0;
      digitalWrite(11,1);
      digitalWrite(12,0);
      digitalWrite(13,0);
      if(_count>0 && _count<21){
        delay(200);
        range = 0;
      }
    }
    break;
}
}
