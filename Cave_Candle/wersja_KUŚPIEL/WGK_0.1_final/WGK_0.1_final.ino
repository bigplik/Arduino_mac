/*
 * this version is compatibile with WGK_test3.1
 */

#define CTR   digitalRead(PB3)==LOW
#define EB    analogRead(A1)<431
#define FB    analogRead(A1)>540
#define HB    analogRead(A1)<541 && analogRead(A1)>450
#define LB    analogRead(A1)>430 && analogRead(A1)<451

//#include <Timers.h>

byte tryb   = 0;
boolean TLF = false; //tryb lock full
boolean TLH = false; //tryb lock half
//boolean TLL = false; //tryb lock low
int battery = 0;

//Timer timer;

void setup() {
  // put your setup code here, to run once:
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
    tryb = 4;
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
//
//  if(timer.available()){
//    for(int i=0;i<10;i++){
//      battery += analogRead(A1);
//    }
//    battery /=10;
//  }

  switch(tryb){
    //empty BATTERY
    case 0:     
          if(CTR){
            delay(500),tryb=1;
          }
          else{
            analogWrite(1,0);
          }
      break;
    //LOW LED
    case 1:
          if(EB){
            delay(2000),tryb=0;
          }
          else{
            if(CTR && !TLH){
              delay(500),tryb++;
            }
            else if(CTR && TLH){
              delay(500),tryb=0;
            }
            else{
              analogWrite(1,25);
            }
          }
      break;
    //MID LED
    case 2:
          if(EB){
            delay(2000),tryb=1,TLH=true;
          }
          else{
            if(CTR && !TLF){
              delay(500),tryb=3;
            }
            else if(CTR && TLF){
              delay(500),tryb=0;
            }
            else{
              analogWrite(1,100);
            }
          }

      break;
    //HIGH LED
    case 3:
          if(LB){
            delay(2000),tryb=2,TLF=true;
          }
          else{
            if(CTR)delay(500),tryb=0;
            else{
              analogWrite(1,175);//this pwm gives about 2.5A at 8.4V
            }
          }
      break;
    case 4:

      break;
  }
}
