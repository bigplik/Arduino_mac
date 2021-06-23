
#define SP _count>0 && _count < 21  //short Press
#define LP count>20                //long Press
#define CTR   digitalRead(3)==LOW
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
boolean TLL = false; //tryb lock low
int battery = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(0,OUTPUT);
pinMode(1,OUTPUT);
pinMode(2,INPUT);
pinMode(3,INPUT_PULLUP);

delay(200);

    if(EB){
        for(byte e=0;e<20;e++){
        digitalWrite(0,1);
        delay(50);
        digitalWrite(0,0);
        delay(50);
        //tryb = 4;
        }
      }
    
    else if(FB){
      for(byte i=0;i<3;i++){
        digitalWrite(0,1);
        delay(500);
        digitalWrite(0,0);
        delay(250);
      }
    }
    
    else if(HB){
      for(byte b=0;b<2;b++){
        digitalWrite(0,1);
        delay(500);
        digitalWrite(0,0);
        delay(250);
      }
    }

    else if(LB){
      for(byte c=0;c<1;c++){
        digitalWrite(0,1);
        delay(500);
        digitalWrite(0,0);
        delay(250);
      }
    }

}

void loop() {
  // put your main code here, to run repeatedly:
if(EB){
  if(CTR && TLL){
    analogWrite(1,20);
    delay(2000);
    analogWrite(1,0);
    TLL=false;
  }
  else{
      TLL=true;
      analogWrite(1,0);
  }
}
else{
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
          analogWrite(1,0);
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
          analogWrite(1,20);
          if(SP){
            delay(200);
            _count=0;
            range = 2;
          }
        }
        break;
      case 2:
        if(CTR){
          delay(20);
          count++;
          longPress();
          shortClick();
    
        }
        else if(!CTR){
          count = 0;
          _count0 = 0;
          analogWrite(1,50);
          if(SP){
            delay(200);
            _count=0;
            range = 3;
          }
        }
        break;
      case 3:
        if(CTR){
          delay(20);
          count++;
          longPress();
          shortClick();
    
        }
        else if(!CTR){
          count = 0;
          _count0 = 0;
          analogWrite(1,100);
          if(SP){
            delay(200);
            _count=0;
            range = 0;
          }
        }
        break;
    }
}
}
