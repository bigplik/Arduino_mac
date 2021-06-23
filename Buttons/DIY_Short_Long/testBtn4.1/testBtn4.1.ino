
#define SP _count>0 && _count < 21  //short Press
#define LP count>20                //long Press

byte range=0;
int count0;
int _count0;
int count;
int _count;

void setup() {
  // put your setup code here, to run once:
pinMode(1,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean button = digitalRead(2);

switch(range){
  case 0:
    if(!button){
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(button){
      count = 0;
      _count0 = 0;
      digitalWrite(1,0);
      digitalWrite(3,0);
      digitalWrite(4,0);
      if(SP){
        delay(200);
        _count=0;
        range=1;
      }
    }
    break;
  case 1:
    if(!button){
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(button){
      count = 0;
      _count0 = 0;
      digitalWrite(1,0);
      digitalWrite(3,1);
      digitalWrite(4,0);
      if(SP){
        delay(200);
        _count=0;
        range = 2;
      }
    }
    break;
  case 2:
    if(!button){
      digitalWrite(3,0);
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(button){
      count = 0;
      _count0 = 0;
      digitalWrite(1,1);
      digitalWrite(3,0);
      digitalWrite(4,0);
      if(SP){
        delay(200);
        _count=0;
        range = 0;
      }
    }
    break;
}
}
