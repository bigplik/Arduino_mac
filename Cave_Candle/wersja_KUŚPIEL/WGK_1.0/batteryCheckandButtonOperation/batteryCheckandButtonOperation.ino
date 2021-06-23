/*
 * This sketch is for battery check and
 * drop power level when Voltage Drops
 * 
 * Also is possible to turn full power for LED
 * unit button is pressed (!button), and when
 * relased, power of LED is come back to the power
 * set in porticular case value eg.case2 is
 * analogWrite(LED,200);
 */
#define SP _count>0 && _count < 21  //short Press
#define LP count>20                //long Press
#define CTR   digitalRead(PB3)==LOW
#define EB    analogRead(A1)<431
#define FB    analogRead(A1)>540
#define HB    analogRead(A1)<541 && analogRead(A1)>450
#define LB    analogRead(A1)>430 && analogRead(A1)<451

byte range=0;
int count0;
int _count0;
int count;
int _count;
boolean button = digitalRead(2);
byte tryb   = 0;
boolean TLF = false; //tryb lock full
boolean TLH = false; //tryb lock half
//boolean TLL = false; //tryb lock low
int battery = 0;

void setup() {
  // put your setup code here, to run once:
  
//pinMode(13,OUTPUT);
//pinMode(12,OUTPUT);
//pinMode(11,OUTPUT);
//pinMode(2,INPUT_PULLUP);
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT_PULLUP);
  //timer.time(5000);
  delay(200);
//    for(int i=0;i<10;i++){
//      battery += analogRead(A1);
//    }
//    battery /=10;

  if(EB){
    for(byte e=0;e<20;e++){
    digitalWrite(0,1);
    delay(20);
    digitalWrite(0,0);
    delay(20);
    //tryb = 4;
    }
  }
//
else if(FB){
  for(byte i=0;i<3;i++){
    digitalWrite(0,1);
    delay(200);
    digitalWrite(0,0);
    delay(200);
  }
}

else 
if(HB){
  for(byte b=0;b<2;b++){
    digitalWrite(0,1);
    delay(200);
    digitalWrite(0,0);
    delay(200);
  }
}

else if(LB){
  for(byte c=0;c<1;c++){
    digitalWrite(0,1);
    delay(200);
    digitalWrite(0,0);
    delay(200);
  }
}

}

void loop() {
  // put your main code here, to run repeatedly:
  

switch(tryb){
  case 0:
    case0();
    break;
  case 1:
    if(EB){
          delay(2000),tryb=0;
    }
    else{
         if(!button && !TLH){
           case1();
         }
         else if(!button && TLH){
           delay(500),tryb=0;
         }
    }
    break;
  case 2:
    if(EB){
            delay(2000),tryb=1,TLH=true;
    }
    else{
         if(CTR && !TLF){
           case2();
         }
         else if(CTR && TLF){
           delay(500),tryb=0;
         }
    }
    break;
}
}
