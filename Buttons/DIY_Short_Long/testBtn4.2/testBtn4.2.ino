
#define SP _count>0 && _count < 21  //short Press
#define LP count>20                //long Press
#define CTR   digitalRead(2)==LOW
#define EB    analogRead(A1)<431
#define FB    analogRead(A1)>540
#define HB    analogRead(A1)<541 && analogRead(A1)>450
#define LB    analogRead(A1)>430 && analogRead(A1)<451

byte range=0;
int count0;
int _count0;
int count;
int _count;
//boolean button = digitalRead(2);
byte tryb   = 0;
boolean TLF = false; //tryb lock full
boolean TLH = false; //tryb lock half
//boolean TLL = false; //tryb lock low
int battery = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(1,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

switch(range){
  case 0:
    if(CTR){
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(!CTR){
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
    if(CTR){
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(!CTR){
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
    if(CTR){
      digitalWrite(3,0);
      delay(20);
      count++;
      longPress();
      shortClick();

    }
    else if(!CTR){
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
