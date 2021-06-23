#define BTN_PRESSED digitalRead(PB3)==LOW
//#define LEDS_OFF    digitalWrite(1,0),digitalWrite(0,0)
#define EMPTY_BATTERY  batteryLevel<431
#define FULL_BATTERY   batteryLevel>510
#define HALF_BATTERY   batteryLevel<511 && batteryLevel>470
#define LOW_BATTERY    batteryLevel>430 && batteryLevel<471
//#define TOGGLE_LED   digitalWrite(0, !digitalRead(0));

byte tryb = 0;
int batteryLevel = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT_PULLUP);

  //battery();

//if(EMPTY_BATTERY) tryb = 3;
//
//else if(FULL_BATTERY){
//  for(int i=0;i<3;i++){
//    digitalWrite(0,1);
//    delay(200);
//    digitalWrite(0,0);
//    delay(200);
//  }
//}
//
//else if(HALF_BATTERY){
//  for(int b=0;b<2;b++){
//    digitalWrite(0,1);
//    delay(200);
//    digitalWrite(0,0);
//    delay(200);
//  }
//}
//
//else if(LOW_BATTERY){
//  for(int c=0;c<1;c++){
//    digitalWrite(0,1);
//    delay(200);
//    digitalWrite(0,0);
//    delay(200);
//  }
//}


}

void loop() {
  // put your main code here, to run repeatedly:

//  if(BTN_PRESSED){
//    delay(500);
//    tryb++;
//    if(tryb>2) tryb=0;
//  }
////  else if(BTN_PRESSED & BATTERY){
////    delay(500);
////    tryb=3;
////  }
//  else{
//    switch(tryb){
//      case 0:
//        if(EMPTY_BATTERY){
//          tryb=3;
//        }
//        else{
//          analogWrite(1,0);
//        }
//        break;
//      case 1:
//        if(EMPTY_BATTERY){
//          tryb=3;
//        }
//        else{
//          analogWrite(1,25);
//        }
//        break;
//      case 2:
//        if(LOW_BATTERY){
//          delay(1000);
//          tryb=1;
//        }
//        else{
//          analogWrite(1,255);
//        }
//        break;
//      case 3:
//        for(int a=0;a<10;a++){
//          //digitalWrite(0,1);
//          analogWrite(1,25);
//          delay(500);
//          //digitalWrite(0,0);
//          analogWrite(1,0);
//          delay(500); 
//        }
//        tryb=4;
//        break;
//      case 4:
//        digitalWrite(1,0);
//        break;
//    }
//  }
}
