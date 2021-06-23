/* This shield has a Joystic on Pin AO, it provide follwing reads:
LEFT - 0
RIGHT - 506
UP - 741
DOWN - 329
PUSH - 142, 143
NOTHING - 1023
   it can be used for menu purposes to build pin managment shield
*/

#include <LCD5110_Graph.h>

LCD5110 myGLCD(2,3,4,6,5); //Use this line with the shield

int daneJoystic = 0;
int ekran = 0;
int analogReads[] = {A1,A2,A3,A4,A5};

boolean horizontalChange = true;
boolean verticalChange = true;

byte i[] = {8,9,10,11,12,13};
byte z = 0;
byte x = 0;
boolean power = 0;

extern uint8_t SmallFont[];

void setup() {
  // put your setup code here, to run once:
  myGLCD.InitLCD(60);
  myGLCD.setFont(SmallFont);
    randomSeed(analogRead(7));
    myGLCD.print("START",CENTER,20);
  myGLCD.update();
  delay(2000);
  }

void loop() {

  int sens = analogRead(A0);
  // put your main code here, to run repeatedly:
  myGLCD.clrScr();
  //myGLCD.print("LCD5110_Graph", CENTER, 0);
  
  //horizontal change
  if(sens == 0){
    ekran++;
  }
  if(sens == 506){
    ekran--;
  }
  if(ekran > 1) ekran = 0;
  else if(ekran < 0) ekran = 1;
 
  myGLCD.printNumI(sens, LEFT, 0);
  myGLCD.printNumI(ekran,LEFT, 40);


 
  //vertical change
  if(ekran == 0){
    if(sens == 143 || sens == 142) power=!power;
    else if(sens == 741) x++;
    else if(sens == 329) x--;
    if(x > 5) x = 0;
    else if(x < 0) x = 5;
  }
  else if(ekran == 1){
    if(sens == 741) z++;
    else if(sens == 329) z--;
    if(z > 4) z=0;
    else if(z < 0) z=4;
  }
  //saving
  //if(A0 == 142 || A0 == 143) save();
  
  switch (ekran){
    case 0:
       myGLCD.print("DIGITAL PIN",CENTER,10);
       myGLCD.print("OUTPUT MODE",CENTER,10);
       pinMode(i[x],OUTPUT); myGLCD.printNumI(i[x],CENTER,30);
       myGLCD.print("OUI",RIGHT,30);
       switch (power){
           case 0:
             digitalWrite(i[x],0); myGLCD.print("LOW",CENTER,40);
             break;
           case 1:
             digitalWrite(i[x],1); myGLCD.print("HIGH",CENTER,40);
             break;     
       }
      break;
    case 1:
       pinMode(i[x],INPUT); myGLCD.print("ANALOG PIN",CENTER,10);
       myGLCD.print("INPUT",CENTER,20);
       int temSens = analogRead(analogReads[z]);
       myGLCD.printNumI(z+1,RIGHT,30);
       myGLCD.printNumI(temSens,RIGHT,40);
      break;    
  }

  /*
  myGLCD.printNumI(a0,LEFT,12);
  myGLCD.printNumI(a1,LEFT,19);
  myGLCD.printNumI(a2,LEFT,26);
  myGLCD.printNumI(a3,LEFT,38);
  myGLCD.printNumI(a4,CENTER,0);
  myGLCD.printNumI(a5,CENTER,12);
  myGLCD.printNumI(a6,CENTER,19);
  myGLCD.printNumI(a7,CENTER,26);
  myGLCD.printNumI(a8,CENTER,38);
  myGLCD.printNumI(a9,RIGHT,0);
  myGLCD.printNumI(a10,RIGHT,12);
  myGLCD.printNumI(a11,RIGHT,19);
  myGLCD.printNumI(a12,RIGHT,26);
  myGLCD.printNumI(a13h,RIGHT,38);
  */

  //myGLCD.drawRect(28, 18, 56, 28);
  //myGLCD.drawLine(0,30,30,30);
  myGLCD.update();
  delay(250);

}

void save(){}
